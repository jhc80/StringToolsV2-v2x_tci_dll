require("code_utils")

IdlHelper={};
IdlHelper.Class={};
IdlHelper.Type={};
IdlHelper.Var={};
IdlHelper.Func={};

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

IdlHelper.Class.FindHintSwitch = function(var,the_str)
    if not var then return false end
    if not var.hint then return false end
    local ret = false;
    for_each_hint(var.hint,function(mem,str)    
		mem:Seek(0);
		while not mem:IsEnd() do
			if mem:NextString() == the_str then
				ret = true;
				return true;
			end    
		end
    end);    
    return ret;
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
	return IdlHelper.Class.FindHintSwitch (var,"optional");
end

IdlHelper.Var.IsNoSetter = function(var)
	return IdlHelper.Class.FindHintSwitch (var,"noset");
end

IdlHelper.Var.IsNoGetter = function(var)
	return IdlHelper.Class.FindHintSwitch (var,"noget");
end

IdlHelper.Func.IsVirtual  = function(func)
	return IdlHelper.Class.FindHintSwitch(func,"virtual");
end

IdlHelper.Func.IsVoid = function(func)
    if not func then return true end
    if not func.ret_type then return true end
	if #func.ret_type ~= 1 then return false end
    return func.ret_type[1].name == "void" and 
		not IdlHelper.Type.IsPointer(func.ret_type[1]);
end

IdlHelper.Type.GetLibConfigType=function(type)
	for _,b in ipairs(basic_type_table) do	
		if type.name == b[1] then
			return b[4];
		end
	end	
	return "<??>";
end

IdlHelper.Type.GetLibConfigDefineType=function(type)
	for _,b in ipairs(basic_type_table) do	
		if type.name == b[1] then
			return b[5];
		end
	end	
	return "<??>";
end

IdlHelper.Class.IsVirtualClass = function(idl_class)
	if not idl_class then return false end
	
	if idl_class._is_virtual_class_ ~= nil then 
		return idl_class._is_virtual_class_;
	end
	
	if idl_class.functions then
		for _,func in ipairs(idl_class.functions) do
			if IdlHelper.Func.IsVirtual(func) then
				idl_class._is_virtual_class_ = true;
				return true;
			end
		end
	end

	idl_class._is_virtual_class_ = false;
	return false;
end


