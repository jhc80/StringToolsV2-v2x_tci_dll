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
        info.is_weak_ptr = IdlHelper.Var.IsWeakPtr(var) 
            and info.is_pointer and not info.is_basic_type;
       
        if info.is_weak_ptr then
            info.is_pointer = false;
        end		
        
        info.var = var;
        info.type = var_type;
		info.is_object = not info.is_basic_type;
		
        if callback(info) then
			break;
		end		
    end	
end

--生成在closure外面的赋值代码--
function code_var_out_closure(var_info)
	if var_info.is_array then
		printf("Malloc(%s,%s,sizeof(%s)*%s)",
			IdlHelper.Var.GetIndex(var_info.var),
			var_info.var.name,
			var_info.type.name,
			var_info.array_size
		);
		return
	end

	if var_info.is_string then
		printf("SetParamString");		
	elseif var_info.is_pointer then
		printf("SetParamPointer");		
	elseif var_info.is_weak_ptr then
		printf("SetParamWeakPointer");
	elseif var_info.is_basic_type then
		printf("SetParam%s",IdlHelper.Var.GetClosureType(var_info.type));
	end
	
	if not var_info.is_weak_ptr then
		printf("(%s,%s)",IdlHelper.Var.GetIndex(var_info.var),var_info.var.name);
	else
		printf("(%s,%s,%s->__weak_ref_id)",IdlHelper.Var.GetIndex(var_info.var),var_info.var.name,var_info.var.name);
	end	
end

--生成在closure内面的取值代码--
function code_var_in_closure(var_info)
	local index = IdlHelper.Var.GetIndex(var_info.var)
	if var_info.is_string then
		printf("CLOSURE_PARAM_STRING(%s,%s)",var_info.var.name,index);
	elseif var_info.is_pointer or var_info.is_array then
		printf("CLOSURE_PARAM_PTR(%s*,%s,%s)",
			var_info.type.name,
			var_info.var.name,
			index
		);
	elseif var_info.is_weak_ptr then
		printf("CLOSURE_PARAM_WEAKPTR(%s*,%s,%s)",
			var_info.type.name,
			var_info.var.name,
			index
		);
	elseif var_info.is_basic_type then
		printf("CLOSURE_PARAM_%s(%s,%s)",
			string.upper(IdlHelper.Var.GetClosureType(var_info.type)),
			var_info.var.name,
			index
		);
	end
end

--生成closure的代码
function code_closure(idl_class)
	local is_new = IdlHelper.Class.IsNew(idl_class);
	
	if  is_new then 
		printfnl("BEGIN_NEW_CLOSURE(%s)",idl_class.name);
	else
		printfnl("BEGIN_CLOSURE(%s)",idl_class.name);
	end	
	printnl("{");
		for_each_variables(idl_class.variables,function(info)
			printf("    ");
			code_var_in_closure(info);
			printnl(";");
	end);	
	printnl("");
	printnl("    return OK;");
	printnl("}");	
	if  is_new then 
		printfnl("END_NEW_CLOSURE(%s);",idl_class.name);
	else
		printfnl("END_CLOSURE(%s);",idl_class.name);
	end	
	
	printnl("");
	
	local dot_or_pointer = is_new and "->" or ".";
	for_each_variables(idl_class.variables,function(info)
		printf("%s%s",idl_class.name,dot_or_pointer);
		code_var_out_closure(info);
		printnl(";");
	end);
end

