require("common");
require("print_buffer");

CBaseCodeGen = class();

function CBaseCodeGen:ctor(idl_class,code_switch)
    self.m_idl_class = idl_class;
    self.m_code_switch = nil;
    self.m_all_includes = {};
    
    self:SetCodeSwitch(code_switch);
end

function CBaseCodeGen:GetIncludes()
    return self.m_all_includes;
end

function CBaseCodeGen:SetCodeSwitch(code_switch)
    self.m_code_switch = code_switch;

    local all_bases = self:GetAllBases();
    if not all_bases then return end
    
    for _,base in ipairs(all_bases) do	
        table.insert(self.m_all_includes,string.lower(base.name));
    end    
end

function CBaseCodeGen:Code_ClassHeader(configs)
    local pb = PrintBuffer.new();
 
    if self.m_code_switch.hash_entry then
        pb:Print(string.format(
            "    C_HASH_ENTRY_DEFINE(%s);",
            c_class_name(self.m_idl_class.name)    
        ),true);
    end    
 
    if self.m_code_switch.linked_list then
        pb:Print(string.format(
            "    C_LINKED_LIST_DEFINE(%s);",
            c_class_name(self.m_idl_class.name)    
        ),true);
    end    
  
    self:for_each_base(function(base)    
        pb:Print(string.format(
            "    %s %s;",
            c_class_name(base.name),
            base_class_name(base.name)
        ),true);
    end);
  
    return pb:GetText();
end

function CBaseCodeGen:Code_InitBasic(configs)
    local pb = PrintBuffer.new();
    
    if self.m_code_switch.hash_entry then
        pb:Print("    C_HASH_ENTRY_CLEAR(self);",true);
    end
    
    if self.m_code_switch.linked_list then
        pb:Print("    C_LINKED_LIST_CLEAR(self);",true);
    end
    
    self:for_each_base(function(base)    
        pb:Print(string.format(
            "    %s(&self->%s);",
            function_name(base,"init_basic"),
            base_class_name(base.name)
        ),true);
    end);
    
    return pb:GetText();
end

function CBaseCodeGen:Code_Init(configs)
    local pb = PrintBuffer.new();    
    
    self:for_each_base(function(base)    
        pb:Print(string.format(
            "    %s(&self->%s);",
            function_name(base,"init"),
            base_class_name(base.name)
        ),true);
    end);
    
    return pb:GetText();
end

function CBaseCodeGen:Code_Destroy(configs)
    local pb = PrintBuffer.new();  
    self:for_each_base(function(base)    
        pb:Print(string.format(
            "    %s(&self->%s);",
            function_name(base,"destroy"),
            base_class_name(base.name)
        ),true);
    end);
    return pb:GetText();
end

function CBaseCodeGen:Code_Copy(configs)
    local pb = PrintBuffer.new();  
    self:for_each_base(function(base)    
        pb:Print(string.format(
            "    %s(&self->%s,&_p->%s);",
            function_name(base,"copy"),
            base_class_name(base.name),
            base_class_name(base.name)
        ),true);
    end);
    return pb:GetText();
end

function CBaseCodeGen:Code_Print(configs)
    local pb = PrintBuffer.new();  
    self:for_each_base(function(base)    
        pb:Print(string.format(
            "    %s(&self->%s,_buf);",
            function_name(base,"print"),
            base_class_name(base.name),
            base_class_name(base.name)
        ),true);
    end);
    return pb:GetText();
end

function CBaseCodeGen:Code_Includes(configs)
    local pb = PrintBuffer.new();
    for _,name in ipairs(self.m_all_includes) do
        pb:Print(string.format(
            "#include \"%s\""..EOL,
            name_to_include_file(name)
        ));
    end
    return pb:GetText();
end

function CBaseCodeGen:GetAllBases()	
    if not self.m_idl_class.bases then
        return
    end
 
	local all = {};
	local flag = false;

	for _,base in ipairs(self.m_idl_class.bases) do	
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

function CBaseCodeGen:for_each_base(callback)
    local bases = self:GetAllBases();
    if not bases then return end
    for _,base in ipairs(bases) do
        callback(base);
    end
end