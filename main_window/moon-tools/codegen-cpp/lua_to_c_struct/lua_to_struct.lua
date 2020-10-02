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
       
        info.var = var;
        info.type = var_type;
		info.is_object = not info.is_basic_type;
		
        if callback(info) then
			break;
		end		
    end	
end

function code_for_basic_type(info)
	local inner_type = IdlHelper.Var.GetInnerType(info.type);
	printfnl("    _ret.%s = data:Get%s();",info.var.name, inner_type);
end

function code_for_array_object(info)	
	printfnl("    _ret.%s={}",info.var.name);
	printfnl("    for i=1,%s,1 do",info.array_size);
	printfnl("        _ret.%s[i] = %s(data);", info.var.name, struct_to_lua_function_name(info.type.name));	
	printfnl("    end");
end

function code_for_array_basic_type(info)
	local as_string = IdlHelper.Var.AsString(info.var);
	local as_binary = IdlHelper.Var.AsBinary(info.var);
	local inner_type = IdlHelper.Var.GetInnerType(info.type);
	
	if as_binary then
		printfnl("    local _size = SIZE_OF_%s*%s;",string.upper(inner_type),info.array_size);
		printfnl("    _ret.%s = new_mem(_size);",info.var.name);	
		printfnl("    data:Read(_ret.%s,_size);",info.var.name);
	elseif as_string then
		printfnl("    local _size = SIZE_OF_%s*%s;",string.upper(inner_type),info.array_size);
		printfnl("    local _tmp = new_mem(_size);",info.var.name);	
		printfnl("    data:Read(_tmp,_size);");
		printfnl("    _ret.%s = _tmp:CStr();",info.var.name);
	else			
		printfnl("    _ret.%s={}",info.var.name);
		printfnl("    for i=1,%s,1 do",info.array_size);
		printfnl("        _ret.%s[i] = data:Get%s();", info.var.name, inner_type);	
		printfnl("    end");
	end
end

function code_struct_to_lua(idl_class)
	printfnl("function %s(data)",struct_to_lua_function_name(idl_class.name));
	printfnl("    local _ret={};");

	for_each_variables(idl_class.variables,function(info)		
		if info.is_array then				
			if info.is_object then				
				code_for_array_object(info);
			elseif info.is_basic_type then
				code_for_array_basic_type(info);
			end	
		elseif info.is_basic_type then			
			code_for_basic_type(info);
		end		
		printnl("");
	end);
	printfnl("end");	
end

