require("common")
require("idl_helper");
require("print_buffer");

function lualib_file_name(name,is_upper)
    return "lualib_"..string.lower(name);
end

function lua_c_func_name(info)
    return string.lower(info.idl_class.name).."_"..
        string.lower(info.name);
end

function c_type_to_lua_type(c_type_name)
	for _,b in ipairs(basic_type_table) do	
		if c_type_name == b[1] then
			return b[2];
		end
	end	
end

function get_lua_type_info(lua_type_name)
    for _,info in ipairs(lua_type_table) do    
        if info[1] == lua_type_name then
                
            local tab = {
                lua_type = info[1],
                lua_c_type = info[2],
                lua_push_func = info[3],
                lua_to_func = info[4],
                lua_array_type = info[5],
                lua_is_func = info[6],
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
            info.name = "new";
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
            info.lua_type = get_lua_type_info(
                c_type_to_lua_type(info.type.name)
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
        
        info.lua_type = get_lua_type_info(
            c_type_to_lua_type(info.type.name)
        );
               
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
function param_define_list(params)
    local str="";    
    local n = 0;
    for_each_params(params,function(info)      
        if info.is_array then
            if info.is_basic_type then
                str = str..", "..info.type.name.." *";
                str = str..string.lower(info.name);
                str = str..", int "..string.lower(info.name).."_len";
                n = n + 1;
            end
        else
            if info.is_string then
                str = str..", "..info.lua_type.lua_c_type.." ";
                str = str..string.lower(info.name);
                n = n + 1;
            elseif info.is_object then
                str = str..", "..c_class_name(info.type.name).." *";
                str = str..string.lower(info.name);
                n = n + 1;
            elseif info.is_basic_type then
                str = str..", "..info.type.name.." ";
                str = str..string.lower(info.name);
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
------------------------------------------------------------------------------
------------------------------------------------------------------------------
--生成头文件--
function code_h(idl_class)
    local lower_class_name = string.lower(idl_class.name);
    local upper_class_name = string.upper(idl_class.name);
    printfnl("#ifndef __LUALIB_%s_H",upper_class_name);
    printfnl("#define __LUALIB_%s_H",upper_class_name);
    printfnl("");

    printfnl("#include \"%s.h\"",to_file_name(idl_class.name));
    printfnl("#include \"luavm.h\"");
    printfnl("");

    printfnl("#define LUA_USERDATA_%s \"lua_userdata_%s\"",upper_class_name,lower_class_name);
    printfnl("");
    printfnl("%s* get_%s(lua_State *L, int idx);",c_class_name(idl_class.name),lower_class_name);
    printfnl(
        "lua_userdata *%s_new_userdata(lua_State *L,%s *pobj,int is_weak);",
        lower_class_name,c_class_name(idl_class.name)
    );

    printfnl("int luaopen_%s(lua_State *L);",lower_class_name);
    printfnl("bool is_%s(lua_State *L, int idx);",lower_class_name);
    printfnl("const luaL_Reg* get_%s_funcs();",lower_class_name);

    printfnl("");
    printfnl("#endif");
end


--生成is_xxx的代码--
function code_is(idl_class)
    local sub_classes_str="";
    local sub_classes = IdlHelper.Class.GetAllSubClasses(idl_class);

    if sub_classes then
        sub_classes_str = sub_classes_str..EOL;
        for i,str in ipairs(sub_classes) do
            sub_classes_str = sub_classes_str..
                (i>1 and EOL or "")..
                "        LUA_USERDATA_"..
                string.upper(str)..
                ",";
        end
    end

    printf(long_text([[
        bool is_%s(lua_State *L, int idx)
        {        
            const char* ud_names[] = {
                LUA_USERDATA_%s,%s
            };            
            lua_userdata *ud = NULL;
            for(size_t i = 0; i < sizeof(ud_names)/sizeof(ud_names[0]); i++)
            {
                ud = (lua_userdata*)luaL_testudata(L, idx, ud_names[i]);
                if(ud)break;
            }
            return %s_is_userdata_valid(ud);  
        }
    ]],8),
        string.lower(idl_class.name),
        string.upper(idl_class.name),sub_classes_str,
        string.lower(idl_class.name)
    );  
end

--生成xxx_is_userdata_valid函数的代码--
function code_is_userdata_valid(idl_class)
	printfnl("LUA_IS_VALID_USER_DATA_FUNC(%s,%s)",
		c_class_name(idl_class.name),
		string.lower(idl_class.name)
	);
	
end

--生成get_xxx函数的代码--
function code_get(idl_class)
	printfnl("LUA_GET_OBJ_FROM_USER_DATA_FUNC(%s,%s)",
		c_class_name(idl_class.name),
		string.lower(idl_class.name)
	);
end


--生成xxx_gc函数的代码--
function code_gc(idl_class)
	printfnl("LUA_GC_FUNC(%s,%s)",
		c_class_name(idl_class.name),
		string.lower(idl_class.name)
	);
end


--生成xxx_new_userdata函数的代码--
function code_new_userdata(idl_class)
	printfnl("LUA_NEW_USER_DATA_FUNC(%s,%s,%s)",
		c_class_name(idl_class.name),
		string.lower(idl_class.name),
		string.upper(idl_class.name)
	);
end


--生成xxx_is_same函数的代码--
function code_is_same(idl_class)
	printfnl("LUA_IS_SAME_FUNC(%s,%s,%s)",
		c_class_name(idl_class.name),
		string.lower(idl_class.name),
		string.upper(idl_class.name)
	);
end

--生成xxx_to_string函数的代码--
function code_to_string(idl_class)
  	printfnl("LUA_TO_STRING_FUNC(%s,%s,%s)",
		c_class_name(idl_class.name),
		string.lower(idl_class.name),
		string.upper(idl_class.name)
	);
end

--生成xxx_new函数的代码--
function code_new(idl_class)
    printf(long_text([[
        static int %s_new_(lua_State *L)
        {
            %s *pt;
            NEW(pt,%s);
            pt->Init();
            %s_new_userdata(L,pt,0);
            return 1;
        }
    ]],8),
        string.lower(idl_class.name),
        c_class_name(idl_class.name),
        c_class_name(idl_class.name),
        string.upper(idl_class.name)
    );
end

--生成函数表的代码--
function code_funcs_table(idl_class)
    
    printf(long_text([[
        static const luaL_Reg %s_funcs_[] = {
            {"__gc",%s_gc_},
            {"__tostring",%s_tostring_},
            {"__is_same",%s_issame_},]],8),
        string.lower(idl_class.name),    
        string.lower(idl_class.name),
        string.lower(idl_class.name),
        string.lower(idl_class.name),
        string.lower(idl_class.name)
    );

    local funcs={};

    for_each_functions(idl_class.functions,function(info)
        if not info.is_callback then
            if not funcs[info.name] then
                funcs[info.name] = 1;
                printfnl("    {\"%s\",%s},",info.name,lua_c_func_name(info));
            end
        end
    end);
    printfnl("    {NULL,NULL},");
    printfnl("};");
end

--生成 get_funcs的代码--
function code_get_functions(idl_class)
    printf(long_text([[
        const luaL_Reg* get_%s_funcs()
        {
            return %s_funcs_;
        }
        ]],8),
        string.lower(idl_class.name),    
        string.lower(idl_class.name)
    );
end

--生成XXX_register的函数代码--
function code_register(idl_class)
 
    printf(long_text([[
        static int luaL_register_%s(lua_State *L)
        {	
            static luaL_Reg _%s_funcs_[MAX_LUA_FUNCS];
            int _index = 0;        
    ]],8),
        string.lower(idl_class.name),        
        string.lower(idl_class.name)
    );

    local all_bases = IdlHelper.Class.GetAllBases(idl_class);
    if all_bases then
        for _,base in ipairs(all_bases) do
            printfnl("    "..
                "CLuaVm::CombineLuaFuncTable(_%s_funcs_,&_index,get_%s_funcs(),false);",
                string.lower(idl_class.name),string.lower(base.name)
            );
        end
    end

    printfnl("    "..
        "CLuaVm::CombineLuaFuncTable(_%s_funcs_,&_index,get_%s_funcs(),true);",
        string.lower(idl_class.name),string.lower(idl_class.name)
    );
    printnl("");

    printf(long_text([[
        luaL_newmetatable(L, LUA_USERDATA_%s);
        lua_pushvalue(L, -1);	
        lua_setfield(L, -2, "__index");	
        luaL_setfuncs(L,_%s_funcs_,0);	
        lua_pop(L, 1);
        luaL_newlib(L,_%s_funcs_);
        return 1;
    }        
    ]],4),
        string.upper(idl_class.name),
        string.lower(idl_class.name),
        string.lower(idl_class.name)
    );  
end

--生成XXX_open函数的代码--
function code_open(idl_class)
    printf(long_text([[
        int luaopen_%s(lua_State *L)
        {
            luaL_requiref(L, "%s",luaL_register_%s,1);
            lua_pop(L, 1);
            return 0;
        }        
        ]],8),
        string.lower(idl_class.name),    
        idl_class.name, string.lower(idl_class.name)
    );
end

--生成所有的include代码--
function code_includes_cpp(idl_class)
    printfnl("#include \"%s.h\"",lualib_file_name(idl_class.name))
    printnl("#include \"mem_tool.h\"");
    printnl("#include \"syslog.h\"");

    local includes = IdlHelper.Class.CollectAllIncludes(idl_class);

    for name in pairs(includes) do
        printfnl("#include \"%s.h\"",lualib_file_name(name));
    end
    
    printnl("");
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

--把函数的参数一个个从lua解出来的代码--
function code_function_params_from_lua(func_info)
   local param_index = 1;
    
    if not func_info.is_static then
        printfnl(
            "    %s *p%s = get_%s(L,%d);",
            c_class_name(func_info.idl_class.name),
            string.lower(func_info.idl_class.name),
            string.lower(func_info.idl_class.name),
            param_index
        );        
        param_index = param_index + 1;                        
        printfnl("    ASSERT(p%s);",string.lower(func_info.idl_class.name));
    end
        
    local function pc_not_array_basic_type(info)
        printfnl("    %s %s = (%s)%s(L,%d);",
            info.type.name, string.lower(info.name),
            info.type.name,info.lua_type.lua_to_func,
            param_index
        );  
    end
    
    local function pc_not_array_string(info)
        printfnl("    %s %s = (%s)%s(L,%d);",
            info.lua_type.lua_c_type, string.lower(info.name),
            info.lua_type.lua_c_type,info.lua_type.lua_to_func,
            param_index
        );  
        printfnl("    ASSERT(%s);",string.lower(info.name));
    end
    
    local function pc_not_array_object(info)
        printfnl("    %s *%s = get_%s(L,%d);",
            c_class_name(info.type.name),
            string.lower(info.name),
            string.lower(info.type.name),param_index            
        );
        printfnl("    ASSERT(%s);",string.lower(info.name));
    end    

    local function pc_array_basic_type(info)
        printfnl("    %s %s[1024];",
            info.type.name,
            string.lower(info.name)
        );
        
        printfnl("    int %s_len = 1024;",
            string.lower(info.name)
        );        
        
        printfnl("    CLuaVm::To%sArray(L,%d,%s,&%s_len);",
            info.lua_type.lua_array_type,
            param_index,
            string.lower(info.name),
            string.lower(info.name)
        );
    end

    local function pc_array_string(info)
        printfnl("    CMemStk %s;",
            string.lower(info.name)
        );
        
        printfnl("    %s.Init(1024);",
            string.lower(info.name)
        );
        
        printfnl("    CLuaVm::To%sArray(L,%d,&%s);",
            info.lua_type.lua_array_type,
            param_index,
            string.lower(info.name)
        );
    end
    
    function pc_callback(info)
        printfnl("    int %s = CLuaVm::ToFunction(L,%d);",
            string.lower(info.name),           
            param_index
        ); 
    end

    for_each_params(func_info.params,function(info)        
        if info.is_array then       
            if info.is_string then
                pc_array_string(info);
            elseif info.is_basic_type then
                pc_array_basic_type(info);
            end
        else
            if info.is_callback then
                pc_callback(info);
            elseif info.is_string then
                pc_not_array_string(info);
            elseif info.is_object then
                pc_not_array_object(info);
            elseif info.is_basic_type then            
                pc_not_array_basic_type(info);
            end
        end            
        param_index = param_index + 1;    
    end);  
end

--生成函数返回值的列表--
function code_return_val_list(rets)
    local n = 0;      
    
    local function pc_not_array_basic_type(info)
        printf("%s %s",
            info.type.name,
            string.lower(info.name)
        );
        n = n + 1;
    end

    local function pc_not_array_string(info)
        printf("%s %s",
            info.lua_type.lua_c_type,
            string.lower(info.name)
        );
        n = n + 1;
    end

    local function pc_not_array_object(info)
        printf("%s *%s",
            c_class_name(info.type.name),
            string.lower(info.name)
        );
        n = n + 1; 
    end

    for_each_return_type(rets,function(info)        
        if not info.is_first then
            printf(",");
        end        
        if not info.is_void then
            if not info.is_array then                
                if info.is_string then
                    pc_not_array_string(info);
                elseif info.is_object then
                    pc_not_array_object(info);
                elseif info.is_basic_type then
                    pc_not_array_basic_type(info);
                end
            end
        end
    end);
    
    return n;
end

--返回值传递给lua的代码--
function code_return_val_to_lua(rets)
    local n = 0;      
    
    local function pc_not_array_basic_type(info)
        printfnl("    %s(L,%s);",info.lua_type.lua_push_func,info.name);
        n = n + 1;
    end

    local function pc_not_array_string(info)
        printfnl("    %s(L,%s);",info.lua_type.lua_push_func,info.name);
        n = n + 1;
    end

    local function pc_not_array_object(info)
        printfnl("    %s_new_userdata(L,%s,1);",
            string.lower(info.type.name),
            string.lower(info.name)
        );
        n = n + 1; 
    end

    for_each_return_type(rets,function(info)            
        if not info.is_void then
            if not info.is_array then                
                if info.is_string then
                    pc_not_array_string(info);
                elseif info.is_object then
                    pc_not_array_object(info);
                elseif info.is_basic_type then
                    pc_not_array_basic_type(info);
                end
            end
        end
    end);
    
    return n;
end

--生成new的函数体--
function code_ctor_body(func_info)
    printfnl("    %s *p%s;",
        c_class_name(func_info.idl_class.name),
        string.lower(func_info.idl_class.name)
    );
    
    printfnl("    NEW(p%s,%s);",
        string.lower(func_info.idl_class.name),    
        c_class_name(func_info.idl_class.name)        
    );
    
    printfnl("    p%s->Init(%s);",
        string.lower(func_info.idl_class.name),
        param_call_list(func_info.params)
    );
    
    printfnl("    %s_new_userdata(L,p%s,0);",
        string.lower(func_info.idl_class.name),
        string.lower(func_info.idl_class.name)
    );
    
    printfnl("    return 1;");
end

--普通的lua函数生成--
function code_normal_lua_function(func_info)
    if func_info.func.override_id then
        printfnl("static status_t %s_v%d(lua_State *L)",
            lua_c_func_name(func_info),func_info.func.override_id
        );
    else
        printfnl("static status_t %s(lua_State *L)",
            lua_c_func_name(func_info)
        );
    end
    
    printnl("{");    
    code_function_params_from_lua(func_info);           
    
    if func_info.is_ctor then
        code_ctor_body(func_info);
    else        
        printf("    ");
        local n = code_return_val_list(func_info.ret_type);
        if n > 0 then printf(" = "); end
        
        if func_info.is_static then
            printfnl("%s::%s(%s);",
                c_class_name(func_info.idl_class.name),
                func_info.name,
                param_call_list(func_info.params)
            );
        else
            printfnl("p%s->%s(%s);",
                string.lower(func_info.idl_class.name),
                func_info.name,
                param_call_list(func_info.params)
            );
        end
        
        for_each_return_type(func_info.ret_type,function(info)        
            if not info.is_void then
                if not info.is_array then                
                    if info.is_string or info.is_object then
                        printfnl("    ASSERT(%s);",string.lower(info.name));
                    end
                end
            end
        end);

        local n = code_return_val_to_lua(func_info.ret_type);
        printfnl("    return %d;",n);
    end
    
    printnl("}");
    printnl("");
end

--生成带重载的函数的总的函数--
function code_choice_override_function(func_info)
    printfnl("static status_t %s(lua_State *L)",lua_c_func_name(func_info));
    printnl("{");
    
    local function pc_check_params(info)
        
        if not info.params then
            printfnl("    return %s_v%d(L);",lua_c_func_name(func_info),info.func.override_id);
            return
        end
    
        print("    if(");
        local param_index = 2;
        
        if info.is_static then
            param_index = 1;
        end
        
        local is_first = true;
        for_each_params(info.params,function(pinfo)        
            if not pinfo.is_array then            
                if pinfo.is_object then
                    if not is_first then
                        printf(" && ");                        
                    end
                    is_first = false;
                    printf("is_%s(L,%d)",
                        string.lower(pinfo.type.name),
                        param_index
                    );
                elseif pinfo.is_basic_type then
                    if not is_first then
                        printf(" && ");                        
                    end
                    is_first = false;
                    printf("%s(L,%d)",
                        pinfo.lua_type.lua_is_func,
                        param_index
                    );
                end
            else
                if not is_first then
                    printf(" && ");                        
                end
                is_first = false;            
                printf("lua_istable(L,%d)",param_index);
            end            
            param_index = param_index + 1;        
        end);
                
        printfnl(")");       
        printfnl("    {");
        printfnl("        return %s_v%d(L);",lua_c_func_name(func_info),info.func.override_id);
        printfnl("    }");
    
    end
    
    table.sort(func_info.idl_class.functions,function(f1,f2)
        local n1 = f1.params and #f1.params or 0;
        local n2 = f2.params and #f2.params or 0;        
        return n2 < n1;
    end);
    
    for_each_functions(func_info.idl_class.functions,function(info)        
        if info.name == func_info.name then            
            pc_check_params(info);   
            printnl("");
        end
    end);
    
    printnl("    return 0;");
    
    printnl("}");
    printnl("");    
end

--生成callback函数的代码--
function code_callback_lua_function(func_info)
    printf("static status_t %s_callback_%s(lua_State *L, int _funcid, bool _once",
        string.lower(func_info.idl_class.name),
        string.lower(func_info.name)
    );    
    local param_list,param_number = param_define_list(func_info.params);
    printf("%s",param_list);
    
    local ret_list,ret_number = return_define_list(func_info.ret_type);
    printf("%s",ret_list);    
    printnl(")");    
    printfnl("{");
    
    
    for_each_params(func_info.params,function(info)    
        if info.is_string or info.is_array or info.is_object then
            printfnl("    ASSERT(%s);",info.name);
        end    
    end);
    
    for_each_return_type(func_info.ret_type,function(info)
        if info.is_void then return end
        if info.is_string or info.is_array or info.is_object then
            printfnl("    ASSERT(%s);",info.name);
        end    
    end);
    
    printnl("");
    printfnl("    if(_funcid == LUA_REFNIL)");
    printfnl("    {");
	printfnl("        return ERROR;");
    printfnl("    }");
    printnl("");
    
    printfnl("    CLuaVm vm;");
	printfnl("    vm.Init(L);");
    
    printfnl("    lua_rawgeti(L,LUA_REGISTRYINDEX,_funcid);");
    
	printfnl("    if(_once)");
    printfnl("    {");
    printfnl("        luaL_unref(L,LUA_REGISTRYINDEX,_funcid);");
    printfnl("    }");
    
    for_each_params(func_info.params,function(info)    
        if info.is_array then
            if info.is_basic_type then                
                printfnl("    CLuaVm::Push%sArray(L,%s,%s_len);",
                    info.lua_type.lua_array_type,
                    string.lower(info.name),
                    string.lower(info.name)
                );    
            end
        else
            if info.is_string then
                printfnl("    %s(L,%s);",
                    info.lua_type.lua_push_func,
                    string.lower(info.name)
                );
            elseif info.is_object then
                printfnl("    %s_new_userdata(L,%s,1);",
                    string.lower(info.type.name),
                    string.lower(info.name)
                );
            elseif info.is_basic_type then
                printfnl("    %s(L,%s);",
                    info.lua_type.lua_push_func,
                    string.lower(info.name)
                );
            end
        end
    end);        
    
    local n = 0;
    local pb = PrintBuffer.new();
    local ret_index = 0;
    for_each_return_type(func_info.ret_type,function(info)
        if info.is_void then return end        
        if info.is_array then
            if info.is_basic_type then            
                pb:Log("    CLuaVm::To%sArray(L,%d,%s,%s_len);",
                    info.lua_type.lua_array_type,
                    ret_index - ret_number,
                    string.lower(info.name),
                    string.lower(info.name)
                );
                ret_index = ret_index + 1;
            end
        else
            if info.is_string then
                pb:Log("    %s->StrCpy(%s(L,%d));",
                    info.name,
                    info.lua_type.lua_to_func,
                    ret_index - ret_number
                );
                ret_index = ret_index + 1;    
            elseif info.is_object then
                pb:Log("    *%s = get_%s(L,%d);",
                    info.name,
                    string.lower(info.type.name),
                    ret_index - ret_number
                );
                ret_index = ret_index + 1;
            elseif info.is_basic_type then
                pb:Log("    *%s = %s(L,%d);",
                    info.name,
                    info.lua_type.lua_to_func,
                    ret_index - ret_number
                );
                ret_index = ret_index + 1;
            end
        end    
    end);
    
    printfnl("    vm.Run(%d,%d);",param_number,ret_number);
    print(pb:GetText());
    
    printfnl("    vm.ClearStack();");
	printfnl("    return OK;");
    printfnl("}");
        
    printnl("");
end

--生成所有lua函数的代码--
function code_all_lua_functions(idl_class)
    auto_assign_func_id(idl_class);
   
    local overrides = {};
    
    for_each_functions(idl_class.functions,function(info)        
        if not info.is_callback then            
            if info.func.override_id then
                overrides[info.name] = info;
            end            
            code_normal_lua_function(info);   
        else
            code_callback_lua_function(info);
        end   
    end);
  
    for _,info in pairs(overrides) do    
        code_choice_override_function(info);
    end
end

--生成cpp代码--
function code_cpp(idl_class)
    code_includes_cpp(idl_class);
    code_is_userdata_valid(idl_class);    
    code_get(idl_class);
    code_new_userdata(idl_class);
    code_gc(idl_class);
    code_is_same(idl_class);
    code_to_string(idl_class);
	printnl("");
	code_is(idl_class);
    printnl("/****************************************************/");
    code_all_lua_functions(idl_class);
    printnl("/****************************************************/");
    code_funcs_table(idl_class);
    printnl("");
    code_get_functions(idl_class);
    code_register(idl_class);
    code_open(idl_class);
end
