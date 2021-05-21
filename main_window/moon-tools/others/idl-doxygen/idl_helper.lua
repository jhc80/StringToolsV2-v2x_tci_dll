require("code_utils")
require("print_buffer")

IdlHelper={};
IdlHelper.Class={};
IdlHelper.Type={};
IdlHelper.Func={};
IdlHelper.Param={};
IdlHelper.Common={};

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

IdlHelper.Class.GetAllSubClasses = function(idl_class)
	if not idl_class.hint then return end    
	local all={};
    
    for_each_hint(idl_class.hint,function(mem)        
        if mem:NextString() == "SubClass" then        
            for_each_word(mem,function(word)
                table.insert(all,word);
            end);        
        end        
    end);

	if #all > 0 then return all end
end

IdlHelper.Class.MakeConnections=function(idl_class)
	if not idl_class.functions then return end
	for _,func in pairs(idl_class.functions) do
		func.idl_class = idl_class;
	end
end

IdlHelper.Class.CollectAllIncludes=function(idl_class)
	local all = {};

	local function add_name(name)
		if not all[name] and name ~=idl_class.name then
			all[name] = true;
		end
	end

	local all_bases = IdlHelper.Class.GetAllBases(idl_class);
	if all_bases then
		for k,v in ipairs(all_bases) do
			add_name(v.name);
		end
	end

	local all_sub_classes = IdlHelper.Class.GetAllSubClasses(idl_class);
	if all_sub_classes then
		for k,v in ipairs(all_sub_classes) do
			add_name(v);
		end
	end

	for_each_functions(idl_class.functions,function(func_info)
		for_each_params(func_info.params, function(param_info)
			if param_info.is_object then
				add_name(param_info.type.name);
			end
		end);

		for_each_return_type(func_info.ret_type,function(ret_info)
			if ret_info.is_object then
				add_name(ret_info.type.name);
			end
		end)
	end);

	return all;
end

IdlHelper.Type.IsString=function(type)
    if not type then return end
    if type.is_string then
        return true;
    end
	return type.name == "string";
end

IdlHelper.Type.IsArray=function(type)
    if not type then
        return
    end
	if type.flags & 0x00000001 ~= 0 then
		return true,type.array_size;
	end
end

IdlHelper.Type.IsPointer=function(type)
	return type.flags & 0x00000002 ~= 0;
end

IdlHelper.Type.IsBasicType=function(type)
    if not type then return true end
	for _,b in ipairs(basic_type_table) do	
		if type.name == b[1] then
			return true,b;
		end
	end	
end

IdlHelper.Param.IsCallback = function(param)
    return IdlHelper.Func.IsCallback(param);
end

IdlHelper.Func.IsVoid = function(func)
    if not func then return true end
    if not func.ret_type then return true end
    return func.ret_type[1].name == "void";
end

IdlHelper.Func.IsCallback = function(func)
    if not func then return false end
    if not func.hint then return false end
    
    local is_callback;
    
    for_each_hint(func.hint,function(mem)
        for_each_word(mem,function(word)
            if word == "callback" then
                is_callback = true;
                return true;
            end
        end);
    end);
    
    return is_callback;
end

IdlHelper.Func.IsStatic = function(func)
    if not func then return false end
    if not func.hint then return false end
    local is_static;    
    for_each_hint(func.hint,function(mem)
        for_each_word(mem,function(word)
            if word == "static" then
                is_static = true;
                return true;
            end
        end);
    end);    
    return is_static;    
end

IdlHelper.Common.GetSomething=function(obj,key)
   if not obj then return "" end
    if not obj.hint then return "" end
    local pbuf = PrintBuffer.new();
    local buf = new_mem();
    
    for_each_hint(obj.hint,function(mem)
        if mem:NextWord() == key then
            mem:ReadLeftStr(buf,true);
            if buf:StrLen() > 0 then
                pbuf:Puts(buf);
            end
        end     
    end);
    
    return pbuf:GetText()
end

IdlHelper.Common.GetComments=function(obj)
    return IdlHelper.Common.GetSomething(obj,"@");
end

IdlHelper.Common.GetRetComments=function(obj)
    return IdlHelper.Common.GetSomething(obj,"!");
end

