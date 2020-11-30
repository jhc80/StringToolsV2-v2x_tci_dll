require("common")
require("idl_helper");
require("cpp_base_codegen");
require("idl_helper");

function begin_cpp_marker(name)
    return "/*##Begin "..name.." ##*/"
end

function end_cpp_marker(name)
    return "/*##End "..name.." ##*/"
end

function begin_cpp_extra(name1,name2)
    return "/*@@Begin "..name1.." "..name2.." @@*/"
end

function end_cpp_extra(name1,name2)
    return "/*@@End "..name1.." "..name2.." @@*/"
end

--遍历idl_class中每一个function的迭代器--
function for_each_functions(functions, callback)
    
    if not functions then return end
    local index = 1;
    for _,func in ipairs(functions) do
        
        local info = {};
        info.func = func;
        info.is_void = IdlHelper.Func.IsVoid(func);
        info.ret_type = func.ret_type;
        info.name = func.name;
        info.is_service = IdlHelper.Func.IsService(func);
        info.params = func.params;
        info.index = index;
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
    
    for _, p in ipairs(params) do
        
        local info = {};
        info.param = p;
        info.name = p.name;  
        info.type = p.type;
        info.is_pointer = IdlHelper.Type.IsPointer(p.type);        
        info.is_array,array_size = IdlHelper.Type.IsArray(p.type);
        info.is_string = IdlHelper.Type.IsString(p.type);
		info.java_type = IdlHelper.Type.GetJavaType(p.type);
        info.is_basic_type = IdlHelper.Type.IsBasicType(p.type);        
        info.is_object = not info.is_basic_type;
        info.index = index;
        index = index + 1;
        if callback(info) then
            return true;
        end        
    end
end

--for_each_params的排序版本，按照name排序
function for_each_params_sorted(params, callback)

	local tmp = {};
	for_each_params(params,function(info)
		table.insert(tmp,info);
	end);
	
	table.sort(tmp,function(e1,e2)
		return e1.name < e2.name
	end);
	
	for _,info in ipairs(tmp) do
		if callback(info) then
            return true;
        end   
	end
end


--遍历每一个返回值的迭代器--
function for_each_return_type(ret_types,callback,name_prefix)
    local index = 1;
    
    if not name_prefix then
        name_prefix = "RetVal";
    end
    
    for _, ret in ipairs(ret_types) do
        
        local info = {};
        info.type = ret;
        info.is_pointer = IdlHelper.Type.IsPointer(ret);        
        info.is_array,array_size = IdlHelper.Type.IsArray(ret);
        info.is_string = IdlHelper.Type.IsString(ret);
        info.is_basic_type = IdlHelper.Type.IsBasicType(ret);        
        info.is_object = not info.is_basic_type;
        
        if ret.var_name then
            info.name = ret.var_name;
        else
            info.name = name_prefix..(index-1);
            index = index + 1;
        end

        if callback(info) then
            return true;
        end        
    end
end

--for_each_return_type的排序版本，按照name排序
function for_each_return_type_sorted(ret_types,callback,name_prefix)

	local tmp = {};
	for_each_return_type(ret_types,function(info)
		table.insert(tmp,info);
	end,name_prefix);
	
	table.sort(tmp,function(e1,e2)
		return e1.name < e2.name
	end);
	
	for _,info in ipairs(tmp) do
		if callback(info) then
            return true;
        end   
	end
end

--把函数参数重新变成在参数中的字符串--
function param_to_string(param)
    local str="";

    if param.is_basic_type then
        str = str..param.type.name;
        if param.is_pointer or param.is_array then
            str = str.." *_"..param.name;
        else
            str = str.." _"..param.name;
        end
    elseif param.is_string then
        str = str.."CMem *_"..param.name;
    else
        str = str..c_class_name(param.type.name).." *_"..param.name;
    end
   
    if param.is_array then
         str = str..",int _"..param.name.."_len";
    end
   
    return str;    
end

--生成函数的声明代码--
function code_service_function_declaration(info,class_prefix)

    if not class_prefix then
        class_prefix="";
    end
    
    local func_name;
    if info.is_service then
        func_name = service_func_name(info.name);
    else
        func_name = not_service_func_name(info.name);
    end
    
    if info.is_service then
        printf("status_t %s%s(CPeerMessage *_message)",
            class_prefix,
            func_name
        );    
    else
        printf("status_t %s%s(",
            class_prefix,
            func_name
        );    
        
        for_each_params(info.params,function(p,index)        
            if p.index > 1 then
                print(", ");
            end
            printf(param_to_string(p));
        end);
        
        if not info.is_void then
            if info.params then
                print(", ");
            end
            print("CClosure *_callback");        
        end
                
        printf(")");        
    end
end

--生成头文件代码--
function code_h(idl_class)
    local peer_name = IdlHelper.peer_name;
    
    printfnl("#ifndef __%s_H",to_upper_underline_case(idl_class.name));
    printfnl("#define __%s_H",to_upper_underline_case(idl_class.name));
    
    print(long_text([[   
        #include "mem.h"
        #include "memfile.h"
        #include "rpc_service_base.h"
        #include "rpc_call_context.h"
    ]],8));
    
    
    local class_name = c_class_name(idl_class.name);
    
    printf(long_text([[
        class %s:public CRpcServiceBase{
        
        public:
            %s();
            virtual ~%s();

            status_t InitBasic();
            status_t Init(CTaskMgr *mgr);
            status_t Destroy();    
            virtual status_t OnSocketConnected();
            virtual status_t OnSocketDisconnected();
            virtual status_t OnRequest(CPeerMessage *msg);
    ]],8),
        class_name,
        class_name,
        class_name        
    );    
    
    printnl(begin_cpp_marker("ServiceFunctions_H"));

    for_each_functions(idl_class.functions,function(info)
       printf("    ");
       code_service_function_declaration(info);       
       printnl(";");       
    end);

    printnl(end_cpp_marker("ServiceFunctions_H"));
    
    printfnl(long_text([[
        };
        
        #endif
    
    ]],8));    
end


--把函数参数idl字符串--
function param_to_idl(param)
    local str="";

    if param.is_array then    
        str = str.."array<";    
    end

	if param.type.namespace then
		str = str..param.type.namespace.."::";
	end
	
    str = str..param.type.name;
    
    if param.is_array then    
        if param.type.array_size then
            str = str..","..param.type.array_size;
        end
        str = str..">";    
    end
    
    str = str.." ";
    
    if param.is_pointer then
        str = str.."*";
    end
    
    str = str..param.name;
   
    return str;    
end

--生成单个参数的idl代码--
function code_single_param_idl(peer_name,info)
    local class_name = param_class_name(peer_name,info.name);
    printnl("[CodeSwitch code_mark=true,bson=true]");
    printfnl("class %s:RpcParamBase{",class_name);
    for_each_params(info.params,function(p)
        print("    ");
        print(param_to_idl(p));
        printnl(";");
    end);
    
    printfnl("}");
    printnl("");
end

--生成单个返回值的idl代码--
function code_single_return_idl(peer_name,info)
    local class_name = return_class_name(peer_name,info.name);
    printnl("[CodeSwitch code_mark=true,bson=true]");
    printfnl("class %s:RpcParamBase{",class_name);
    
    for_each_return_type(info.ret_type,function(ret)
        print("    ");
        print(param_to_idl(ret));
        printnl(";");
    end);
    
    printfnl("}");
    printnl("");
end

--重新生成函数参数的idl代码--
function code_idl(idl_class)
    for_each_functions(idl_class.functions,function(info)
        if info.is_service and info.params then            
            code_single_param_idl(idl_class.peer_name,info);            
        end
        
        if info.is_service and not info.is_void then
            code_single_return_idl(idl_class.peer_name,info);
        end        
    end);
end

--生成通用的cpp include的头文件名--
function common_cpp_include_name(name)
    return to_lower_underline_case("linkrpc_"..name.."_types");
end

--生成c++的代码的第一部分--
function code_cpp_header(idl_class)

printf(long_text([[
#include "%s.h"
#include "syslog.h"
#include "mem_tool.h"
#include "%s.h"

%s::%s()
{
    this->InitBasic();
}

%s::~%s()
{
    this->Destroy();
}

status_t %s::InitBasic()
{
    CRpcServiceBase::InitBasic();
    return OK;
}

status_t %s::Init(CTaskMgr *mgr)
{
    this->InitBasic();
    CRpcServiceBase::Init(mgr);

    return OK;
}

status_t %s::Destroy()
{
    CRpcServiceBase::Destroy();
    this->InitBasic();
    return OK;
}

status_t %s::OnSocketConnected()
{
    return OK;
}

status_t %s::OnSocketDisconnected()
{
    return OK;
}

]]),
to_lower_underline_case(idl_class.name),
common_cpp_include_name(idl_class.peer_name),
c_class_name(idl_class.name),c_class_name(idl_class.name),
c_class_name(idl_class.name),c_class_name(idl_class.name),
c_class_name(idl_class.name),
c_class_name(idl_class.name),
c_class_name(idl_class.name),
c_class_name(idl_class.name),
c_class_name(idl_class.name),
c_class_name(idl_class.name)
); 
end

--生成service function 的函数体--
function code_service_function(idl_class,info)
    local prefix = c_class_name(idl_class.name).."::";    
    code_service_function_declaration(info,prefix);

    printnl("");
    printnl("{");    
    printnl("    ASSERT(_message);");
    local param_class_name = c_class_name(param_class_name(
        idl_class.peer_name,info.name
    ));
    
    if info.params then
        printf(long_text([[
            %s _param;
            _param.Init();
            ASSERT( _param.LoadBson(_message->GetBody()) );]]
        ,8),param_class_name);
    end
    
    printfnl("    ///////////////");
  
    if not info.is_void then
        printf(long_text([[
            ///////////////
            CRpcCallContext _context;
            _context.Init();
            _context.FromPeerMessage(_message); 
            ]],8)
        );    
    
        printfnl("    %s _ret;",c_class_name(return_class_name
            (idl_class.peer_name,info.name
        )));
        
        printfnl("    _ret.Init();");
            
        for_each_return_type(info.ret_type,function(r)        
            printfnl("    //_ret.%s();",
                param_set_func_name(r.name)
            );        
        end); 
        printfnl("    this->SendReturnValue(&_context,&_ret);");        
    end
    
    printfnl("    return OK;");
        
    printnl("}");
end

--生成不是service的函数代码--
function code_not_service_function(idl_class,info)    
    local prefix = c_class_name(idl_class.name).."::";    
    code_service_function_declaration(info,prefix);   
    printnl("");
    printnl("{");
    
    if info.params then
        printfnl("    %s _param;",c_class_name(param_class_name(
            idl_class.peer_name,info.name
        )));

        printfnl("    _param.Init();");
        
        for_each_params(info.params,function(p)     
            printf("    _param.%s(",param_set_func_name(p.name));                
            if p.is_array then
                printf("_%s, _%s_len",p.name,p.name);
            else
                printf("_%s",p.name);
            end        
            printfnl(");");
        end);
    end
    
    if not info.is_void then
        printfnl("    int _cbid = this->AddCallback(_callback);");    
    else
        printfnl("    int _cbid = 0;");
    end

    local param_str = info.params and "&_param" or "NULL";
    
    printfnl(
        "    return this->SendRequest(%s,%s,_cbid);",
        param_str,
        func_id_name(idl_class.peer_name,info.name)
    );
        
    printnl("}");
end

function code_request_function(idl_class)

    printfnl("status_t %s::OnRequest(CPeerMessage *_message)",
        c_class_name(idl_class.name)
    );
    
    printfnl("{");
    
    printfnl("    ASSERT(_message);");
    
    printnl("");
    printfnl("    int method = _message->GetFunc();");
    printfnl("    this->SetDestPeerName(_message->GetFrom());");
    printnl("");

    printnl(begin_cpp_marker("OnRequest_Cpp"));

    printfnl("    switch(method)");
    printfnl("    {");
    
    for_each_functions(idl_class.functions,function(info)
        if info.is_service then
            printfnl("        case %s:",func_id_name(idl_class.peer_name,info.name));
            printfnl("            this->%s(_message);",service_func_name(info.name));
            printfnl("            break;");
        end
    end);
    
    printfnl("        default:");
    printfnl("            XLOG(LOG_MODULE_USER,LOG_LEVEL_ERROR,");
    printnl("                \"unknown method: %d\",method");
    printfnl("            );");    
    printfnl("            break;");
    printfnl("    }");
    
    printnl(end_cpp_marker("OnRequest_Cpp"));

    printfnl("    return OK;");
    printfnl("}");   
end

--生成c++代码--
function code_cpp(idl_class)
    code_cpp_header(idl_class);        
    code_request_function(idl_class);
    printnl("");
    for_each_functions(idl_class.functions,function(info)
        
        if info.is_service then
            printnl(begin_cpp_extra("Function",service_func_name(info.name)));
            code_service_function(idl_class,info);
            printnl(end_cpp_extra("Function",service_func_name(info.name)));
        else
            printnl(begin_cpp_extra("Function",not_service_func_name(info.name)));
            code_not_service_function(idl_class,info);
            printnl(end_cpp_extra("Function",not_service_func_name(info.name)));			
        end        
        
        printnl("");
    end);        

    printnl("/*@@ Insert Function Here @@*/");
end

--生成宏定义的头文件--
function code_message_define_h(idl_class)
    printfnl("#ifndef __%s_MESSAGE_H",to_upper_underline_case(idl_class.name));    
    printfnl("#define __%s_MESSAGE_H",to_upper_underline_case(idl_class.name));
    printnl("");
    
    printnl(begin_cpp_marker("Messages_H"));

    local index = 1;
    for_each_functions(idl_class.functions,function(info)
        if info.is_service then
            printfnl("#define %s %d",
                func_id_name(idl_class.peer_name,info.name),
                idl_class.start_id + index
            );
            index = index + 1;
        end        
    end);        
    
    printnl(end_cpp_marker("Messages_H"));

    printnl("");
    printfnl("#endif");
end

---生成一个包含所有参数的include文件
function code_common_includes(idl_class)
    printfnl("#include \"%s_messages.h\"",to_lower_underline_case(idl_class.name));

    for_each_functions(idl_class.functions,function(info)
        if info.is_service and info.params then            
            local class_name = param_class_name(idl_class.peer_name,info.name);
            printfnl("#include \"%s.h\"",to_lower_underline_case(class_name));
        end
        
        if info.is_service and not info.is_void then
            local class_name = return_class_name(idl_class.peer_name,info.name);
            printfnl("#include \"%s.h\"",to_lower_underline_case(class_name));        
        end
    end);
end


