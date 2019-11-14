--如何转成js的类名的方法--
function js_class_name(name)
	return name;
end

function begin_js_marker(name)
    return "/*##Begin "..name.." ##*/"
end

function end_js_marker(name)
    return "/*##End "..name.." ##*/"
end

function begin_js_extra(name1,name2)
    return "/*@@Begin "..name1.." "..name2.." @@*/"
end

function end_js_extra(name1,name2)
    return "/*@@End "..name1.." "..name2.." @@*/"
end

------------------------------------
--生成js 的 onRequest函数代码--
function code_js_request_function(idl_class)

    printfnl("onRequest(_context,_param)",
        js_class_name(idl_class.name)
    );
    
    printfnl("{");    
    printnl("");
    
    printnl(begin_js_marker("Request"));
    
    printfnl("    switch(_context.method)");
    printfnl("    {");
    
    for_each_functions(idl_class.functions,function(info)
        if info.is_service then
            printfnl("        case %s:",func_id_name(idl_class.peer_name,info.name));
            printfnl("            this.%s(_context,_param);",
                string.lower_first_char(service_func_name(info.name))
            );
            printfnl("            break;");
        end
    end);
    
    printfnl("        default:");
    printfnl("            console.error(");
    printnl("                \"unknown method: \"+_context.method");
    printfnl("            );");    
    printfnl("            break;");
    printfnl("    }");    
    
    printnl(end_js_marker("Request"));
    
    printfnl("}");   
end


--生成js文件头的内容--
function code_js_header(idl_class)

    printf(long_text([[
        "use strict";
        
        class %s extends PeerServiceBase{

        constructor()
        {
            super();
        }        
    ]],8),
        js_class_name(idl_class.name)
    );    
end

--生成js函数的声明代码--
function code_js_service_function_declaration(info,is_async)
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
        printf("%s(_context,_param)",func_name);    
    else
		if is_async then
			print("async ");
		end
        printf("%s(",func_name); 
        for_each_params(info.params,function(p,index)        
            if p.index > 1 then
                print(", ");
            end
            printf("_%s",to_lower_underline_case(p.name));
        end);
        
        if not info.is_void and not is_async then
            if info.params then
                print(", ");
            end
            print("_callback");        
        end
                
        printf(")");        
    end
end

--生成不是js service的函数代码--
function code_js_not_service_function(idl_class,info)    
    code_js_service_function_declaration(info);   
    printnl("");
    printnl("{");
    
    if not info.is_void then
        printfnl("    let _cbid = this.addCallback(_callback);");    
    else
        printfnl("    let _cbid = 0;");
    end
        
    if info.params then
        printfnl("    let _param={");
        for_each_params(info.params,function(p,index)        
            printf("        %s : ",p.name);
            printfnl("_%s,",to_lower_underline_case(p.name));
        end);
        printfnl("    };");
    end

    local param_str = info.params and "_param" or "null";
    
    printfnl(
        "    return this.sendRequest(%s,%s,_cbid);",
        param_str,
        func_id_name(idl_class.peer_name,info.name)
    );
        
    printnl("}");
end

--生成不是js service的函数ASync代码--
function code_js_not_service_async_function(idl_class,info)
	code_js_service_function_declaration(info,true);   
	printnl("");
	printnl("{");
	
	local func_name = string.lower_first_char(
            not_service_func_name(info.name)
    );

	local async_func_name = string.lower_first_char(
            not_service_func_name(info.name,true)
    );
	
	printfnl("   return new Promise((resolve,reject)=>{        ");
	printf("        this.%s(",func_name);
	
	for_each_params(info.params,function(p,index)        
		printf("_%s,",to_lower_underline_case(p.name));
	end);
		
	printfnl("(res,val)=>{");
	printfnl("            let ret={result:res,value:val};");
	printfnl("            if(Common.Success(res))");
	printfnl("                resolve(ret);");
	printfnl("            else");
	printfnl("                reject(\"%s rejected: \"+res);",async_func_name);
	printfnl("        });");
	printfnl("    });");
	
	printnl("}");
end

--生成js service function 的函数体--
function code_js_service_function(idl_class,info)
    code_js_service_function_declaration(info);
    printnl("");
    printnl("{");        
        
    if not info.is_void then
        printnl("    //let _ret={");        
        for_each_return_type(info.ret_type,function(r)        
            printfnl("    //    %s:",r.name);
        end);     
        printnl("    //};");
        printfnl("    this.sendReturnValue(_context,_ret);");
    end
    
    printnl("}");
end

--生成js代码--
function code_js(idl_class)
    code_js_header(idl_class);    
    code_js_request_function(idl_class);
    printnl("");
    for_each_functions(idl_class.functions,function(info)        
        if info.is_service then
            printnl(begin_js_extra("Method",service_func_name(info.name)));
            code_js_service_function(idl_class,info);
            printnl(end_js_extra("Method",service_func_name(info.name)));
        else
            printnl(begin_js_extra("Method",not_service_func_name(info.name)));
            code_js_not_service_function(idl_class,info);
            printnl(end_js_extra("Method",not_service_func_name(info.name)));
		
			printnl("");		
			if not info.is_void then
				printnl(begin_js_extra("Method",not_service_func_name(info.name,true)));
				code_js_not_service_async_function(idl_class,info);
				printnl(end_js_extra("Method",not_service_func_name(info.name,true)));						
			end
        end        
        
        printnl("");
    end);        
    
    printnl("/*@@ Insert Method Here @@*/");
    
    printnl("");
    printnl("}");
end

--生成宏定义的文件--
function code_js_message_define(idl_class)
    local index = 1;
    printnl(begin_js_marker("Messages"));
        
    for_each_functions(idl_class.functions,function(info)
        if info.is_service then
            printfnl("const %s = %d;",
                func_id_name(idl_class.peer_name,info.name),
                idl_class.start_id + index
            );
            index = index + 1;
        end        
    end);            
    
    printnl(end_js_marker("Messages"));
end
