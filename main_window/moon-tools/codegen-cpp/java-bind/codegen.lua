require("common")
require("idl_helper");
require("print_buffer");

function jnilib_file_name(name)
    return "jnilib_"..string.lower(name);
end

function java_file_name(name)
	return c_class_name(name);
end

function java_class_name(name)
	return c_class_name(name);
end

function java_class_path(name)
	return string.gsub(package_name,"%.","/")..
		"/"..java_class_name(name);
end

function jni_c_func_name(info)
    local name = string.lower(info.idl_class.name).."_"..
        string.lower(info.name);
	if info.func.override_id then
		name = name.."_v"..info.func.override_id;
	end
	return name;
end

function c_type_to_jni_type(c_type_name)
	for _,b in ipairs(basic_type_table) do	
		if c_type_name == b[1] then
			return b[2];
		end
	end	
end

function get_jni_type_info(jni_type_name)
    for _,info in ipairs(jni_type_table) do    
        if info[1] == jni_type_name then
            local tab = {
                jni_type = info[1],
                jni_c_type = info[2],
				jni_array_type = info[5],
            };            
            return tab;
        end    
    end
end

--遍历idl_class中每一个function的迭代器--
function for_each_functions(functions, callback)    
    if not functions then return end
    local index = 1;
    for _,func in ipairs(functions) do        
        local info = {};
        info.func = func;
        info.is_void = IdlHelper.Func.IsVoid(func);
        info.is_static = IdlHelper.Func.IsStatic(func);
        info.is_callback = IdlHelper.Func.IsCallback(func);
        info.ret_type = func.ret_type;
        info.name = func.name;
        info.params = func.params;
        info.index = index;        
        info.is_ctor = (func.idl_class.name == info.name);
        info.idl_class = func.idl_class;
        
        if info.is_ctor then
            info.is_static = true;
            info.name = "_new";
        end
        
        index = index + 1;
        if callback(info) then        
            return true;
        end        
    end
end

--遍历每一个函数参数的迭代器--
function for_each_params(params, callback)
    if not params then return end
    local index = 1;
    local is_first = true;
    
    for _, p in ipairs(params) do        
        local info = {};
        info.param = p;
        info.name = p.name;  
        info.type = p.type;
        info.is_array,array_size = IdlHelper.Type.IsArray(p.type);
        info.is_string = IdlHelper.Type.IsString(p.type);
        info.is_basic_type = IdlHelper.Type.IsBasicType(p.type);        
        info.is_callback = IdlHelper.Param.IsCallback(p);
        info.is_object = not info.is_basic_type;
        
        if info.type then
            info.jni_type = get_jni_type_info(
                c_type_to_jni_type(info.type.name)
            );
        end
        
        info.is_first = is_first;
        is_first = false;
        info.index = index;
        index = index + 1;
        if callback(info) then
            return true;
        end        
    end
end

--遍历每一个返回值的迭代器--
function for_each_return_type(ret_types,callback,name_prefix)
    local index = 1;
    
    if not name_prefix then
        name_prefix = "ret";
    end
    local is_first = true;
    
    for _, ret in ipairs(ret_types) do        
        local info = {};
        info.type = ret;
        info.is_pointer = IdlHelper.Type.IsPointer(ret);        
        info.is_array,array_size = IdlHelper.Type.IsArray(ret);
        info.is_string = IdlHelper.Type.IsString(ret);
        info.is_basic_type = IdlHelper.Type.IsBasicType(ret);        
        info.is_object = not info.is_basic_type;
        info.is_void = info.type.name == "void";
        
        info.is_first = is_first;
        is_first = false;
        
        if info.type then
            info.jni_type = get_jni_type_info(
                c_type_to_jni_type(info.type.name)
            );
        end
                       
        info.name = name_prefix..(index-1);
        index = index + 1;

        if callback(info) then
            return true;
        end        
    end
end

--参数调用的列表--
function param_call_list(params)
    local str="";
    
    for_each_params(params,function(info)
        if not info.is_first then
            str = str..",";
        end
        
        if info.is_string and info.is_array then
            str = str.."&";
        end

        str = str..string.lower(info.name);
        
        if info.is_array and not info.is_string then
            str = str..","..string.lower(info.name).."_len";            
        end
        
    end);
  
    return str;
end

--参数声明的列表，带类型--
function jni_param_define_list(params)
    local str="";    
    local n = 0;
    for_each_params(params,function(info)      
        if info.is_array then
            if info.is_basic_type then
				str = str..", "..info.jni_type.jni_array_type.." ";
				str = str.."_"..string.lower(info.name);
                n = n + 1;
			else
				str = str..", ".."jobjectArray ";
				str = str.."_"..string.lower(info.name);
                n = n + 1;
            end
        else
            if info.is_string then
                str = str..", "..info.jni_type.jni_type.." ";
                str = str.."_"..string.lower(info.name);
                n = n + 1;
            elseif info.is_object then
                str = str..", ".."jobject ";
                str = str.."_"..string.lower(info.name);
                n = n + 1;
            elseif info.is_basic_type then
                str = str..", "..info.jni_type.jni_type.." ";
                str = str.."_"..string.lower(info.name);
                n = n + 1;
            end
        end
    end);
  
    return str,n;
end

--返回值的定义列表，用于callback函数的声明--
function return_define_list(ret_types)
    local str="";    
    local n = 0;
    for_each_return_type(ret_types,function(info)      
        if info.is_void then
            return
        end
        if info.is_array then
            if info.is_basic_type then
                str = str..", "..info.type.name.." *";
                str = str..string.lower(info.name);
                str = str..", int *"..string.lower(info.name).."_len";
                n = n + 1;
            end
        else
            if info.is_string then
                str = str..", CMem *";
                str = str..string.lower(info.name);
                n = n + 1;
            elseif info.is_object then
                str = str..", "..c_class_name(info.type.name).." **";
                str = str..string.lower(info.name);
                n = n + 1;
            elseif info.is_basic_type then
                str = str..", "..info.type.name.." *";
                str = str..string.lower(info.name);
                n = n + 1;
            end
        end
    end);
  
    return str,n;
end


function auto_assign_func_id(idl_class)
    local counts = {};
    for_each_functions(idl_class.functions,function(info)
        if not counts[info.name] then
            counts[info.name] = 0;
        else
            counts[info.name] = counts[info.name] + 1;
        end
    end);

    local auto_ids={};
    for_each_functions(idl_class.functions,function(info)
        if counts[info.name] > 0 then
            if not auto_ids[info.name] then
                auto_ids[info.name] = 0;
            end
            auto_ids[info.name] = auto_ids[info.name] + 1;
            info.func.override_id = auto_ids[info.name];
        end
    end);
end

------------------------------------------------------------------------------
------------------------------------------------------------------------------
--生成头文件--
function code_h(idl_class)
    local lower_class_name = string.lower(idl_class.name);
    local upper_file_name = string.upper(jnilib_file_name(idl_class.name));
	
	printfnl("#ifndef __%s_H",upper_file_name);
	printfnl("#define __%s_H",upper_file_name);
	printfnl("");
	printfnl("#include \"jni_object.h\"");
	printfnl("#include \"%s.h\"",to_file_name(idl_class.name));
	printfnl("");
	printfnl("%s* get_%s(JNIEnv* env,jobject obj);",
		c_class_name(idl_class.name),
		lower_class_name);

	printfnl("jobject create_java_%s(JNIEnv* env,%s *%s, bool is_weak);",
		lower_class_name,c_class_name(idl_class.name),lower_class_name
	);
	
	printfnl("status_t register_%s_native_methods(JNIEnv* env);",lower_class_name);
	printfnl("");
	printfnl("#endif");
end

--生成所有的include代码--
function code_includes_cpp(idl_class)
    printfnl("#include \"%s.h\"",jnilib_file_name(idl_class.name))

    local includes = IdlHelper.Class.CollectAllIncludes(idl_class);

    for name in pairs(includes) do
        printfnl("#include \"%s.h\"",jnilib_file_name(name));
    end
    printnl("#include \"mem_tool.h\"");
    printnl("#include \"syslog.h\"");    
    printnl("");
end

--生成get_xxx函数的代码--
function code_get(idl_class)
	printfnl("JNI_GET_OBJ_FROM_USER_DATA_FUNC(%s,%s)",
		c_class_name(idl_class.name),
		string.lower(idl_class.name)
	);
end


--生成xxx_gc函数的代码--
function code_gc(idl_class)
	printfnl("JNI_GC_FUNC(%s,%s)",
		c_class_name(idl_class.name),
		string.lower(idl_class.name)
	);
end

--生成create_java_xxx的代码--
function code_create_java_obj(idl_class)
	printfnl("jobject create_java_%s(JNIEnv* _env,%s *%s, bool _is_weak)",
		string.lower(idl_class.name),
		c_class_name(idl_class.name),
		string.lower(idl_class.name));

	printfnl("{");
	printfnl("    ASSERT(%s);",string.lower(idl_class.name));	
	printfnl("    jclass class_%s = _env->FindClass(\"%s\");",
		string.lower(idl_class.name),
		java_class_path(idl_class.name)
	);
	
	printfnl("    ASSERT(class_%s);",string.lower(idl_class.name));
	printfnl("    jmethodID m_id = _env->GetMethodID(class_%s, \"__dummy\", \"()V\");  ",
		string.lower(idl_class.name));
	printfnl("    ASSERT(m_id);");
	printfnl("    jobject obj = _env->NewObject(class_%s,m_id);",
		string.lower(idl_class.name));
	printfnl("    ASSERT(obj);");
	printfnl("    jfieldID id_obj=_env->GetFieldID(class_%s,\"__obj\",\"L\");",
		string.lower(idl_class.name));
	printfnl("    ");
	printfnl("    CJniObject *jni_obj;");
	printfnl("    NEW(jni_obj,CJniObject);");
	printfnl("    jni_obj->Init();");
	printfnl("    jni_obj->SetLocalObj(%s);",string.lower(idl_class.name));
	printfnl("    jni_obj->SetWeakRef(_is_weak);");
	printfnl("    ");
	printfnl("    _env->SetLongField(obj,id_obj,(jlong)jni_obj);    ");
	printfnl("    return obj;");
	printfnl("}");
end

--生成所有jni函数的代码--
function code_all_jni_functions(idl_class)
    auto_assign_func_id(idl_class);   
    local overrides = {};    
    for_each_functions(idl_class.functions,function(info)        
        if not info.is_callback then                   
            code_normal_jni_function(info);   
        else
            code_callback_jni_function(info);
        end   
    end);
end

--普通的lua函数生成--
function code_normal_jni_function(func_info)
	local thiz_str = ",jobject _thiz";
	if func_info.is_static then thiz_str = "" end
	printfnl("static status_t %s(JNIEnv* _env%s%s)",
		jni_c_func_name(func_info),
		thiz_str,
		jni_param_define_list(func_info.params)
	);
    
    printnl("{");    
    
    if func_info.is_ctor then
    else           
    end
    
    printnl("}");
    printnl("");
end

--生成callback函数调用--
function code_callback_jni_function(func_info)
end

--生成cpp代码--
function code_cpp(idl_class)
	code_includes_cpp(idl_class);
	code_get(idl_class);
	code_gc(idl_class);
	printnl("");
	code_create_java_obj(idl_class);
	code_all_jni_functions(idl_class);
end

function code_java(idl_class)
	printnl("I am java file");
end
