require("common")

--除掉字符串中的 '-' 等不能在变量中出现的字符--
function convert_invalid_chars(str)
    local tmp = string.gsub(str,"-","_");
    return tmp;
end

--把member变成tolua方法名字--
function to_lua_function_name(name)
    local tmp = convert_invalid_chars(name);
    return string.format("%s_to_lua",tmp);
end

--把member变成c语言类型的名字--
function c_type_name(name)
    local tmp = name.."_t";    
    return convert_invalid_chars(tmp);
end

--生成c源码的文件名--
function to_lua_c_filename(name)
    return convert_invalid_chars(name).."_to_lua.c";
end

--生成成员变量的名字--
function var_name(name)
    return convert_invalid_chars(name);
end

--生成c源码的头文件名--
function to_lua_h_filename(name)
    return convert_invalid_chars(name).."_to_lua.h";
end

--生成enum类型的成员名字--
function enum_value_name(enum_type, name)
    return convert_invalid_chars(enum_type.."_"..name);
end

--生成bit string类型的成员名字--
function bit_string_value_name(type_name, name)
    return convert_invalid_chars(type_name.."_"..name);
end

--生成choice的present类型的名字--
function choice_present_name(type_name,name)
    return convert_invalid_chars(type_name.."_PR_"..name);
end

--判断参数是否需要是一个指针类型--
function is_object_type(member)
    return member.is_string or
        (not member.is_basic_type);
end

--生成to_lua函数的完整声明,不带;--
function code_to_lua_function_declare(member)
    printf("int %s(",to_lua_function_name(member.Identifier));
    if not is_object_type(member) then
        printf("%s _val",c_type_name(member.Identifier));
    else
        printf("%s *_pval",c_type_name(member.Identifier));
    end
    
    printf(",struct print_buffer *_pbuf");
    
    printf(")");
end


--对每一个member,生成头文件--
function code_h(member)

    printfnl("#ifndef __%s_H",
        string.upper(to_lua_function_name(member.Identifier))
    );

    printfnl("#define __%s_H",
        string.upper(to_lua_function_name(member.Identifier))
    );
    printfnl("");    
    
    printfnl("#include \"asn1c_to_lua_common.h\"");
    printfnl("#include \"%s.h\"",member.Identifier);
    printfnl("");
    code_to_lua_function_declare(member);
    
    printfnl(";");
    printnl("");
    printfnl("#endif");
    printnl("");
end

--生成基本类型成员的方法--
function code_basic_members(member)
	printfnl(
		"    %s(_val,_pbuf);",
		to_lua_function_name(member.ref_type.name)
	);    
end

function code_single_object_member_to_lua(m,tab,is_choice,nest_name)
    local choice = "";
    
    if not nest_name then nest_name = "" end    
    if is_choice then choice = "choice."  end
    
    printfnl("    %sprint_buffer_tab_printf(_pbuf,\"%s = \");",
        tab,convert_invalid_chars(m.Identifier));

    local addr_or_star_str = is_object_type(m) and "&" or "";
    
    if m.is_optional then 
        addr_or_star_str=""; 
        if not is_object_type(m) then
            addr_or_star_str="*";
        end
    end
        
    if not m.is_basic_type and not m.is_string then
        printfnl("    %sprint_buffer_printf(_pbuf,\"{\");",tab);
        printfnl("    %sprint_buffer_nl(_pbuf);",tab);
        printfnl("    %sprint_buffer_inc_level(_pbuf,1);",tab);
    end
    
    if not m.members then
        printfnl(
            "    %s%s(%s_pval->%s%s%s,_pbuf);",tab,
            to_lua_function_name(m.ref_type.name),
            addr_or_star_str,
            choice,
            nest_name,            
            var_name(m.Identifier)
        );
    else
        for_each_member(m,function(mm)
            code_single_object_member_to_lua(mm,tab,is_choice,nest_name..m.Identifier..".");
            printfnl("    %sprint_buffer_printf(_pbuf,\",\");",tab);
            printfnl("    %sprint_buffer_nl(_pbuf);",tab);
        end);
    end
    if not m.is_basic_type and not m.is_string then
        printfnl("    %sprint_buffer_inc_level(_pbuf,-1);",tab);
        printfnl("    %sprint_buffer_tab_printf(_pbuf,\"}\");",tab);           
    end    
end

--为object类型的对象的每一个成员生成代码--
function code_object_members(member)
     for_each_member(member,function(m)      

        local tab = "";
        
        if m.is_optional then
            tab = "    ";
            printfnl("    if(_pval->%s)",var_name(m.Identifier));
            printfnl("    {");
        end
     
        code_single_object_member_to_lua(m,tab);        
        
        printfnl("    %sprint_buffer_printf(_pbuf,\",\");",tab);
        printfnl("    %sprint_buffer_nl(_pbuf);",tab);

        if m.is_optional then
            printfnl("    }");
        end
    
        printnl("");
    end);
end

--为enum对象生成代码--
function code_enum_members(member)
    printfnl("    const char *val_name = \"\";");
    printfnl("");
    printfnl("    switch(_val)");
    printfnl("    {");
    

    for_each_member(member,function(m)        
        local value_name = enum_value_name(member.Identifier,m.Identifier);
        
        printfnl("        case %s:",value_name);
        printfnl("            val_name = \"%s\";",value_name);
        printfnl("            break;");
        
    end);    
    
    printfnl("        default:");
    printfnl("            val_name=\"<unknown>\";");
    printfnl("            break;");    
    printfnl("    }");    
    printnl("");    
    printnl("    print_buffer_printf(_pbuf,\"\\\"%s\\\"\",val_name);");
end    

--生成bit string类型的成员代码--
function code_bit_string_members(member)    
    for_each_member(member,function(m)        
        local value_name = bit_string_value_name(member.Identifier,m.Identifier);        
        printnl(
            "    print_buffer_log(_pbuf,\""..
            convert_invalid_chars(m.Identifier)..
            " = %s,\","..EOL..
            string.format("        TO_LUA_BIT_TO_BOOL(_pval,%s)",value_name)..EOL..
            "    );"
        );        
        printnl("");
    end);
end

--生成string类型的成员代码--
function code_string_members(member)    
	printfnl(
		"    %s(_pval,_pbuf);",
		to_lua_function_name(member.ref_type.name),
		var_name(member.Identifier)
	);
end

--判断容器中的内容是否是基本类型
function is_basic_container(v)
    for _,m in ipairs(v.members) do
       m.Identifier = "__m__";        
    end    
    
    local is_basic;
    for_each_member(v,function(m)
    
        if m.is_basic_type then
            is_basic = true;
        end
    end);    
    
    return is_basic;
end

--生成容器类型的成员代码--
function code_container_members(member)
    if not is_basic_container(member) then
        printfnl("    %s_to_lua(%s,_pval,",
            expr_type_to_string(member.expr_type),
            c_type_name(member.Identifier)
        );
    else
        printfnl("    %s_BASIC_to_lua(%s,_pval,",
            expr_type_to_string(member.expr_type),
            c_type_name(member.Identifier)
        );    
    end
    
    printfnl("        %s,%s,_pbuf);",
        c_type_name(member.entry_ref_type.name),
        to_lua_function_name(member.entry_ref_type.name)
    );

end

--生成所有choice类型的代码--
function code_choice_members(member)
    for_each_member(member,function(m)        
        local pr_name = choice_present_name(member.Identifier,m.Identifier);                
        printfnl("    if(_pval->present == %s)",pr_name);
        printfnl("    {");          
        local tab = "    ";
        code_single_object_member_to_lua(m,tab,true);
        printfnl("    %sprint_buffer_printf(_pbuf,\",\");",tab);
        printfnl("    %sprint_buffer_nl(_pbuf);",tab);
        printfnl("    }");        
        printnl("");
    end);
end

--收集所有的include信息
function collect_all_includes(member)

    local all_includes={};
    
    function add(name)
        if not all_includes[name] then
            all_includes[name] = true;
        end
    end

    for_each_member(member,function(m)        
        if m.ref_type then
            if m.meta_type == AMT_TYPEREF then            
                add(m.ref_type.name);
            end
        end            
    end);
    
    if member.entry_ref_type then   
        if member.entry_ref_type.meta_type == AMT_TYPE then
            add(member.entry_ref_type.name);
        end
    end

    return all_includes;
end

--生成每一个member的c代码--
function code_c(member)
    printfnl("#include \"%s\"",to_lua_h_filename(member.Identifier));    

    
    local all_includes = collect_all_includes(member);
    
    for name,_ in pairs(all_includes) do
        printfnl("#include \"%s\"",to_lua_h_filename(name));    
    end

    printnl("");        
    code_to_lua_function_declare(member);
    printnl("");
    printnl("{");
    
    printfnl("    TO_LUA_ASSERT(_pbuf);");    
    
    if not member.is_basic_type then    
        printfnl("    TO_LUA_ASSERT(_pval);");    
    end   
    
    printnl("");
    
    if member.is_enum then
        code_enum_members(member);
    elseif member.is_bit_string then
        code_bit_string_members(member);
    elseif member.is_string then
        code_string_members(member);
    elseif member.is_basic_type then
		code_basic_members(member);
    elseif member.is_container then
        code_container_members(member);
    elseif member.is_choice then
        code_choice_members(member);
    else
        code_object_members(member);
    end
    
    
    printnl("");
    printnl("    return TO_LUA_OK;");
    printnl("}");
    printnl("");
end

--生成wireshark用的protocal 和 field 等信息--
function code_wireshark_strings(asn1_table)
    
    local all_ids={};
    
    for_each_module(asn1_table,function(module)
        for_each_member(module,function(member)
            if member.meta_type == AMT_TYPE then
                local str = convert_invalid_chars(member.Identifier);
                all_ids[str] = 1;
                
                for_each_member(member,function(m)
                    local str = convert_invalid_chars(m.Identifier);
                    all_ids[str] = 1;
                end);
            end
        end);
    end);

    local sorted = {};
    
    for k,v in pairs(all_ids) do
        table.insert(sorted,k);
    end
    
    table.sort(sorted,function(e1,e2)
        return string.lower(e1) < string.lower(e2);
    end);
    
    for _, str in ipairs(sorted) do    
        
        printfnl("%s = ProtoField.string(\"%s\"),",
            str,str
        );
        
    end    

end
