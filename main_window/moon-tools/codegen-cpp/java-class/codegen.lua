require("common")
require("idl_helper");

function ptab(level)
    local str = "";
    for i=1,level,1 do
        str = str.."    ";
    end
    return str;
end               
---------------------------------------------
function code_begin_marker(name)
    if not code_switch.code_mark then
        return
    end
    return printnl("/*##Begin "..name.."##*/");
end

function code_end_marker(name)
    if not code_switch.code_mark then
        return
    end
    return printnl("/*##End "..name.."##*/");
end

function code_begin_extra(name)
    if not code_switch.code_mark then
        return
    end
    return printnl("/*@@Begin Function "..name.."@@*/");
end

function code_end_extra(name)
    if not code_switch.code_mark then
        return
    end
    return printnl("/*@@End  Function "..name.."@@*/");
end
--------------------------------------------------------
function for_each_variables(variables,callback)
    if not variables then return end
    
    for _,var in ipairs(variables) do	
        local var_type = var.type;
        local is_array,array_size = IdlHelper.Type.IsArray(var_type);
        local is_string = IdlHelper.Type.IsString(var_type);
        local is_basic_type = IdlHelper.Type.IsBasicType(var_type);
     
        local info = {};
        info.var = var;
        info.var_type = var_type;
        info.is_array = is_array;
        info.array_size = array_size;
        info.is_string = is_string;
        info.is_basic_type = is_basic_type;
        info.is_object = not is_basic_type;
		info.is_no_setter = IdlHelper.Var.IsNoSetter(var);
		info.is_no_getter = IdlHelper.Var.IsNoGetter(var);
		info.java_type = IdlHelper.Type.GetJavaType(var_type);
	    callback(info);
    end
end

--按字典顺序排序
function for_each_variables_sorted(variables, callback)
    if not variables then return end
    local sorted = {};
    for _,var in ipairs(variables) do	
        table.insert(sorted,var);
    end

    table.sort(sorted,function(e1,e2)
        return string.lower(e1.name) < string.lower(e2.name);
    end);

    for_each_variables(sorted,callback);
end

--生成所有的成员变量的代码--
function code_java_all_members(idl_class)
	for_each_variables(idl_class.variables,function(info)	
		printf("    private ");
		
		if info.is_string then
			printf("String");
		elseif info.is_basic_type then
			printf("%s",info.java_type);
		elseif info.is_object then
			printf("%s",java_class_name(info.var_type.name));
		end
		
		if info.is_array then
			printf("[]");
		end
		printf(" ");
		
		printf("%s",member_name(info.var.name));
		
		if info.var.init_value then
			printf(" = %s",info.var.init_value);
		end
		
		printnl(";");
		
	end)
	
	

end

--生成一个构造函数
function code_java_ctor_function(idl_class)
	printfnl("    public %s()",java_class_name(idl_class.name));
	printfnl("    {");
	
	for_each_variables(idl_class.variables,function(info)	
		if info.is_array then
			if info.array_size then
				printf("        this.%s = new ",member_name(info.var.name));
				
				if info.is_string then
					print("String");
				elseif info.is_basic_type then
					print(info.java_type);
				elseif info.is_object then
					print(java_class_name(info.var_type.name));
				end
				
				printfnl("[%s];",info.array_size);
			end
		end	
	end);
	
	
	printfnl("    }");
end

--生成所有的java代码--
function code_java(idl_class)	
	code_begin_marker("Header");	
	printfnl("package %s;",java_package_name);	
	printnl("");
	printfnl("import android.util.Log;");
	code_end_marker("Header");
	printnl("");
	
	printf("public %s",java_class_name(idl_class.name));
	
	local all_bases = IdlHelper.Class.GetAllBases(idl_class);	
	if all_bases then	
		print(" extends ");
		for i, base in ipairs(all_bases) do
			if i > 1 then print(",");end
			print(java_class_name(base.name));
		end	
	end
	printnl("{");	
	code_java_all_members(idl_class);
	printnl("");
	code_java_ctor_function(idl_class);
	printnl("");
	printnl("}");
end
