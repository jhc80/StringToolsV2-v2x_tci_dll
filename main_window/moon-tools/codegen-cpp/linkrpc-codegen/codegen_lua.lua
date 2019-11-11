--如何转成lua的类名的方法--
function lua_class_name(name)
	return name;
end
-----------------------------------
function begin_lua_marker(name)
    return "--##Begin "..name.." ##--"
end

function end_lua_marker(name)
    return "--##End "..name.." ##--"
end

function begin_lua_extra(name1,name2)
    return "--@@Begin "..name1.." "..name2.." @@--"
end

function end_lua_extra(name1,name2)
    return "--@@End "..name1.." "..name2.." @@--"
end
-----------------------------------
--生成lua 的 onRequest函数代码--
function code_lua_request_function(idl_class)

    printfnl("function %s:OnRequest(_context,_param)",        
        lua_class_name(idl_class.name)
    );
    
    printnl(begin_lua_marker("OnRequest"));
    printnl("    local method = _context.method;");
        
    for_each_functions(idl_class.functions,function(info)
        if info.is_service then
            printfnl("    if method == %s then",func_id_name(idl_class.peer_name,info.name));
            printfnl("        self:%s(_context,_param);",
                service_func_name(info.name)
            );
            printfnl("    end");
        end
    end);    
    printnl(end_lua_marker("OnRequest"));
    printfnl("end");   
end


--生成lua文件头的内容--
function code_lua_header(idl_class)

    printf(long_text([[
        require("common")
        require("peer_service_base")
        require("%s")

        %s = class(PeerServiceBase);

        function %s:ctor()
        end
    ]],8),
        common_cpp_include_name(idl_class.peer_name),
        lua_class_name(idl_class.name),
        lua_class_name(idl_class.name)
    );    
end

--生成lua函数的声明代码--
function code_lua_service_function_declaration(idl_class, info,is_async)
    local func_name;
    if info.is_service then
        func_name = string.upper_first_char(
            service_func_name(info.name)
        );
    else
        func_name = string.upper_first_char(
            not_service_func_name(info.name,is_async)
        );
    end
    
    if info.is_service then
        printf("function %s:%s(_context,_param)",
            lua_class_name(idl_class.name),
            func_name
        );    
    else
        printf("function %s:%s(",
            lua_class_name(idl_class.name),
            func_name
        );    
        
		local param_num = 0;
		if is_async then
			printf("thread");
			param_num = param_num + 1;
		end
		
        for_each_params(info.params,function(p,index)        
            if p.index + param_num > 1  then
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

--生成不是lua service的函数代码--
function code_lua_not_service_function(idl_class,info)    
    code_lua_service_function_declaration(idl_class,info);   
    printnl("");
    
    if not info.is_void then
        printfnl("    local _cbid = self:AddCallback(_callback);");    
    else
        printfnl("    local _cbid = 0;");
    end
        
    if info.params then
        printfnl("    local _param={");
        for_each_params(info.params,function(p,index)        
            printf("        %s = ",p.name);
            printfnl("_%s,",to_lower_underline_case(p.name));
        end);
        printfnl("    };");
    end

    local param_str = info.params and "_param" or "null";
    
    printfnl(
        "    return self:SendRequest(%s,%s,_cbid);",
        param_str,
        func_id_name(idl_class.peer_name,info.name)
    );
        
    printnl("end");
end

--生成不是lua service的Async函数代码--
function code_lua_not_service_async_function(idl_class,info)    
    code_lua_service_function_declaration(idl_class,info,true);   
	printnl("");
	local func_name = string.upper_first_char(
        not_service_func_name(info.name)
    );
	
	printfnl("    local ret = {};");
	printfnl("    local done = false;");
	printfnl("    ");
	printf("    self:%s(",func_name);
	
	for_each_params(info.params,function(p,index) 
		printf("_%s,",to_lower_underline_case(p.name));
	end);
	
	printnl("function(res,val)");
	printfnl("        ret.res = res;");
	printfnl("        ret.val = val;");
	printfnl("        done = true;");
	printfnl("    end);");
	printfnl("    ");
	printfnl("    while not done and not thread:IsDead() do");
	printfnl("        thread:Sleep(1);");
	printfnl("    end");
	printfnl("    ");
	printfnl("    return ret;");
	
    printnl("end");
end


--生成lua service function 的函数体--
function code_lua_service_function(idl_class,info)
    code_lua_service_function_declaration(idl_class,info);
    printnl("");
        
    if not info.is_void then
        printnl("    --local _ret={");        
        for_each_return_type(info.ret_type,function(r)        
            printfnl("    --    %s = ",r.name);
        end);     
        printnl("    --};");
        printfnl("    self:SendReturnValue(_context,_ret);");
    end
    
    printnl("end");
end

--生成lua代码--
function code_lua(idl_class)
    code_lua_header(idl_class);    
    code_lua_request_function(idl_class);
    printnl("");
    for_each_functions(idl_class.functions,function(info)      
        if info.is_service then
            printnl(begin_lua_extra("Method",service_func_name(info.name)));
            code_lua_service_function(idl_class,info);
            printnl(end_lua_extra("Method",service_func_name(info.name)));
        else
            printnl(begin_lua_extra("Method",not_service_func_name(info.name)));
            code_lua_not_service_function(idl_class,info);
            printnl(end_lua_extra("Method",not_service_func_name(info.name)));
			
			if not info.is_void then
				printnl("");
				printnl(begin_lua_extra("Method",not_service_func_name(info.name,true)));
				code_lua_not_service_async_function(idl_class,info);
				printnl(end_lua_extra("Method",not_service_func_name(info.name,true)));
			end
        end                
        printnl("");
    end);        
    printnl("--@@ Insert Method Here @@--");    
end

--生成宏定义的文件--
function code_lua_message_define(idl_class)
    local index = 1;    
    printnl(begin_lua_marker("Messages"));
    for_each_functions(idl_class.functions,function(info)
        if info.is_service then
            printfnl("%s = %d;",
                func_id_name(idl_class.peer_name,info.name),
                idl_class.start_id + index
            );
            index = index + 1;
        end        
    end);            
    printnl(end_lua_marker("Messages"));
end

---生成一个包含所有消息类型require的文件--
function code_common_requires_lua(idl_class)
    printfnl("require (\"%s_messages\")",to_lower_underline_case(idl_class.name));
end


