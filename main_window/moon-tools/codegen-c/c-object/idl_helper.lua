require("code_utils")

IdlHelper={};
IdlHelper.Class={};
IdlHelper.Type={};
IdlHelper.Var={};

IdlHelper.Class.GetAllBases=function(idl_class)	
	if not idl_class.bases then
		return
	end
	
	local all = {};
	
	local flag = false;
	for _,base in ipairs(idl_class.bases) do	
		local tmp = {openness="public"};		
		if base[1] == "private" or base[1] == "public" then
			tmp.openness=base[1];
			tmp.name = base[2];
		else
			tmp.name=base[1];
		end		
		flag = true;
		table.insert(all,tmp)		
	end
	
	return flag and all or nil;	
end

IdlHelper.Type.IsString=function(type)
    if type.is_string then
        return true;
    end
	return type.name == "string";
end

IdlHelper.Type.IsArray=function(type)
	if type.flags & 0x00000001 ~= 0 then
		return true,type.array_size;
	end
end

IdlHelper.Type.IsPointer=function(type)
	return type.flags & 0x00000002 ~= 0;
end

IdlHelper.Type.IsBasicType=function(type)
	for _,b in ipairs(basic_type_table) do	
		if type.name == b[1] then
			return true,b;
		end
	end	
end

IdlHelper.Type.GetPrintFormat=function(type)
    for _,b in ipairs(basic_type_table) do	
		if type.name == b[1] then
			return b[2];
		end
	end	
    return "%d";
end

IdlHelper.Var.IsOptional = function(var)
    if not var then return false end
    if not var.hint then return false end
    local ret = false;
    for_each_hint(var.hint,function(mem,str)    
        if mem:NextString() == "optional" then
            ret = true;
            return true;
        end    
    end);    
    return ret;
end