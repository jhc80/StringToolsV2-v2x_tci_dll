--如何转成java的类名的方法--
function java_class_name(name)
	return name;
end

function java_function_name(name)
	return string.lower_first_char(name);
end

function begin_java_marker(name)
    return "/*##Begin "..name.." ##*/"
end

function end_java_marker(name)
    return "/*##End "..name.." ##*/"
end

function begin_java_extra(name1,name2)
    return "/*@@Begin "..name1.." "..name2.." @@*/"
end

function end_java_extra(name1,name2)
    return "/*@@End "..name1.." "..name2.." @@*/"
end

------------------------------------
--生成java 的 onRequest函数代码--
function code_java_request_function(idl_class)

    printfnl("public boolean onRequest(RpcCallContext _context,RpcParamBase _param)",
        java_class_name(idl_class.name)
    );
    
    printfnl("{");    
	printfnl("    this.setDestPeerName(_context.from);");
	printnl("");
	
    printnl(begin_java_marker("Request"));
    
    printfnl("    switch(_context.method)");
    printfnl("    {");
    
    for_each_functions(idl_class.functions,function(info)
        if info.is_service then
            printfnl("        case %s.%s:",
				java_class_name(idl_class.name.."Messages"),
				func_id_name(idl_class.peer_name,info.name));
				
            printfnl("            this.%s(_context,_param);",
                string.lower_first_char(service_func_name(info.name))
            );
            printfnl("            break;");
        end
    end);
    
    printfnl("        default:");
    printfnl("            Log.e(\"linkrpc\",");
    printnl("                \"unknown method: \"+_context.method");
    printfnl("            );");    
    printfnl("            break;");
    printfnl("    }");    
    
    printnl(end_java_marker("Request"));
    
    printfnl("}");   
end


--生成java文件头的内容--
function code_java_header(idl_class)

    printf(long_text([[
        package %s;

        import com.android.log;
        import com.cvtest.common.PeerServiceBase;
        import com.cvtest.common.RpcParamBase;
		
        public class %s extends PeerServiceBase{

        %s()
        {
            super();
        }        
    ]],8),
		java_package_name(idl_class.peer_name),
        java_class_name(idl_class.name),
		java_class_name(idl_class.name)
    );    
end

--生成java函数的声明代码--
function code_java_service_function_declaration(info,is_async)
    local func_name;
    if info.is_service then
        func_name = string.lower_first_char(
            service_func_name(info.name)
        );
    else
        func_name = string.lower_first_char(
            not_service_func_name(info.name,is_async)
        );
    end
    
    if info.is_service then
        printf("%s(RpcCallContext _context,MiniBson _msg_body)",func_name);    
    else
        printf("%s(",func_name); 
        for_each_params(info.params,function(p,index)        
            if p.index > 1 then
                print(",");
            end
			
			if p.is_string then
				printf("string");			
			elseif p.is_basic_type then
				printf("%s",p.java_type);
			elseif p.is_object then
				printf("%s", java_class_name(p.type.name));
			end
			
			if p.is_array then
				printf("[]");
			end
			
            printf(" _%s",to_lower_underline_case(p.name));
        end);
        
        if not info.is_void and not is_async then
            if info.params then
                print(", ");
            end
            print("Callback _callback");        
        end
                
        printf(")");        
    end
end

--生成不是java service的函数代码--
function code_java_not_service_function(idl_class,info)    
	printf("public boolean ");
    code_java_service_function_declaration(info);   
    printnl("");
    printnl("{");
    
    if info.params then
		local param_cls_name = java_class_name(
			param_class_name(idl_class.peer_name,info.name)
		);
		
        printfnl("    %s _param = new %s();",param_cls_name,param_cls_name);
        
        for_each_params(info.params,function(p)     
            printf("    _param.%s(",java_function_name(param_set_func_name(p.name)));
            printf("_%s",p.name);
            printfnl(");");
        end);
    end
    
    if not info.is_void then
        printfnl("    int _cbid = this.addCallback(_callback);");    
    else
        printfnl("    int _cbid = 0;");
    end

    local param_str = info.params and "_param" or "null";
    
    printfnl(
        "    return this.sendRequest(%s,%s.%s,_cbid);",
        param_str,
		java_class_name(idl_class.name.."Messages"),
        func_id_name(idl_class.peer_name,info.name)
    );
        
    printnl("}");
end

--生成java service function 的函数体--
function code_java_service_function(idl_class,info)
	printf("public boolean ");	
    code_java_service_function_declaration(info);
    printnl("");
    printnl("{");        
        
    local param_class_name = java_class_name(
		param_class_name(idl_class.peer_name,info.name)
	);
    
    if info.params then
        printf(long_text([[
            %s _param = new %s();
            if(!_param.LoadBson(_msg_body))
            {
                Log.e("rpc","load params fail %s");
                return false;
            }
        ]]
        ,8),param_class_name,param_class_name,param_class_name);
    end
    
    printfnl("    ///////////////");
  
    if not info.is_void then
		local ret_class_name = java_class_name(
			return_class_name(idl_class.peer_name,info.name)
		);
        printfnl("    %s _ret  = new %s();",ret_class_name,ret_class_name);
                    
        for_each_return_type(info.ret_type,function(r)        
            printfnl("    //_ret.%s();",
                java_function_name(param_set_func_name(r.name))
            );        
        end); 
        printfnl("    this.sendReturnValue(_context,_ret);");        
    end
    
    printfnl("    return true;");
    
    printnl("}");
end

--生成java代码--
function code_java(idl_class)
    code_java_header(idl_class);    
    code_java_request_function(idl_class);
    printnl("");
    for_each_functions(idl_class.functions,function(info)        
        if info.is_service then
            printnl(begin_java_extra("Method",service_func_name(info.name)));
            code_java_service_function(idl_class,info);
            printnl(end_java_extra("Method",service_func_name(info.name)));
        else
            printnl(begin_java_extra("Method",not_service_func_name(info.name)));
            code_java_not_service_function(idl_class,info);
            printnl(end_java_extra("Method",not_service_func_name(info.name)));
        end        
        
        printnl("");
    end);        
    
    printnl("/*@@ Insert Method Here @@*/");
    
    printnl("");
    printnl("}");
end

--生成宏定义的文件--
function code_java_message_define(idl_class)
    local index = 1;
	
	printfnl("package %s;",java_package_name(idl_class.peer_name));
	printfnl("");
	printfnl("public class %s{",java_class_name(idl_class.name.."Messages"));
	
    printnl(begin_java_marker("Messages"));
        
    for_each_functions(idl_class.functions,function(info)
        if info.is_service then
            printfnl("    public final static int %s = %d;",
                func_id_name(idl_class.peer_name,info.name),
                idl_class.start_id + index
            );
            index = index + 1;
        end        
    end);            
    
    printnl(end_java_marker("Messages"));
	printfnl("}");
end