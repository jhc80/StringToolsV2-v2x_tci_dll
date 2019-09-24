require("common");

ASN1_Helper=class();

function ASN1_Helper:ctor(asn1_table)
    self.m_the_table = asn1_table;
    self.m_flat_map = nil;
    self.m_flat_map_const = nil;
end

local function is_only_id_obj(obj)    
    local c = 0;
    local find_id = false;
    
    for key,_ in pairs(obj) do    
        c = c + 1;        
        if key == "__id__" then
            find_id = true;
        end
    end    
    
    if find_id then
        return c == 1;
    end
end

local function is_container(obj)
    return obj.expr_type == ASN_CONSTR_SEQUENCE_OF 
        or obj.expr_type == ASN_CONSTR_SET_OF;
end
    
function ASN1_Helper:GenerateFlatHashTable()   
   local function generate_flat_hash_table_recursive(tab,map)
        for k,v in pairs(tab) do            
            if type(v) == "table" then
                if v.__id__ and not is_only_id_obj(v) then
                    map[v.__id__] = v;                
                end
                generate_flat_hash_table_recursive(v,map);
            end
        end
    end
    self.m_flat_map = {};    
    generate_flat_hash_table_recursive(self.m_the_table,self.m_flat_map);           

    self.m_flat_map_const = clone_table(self.m_flat_map);
end

function ASN1_Helper:FixLinks()
    local function fix_links_recursive(tab,map)
        for k,v in pairs(tab) do        
            if type(v) == "table" then            
                if is_only_id_obj(v) then
                    tab[k] = map[v.__id__];
                    if not tab[k] then
                        return;
                    end              
                elseif not fix_links_recursive(v,map) then
                    return;
                end
            end        
        end
        return true;
    end
    
    local ret = fix_links_recursive(self.m_the_table,self.m_flat_map);
    self:FixDuplicateTypeNames();
    return ret;
end

function ASN1_Helper:FindReferenceTypeByName(name)        
    local no_ref_find;
    
	for k,v in pairs(self.m_flat_map) do		
		if v.Identifier == name then		   
            if v.expr_type ~= A1TC_REFERENCE and v.expr_type ~= A1TC_EXPORTVAR then
                return v;
            end 
            
            if v.expr_type == A1TC_REFERENCE  and v.meta_type ~= AMT_INVALID then
                no_ref_find = v;
            end
        end
	end
    
    if not no_ref_find then return end
    if not no_ref_find.reference then return end
    if not no_ref_find.reference.components then return end
    return self:FindReferenceTypeByName(no_ref_find.reference.components.name);
end

--rebuld reference type, must be after fixLinks
function ASN1_Helper:RebuildReferenceTypes()	
	local function get_ref_name(v)
		if v.meta_type ~= AMT_TYPEREF then return end
		if v.expr_type ~= A1TC_REFERENCE then return end		
		if not v.reference then return end
		if not v.reference.components then return end
		return v.reference.components.name;
	end
	
	for k,v in pairs(self.m_flat_map) do	     
		if v.meta_type or v.expr_type then
			v.ref_type = {
				meta_type = v.meta_type,
				expr_type = v.expr_type,
				name = expr_type_to_string(v.expr_type),
                c_type = expr_type_to_c_type(v.expr_type),
                is_raw = true,
			};
		end
	
		local ref_name = get_ref_name(v);
		if ref_name then
			local ref_type = self:FindReferenceTypeByName(ref_name);
			if ref_type then
				v.ref_type={
					meta_type = ref_type.meta_type,
					expr_type = ref_type.expr_type,
					name = ref_type.Identifier,
                    c_type = expr_type_to_c_type(ref_type.expr_type),
				}
			else
				printnl("can not find reference type of "..ref_name);
				return false;
			end
		end
	end
	
	return true;
end

--must be after rebuild reference types
function ASN1_Helper:RebuildContainerEntryTypes()
   	for k,v in pairs(self.m_flat_map) do        
        if is_container(v) then
            if not v.members then return end
            if not v.members[1] then return end
            if not v.members[1].ref_type then return end
            v.entry_ref_type = v.members[1].ref_type;        
        end
    end    
    return true;
end

function ASN1_Helper:FindDuplicateTypeNames()
    local name_table={};
    local duplicate = {};

    for_each_module(self.m_the_table,function(module)
        if module.members then
            for _,m in ipairs(module.members) do	
                if m.meta_type == AMT_TYPE or m.meta_type == AMT_TYPEREF then
                    local id = m.Identifier;
                    if not name_table[id] then
                        name_table[id] = 1;
                    else
                        name_table[id] = name_table[id] + 1;
                        duplicate[id] = name_table[id];
                    end
                end
            end
        end
    end)
    return duplicate;
end

function ASN1_Helper:FindDuplicatePrefix(module,name)
    local id = module.__id__;
    module = self.m_flat_map_const[id];

    local prefix = module.ModuleName.."_";

    if not module.imports then
        return prefix;
    end

    for _,import in ipairs(module.imports) do
        if import.xp_members then
            for _,member in ipairs(import.xp_members) do                
                if member.Identifier == name then                                        
                    return import.fromModuleName.."_";
                end
            end
        end
    end

    return prefix;
end

function ASN1_Helper:FixDuplicateTypeNames()
    local dups = self:FindDuplicateTypeNames();   
    
    for k,v in pairs(self.m_flat_map) do
        local prefix = "";
    
        if v.Identifier and dups[v.Identifier] then
            if v.module then
                prefix = v.module.ModuleName.."_";
            end
    
            if v.reference and v.reference.module then
                prefix = self:FindDuplicatePrefix(v.reference.module,v.Identifier);
            end

            v.Identifier = prefix..v.Identifier;
        end

        if  v.reference 
            and v.reference.components 
            and v.reference.components.name 
        then
            if dups[v.reference.components.name] then
                if v.reference and v.reference.module then
                    prefix = self:FindDuplicatePrefix(v.reference.module,v.reference.components.name);
                end    
                v.reference.components.name = prefix..v.reference.components.name;
            end
        end
    end
end
