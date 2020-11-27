IdlHelper={};
IdlHelper.Class={};
IdlHelper.Type={};
IdlHelper.Func={};
IdlHelper.Param ={};

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

IdlHelper.Class.GetPeerName=function(idl_class)    
    if not idl_class.hint then return end
    
    local name;
    for_each_hint(idl_class.hint,function(mem)    
        if mem:NextString() == "Peer" then
            name = mem:NextString();
            return true;
        end    
    end);

    return name;
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
    return "<??>";
end

IdlHelper.Type.GetBsonType=function(type)
	for _,b in ipairs(basic_type_table) do	
		if type.name == b[1] then
			return b[3];
		end
	end	
	return "<??>";
end

IdlHelper.Type.GetJavaType=function(type)
	for _,b in ipairs(basic_type_table) do	
		if type.name == b[1] then
			return b[4];
		end
	end	
	return "<??>";
end

IdlHelper.Func.IsVoid = function(func)
    if not func then return true end
    if not func.ret_type then return true end
    return func.ret_type[1].name == "void";
end

IdlHelper.Func.IsService=function(func)
    if not func then return end
    if not func.hint then return end    

    local is_service = false;
    for_each_hint(func.hint,function(mem)    
        if mem:NextString() == "service" then
            is_service = true;
            return true;
        end    
    end);
    return is_service;
end

IdlHelper.Class.GetStartId=function(idl_class)
    if not idl_class then return 0 end
    if not idl_class.hint then return 0 end    
    
    local start_id;
    for_each_hint(idl_class.hint,function(mem)    
        if mem:NextString() == "StartId" then
            start_id = tonumber(mem:NextString());
            return true;
        end    
    end);

    return start_id;
end

IdlHelper.Class.GetClientName=function(idl_class)
    if not idl_class then return  end
    if not idl_class.hint then return  end    
    
    local name,id;
    for_each_hint(idl_class.hint,function(mem)    
        if mem:NextString() == "Client" then
            name = mem:NextString();
            id = mem:NextString();
            return true;
        end    
    end);

    return name,id;
end
