IdlHelper={};
IdlHelper.Class={};
IdlHelper.Type={};
IdlHelper.Var={};

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

IdlHelper.Type.GetSqliteType=function(type)
	for _,b in ipairs(basic_type_table) do	
		if type.name == b[1] then
			return b[2];
		end
	end	
end

IdlHelper.Type.GetSqliteType_2=function(type)
	local t = IdlHelper.Type.GetSqliteType(type);
	if t == "INTEGER64" then
		return "INTEGER";
	end
	return t;
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
