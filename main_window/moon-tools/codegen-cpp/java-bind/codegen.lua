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

function java_method_name(name)
    if string.byte(name,1) == 95 then
        return name;
    end
    return java_function_name(name);
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
                java_type = info[2],
                jni_array_type = info[5],
				jni_array_func_name = info[4],
                jni_type_signature = info[3],
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

--自动给重名的函数分配id--
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

--生成函数返回值类型的列表--
function jni_function_ret_list(func_info)
    local str = "";
    for_each_return_type(func_info.ret_type,function(info)
        if not info.is_array then
            if info.is_basic_type then
                str = str..info.jni_type.jni_type.." ";
            elseif info.is_string then
                str = str.."jstring ";
            else
                str = str.."jobject ";
            end
        else
            if info.is_basic_type then
                str = str..info.jni_type.jni_array_type.." ";
            else
                str = str.."jobjectArray ";
            end
        end
    end)
    return str;
end

--生成jni函数的签名--
function jni_function_signature(func_info)
    local str="(";
    for_each_params(func_info.params,function(info)
        if info.is_array then
            str=str.."[";
        end
        if info.is_basic_type then
            str=str..info.jni_type.jni_type_signature;
        elseif info.is_string then
            str=str.."Ljava/lang/String;";
        else
            str=str.."L"..java_class_path(info.type.name)..";";
        end
    end);

    str=str..")";

    for_each_return_type(func_info.ret_type,function(info)
        if info.is_array then
            str=str.."[";
        end
        if info.is_basic_type then
            str=str..info.jni_type.jni_type_signature;
        elseif info.is_string then
            str=str.."Ljava/lang/String;";
        else
            str=str.."L"..java_class_path(info.type.name)..";";
        end
    end)
    return str;
end

--生成本地方法调用返回值的列表--
function jni_call_ret_list(func_info)
    local str = "";
    local part2 = "";
    for_each_return_type(func_info.ret_type,function(info)
        if info.is_void then return end
        if not info.is_array then
            if info.is_string then
                str = str.."const char* "..info.name;
                part2 = part2.."    ASSERT(_"..info.name..");"..EOL;
                part2 = part2..string.format("    jstring %s = _env->NewStringUTF(_%s);",
                    info.name, info.name
                );
            elseif info.is_basic_type then
                str = str..info.jni_type.jni_type.." _"..info.name;                
            else
                str = str..c_class_name(info.type.name).."* _"..info.name;
                part2 = part2.."    ASSERT(_"..info.name..");"..EOL;
                part2 = part2..string.format("    jobject %s = create_java_%s(_env,_%s,true);",
                   info.name, string.lower(info.type.name),info.name
                );            
            end
        end
    end)
    return str,part2;
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
	printfnl("JNI_GET_OBJ_FUNC(%s,%s)",
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
    printfnl("CREATE_JAVA_OBJ_FUNC(%s,\"%s\")",
        c_class_name(idl_class.name),
        java_class_path(idl_class.name));
end

--生成把参数从jni参数列表中解出来的代码--
function code_extract_params(func_info)
	for_each_params(func_info.params,function(info)
		if info.is_array then
			if info.is_string then
				printfnl("    CMemStk %s;",string.lower(info.name));
				printfnl("    %s.Init();",string.lower(info.name));
				printfnl("    GetStringArrayElements(_env,_%s,&%s);",
					string.lower(info.name),string.lower(info.name));
				printnl("");
			elseif info.is_basic_type then
				printfnl("    %s *%s = (%s*)_env->Get%sElements(_%s,0);",
					info.type.name, string.lower(info.name), info.type.name,
					info.jni_type.jni_array_func_name,string.lower(info.name));
				printfnl("    ASSERT(%s);",string.lower(info.name));
				printfnl("    int %s_len = env->GetArrayLength(_%s);",
					string.lower(info.name),string.lower(info.name));
			else
				printfnl("    int %s_len = 0;",string.lower(info.name));
				printfnl("    %s *%s = GetObjectArrayElements<%s>(_env,%s,&%s_len);",
					c_class_name(info.type.name),string.lower(info.name),
					c_class_name(info.type.name),string.lower(info.name),string.lower(info.name));
				printfnl("    ASSERT(%s);",string.lower(info.name));
			end
		else
			if info.is_string then
				printfnl("    const char *%s = _env->GetStringUTFChars(_%s,NULL);",
					string.lower(info.name),string.lower(info.name));
				printfnl("    ASSERT(%s);",string.lower(info.name));
			elseif info.is_object then
				printfnl("    %s *%s = get_%s(_env,_%s);",
					c_class_name(info.type.name),string.lower(info.name),
					string.lower(info.type.name),string.lower(info.name));
				printfnl("    ASSERT(%s);",string.lower(info.name));
			else
				printfnl("    %s %s = (%s)_%s;",info.type.name, string.lower(info.name),
					info.type.name,string.lower(info.name));
			end
		end
	end);
end

--生成释放局部变量的代码--
function code_release_params(func_info)
    for_each_params(func_info.params,function(info)
        if info.is_array then
            if info.is_object then
                printfnl("    ReleaseObjectArrayElements<%s>(_%s,%s,0);",
                    c_class_name(info.type.name),
                    string.lower(info.name),
                    string.lower(info.name)
                );
            elseif info.is_string then
                --nothing?
            elseif info.is_basic_type then
                printfnl("    _env->Release%sElements(_%s,%s,0);",
                    info.jni_type.jni_array_func_name,
                    string.lower(info.name),
                    string.lower(info.name)
                ); 
            end
        else
            if info.is_string then
                printfnl("    _env->ReleaseStringUTFChars(_%s,%s,0);",
                    string.lower(info.name),
                    string.lower(info.name)
                ); 
            end
        end
    end);
end

--生成jni的构造函数代码--
function code_jni_ctor_function(func_info)
	code_extract_params(func_info);
	printnl("");
	printfnl("    %s *_this = NULL;",c_class_name(func_info.idl_class.name));
	printfnl("    NEW(_this,%s);",c_class_name(func_info.idl_class.name));
    printfnl("    _this->Init(%s);",param_call_list(func_info.params));
    printnl("");
    code_release_params(func_info);
    printfnl("    return OK;");
end

function code_jni_normal_function(func_info)
    if not func_info.is_static then
        printfnl("    %s *_this = get_%s(_env,_this_obj);",
            c_class_name(func_info.idl_class.name),
            string.lower(func_info.idl_class.name)
        );
        printfnl("    ASSERT(_this);");
        printnl("");        
    end

    code_extract_params(func_info);
    printnl("");
    print("    ");
    local call_ret_list,part2 =  jni_call_ret_list(func_info);

    if call_ret_list ~= "" then
        printf("%s = ",call_ret_list);
    end

    if not func_info.is_static then
        printf("_this->");
    else
        printf("%s::",c_class_name(func_info.idl_class.name));
    end

    printfnl("%s(%s);",func_info.name,param_call_list(func_info.params));

    if part2 ~= "" then
        printnl(part2);
    end

    printnl("");
    code_release_params(func_info);
    printnl("");
    if not IdlHelper.Func.IsVoid(func_info) then
        printfnl("    return ret0;");
    end
end

--普通的lua函数生成--
function code_jni_function(func_info)
	local thiz_str = ",jobject _this_obj";
    if func_info.is_static then thiz_str = "" end
    
    printf("static ");
	if func_info.is_ctor then
		printf("jint ");
	else
		print(jni_function_ret_list(func_info));
	end
	printfnl("%s(JNIEnv* _env%s%s)",
		jni_c_func_name(func_info),
		thiz_str,
		jni_param_define_list(func_info.params)
	);
    
    printnl("{");    
    if func_info.is_ctor then
		code_jni_ctor_function(func_info);
    else           
        code_jni_normal_function(func_info);
    end
    
    printnl("}");
    printnl("");
end

--生成callback函数调用--
function code_callback_jni_function(func_info)
end

--生成所有jni函数的代码--
function code_all_jni_functions(idl_class)
    auto_assign_func_id(idl_class);   
    local overrides = {};    
    for_each_functions(idl_class.functions,function(info)        
        if not info.is_callback then                   
            code_jni_function(info);   
        else
            code_callback_jni_function(info);
        end   
    end);
end

--生成native method table的代码--
function code_native_method_table(idl_class)
    printfnl("static const JNINativeMethod %s_native_methods[]={",
        string.lower(idl_class.name));

    printfnl([[    {"_gc","",(void*)%s__gc},]],
        string.lower(idl_class.name)
    );

    for_each_functions(idl_class.functions,function(info)        
        if not info.is_callback then
            printfnl([[    {"%s","%s",(void*)%s},]],
                java_method_name(info.name),
                jni_function_signature(info),
                jni_c_func_name(info)
            );
        end   
    end);
    printfnl("};");
end

--生成register函数的代码--
function code_register(idl_class)
	printfnl("status_t register_%s_native_methods(JNIEnv* env)",string.lower(idl_class.name));
	printfnl("{");
	printfnl("    jclass clazz;");
	printfnl("    clazz = env->FindClass(\"%s\");",java_class_path(idl_class.name));
	printfnl("    ASSERT(clazz);");
	printfnl("    int32_t size = sizeof(%s_native_methods)/sizeof(%s_native_methods[0]);",
		string.lower(idl_class.name),
		string.lower(idl_class.name));
	printfnl("    ASSERT(env->RegisterNatives(clazz, %s_native_methods , size) == JNI_OK);",
		string.lower(idl_class.name));
	printfnl("    return OK;");
	printfnl("}");
end

--生成cpp代码--
function code_cpp(idl_class)
	code_includes_cpp(idl_class);
	code_get(idl_class);
	code_gc(idl_class);
    code_create_java_obj(idl_class);
    printnl("");
    code_all_jni_functions(idl_class);
    printnl("");
    code_native_method_table(idl_class);
	code_register(idl_class);
end

--参数java声明的列表，带类型--
function java_param_define_list(params)
    local pbuf = PrintBuffer.new();
    local n = 0;
    
	for_each_params(params,function(info)
		local arr = "";
		if info.is_array then arr = "[]"; end
		if info.is_string then
			if n > 0 then pbuf:Printf(", "); end
			pbuf:Printf("String%s %s", arr,string.lower(info.name));
			n = n + 1;
		elseif info.is_object then
			if n > 0 then pbuf:Printf(", "); end
			pbuf:Printf("%s%s %s",
				java_class_name(info.type.name),
				arr,string.lower(info.name)
			);
			n = n + 1;
		elseif info.is_basic_type then
			if n > 0 then pbuf:Printf(", "); end
			pbuf:Printf("%s%s %s",
				info.jni_type.java_type,
				arr,string.lower(info.name)
			);
			n = n + 1;
		end		
				
    end);
	
    return pbuf:GetText(),n;
end

--生成java代码的参数调用列表--
function java_param_call_list(func_info)
	local str = "";
	for_each_params(func_info.params,function(info)
		if not info.is_first then
			str = str .. ",";
		end
		str = str..string.lower(info.name);		
	end);
	return str;
end

--生成java ctor函数的代码--
function code_java_ctor_function(func_info)
	printf("    public ");
    local param_def = java_param_define_list(func_info.params);	
	printfnl("%s(%s)",java_class_name(func_info.idl_class.name),param_def);
	printfnl("    {");
	printfnl("        this._new(%s);",java_param_call_list(func_info));
	printfnl("    }");
end

--生成java的函数代码--
function code_java_function(func_info)
	printf("    public native ");
	for_each_return_type(func_info.ret_type,function(info)    
		if info.is_string then
			printf("String");
		elseif info.is_object then
			printf("%s",java_class_name(info.type.name));
		else
			printf("%s",info.jni_type.java_type);
		end
		
		if info.is_array then
			printf("[]");
		end
    end)
	
	local param_def = java_param_define_list(func_info.params);	
	printfnl(" %s(%s);",java_method_name(func_info.name),param_def);
end

function code_java(idl_class)	
	printfnl("package %s;",package_name);
	printnl("");	
	printfnl("public class %s{", java_class_name(idl_class.name));
	printfnl("    private long __obj = 0;");
	printfnl("    private void __dummy(){}");
	printnl("");
	for_each_functions(idl_class.functions,function(info)        
        if not info.is_ctor then            
			code_java_ctor_function(info);
        end   
    end);
	printnl("");
	
	printfnl("    public void destroy()");
	printfnl("    {");
	printfnl("        this._gc();");
	printfnl("    }");
	printnl("");
	printfnl("    protected void finalize()");
	printfnl("    {");
	printfnl("        this.destroy();");
	printfnl("    }");
	printnl("");
	printfnl("    public native void _gc()");

	for_each_functions(idl_class.functions,function(info)        
        if not info.is_callback then            
			code_java_function(info);
        end   
    end);
	
	printnl("}");
end
