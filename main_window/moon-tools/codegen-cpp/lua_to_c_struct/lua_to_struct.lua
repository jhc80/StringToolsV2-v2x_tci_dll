require("utils")
require("idl_helper")
require("code_utils")

--每一个变量的迭代器--
function for_each_variables(variables,callback)
    if not variables then return end
    
    for _,var in ipairs(variables) do		
        local info = {};
        local var_type = var.type;
        info.is_pointer = IdlHelper.Type.IsPointer(var_type);
        info.is_array,info.array_size = IdlHelper.Type.IsArray(var_type);
		info.is_string = IdlHelper.Type.IsString(var_type);
        info.is_basic_type = IdlHelper.Type.IsBasicType(var_type);
		info.full_size = IdlHelper.Var.GetFullSize(var);
	
        info.var = var;
        info.type = var_type;
		info.is_object = not info.is_basic_type;
		
        if callback(info) then
			break;
		end		
    end	
end


function code_struct_to_lua(idl_class)
	function code_for_basic_type(info)
		local inner_type = IdlHelper.Var.GetInnerType(info.type);
		printfnl("    _obj.%s = data:Get%s();",info.var.name, inner_type);
	end

	function code_for_array_object(info)
		printnl("");
		printfnl("    _obj.%s={};",info.var.name);
		
		if info.full_size and info.array_size~= info.full_size then
			printfnl("    local _arr_size = (%s<%s) and %s or %s;",
				info.array_size,info.full_size,
				info.array_size,info.full_size);
			
			printfnl("    for i=1,_arr_size,1 do");
			printfnl("        _obj.%s[i] = %s(data);", info.var.name, struct_to_lua_function_name(info.type.name));	
			printfnl("    end");

			if info.full_size then
				printfnl("    data:Skip((%s-_arr_size)*%s());",
					info.full_size,
					lua_size_function_name(info.type.name)
				);
			end
		else
			printfnl("    for i=1,%s,1 do",info.array_size);
			printfnl("        _obj.%s[i] = %s(data);", info.var.name, struct_to_lua_function_name(info.type.name));	
			printfnl("    end");
		end
		
		printnl("");
	end

	function code_for_array_basic_type(info)
		local as_string = IdlHelper.Var.AsString(info.var);
		local as_binary = IdlHelper.Var.AsBinary(info.var);
		local inner_type = IdlHelper.Var.GetInnerType(info.type);
		
		printnl("");
		if as_binary then
			printfnl("    local _size = SIZE_OF_%s*%s;",string.upper(inner_type),info.array_size);
			printfnl("    _obj.%s = new_mem(_size);",info.var.name);	
			printfnl("    data:Read(_obj.%s,_size);",info.var.name);
			if info.full_size then
				printfnl("    data:Skip((%s-%s)*SIZE_OF_%s);",
					info.full_size,info.array_size,
					string.upper(inner_type)
				);
			end
		elseif as_string then
			printfnl("    local _size = SIZE_OF_%s*%s;",string.upper(inner_type),info.array_size);
			printfnl("    local _tmp = new_mem(_size);",info.var.name);	
			printfnl("    data:Read(_tmp,_size);");
			printfnl("    _obj.%s = _tmp:CStr();",info.var.name);
			if info.full_size then
				printfnl("    data:Skip((%s-%s)*SIZE_OF_%s);",
					info.full_size,info.array_size,
					string.upper(inner_type)
				);
			end
		else			
			printfnl("    _obj.%s={};",info.var.name);
			
			if info.full_size and info.array_size~= info.full_size then
				printfnl("    local _arr_size = (%s<%s) and %s or %s;",
				info.array_size,info.full_size,
				info.array_size,info.full_size);
				
				printfnl("    for i=1,_arr_size,1 do");
				printfnl("        _obj.%s[i] = data:Get%s();", info.var.name, inner_type);	
				printfnl("    end");
				
				if info.full_size then
					printfnl("    data:Skip((%s-_arr_size)*%s());",
						info.full_size,
						lua_size_function_name(info.type.name)
					);
				end
			else
				printfnl("    for i=%s,1 do",info.array_size);
				printfnl("        _obj.%s[i] = data:Get%s();", info.var.name, inner_type);	
				printfnl("    end");
			end
		end
		printnl("");
	end
	
	function code_for_object(info)
		printfnl("    _obj.%s = %s(data);",info.var.name, struct_to_lua_function_name(info.type.name));
	end

	printfnl("function %s(data)",struct_to_lua_function_name(idl_class.name));
	printfnl("    local _obj={};");

	for_each_variables(idl_class.variables,function(info)		
		if info.is_array then				
			if info.is_object then				
				code_for_array_object(info);
			elseif info.is_basic_type then
				code_for_array_basic_type(info);
			end	
		elseif info.is_basic_type then			
			code_for_basic_type(info);
		elseif info.is_object then
			code_for_object(info);
		end		
	end);
	printfnl("    return _obj;");
	printfnl("end");	
end


function code_lua_to_struct(idl_class)	
	function code_for_array_object(info)
		printnl("");
		
		if info.full_size and info.array_size~= info.full_size then
			printfnl("    local _arr_size = (#_obj.%s<%s) and #_obj.%s or %s;",
				info.var.name,info.full_size,
				info.var.name,info.full_size);
				
			printfnl("    for i=1,_arr_size,1 do");
			printfnl("        %s(_obj.%s[i],file);",lua_to_struct_function_name(info.type.name),info.var.name);	
			printfnl("    end");
			
			if info.full_size then
				printfnl("    file:FillBlock((%s-_arr_size)*%s(),0);",
					info.full_size,
					lua_size_function_name(info.type.name)
				);
			end
		else
			printfnl("    for i=1,%s,1 do",info.array_size);
			printfnl("        %s(_obj.%s[i],file);",lua_to_struct_function_name(info.type.name),info.var.name);	
			printfnl("    end");
		end
		
		printnl("");
	end
	
	function code_for_array_basic_type(info)	
		local as_string = IdlHelper.Var.AsString(info.var);
		local as_binary = IdlHelper.Var.AsBinary(info.var);
		local inner_type = IdlHelper.Var.GetInnerType(info.type);
		printnl("");
		if as_binary then
			printfnl("    local _size = SIZE_OF_%s*%s;",string.upper(inner_type),info.array_size);			
			printfnl("    if _obj.%s == nil then", info.var.name);
			printfnl("        file:FillBlock(_size,0);");
			printfnl("    else");			
			printfnl("        file:Write(_obj.%s,_size);",info.var.name);
			printfnl("        if _size > _obj.%s:GetSize() then",info.var.name);
			printfnl("            file:FillBlock(_size-_obj.%s:GetSize(),0);",info.var.name);
			printfnl("        end");
			printfnl("    end");
			
			if info.full_size then
				printfnl("    file:FillBlock((%s-%s)*SIZE_OF_%s,0);",
					info.full_size,info.array_size,
					string.upper(inner_type)
				);
			end
		elseif as_string then						
			printfnl("    local _mem = Mem.new();");
			printfnl("    _mem:SetRawBuf(_obj.%s);",info.var.name);
			printfnl("    local _size = SIZE_OF_%s*%s;",string.upper(inner_type),info.array_size);
			printfnl("    file:Write(_mem,_size);");
			printfnl("    if _size > _mem:GetSize() then");
			printfnl("        file:FillBlock(_size-_mem:GetSize(),0);");
			printfnl("    end");
			if info.full_size then
				printfnl("    file:FillBlock((%s-%s)*SIZE_OF_%s,0);",
					info.full_size,info.array_size,
					string.upper(inner_type)
				);
			end
		else						
			if info.full_size and info.array_size~= info.full_size then
				printfnl("    local _arr_size = (#_obj.%s<%s) and #_obj.%s or %s;",
					info.var.name,info.full_size,
					info.var.name,info.full_size);
				
				printfnl("    for i=1,_arr_size,1 do");
				printfnl("        file:Put%s(_obj.%s[i]);",inner_type,info.var.name);	
				printfnl("    end");
			else
				printfnl("    for i=1,%s,1 do",info.array_size);
				printfnl("        file:Put%s(_obj.%s[i]);",inner_type,info.var.name);	
				printfnl("    end");
			end
		end	

		printnl("");
	end
	
	function code_for_basic_type(info)
		local inner_type = IdlHelper.Var.GetInnerType(info.type);
		printfnl("    file:Put%s(_obj.%s);",inner_type,info.var.name);
	end
	
	function code_for_object(info)
		printfnl("    %s(_obj.%s,file);",lua_to_struct_function_name(info.type.name), info.var.name);
	end
	
	printfnl("function %s(_obj,file)",lua_to_struct_function_name(idl_class.name));
	for_each_variables(idl_class.variables,function(info)		
		if info.is_array then				
			if info.is_object then				
				code_for_array_object(info);
			elseif info.is_basic_type then
				code_for_array_basic_type(info);
			end	
		elseif info.is_basic_type then			
			code_for_basic_type(info);
		elseif info.is_object then
			code_for_object(info);		
		end		
	end);
	
	printfnl("end");	
end

function code_size(idl_class)
	function code_for_array_object(info)
		local size_str = info.array_size;
		if info.full_size then
			size_str = info.full_size;
		end
		
		printfnl("    _size = _size + %s*%s();  --%s", 
			size_str,
			lua_size_function_name(info.type.name),
			info.var.name
		);
	end
	
	function code_for_array_basic_type(info)	
		local as_string = IdlHelper.Var.AsString(info.var);
		local as_binary = IdlHelper.Var.AsBinary(info.var);
		local inner_type = IdlHelper.Var.GetInnerType(info.type);
		
		local size_str = info.array_size;
		if info.full_size then
			size_str = info.full_size;
		end
		
		printfnl("    _size = _size + %s*SIZE_OF_%s;  --%s", 
			size_str, 
			string.upper(inner_type),
			info.var.name
		);
	end
	
	function code_for_basic_type(info)
		local inner_type = IdlHelper.Var.GetInnerType(info.type);
		printfnl("    _size = _size + SIZE_OF_%s;  --%s",
			string.upper(inner_type),
			info.var.name);
	end
	
	function code_for_object(info)
		printfnl("    _size = _size + %s();  --%s",
			lua_size_function_name(info.type.name),
			info.var.name);
	end
	
	printfnl("function %s()",lua_size_function_name(idl_class.name));
	printfnl("    local _size = 0;");
	for_each_variables(idl_class.variables,function(info)		
		if info.is_array then				
			if info.is_object then				
				code_for_array_object(info);
			elseif info.is_basic_type then
				code_for_array_basic_type(info);
			end	
		elseif info.is_basic_type then			
			code_for_basic_type(info);
		elseif info.is_object then
			code_for_object(info);		
		end		
	end);
	printfnl("    return _size;");
	printfnl("end");	
end