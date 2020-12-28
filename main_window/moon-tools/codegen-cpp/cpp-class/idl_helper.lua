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

IdlHelper.Class.SetCodeSwitches=function(idl_class,code_switch)
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

IdlHelper.Type.GetXmlType=function(type)
	return IdlHelper.Type.GetBsonType(type);
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
			return b[7];
		end
	end	
	return "<??>";
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

IdlHelper.Var.IsOptional = function(var)
    return IdlHelper.Class.FindHintSwitch(var,"optional");
end

IdlHelper.Var.IsWeakPtr = function(var)
    return IdlHelper.Class.FindHintSwitch(var,"weak");
end

IdlHelper.Type.GetCJsonValue=function(type)
	for _,b in ipairs(basic_type_table) do	
		if type.name == b[1] then
			return b[5];
		end
	end	
	return "<??>";
end

IdlHelper.Type.GetCJsonType=function(type)
	for _,b in ipairs(basic_type_table) do	
		if type.name == b[1] then
			return b[6];
		end
	end	
	return "<??>";
end

IdlHelper.Class.IsAsn1Choice = function(var)
	return IdlHelper.Class.FindHintSwitch(var,"Asn1Choice");
end

IdlHelper.Type.IsStruct = function(type)
	return IdlHelper.Class.FindHintSwitch(type,"struct");
end

IdlHelper.Var.IsNoSetter = function(var)
	return IdlHelper.Class.FindHintSwitch (var,"noset");
end

IdlHelper.Var.IsNoGetter = function(var)
	return IdlHelper.Class.FindHintSwitch (var,"noget");
end

IdlHelper.Var.IsNoXml = function(var)
	return IdlHelper.Class.FindHintSwitch (var,"noxml");
end

IdlHelper.Var.IsNoBson = function(var)
	return IdlHelper.Class.FindHintSwitch (var,"nobson");
end

IdlHelper.Var.GetXml2Info = function(var)
	if not var then return end
	if not var.hint then return end
	
	local info={};
	local hit = false;

	for_each_hint(var.hint,function(mem,str)    
		mem:Seek(0);
		mem:SetSplitChars(",=");
		while not mem:IsEnd() do
			local s = mem:NextString();
			if s == "array" then
				info.is_array = true;
				info.array_entry = mem:NextString();
				hit = true;
			end
			if s == "map" then
				info.is_map = true;
				info.map_entry = mem:NextString();
				hit = true;
			end			
			if s == "name" then
				info.name = mem:NextString();			
				hit = true;
			end
			if s == "value" then
				info.is_value = true;
				hit = true;
			end
		end
	end);    

	if hit then return info end
end