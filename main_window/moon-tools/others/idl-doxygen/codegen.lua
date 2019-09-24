require("common")
require("idl_helper")
require("print_buffer")

function for_each_functions(functions, callback)    
    if not functions then return end
    for _,func in ipairs(functions) do        
        local info = {};
        info.func = func;
        info.is_void = IdlHelper.Func.IsVoid(func);
        info.is_static = IdlHelper.Func.IsStatic(func);
        info.is_callback = IdlHelper.Func.IsCallback(func);
        info.ret_type = func.ret_type;
        info.name = func.name;
        info.params = func.params;
        info.is_ctor = (func.idl_class.name == info.name);
        info.idl_class = func.idl_class;
        info.raw_source = func.raw_source;
        
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
        info.is_array,info.array_size = IdlHelper.Type.IsArray(p.type);
        info.is_string = IdlHelper.Type.IsString(p.type);
        info.is_callback = IdlHelper.Param.IsCallback(p);
        info.is_basic_type = IdlHelper.Type.IsBasicType(p.type);        
        info.is_object = not info.is_basic_type;       
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
        info.is_array,info.array_size = IdlHelper.Type.IsArray(ret);
        info.is_string = IdlHelper.Type.IsString(ret);
        info.is_basic_type = IdlHelper.Type.IsBasicType(ret);        
        info.is_object = not info.is_basic_type;
        info.is_void = info.type.name == "void";
        
        info.is_first = is_first;
        is_first = false;
        
        info.name = name_prefix..(index-1);
        info.index = index;
        index = index + 1;

        if callback(info) then
            return true;
        end        
    end
end

function get_base_classes(all_bases)
    local pb = PrintBuffer.new();
    local bases = all_bases;
    if not bases then return "" end;
    
    local c = 0;
    for _,info in ipairs(bases) do
        c = c + 1;        
        if c == 1 then
            pb:Print(":");
        else
            pb:Print(",");
        end
        pb:Print(string.format(
            "%s %s",
            info.openness, c_class_name(info.name)
        ));        
    end
    return pb:GetText();
end

function get_type_name(p)
        local type_name = p.type.name;
        if p.is_string then
            type_name = "字符串";
        elseif p.is_object then
            type_name = c_class_name(type_name);
        end
        
        if p.is_array then
            type_name = p.type.name.."型数组";
        end
        return type_name;
end

--生成单个函数的模板--
function code_function(info)
    printfnl("    /** ");
    printf("    * @brief 函数%s",info.name);
    
    if info.is_static then
        print("，静态类型");
    end
    
    if info.is_ctor then
        printf("，构造函数，使用%s.new来创建",
            c_class_name(info.idl_class.name)
        );
    end
    
    printnl(",");
    
    for_each_params(info.params,function(p)
      
        printfnl("    * @param %s 类型: %s,",
            p.name,
            get_type_name(p)        
        );    
    end);
    
    if not info.is_void then
        printfnl("    * @return 有%d个返回值",#info.ret_type);
        
        for_each_return_type(info.ret_type,function(ret)        
            printfnl("    *   - 返回值%d, 类型: %s,%s%s",
                ret.index,
                get_type_name(ret),
                more_ret_comments(ret),            
                IdlHelper.Common.GetRetComments(info.func)
            ); 
        end);
    end
    
    printfnl("    */");    
end

--生成整个类的doxygen模板
function code_doxygen(idl_class)

    printfnl("/** ");
    printfnl(" * @brief 定义了%s类,%s",
        c_class_name(idl_class.name),
        IdlHelper.Common.GetComments(idl_class)
    );
    printfnl(" */");
    
    printfnl("class %s%s {",
        c_class_name(idl_class.name),
        get_base_classes(IdlHelper.Class.GetAllBases(idl_class))
    );
    
    for _,func in ipairs(idl_class.functions) do
        func.idl_class = idl_class;
    end

    printfnl("public:");
    
    for_each_functions(idl_class.functions,function(info)    
        code_function(info);
              
        printfnl("    %s%s",
            info.is_static and "static " or "",
            info.raw_source
        );
        printnl("");
    end);
    
    
    printnl("};");
end
