require("common");
require("print_buffer");
require("code_utils");

CppBaseCodeGen = class();

function CppBaseCodeGen:ctor(idl_class,code_switch)
    self.m_idl_class = idl_class;
    self.m_code_switch = nil;
    self.m_all_includes = {};
    self.m_how_to_convert_file_name = to_lower_underline_case;
    self:SetCodeSwitch(code_switch);
end

function CppBaseCodeGen:GetIncludes()
    return self.m_all_includes;
end

function CppBaseCodeGen:SetCodeSwitch(code_switch)
    self.m_code_switch = code_switch;

    local all_bases = self:GetAllBases();
    if not all_bases then return end
    
    for _,base in ipairs(all_bases) do	
        table.insert(self.m_all_includes,base.name);
    end        
end

function CppBaseCodeGen:Code_ClassHeader(configs)
    local pb = PrintBuffer.new();
    
    if self.m_code_switch.weak_ref 
        or self.m_code_switch.task_container 
        or self.m_code_switch.hash_entry
    then
        pb:Print("public:",true);
    end
    
    if self.m_code_switch.weak_ref then
        pb:Print("    WEAK_REF_ID_DEFINE();",true);        
    end
    
    if self.m_code_switch.task_container then
        pb:Print("    TASK_CONTAINER_DEFINE();",true);        
    end

    return pb:GetText();
end

function CppBaseCodeGen:Code_InitBasic(configs)
    local pb = PrintBuffer.new();
    
    pb:Print(self:Code_CallBase("InitBasic()"));
    
    if self.m_code_switch.weak_ref then
        pb:Print("    WEAK_REF_ID_CLEAR();",true);        
    end
    
    if self.m_code_switch.task_container then
        pb:Print("    TASK_CONTAINER_CLEAR();",true);        
    end
       
    return pb:GetText();
end

function CppBaseCodeGen:Code_Init(configs)
    local pb = PrintBuffer.new();
    pb:Print(self:Code_CallBase("Init()"));
    
    if self.m_code_switch.weak_ref then
        pb:Print("    WEAK_REF_ID_INIT();",true);        
    end
    
    if self.m_code_switch.task_container then
        pb:Print("    TASK_CONTAINER_INIT(_taskmgr);",true);        
    end
    
    return pb:GetText();
end

function CppBaseCodeGen:Code_Destroy(configs)
    return self:Code_CallBase("Destroy()");
end

function CppBaseCodeGen:Code_Copy(configs)
    return self:Code_CallBase("Copy(_p)");
end

function CppBaseCodeGen:Code_Print(configs)
    return self:Code_CallBase("Print(_buf)");
end

function CppBaseCodeGen:Code_Includes(configs)
    local pb = PrintBuffer.new();
    
    if self.m_code_switch.task_container then
        pb:Log("#include \"taskmgr.h\"");
    end
    
    if self.m_code_switch.bson then
        pb:Log("#include \"minibson.h\"");
    end

    for _,name in ipairs(self.m_all_includes) do
        pb:Print(string.format(
            "#include \"%s.h\""..EOL,
            self.m_how_to_convert_file_name(name)
        ));
    end
    return pb:GetText();
end

function CppBaseCodeGen:Code_InitParam(config)
    local pb = PrintBuffer.new();
    if code_switch.task_container then
        pb:Print("CTaskMgr *_taskmgr");
        if config and config.add_comma then
            pb:Print(",");
        end                
    end   
    return pb:GetText();
end

function CppBaseCodeGen:Code_InitCallParam(config)
    local pb = PrintBuffer.new();
    if code_switch.task_container then
        pb:Print("GetTaskMgr()");
        if config and config.add_comma then
            pb:Print(",");
        end            
    end
    return pb:GetText();
end

function CppBaseCodeGen:GetAllBases()	
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

function CppBaseCodeGen:Code_ClassBase(nl)
    local pb = PrintBuffer.new();
    local bases = self:GetAllBases();
    if not bases then return "" end;
    
    local c = 0;
    for _,info in ipairs(bases) do
        c = c + 1;        
        if c == 1 then
            pb:Print(":");
        else
            pb:Print(",");
        end
        pb:Print(string.format(
            "%s %s",
            info.openness, c_class_name(info.name)
        ),nl);        
    end
    return pb:GetText();
end

function CppBaseCodeGen:Code_CallBase(func_name)
    local pb = PrintBuffer.new();
    local bases = self:GetAllBases();
    if not bases then return "" end;
    
    for _,info in ipairs(bases) do        
        pb:Print(string.format(
            "    %s::%s;",
            c_class_name(info.name),func_name
        ),true);        
    end
    return pb:GetText();
end

function CppBaseCodeGen:GetUserIncludes()
    local idl_class = self.m_idl_class;
    if not idl_class.hint then return end   
    local all = {};
        
    for_each_hint(idl_class.hint,function(mem,str)        
        mem:SetSplitChars(" \t\r\n");
        local str = mem:NextString();
        if str == "Includes" then
            for_each_word(mem,function(word)            
                table.insert(all,word);
            end);
        end
    end);
    
    if #all > 0 then return all end
end

function CppBaseCodeGen:GetNameSpace()
    if name_space ~= "" then
        return name_space;
    end
    
    local idl_class = self.m_idl_class;
    if not idl_class.hint then return end   
        
    local ns = nil;
    for_each_hint(idl_class.hint,function(mem,str)        
        mem:SetSplitChars(" \t\r\n");
        local str = mem:NextString();
        if str == "NameSpace" then
            ns = mem:NextString();
            return true;
        end
    end);
    
    return ns;
end

function CppBaseCodeGen:Code_NameSpaceBegin()
    local ns = self:GetNameSpace();
    if ns then
        return "namespace "..ns.." {";
    end
end

function CppBaseCodeGen:Code_NameSpaceEnd()
    local ns = self:GetNameSpace();
    if ns then
        return "}  //name space "..ns;
    end
end

function CppBaseCodeGen:SetHowToConvertFileName(func)
    self.m_how_to_convert_file_name = func;
end