require("common")
require("idl_helper")
require("c_base_codegen")

function name_to_include_file(name)
	return to_file_name(name)..".h";
end

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
    return printnl("/*@@End Function "..name.."@@*/");
end
--------------------------------------
local str_temp_code = "";
function temp_code(str)
    str_temp_code = str_temp_code..str;
end

function clear_temp_code()
    str_temp_code = "";
end

function temp_code_nl(str)
    str_temp_code = str_temp_code..str..EOL;
end

function get_temp_code()
    return str_temp_code;
end
--------------------------------------
function base_class_name(name)
    return "base_"..to_lower_underline_case(name);
end

--对每一个变量的迭代器--
function for_each_variables(variables,callback)
    if not variables then 
        return 
    end
    
    for _,var in ipairs(variables) do	
        local var_type = var.type;
        local is_pointer = IdlHelper.Type.IsPointer(var_type);
        local is_array,array_size = IdlHelper.Type.IsArray(var_type);
        local is_string = IdlHelper.Type.IsString(var_type);
        local is_basic_type = IdlHelper.Type.IsBasicType(var_type);
        local is_object = not is_basic_type;
        local is_optional = IdlHelper.Var.IsOptional(var) and is_object and not is_array;
        
        if is_string then
            is_object = false;
            is_basic_type = false;
        end
        
        local info = {};
        info.var = var;
        info.var_type = var_type;
        info.is_pointer = is_pointer;
        info.is_array = is_array;
        info.array_size = array_size;
        info.is_string = is_string;
        info.is_basic_type = is_basic_type;
        info.is_object = is_object;
        info.is_optional = is_optional;
		info.is_no_setter = IdlHelper.Var.IsNoSetter(var);
		info.is_no_getter = IdlHelper.Var.IsNoGetter(var);
        callback(info);
    end
end

--转换一些特殊的类型--
function covert_special_types(idl_class)
    for_each_variables(idl_class.variables,function(info)        
        if info.is_string then 
            info.var_type.name = "char*" ;
            info.var_type.const_name = "const char*";
            info.var_type.is_string = true;
        end
    end);
end

function this_pointer()
    return c_class_name(g_idl_class.name).." *self";
end

--头文件中变量的定义--
function code_variables_define(variables)
	for_each_variables(variables,function(info)		
		print("    "..(
			(info.is_basic_type or info.is_string)
			and info.var_type.name 
			or c_class_name(info.var_type.name)
		));       
		
		local name_prefix="";
		if info.is_pointer then
			name_prefix = name_prefix.."*";
		end
		
		if info.is_array and not info.array_size then
			name_prefix = name_prefix.."*";
		end
        
        if info.is_optional then
            name_prefix = name_prefix.."*";
        end
        
		print(string.format(
			" %s%s",
			name_prefix,
			member_name(info.var.name)
		));
		
		if info.is_array and info.array_size then
			print("["..info.array_size.."]");
		end
        printnl(";");
        
		if info.is_array and not info.array_size then
			print("    int "..member_name_len(info.var.name));	
            printnl(";");
		end		
	end);
end

--生成所有的include 代码--
function code_all_includes(idl_class)
    local all_names = {};
    local all_names_sorted = {};
    
    function add_name(name)
        local l_name = string.lower(name);
        if not all_names[l_name] then
            all_names[l_name] = true;
            table.insert(all_names_sorted,name);
        end
    end
	
	common_include_h();

	local all_bases = IdlHelper.Class.GetAllBases(idl_class);
	
	if all_bases then
		for _,base in ipairs(all_bases) do
            add_name(base.name);
		end
	end
    
    for_each_variables(idl_class.variables,function(info)        
        if info.is_object  and info.var.name ~= idl_class.name then
            add_name(info.var_type.name);
        end        
    end);    
    
    for _,name in ipairs(all_names_sorted) do    
        printnl(string.format(        
            "#include \"%s\"",
            name_to_include_file(name)
        ));    
    end
    
end

--头文件代码生成--
function code_h(idl_class)
	printnl(string.format(
		"#ifndef _C_%s_H",
        string.upper(camel_to_underline_case(idl_class.name))
	));
	
	printnl(string.format(
		"#define _C_%s_H",
        string.upper(camel_to_underline_case(idl_class.name))
	));
			
	printnl("");
    
    code_begin_marker("Includes_H");    
    code_all_includes(idl_class);      
    code_end_marker("Includes_H");
    
	printnl("");
    
	print(string.format("%s",
		c_class_name(idl_class.name)
	));
	
	printnl("{");
	    
    code_begin_marker("Members");
  	
	if code_switch.weak_ref then
		printnl("    C_WEAK_REF_ID_DEFINE();");
	end
	
    local c_base_code = g_c_base_codegen:Code_ClassHeader();
    
    if string.len(c_base_code) > 0 then        
        print(c_base_code);
		printnl("");
    end

	if idl_class.variables then
		code_variables_define(idl_class.variables);
	end

    code_end_marker("Members");
   
    printnl("};");
    
	printnl("");		
	    
    printnl(string.format(
        "status_t %s(%s);",
        this_function_name("init_basic"),
        this_pointer()
    ));
    
    printnl(string.format(
        "status_t %s(%s);",
        this_function_name("init"),
        this_pointer()
    ));
    
    
	printnl(string.format(
        "status_t %s(%s);",
        this_function_name("destroy"),
        this_pointer()
    ));
	
	if code_switch.copy_comp_print then        
        printnl(string.format(
            "status_t %s(%s,%s *_p);",
            this_function_name("copy"),
            this_pointer(),
            c_class_name(idl_class.name)
        ));
    
        printnl(string.format(
            "status_t %s(%s,%s *_p);",
            this_function_name("comp"),
            this_pointer(),
            c_class_name(idl_class.name)
        ));
        
        printnl(string.format(
            "status_t %s(%s,struct log_buffer *_buf);",
            this_function_name("print"),
            this_pointer()
        ));
	end	
    
    printnl("");
    code_begin_marker("Getters_H");
    code_all_getter_declaration_h(idl_class);
    code_end_marker("Getters_H");

    printnl("");
    code_begin_marker("Setters_H");
    code_all_setter_declaration_h(idl_class);
    code_end_marker("Setters_H");
    
	printnl("");
	printnl("#endif");
end

--得到变量的初始值--
function get_init_value(info)
    local init_value = "0";
    if     info.is_pointer 
        or info.is_optional
        or info.is_string
    then
        init_value = "NULL";
    end
    
    if info.var.init_value then
        init_value = info.var.init_value;
    end
    
    return init_value;
end

--生成InitBasic函数的代码--
function code_cpp_init_basic(idl_class)
	printnl(string.format(
        "status_t %s(%s)",
        this_function_name("init_basic"),
        this_pointer()
    ));    
    printnl("{");
        
    clear_temp_code();
    local need_i = false;
        
    function pc_array_with_array_size(info)
        need_i = true;
        temp_code_nl(string.format(
            "    for(i = 0; i < %s; i++)",
            info.array_size
        ));
        
        temp_code_nl("    {");
        
        if info.is_basic_type or info.is_pointer or info.is_string then
            temp_code_nl(string.format(
                "        self->%s[i] = %s;",
                member_name(info.var.name),
                get_init_value(info)
            )); 
        else
            temp_code_nl(string.format(
                "        %s(&self->%s[i]);",
                function_name(info.var_type,"init_basic"),
                member_name(info.var.name)
            ));
        end
        
        temp_code_nl("    }");
    end
    
    function pc_array_without_array_size(info)
        temp_code_nl(string.format(
            "    self->%s = NULL;",
            member_name(info.var.name)
        )); 
        temp_code_nl(string.format(
            "    self->%s = 0;",
            member_name_len(info.var.name)
        )); 
    end
    
    function pc_not_array(info)
        if info.is_basic_type or info.is_pointer or info.is_string or info.is_optional then
            temp_code_nl(string.format(
                "    self->%s = %s;",
                member_name(info.var.name),
                get_init_value(info)
            ));
        else
            temp_code_nl(string.format(
                "    %s(&self->%s);",
                function_name(info.var_type,"init_basic"),
                member_name(info.var.name)
            ));
        end   
    end
        
    for_each_variables(idl_class.variables,function(info)         
        if info.is_array then        
            if info.array_size then
                pc_array_with_array_size(info);              
            else
                pc_array_without_array_size(info);
            end
        else 
            pc_not_array(info);
        end    
    end);
    
    code_begin_marker("InitBasic");
    
    if need_i then
        printnl("    int i = 0;");        
        printnl("");
    end

  	if code_switch.weak_ref then
		printnl("    C_WEAK_REF_ID_CLEAR(self);");
	end

    print(g_c_base_codegen:Code_InitBasic());     
    print(get_temp_code());
    
    code_end_marker("InitBasic");
    
    printnl("    return OK;");
    printnl("}");
end

--生成Init函数的代码--
function code_cpp_init(idl_class)
	printnl(string.format(
        "status_t %s(%s)",
        this_function_name("init"),
        this_pointer()
    ));    
    printnl("{");
    
    clear_temp_code();
    local need_i = false;
    
    function pc_array_with_array_size(info)
        if info.is_object then
            need_i = true;
            temp_code_nl(string.format(
                "    for(i = 0; i < %s; i++)",
                info.array_size
            ));
            temp_code_nl("    {");
            
            temp_code_nl(string.format(
                "        %s(&self->%s[i])",
                function_name(info.var_type,"init"),
                member_name(info.var.name)
            ));
            
            temp_code_nl("    }");
        end
    end
    
    function pc_not_array(info)
        if info.is_object and not info.is_pointer and not info.is_optional then
            temp_code_nl(string.format(
                "    %s(&self->%s);",
                function_name(info.var_type,"init"),
                member_name(info.var.name)
            ));
        end        
    end
    
    for_each_variables(idl_class.variables,function(info)         
        if info.is_array then        
            if info.array_size then
                pc_array_with_array_size(info);
            end
        else 
            pc_not_array(info);
        end    
    end);

    code_begin_marker("Init");

    if need_i then
        printnl("    int i = 0;");        
        printnl("");
    end

  	if code_switch.weak_ref then
		printnl("    C_WEAK_REF_ID_INIT(self);");
	end

    printnl(string.format(
        "    %s(self);",
        this_function_name("init_basic")
    ));
    
    print(g_c_base_codegen:Code_Init());
    print(get_temp_code());        
    
    code_end_marker("Init");
    
    printnl("    return OK;");
    printnl("}");
end

--生成Destroy的代码--
function code_cpp_destroy(idl_class)
	printnl(string.format(
        "status_t %s(%s)",
        this_function_name("destroy"),
        this_pointer()
    ));    
    printnl("{");
    
    clear_temp_code();
    local need_i = false;
    
    function pc_array_with_array_size_object(info)
        need_i = true;
        temp_code_nl(string.format(
            "    for(i = 0; i < %s; i++)",
            info.array_size
        ));
        temp_code_nl("    {");
        
        temp_code_nl(string.format(
            "        %s(&self->%s[i]);",
            function_name(info.var_type,"destroy"),
            member_name(info.var.name)
        ));
        
        temp_code_nl("    }");
    end
    
    function pc_array_no_array_size_object(info)
    
        need_i = true;

        temp_code_nl(string.format(
            "    for(i = 0; i < self->%s; i++)",
            member_name_len(info.var.name)
        ));
        temp_code_nl("    {");
        
        temp_code_nl(string.format(
            "        %s(&self->%s[i]);",
            function_name(info.var_type,"destroy"),
            member_name(info.var.name)
        ));
        
        temp_code_nl("    }");
        
        temp_code_nl(string.format(
            "    X_FREE(self->%s);",
            member_name(info.var.name)
        ));
    end    
        
    function pc_array_no_array_size_string(info)
    
        need_i = true;

        temp_code_nl(string.format(
            "    for(i = 0; i < self->%s; i++)",
            member_name_len(info.var.name)
        ));
        temp_code_nl("    {");
        
        temp_code_nl(string.format(
            "        X_FREE(self->%s[i]);",
            member_name(info.var.name)
        ));
        
        temp_code_nl("    }");
        
        temp_code_nl(string.format(
            "    X_FREE(self->%s);",
            member_name(info.var.name)
        ));
    end   
    
    function pc_array_no_array_size_basic(info)
        temp_code_nl(string.format(
            "    X_FREE(self->%s);",
            member_name(info.var.name)
        ));
    end
    
    function pc_not_array_object(info)
        if info.is_optional then            
            temp_code_nl(string.format(
                "    if(self->%s)",
                member_name(info.var.name)
            ));
            
            temp_code_nl("    {");
            
            temp_code_nl(string.format(
                "        %s(self->%s);",
                function_name(info.var_type,"destroy"),
                member_name(info.var.name)
            ));
            temp_code_nl(string.format(
                "        X_FREE(self->%s);",
                member_name(info.var.name)
            ));
            temp_code_nl("    }");
        elseif not info.is_pointer then
            temp_code_nl(string.format(
                "    %s(&self->%s);",
                function_name(info.var_type,"destroy"),
                member_name(info.var.name)
            ));
        end
    end

    function pc_not_array_string(info)
		temp_code_nl(string.format(
			"    X_FREE(self->%s);",
			member_name(info.var.name)
		));
    end
        
		
    for_each_variables(idl_class.variables,function(info)         
        if info.is_array then        
            if info.array_size then
                if info.is_object then
                    pc_array_with_array_size_object(info);
                end
            else
                if info.is_basic_type or info.is_pointer then
                    pc_array_no_array_size_basic(info);
                elseif info.is_string then
                    pc_array_no_array_size_string(info);
                else
                    pc_array_no_array_size_object(info);
                end
            end
        else 
			if info.is_string then
				pc_not_array_string(info);
            elseif info.is_object then
                pc_not_array_object(info);
            end        
        end    
    end);
    
    code_begin_marker("Destroy");
    if need_i then
        printnl("    int i = 0;");        
        printnl("");
    end
    
    print(g_c_base_codegen:Code_Destroy());
    print(get_temp_code());
    printnl(string.format(
        "    %s(self);",
        this_function_name("init_basic")
    ));
    code_end_marker("Destroy");
    
    printnl("    return OK;");
    printnl("}");
end

--生成Copy函数的代码--
function code_cpp_copy(idl_class)
	printnl(string.format(
        "status_t %s(%s,%s *_p)",
        this_function_name("copy"),
        this_pointer(),
        c_class_name(idl_class.name)
    ));    
    printnl("{");

    clear_temp_code();
    local need_i = false;
    
    function pc_array(info)
        need_i = true; 
        local array_size = info.array_size;
        
        if not array_size then
            array_size = "self->"..member_name_len(info.var.name);
            
            temp_code_nl(string.format(
                "    %s(self,_p->%s);",
                alloc_name(info.var.name),
                member_name_len(info.var.name)
            ));
        end
        
        temp_code_nl(string.format(
            "    for(i = 0; i < %s; i++)",
            array_size
        ));
        temp_code_nl("    {");
        if info.is_basic_type or info.is_pointer then
            temp_code_nl(string.format(
                "        self->%s[i] = _p->%s[i];",
                member_name(info.var.name),
                member_name(info.var.name)
            )); 
        elseif info.is_string then
            temp_code_nl(string.format(
                "        %s(self,i,_p->%s[i]);",
                setter_array_elem_name(info.var.name),
                member_name(info.var.name),
                member_name(info.var.name)
            ));        
        else
            temp_code_nl(string.format(
                "        %s(&self->%s[i],&_p->%s[i]);",
                function_name(info.var_type,"copy"),
                member_name(info.var.name),
                member_name(info.var.name)
            ));
        end
        temp_code_nl("    }");
    end
    
    function pc_not_array(info)
        if info.is_string then
            temp_code_nl(string.format(
                "    %s(self,_p->%s);",
                setter_name(info.var.name),
                member_name(info.var.name)
            ));
        elseif info.is_basic_type or info.is_pointer then
            temp_code_nl(string.format(
                "    self->%s = _p->%s;",
                member_name(info.var.name),
                member_name(info.var.name)
            ));
        else
        
            if info.is_optional then            
                temp_code_nl(string.format(
                    "    %s(self,_p->%s);",
                    setter_name(info.var.name),
                    member_name(info.var.name)
                ));            
            else        
                temp_code_nl(string.format(
                    "    %s(&self->%s,&_p->%s);",
                    function_name(info.var_type,"copy"),
                    member_name(info.var.name),
                    member_name(info.var.name)
                ));
            end
        end       
    end
    
    for_each_variables(idl_class.variables,function(info)         
        if info.is_array then 
            pc_array(info);
        else 
            pc_not_array(info);
        end    
    end);
    
    code_begin_marker("Copy");
    
    if need_i then
        printnl("    int i = 0;");        
        printnl("");
    end
    
    printnl("    ASSERT(_p);");
    printnl("    if(self == _p)return OK;");
    printnl("");
    
    print(g_c_base_codegen:Code_Copy());
    print(get_temp_code());
    
    code_end_marker("Copy");    
    printnl("    return OK;");
    printnl("}");
end

--生成Copy函数的代码--
function code_cpp_comp(idl_class)
	printnl(string.format(
        "status_t %s(%s,%s *_p)",
        this_function_name("comp"),
        this_pointer(),
        c_class_name(idl_class.name)
    ));    
    printnl("{");
    printnl("    ASSERT(_p);");
    printnl("    if(self == _p)return 0;");
    printnl("    ASSERT(0);");
    printnl("    return 0;");
    printnl("}");
    
end

--生成Print函数的代码--
function code_cpp_print(idl_class)
	printnl(string.format(
        "status_t %s(%s,struct log_buffer *_buf)",
        this_function_name("print"),
        this_pointer()        
    ));    
    printnl("{");
    
    clear_temp_code();
    local need_i = false;
    
    function pc_array_basic_type(info)
        temp_code_nl(string.format(
            "        log_buffer_log(_buf,\"%s,\",self->%s[i]);",
            info.is_pointer and "0x%p" or IdlHelper.Type.GetPrintFormat(info.var_type),
            member_name(info.var.name)                        
        )); 
    end
    
    function pc_array_object(info)
        temp_code_nl("        log_buffer_log(_buf,\"[%d]={\",i);");        
        temp_code_nl("        log_buffer_inc_level(_buf,1);");
        temp_code_nl(string.format(
            "        %s(&self->%s[i],_buf);",
            function_name(info.var_type,"print"),
            member_name(info.var.name)                    
        ));
        temp_code_nl("        log_buffer_inc_level(_buf,-1);");
        temp_code_nl("        log_buffer_log(_buf,\"},\");");
    end
    
    function pc_array_string(info)
        temp_code_nl(string.format(
            "        log_buffer_log(_buf,\"[%%d] = %%s\",i,self->%s[i]);",
            member_name(info.var.name)
        ));        
    end
    
    function pc_array(info)
        need_i = true;
        
        temp_code_nl(string.format(
            "    log_buffer_log(_buf,\"%s = [\");",
            info.var.name
        ));
     
        temp_code_nl("    log_buffer_inc_level(_buf,1);");
        local array_size = info.array_size 
            and info.array_size 
            or "self->"..member_name_len(info.var.name);

        temp_code_nl(string.format(
            "    for(i = 0; i < %s; i++)",
            array_size
        ));
        
        temp_code_nl("    {");
        
        if info.is_basic_type or info.is_pointer then
            pc_array_basic_type(info);
        elseif info.is_string then
            pc_array_string(info);
        else            
            pc_array_object(info);
        end        
        
        temp_code_nl("    }");
        temp_code_nl("    log_buffer_inc_level(_buf,-1);");
        temp_code_nl("    log_buffer_log(_buf,\"]\");");
    end
    
    function pc_not_array_basic_type(info)
        temp_code_nl(string.format(
            "    log_buffer_log(_buf,\"%s = %s\",self->%s);",
            info.var.name,
            info.is_pointer and "0x%p" or IdlHelper.Type.GetPrintFormat(info.var_type),
            member_name(info.var.name)                        
        ));                 
    end
    
    function pc_not_array_object(info)
        temp_code_nl(string.format(
            "    log_buffer_log(_buf,\"%s = {\");",
            info.var.name                    
        ));

        temp_code_nl("    log_buffer_inc_level(_buf,1);");    
        
        local addr = "&";
        if info.is_optional then
            addr = "";
        end
        
        temp_code_nl(string.format(
            "    %s(%sself->%s,_buf);",
            function_name(info.var_type,"print"),
            addr,
            member_name(info.var.name)                    
        ));        
        
        
        temp_code_nl("    log_buffer_inc_level(_buf,-1);");
        temp_code_nl("    log_buffer_log(_buf,\"},\");");
    end
    
    function pc_not_array_string(info)   
        temp_code_nl(string.format(
            "    log_buffer_log(_buf,\"%s = %%s\",self->%s);",
            info.var.name,
            member_name(info.var.name)
        ));
    end
    
    for_each_variables(idl_class.variables,function(info)         
        if info.is_array then        
            pc_array(info);
        else 
            if info.is_string then
                pc_not_array_string(info);            
            elseif info.is_basic_type or info.is_pointer then
                pc_not_array_basic_type(info);
            else
                pc_not_array_object(info);
            end        
        end    
    end);
    
    code_begin_marker("Print");
    if need_i then
        printnl("    int i = 0;");        
        printnl("");
    end
    
    printnl("    ASSERT(_buf);");
    print(g_c_base_codegen:Code_Print());
    print(get_temp_code());
    
    code_end_marker("Print");
    
    printnl("    return OK;");
    printnl("}");
end

--生成Getter函数的声明--
function code_getter_declaration(info)
    if info.is_basic_type or info.is_string then    
        print(info.var_type.name);
    else
        print(c_class_name(info.var_type.name));
    end
    
    if info.is_array or info.is_pointer or info.is_object then
        print("*");
    end
    
    if info.is_array and info.is_pointer then
        print("*");
    end    
      
    print(string.format(
        " %s(%s)",
        getter_name(info.var.name),
        this_pointer()
    ));  
end

--生成Getter函数body--
function code_getter_body(info)
    printnl("");
    printnl("{");
    
    if      info.is_object and 
        not info.is_pointer and 
        not info.is_array and
        not info.is_optional
    then
        printnl(string.format(
            "    return &self->%s;",
            member_name(info.var.name)
        ));     
    else    
        printnl(string.format(
            "    return self->%s;",
            member_name(info.var.name)
        )); 
    end
    
        
    printnl("}");
end

--生成专门针对 string的get函数体--
function code_getter_body_string(info,need_class_prefix)
    printnl("");
    printnl("{");
    
    printnl(string.format(
        "    return self->%s;",
        member_name(info.var.name)
    ));
    
    printnl("}");
end

--生成专门返回数组长度的代码声明--
function code_getter_declaration_array_len(info)
   print("int");
    
   print(string.format(
        " %s(%s)",
        getter_array_len_name(info.var.name),
        this_pointer()        
    )); 
end

--生成专门返回数组长度的函数body--
function code_getter_body_array_len(info)
    printnl("");
    printnl("{");
    
    local len_name = "self->"..member_name_len(info.var.name);
    
    if info.array_size then
        len_name = info.array_size;
    end
    
    printnl(string.format(
        "    return %s;",
        len_name
    ));            
    printnl("}");
end

--生成专门返回数组各个元素的函数声明--
function code_getter_declaration_get_array_elem(info,need_class_prefix)
    if info.is_basic_type or info.is_string then
        print(info.var_type.name);
    else
        print(c_class_name(info.var_type.name));
    end
    
    if (info.is_array and info.is_pointer) or info.is_object then
        print("*");
    end

    
    print(string.format(
        " %s(%s,int _index)",
        getter_array_elem_name(info.var.name),
        this_pointer()
    )); 
end

--生成专门返回数组各个元素的函数体--
function code_getter_body_get_array_elem(info,need_class_prefix)
    printnl("");
    printnl("{");
    
    if not info.array_size then
        printnl(string.format(
            "    ASSERT(self->%s);",
            member_name(info.var.name)
        ));
    end
    
    printnl(string.format(
        "    ASSERT(_index >= 0 && _index < %s);",
        info.array_size and info.array_size or 
        "self->"..member_name_len(info.var.name)
    ));
    
    if info.is_pointer or info.is_basic_type or info.is_string then    
        printnl(string.format(
            "    return self->%s[_index];",
            member_name(info.var.name)
        ));
    else
        printnl(string.format(
            "    return &self->%s[_index];",
            member_name(info.var.name)
        ));    
    end    
    
    printnl("}");
end

--生成所有函数的getter的cpp代码--
function code_all_getter_cpp(idl_class)
    for_each_variables(idl_class.variables,function(info)    
		if info.is_no_getter then return end
        info.idl_class = idl_class;
        
        code_begin_extra(getter_name(info.var.name));
        code_getter_declaration(info,true);
        code_getter_body(info);
        code_end_extra(getter_name(info.var.name));
        printnl("");
        
        if info.is_array then      
            code_begin_extra(getter_array_len_name(info.var.name));
            code_getter_declaration_array_len(info,true);
            code_getter_body_array_len(info);
            code_end_extra(getter_array_len_name(info.var.name));
            printnl("");
            
            code_begin_extra(getter_array_elem_name(info.var.name));
            code_getter_declaration_get_array_elem(info,true);            
            code_getter_body_get_array_elem(info);
            code_end_extra(getter_array_elem_name(info.var.name));
            printnl("");
        end
    end);
end

--生成所有函数的getter声明--
function code_all_getter_declaration_h(idl_class)
    for_each_variables(idl_class.variables,function(info)    
		if info.is_no_getter then return end
        info.idl_class = idl_class;
        code_getter_declaration(info);
        printnl(";");
                
        if info.is_array then
            code_getter_declaration_array_len(info);
            printnl(";");            
            code_getter_declaration_get_array_elem(info);            
            printnl(";");
        end
    end);
end

--生成setter方法的函数声明，不是数组的基本数据类型--
function code_setter_declaration_basic_not_array(info)
    print("status_t");
    
    print(string.format(
        " %s(%s,%s %s_%s)",
        setter_name(info.var.name),
        this_pointer(),
        info.var_type.name,
        info.is_pointer and "*" or "",
        string.lower(info.var.name)
    )); 
end

--生成setter方法的函数体，不是数组的基本数据类型--
function code_setter_body_basic_not_array(info,need_class_prefix)

    printnl("");
    printnl("{");
    
    printnl(string.format(
      "    self->%s = _%s;",
      member_name(info.var.name),
      string.lower(info.var.name)
    )); 
    
    printnl("    return OK;");    
    printnl("}");
end

--生成setter方法的函数声明，不是数组的普通对象--
function code_setter_declaration_object_not_array(info)

    print("status_t");    
    
    print(string.format(
        " %s(%s,%s *_%s)",        
        setter_name(info.var.name),
        this_pointer(),
        c_class_name(info.var_type.name),
        string.lower(info.var.name)
    )); 
end

--生成setter方法的函数体，不是数组的普通对象--
function code_setter_body_object_not_array(info)
    printnl("");
    printnl("{");    
    if info.is_pointer then
        printnl(string.format(
          "    self->%s = _%s;",
          member_name(info.var.name),
          string.lower(info.var.name)
        )); 
        printnl("    return OK;");
    elseif info.is_optional then    
        printfnl(
            "    if(self->%s)",
            member_name(info.var.name)
        );
        
        printnl("    {");
        
        printfnl(
            "        %s(self->%s);",
            function_name(info.var_type,"destroy"),
            member_name(info.var.name)
        );
        printfnl(
            "        X_FREE(self->%s);",
            member_name(info.var.name)
        );
        printnl("    }");
        
        printnl("");
        printfnl("    if(_%s == NULL)",string.lower(info.var.name));
        printnl("        return OK;");
        printnl("");
        
        printnl(string.format(
          "    return %s(self->%s,_%s);",
          function_name(info.var_type,"copy"),
          member_name(info.var.name),
          string.lower(info.var.name)
        )); 
        
    else
        printnl(string.format(
            "    ASSERT(_%s);",
            string.lower(info.var.name)
        ));
        
        printnl(string.format(
          "    return %s(&self->%s,_%s);",
          function_name(info.var_type,"copy"),
          member_name(info.var.name),
          string.lower(info.var.name)
        )); 
    end
    printnl("}");
end

--专门生成string 类型的setter函数声明，不是数组--
function code_setter_declaration_string_not_array(info)

   print("status_t");
        
    print(string.format(
        " %s(%s,const char *_%s)",
        setter_name(info.var.name),        
        this_pointer(),
        string.lower(info.var.name)
    )); 
end

--专门生成string 类型的setter函数体，不是数组--
function code_setter_body_string_not_array(info,need_class_prefix)
    printnl("");
    printnl("{");
    
    printnl("    int len = 0;");

    printnl(string.format(
        "    if(_%s == NULL)",
        string.lower(info.var.name)
    ));
    
    printfnl("    {");
    printfnl("        X_FREE(self->%s);",member_name(info.var.name));
    printnl("        return OK;");
    printfnl("    }");        
        
    printnl(string.format(
        "    len = strlen(_%s);",
        string.lower(info.var.name)
    ));
    
    printnl(string.format(
        "    X_FREE(self->%s);",
        member_name(info.var.name)
    ));
    
    printnl(string.format(
        "    X_MALLOC(self->%s,char,len+1);",
        member_name(info.var.name)
    ));
    
    printnl(string.format(
        "    memcpy(self->%s,_%s,len+1);",
        member_name(info.var.name),
        string.lower(info.var.name)
    ));
    
    printnl("    return OK;");
    printnl("}");
end

--生成setter方法的函数声明--
function code_setter_declaration_array(info)
    print("status_t");
    
    local type_name = info.is_object 
        and c_class_name(info.var_type.name)
        or info.var_type.name;
    
    print(string.format(
        " %s(%s,%s %s_%s[], int _len)",
        setter_name(info.var.name),
        this_pointer(),
        type_name,
        info.is_pointer and "*" or "",
        string.lower(info.var.name)
    )); 
end


--生成setter方法的函数体--
function code_setter_body_array(info,need_class_prefix)      
    printnl("");
    printnl("{");
    
    local var_type_name = info.var_type.name;
    if info.is_object then
        var_type_name = c_class_name(info.var_type.name);
    end
    
    if info.is_pointer then
        var_type_name = var_type_name.."*";
    end
    
    clear_temp_code();
    
    local need_i = false;
    
    temp_code_nl(string.format(
        "    ASSERT(_%s);",
        string.lower(info.var.name)
    ));
    
    if not info.array_size then
        temp_code_nl(string.format(
            "    %s(self,_len);",
            alloc_name(info.var.name)
        ));
    end
    
    if info.is_basic_type or info.is_pointer then        
        temp_code_nl(string.format(        
        "    self->%s = _%s;",
        member_name(info.var.name),
        string.lower(info.var.name)
        ));        
    else    
        need_i = true;
        temp_code_nl("    for(i = 0; i < _len; i++)");
        temp_code_nl("    {");
        
        local addr = "&";
        if info.is_string then
            addr = "";
        end
        temp_code_nl(string.format(
            "        %s(self,i,%s_%s[i]);",
            setter_array_elem_name(info.var.name),
            addr,
            string.lower(info.var.name)
        ));
        temp_code_nl("    }");
    end    
    
    if need_i then
        printnl("    int i = 0;");
        printnl("");
    end
    
    print(get_temp_code());
    
    printnl("    return OK;");    
    printnl("}");
end

--生成数组设置每个elem的函数声明--
function code_setter_declaration_array_elem(info)
    print("status_t");

    if info.is_basic_type then
        type_name = info.var_type.name;
    elseif info.is_string then
        type_name = info.var_type.const_name;
    else
        type_name = c_class_name(info.var_type.name);
    end
        
    local star = (info.is_pointer or info.is_object) and "*" or "";
    
    print(string.format(
        " %s(%s,int _index,%s %s_%s)",        
        setter_array_elem_name(info.var.name),
        this_pointer(),
        type_name,
        star,
        string.lower(info.var.name)
    )); 
end

--生成数组设置每个elem的函数体--
function code_setter_body_array_elem(info)
    printnl("");
    printnl("{");
    
    if info.is_string then
        printnl("    int len = 0;");
    end
    
    if not info.array_size then
        printnl(string.format(
            "    ASSERT(self->%s);",
            member_name(info.var.name)
        ));
    end
    
    printnl(string.format(
        "    ASSERT(_index >= 0 && _index < %s);",
        info.array_size and info.array_size or 
        "self->"..member_name_len(info.var.name)
    ));
    
    if info.is_pointer or info.is_basic_type then    
        printnl(string.format(
            "    self->%s[_index] = _%s;",
            member_name(info.var.name),
            string.lower(info.var.name)
        ));
    elseif info.is_string then    
        printnl(string.format(
            "    if(_%s == NULL)",
            string.lower(info.var.name)
        ));
        
        printfnl("    {");
        printfnl("        X_FREE(self->%s[_index]);",member_name(info.var.name));
        printnl("        return OK;");
        printfnl("    }");
        
        printnl(string.format(
            "    len = strlen(_%s);",
            string.lower(info.var.name)
        ));
        
        printnl(string.format(
            "    X_FREE(self->%s[_index]);",
            member_name(info.var.name)
        ));
        
        printnl(string.format(
            "    X_MALLOC(self->%s[_index],char,len+1);",
            member_name(info.var.name)
        ));
        
        printnl(string.format(
            "    memcpy(self->%s[_index],_%s,len+1);",
            member_name(info.var.name),
            string.lower(info.var.name)
        ));
    else
        printnl(string.format(
            "    ASSERT(_%s);",
            string.lower(info.var.name)
        ));
        
        printnl(string.format(
            "    %s(&self->%s[_index],_%s);",
            function_name(info.var_type,"copy"),
            member_name(info.var.name),
            string.lower(info.var.name)
        ));
    end
    
    printnl("    return OK;");
        
    printnl("}");
end

--返回未知长度的数组进行alloc操作的函数声明--
function code_alloc_declaration_unknown_array(info)
    print("status_t");
    print(string.format(
        " %s(%s,int _len)",        
        alloc_name(info.var.name),
        this_pointer()
    )); 
end

--返回未知长度的数组进行alloc操作的函数body--
function code_alloc_body_unknown_array(info,need_class_prefix)       
    printnl("");
    printnl("{");
    
    local var_type_name = info.var_type.name;
    if info.is_object then
        var_type_name = c_class_name(info.var_type.name);
    end
    
    if info.is_pointer then
        var_type_name = var_type_name.."*";
    end
    
    clear_temp_code();
    local need_i = false;
    
    temp_code_nl(string.format(
        "    if(self->%s == _len)",
        member_name_len(info.var.name)
    ));
    
    temp_code_nl("        return OK;");
    temp_code_nl("");
        
    if info.is_object and not info.is_pointer then
        need_i = true;
        temp_code_nl(string.format(
            "    for(i = 0; i < self->%s; i++)",
            member_name_len(info.var.name)
        ));
        temp_code_nl("    {");
        
        temp_code_nl(string.format(
            "        %s(&self->%s[i]);",
            function_name(info.var_type,"destroy"),
            member_name(info.var.name)
        ));
        
        temp_code_nl("    }");
    end
        
    temp_code_nl(string.format(
        "    X_FREE(self->%s);",
        member_name(info.var.name)
    ));
    
   temp_code_nl("");
    
	temp_code_nl("    if(_len > 0)");
	temp_code_nl("    {");
    
    temp_code_nl(string.format(
    "        X_MALLOC(self->%s,%s,_len);",
        member_name(info.var.name),var_type_name
    ));
    
    if info.is_basic_type or info.is_pointer or info.is_string then        
        temp_code_nl(string.format(        
        "        memset(self->%s,0,sizeof(%s)*_len);",
        member_name(info.var.name),
        var_type_name
        ));        
    else
    
        need_i = true;
        temp_code_nl("        for( i = 0; i < _len; i++)");
        temp_code_nl("        {");
        temp_code_nl(string.format(
            "            %s(&self->%s[i]);",
            function_name(info.var_type,"init"),
            member_name(info.var.name)        
        ));
        temp_code_nl("        }");
    end
     
	temp_code_nl("    }");
    
    temp_code_nl(string.format(
    "    self->%s = _len;",
    member_name_len(info.var.name)    
    ));
    
    temp_code_nl("    return OK;");
    
    if need_i then
        printnl("    int i;");
        printnl("");
    end
    
    print(get_temp_code());
    
    printnl("}");
end


--生成所有函数的setter代码--
function code_all_setter_cpp(idl_class)
    for_each_variables(idl_class.variables,function(info)   
		if info.is_no_setter then return end
        info.idl_class = idl_class;
        
        if not info.is_array then
            if info.is_string then
                code_begin_extra(setter_name(info.var.name));
                code_setter_declaration_string_not_array(info,true);
                code_setter_body_string_not_array(info);
                code_end_extra(setter_name(info.var.name));
                printnl("");                
            elseif info.is_basic_type then
                code_begin_extra(setter_name(info.var.name));
                code_setter_declaration_basic_not_array(info,true);
                code_setter_body_basic_not_array(info);
                code_end_extra(setter_name(info.var.name));
                printnl("");                
            elseif info.is_object then
                code_begin_extra(setter_name(info.var.name));
                code_setter_declaration_object_not_array(info,true);                
                code_setter_body_object_not_array(info);
                code_end_extra(setter_name(info.var.name));
                printnl("");                
            end
        else            
            if not info.array_size then
                code_begin_extra(alloc_name(info.var.name));
                code_alloc_declaration_unknown_array(info,true);
                code_alloc_body_unknown_array(info,true);
                code_end_extra(alloc_name(info.var.name));
                printnl("");
            end
            
            code_begin_extra(setter_name(info.var.name));
            code_setter_declaration_array(info,true);            
            code_setter_body_array(info);
            code_end_extra(setter_name(info.var.name));
            printnl("");                

            code_begin_extra(setter_array_elem_name(info.var.name));
            code_setter_declaration_array_elem(info,true);
            code_setter_body_array_elem(info);
            code_end_extra(setter_array_elem_name(info.var.name));
            printnl("");
        end
    end);
end

--生成所有函数的setter在头文件中的声明--
function code_all_setter_declaration_h(idl_class)
    for_each_variables(idl_class.variables,function(info)    
		if info.is_no_setter then return end
        info.idl_class = idl_class;
        
        if not info.is_array then
            if info.is_string then
                code_setter_declaration_string_not_array(info);
                printnl(";");            
            elseif info.is_basic_type then
                code_setter_declaration_basic_not_array(info);
                printnl(";");
            elseif info.is_object then
                code_setter_declaration_object_not_array(info);                
                printnl(";");             
            end
        else            
            if not info.array_size then
                code_alloc_declaration_unknown_array(info);
                printnl(";");
            end
            
            code_setter_declaration_array(info);
            printnl(";");
            
            code_setter_declaration_array_elem(info);
            printnl(";");            
        end
    end);
end

--生成所有的cpp代码--
function code_cpp(idl_class)
    printnl(string.format(
        "#include \"%s\"",
        name_to_include_file(idl_class.name)
    ));
    
	common_include_c();
    printnl("");
    
    code_cpp_init_basic(idl_class);
    printnl("");
    code_cpp_init(idl_class);
    printnl("");
    code_cpp_destroy(idl_class);
    printnl("");
    if code_switch.copy_comp_print then
        code_cpp_copy(idl_class);
        printnl("");
        code_cpp_comp(idl_class);
        printnl("");
        code_cpp_print(idl_class);
        printnl("");        
    end
    
    printnl("");
    code_all_getter_cpp(idl_class);
    
    printnl("");
    code_all_setter_cpp(idl_class);
    
    if code_switch.code_mark then
        printnl("/*@@ Insert Function Here @@*/");
    end    
end


