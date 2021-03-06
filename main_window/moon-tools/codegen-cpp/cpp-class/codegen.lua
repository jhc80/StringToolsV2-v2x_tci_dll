require("common")
require("idl_helper");
require("cpp_base_codegen");

local g_cpp_base_codegen = nil;

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
----------------------------------------------
function ptab(level)
    local str = "";
    for i=1,level,1 do
        str = str.."    ";
    end
    return str;
end               
---------------------------------------------
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
    return printnl("/*@@End  Function "..name.."@@*/");
end
--------------------------------------------------------
function for_each_variables(variables,callback)
    if not variables then return end
    
    for _,var in ipairs(variables) do	
        local var_type = var.type;
        local is_pointer = IdlHelper.Type.IsPointer(var_type);
        local is_array,array_size = IdlHelper.Type.IsArray(var_type);
        local is_string = IdlHelper.Type.IsString(var_type);
        local is_basic_type = IdlHelper.Type.IsBasicType(var_type);
        local is_optional = IdlHelper.Var.IsOptional(var);
        local c_json_value = IdlHelper.Type.GetCJsonValue(var_type);
        local c_json_type =  IdlHelper.Type.GetCJsonType(var_type);        
		local is_struct = IdlHelper.Type.IsStruct(var);

        local is_weak_ptr = IdlHelper.Var.IsWeakPtr(var) 
            and is_pointer and not is_basic_type;
       
        if is_weak_ptr then
            is_pointer = false;
        end		
        
        local info = {};
        info.var = var;
        info.var_type = var_type;
        info.is_pointer = is_pointer;
        info.is_array = is_array;
        info.array_size = array_size;
        info.is_string = is_string;
        info.is_basic_type = is_basic_type;
        info.is_object = not is_basic_type;
        info.is_optional = is_optional;
        info.c_json_value = c_json_value;
        info.c_json_type = c_json_type;
        info.is_weak_ptr = is_weak_ptr;		
		info.is_no_setter = IdlHelper.Var.IsNoSetter(var);
		info.is_no_getter = IdlHelper.Var.IsNoGetter(var);
		info.is_no_xml = IdlHelper.Var.IsNoXml(var);
		info.is_no_bson = IdlHelper.Var.IsNoBson(var);
		info.is_no_copy = IdlHelper.Var.IsNoCopy(var);
		info.is_no_print = IdlHelper.Var.IsNoPrint(var);
		
		info.is_struct = is_struct;
		var_type.is_struct = is_struct;
		
        callback(info);
    end
end

--?????????????????????
function for_each_variables_sorted(variables, callback)
    if not variables then return end
    local sorted = {};
    for _,var in ipairs(variables) do	
        table.insert(sorted,var);
    end

    table.sort(sorted,function(e1,e2)
        return string.lower(e1.name) < string.lower(e2.name);
    end);

    for_each_variables(sorted,callback);
end

--?????????namespace???????????????
function c_class_name_with_ns(type)
    if type.namespace then
		if name_space ~= type.namespace then
			return type.namespace.."::"..c_class_name(type.name);
		end
    end	
	
	if type.is_struct then
		return c_struct_name(type.name);
	end
	
    return c_class_name(type.name);
end

--???????????????????????????--
function covert_special_types(idl_class)
    for_each_variables(idl_class.variables,function(info)        
        if info.is_string then 
            info.var_type.name = "Mem" 
            info.var_type.is_string = true;
        end
    end);
end

--???????????????????????????--
function code_variables_define(variables)
	for_each_variables(variables,function(info)    
        print("    ");
        
        if info.is_weak_ptr then
            print("CWeakPointer<");
        end
    
		print(
			info.is_basic_type 
			and info.var_type.name 
			or c_class_name_with_ns(info.var_type)
		);
		     
        if info.is_weak_ptr then
            print(">");
        end

		local name_prefix="";

        if info.is_optional then
            if info.is_object or info.is_string or info.is_basic_type then
                name_prefix = name_prefix.."*";
            end
        else
            if info.is_pointer  then
                name_prefix = name_prefix.."*";
            end            
            if info.is_array and not info.array_size then
                name_prefix = name_prefix.."*";
            end
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

--???????????????include ??????--
function code_all_includes(idl_class)
    local all_names = {};
    local all_names_sorted = {};
    
    function add_name(name)
        if not all_names[name] then
            all_names[name] = true;
            table.insert(all_names_sorted,name);
        end
    end    

    if code_switch.bson then
        add_include("minibson");
    end
	
    
	local all_bases = IdlHelper.Class.GetAllBases(idl_class);	
	if all_bases then
		for _,base in ipairs(all_bases) do
            add_name(to_file_name(base.name,name_space));
		end
	end
    
    for_each_variables(idl_class.variables,function(info)        
        if 	info.is_object 
			and info.var.name ~= idl_class.name 
			and not info.is_string 
			and not info.var_type.is_struct
		then
            add_name(to_file_name(info.var_type.name,info.var_type.namespace));
        end
        
        if info.is_weak_ptr then
            add_include("weak_pointer");
        end
    end);

    code_begin_marker("Inlcudes");
    
    if code_switch.lib_config then
        add_include("libconfig",true);
    end

    if code_switch.cjson then
        add_include("cJSON");
    end
    
	if code_switch.xml or code_switch.xml2 then
        add_include("xml");
    end
	
	if code_switch.task_container then
        add_include("taskmgr");
    end
		
    for _,name in ipairs(all_names_sorted) do    
        add_include(name);
    end
       
    local user_includes = g_cpp_base_codegen:GetUserIncludes();
    if user_includes then
        for _,name in ipairs(user_includes) do
            add_include(name);
        end
    end
    
    code_end_marker("Inlcudes");
    
    common_includes_h(idl_class);    
end

--?????????????????????--
function code_h(idl_class)
	g_cpp_base_codegen = CppBaseCodeGen.new(idl_class,code_switch);
	
	printnl(string.format(
		"#ifndef __%s_H",to_upper_underline_case(to_file_name(idl_class.name,name_space))
	));
	
	printnl(string.format(
		"#define __%s_H",to_upper_underline_case(to_file_name(idl_class.name,name_space))
	));
		
	printnl("");
    code_all_includes(idl_class);
	printnl("");
    
    local ns = g_cpp_base_codegen:Code_NameSpaceBegin();
    if ns then
        if code_switch.code_mark then
            code_begin_marker("namespace_begin");
        end
        
        printnl(ns);
        
        if code_switch.code_mark then
            code_end_marker("namespace_begin");
        end
        
        printnl("");
    end
        
    if code_switch.code_mark then
        local all_bases_code = g_cpp_base_codegen:Code_ClassBase(true);
        printfnl("class %s",c_class_name(idl_class.name));
        code_begin_marker("Bases");
        print(all_bases_code);
        code_end_marker("Bases");
    else
        local all_bases_code = g_cpp_base_codegen:Code_ClassBase();    
        print(string.format("class %s%s",
            c_class_name(idl_class.name),
            all_bases_code
        ));
            
    end
	printnl("{");
    
    code_begin_marker("Members");
    
    local code_class = g_cpp_base_codegen:Code_ClassHeader();
    if code_class~="" then
        printnl("public:");
        printnl(code_class);
    end
    
	if idl_class.variables then
		printnl("public:");
		code_variables_define(idl_class.variables);
	end
    
    code_end_marker("Members");

	printnl("");
	printnl("public:");
	
	
	printnl("    "..c_class_name(idl_class.name).."();");
	printnl("    virtual ~"..c_class_name(idl_class.name).."();");
	printnl("");
	printnl("    status_t InitBasic();");
    
    if code_switch.task_container then
        printnl("    status_t Init(CTaskMgr *_taskmgr);");	
    else
        printnl("    status_t Init();");	
    end    
    
	printnl("    status_t Destroy();");	
	
	if code_switch.copy_comp_print then
		printnl("");
		printnl("    status_t Copy("..c_class_name(idl_class.name).." *_p);");	
		printnl("    int Comp("..c_class_name(idl_class.name).." *_p);");	
		printnl("    status_t Print(CFileBase *_buf);");
	end
  
    printnl("");

    code_begin_marker("Getter_H");
    code_all_getter_declaration_h(idl_class);
    code_end_marker("Getter_H");

    code_begin_marker("Setter_H");
    code_all_setter_declaration_h(idl_class);
    code_end_marker("Setter_H");

    if code_switch.bson then
        printnl("");
		code_begin_marker("Bson");
        printnl("    status_t SaveBson(CMiniBson *_bson);");
        printnl("    status_t SaveBson(CMem *_mem);");
        printnl("    status_t LoadBson(CMiniBson *_bson);");
        printnl("    status_t LoadBson(CFileBase *_file);");
		code_end_marker("Bson");
    end

    if code_switch.lib_config then
		printnl("");
		code_begin_marker("LibConfig");	
        printnl("    status_t LoadConfig(const config_setting_t *_settings);");
        printnl("    status_t LoadConfig(const char *_filename,const char *_path);");
        printnl("    status_t SaveConfig(config_setting_t *_settings);");
        printnl("    status_t SaveConfig(const char *filename,const char *root_name);");
		code_end_marker("LibConfig");	
    end

    if code_switch.cjson then
	    printnl("");
		code_begin_marker("JSON");	
        printnl("    status_t LoadJson(const cJSON *_json);");
        printnl("    status_t LoadJson(const char *_json);");
        printnl("    status_t SaveJson(cJSON *_root);");
        printnl("    status_t SaveJson(CFileBase *_file);");
		code_end_marker("JSON");	
    end
    
	if code_switch.xml or code_switch.xml2 then
	    printnl("");
		code_begin_marker("XML");
        printnl("    status_t LoadXml(CXmlNode *_root);");

        if code_switch.xml2 then
            printnl("    status_t SaveXml(CFileBase *_xml, const char *node_name);");
        else
            printnl("    status_t SaveXml(CFileBase *_xml);");
        end
		printnl("    status_t LoadXml(const char *fn, const char *path);");
		printnl("    status_t SaveXml(const char *fn, const char *node_name);");
		code_end_marker("XML");
    end
        
    printnl("};");	
	printnl("");
    
    local ns = g_cpp_base_codegen:Code_NameSpaceEnd();
    if ns then
        printnl("");
        if code_switch.code_mark then
            code_begin_marker("namespace_end");
        end    
        printnl(ns);
        if code_switch.code_mark then
            code_end_marker("namespace_end");
        end        
        printnl("");
    end
    
	printnl("#endif");
end

--????????????????????????--
function get_init_value(info)
    local init_value = "0";

    if info.is_pointer then
        init_value = "NULL";
    end

    if info.var.init_value then
        init_value = info.var.init_value;
    end
    
    return init_value;
end

--??????InitBasic???????????????--
function code_cpp_init_basic(idl_class)
	printnl(string.format(
        "status_t %s::InitBasic()",
        c_class_name(idl_class.name),
        c_class_name(idl_class.name)
    ));    
    printnl("{");
        
    clear_temp_code();
    local need_i = false;
        
    function pc_array_with_array_size(info)
		if info.is_struct then		
			 temp_code_nl(string.format(
                "    memset(%s,0,sizeof(%s));",
                member_name(info.var.name),
				member_name(info.var.name)
            ));		
			return
		end
		
        need_i = true;
        temp_code_nl(string.format(
            "    for(i = 0; i < %s; i++)",
            info.array_size
        ));
        
        temp_code_nl("    {");
        
        if info.is_basic_type or info.is_pointer then
            temp_code_nl(string.format(
                "        this->%s[i] = %s;",
                member_name(info.var.name),
                get_init_value(info)
            )); 
        else
            temp_code_nl(string.format(
                "        this->%s[i].InitBasic();",
                member_name(info.var.name)
            ));
        end
        
        temp_code_nl("    }");
    end
    
    function pc_array_without_array_size(info)
        temp_code_nl(string.format(
            "    this->%s = NULL;",
            member_name(info.var.name)
        )); 
        temp_code_nl(string.format(
            "    this->%s = 0;",
            member_name_len(info.var.name)
        )); 
    end
    
    function pc_not_array(info)
        if info.is_optional then
            temp_code_nl(string.format(
                "    this->%s = NULL;",
                member_name(info.var.name)
            ));
        elseif info.is_basic_type or info.is_pointer then
            temp_code_nl(string.format(
                "    this->%s = %s;",
                member_name(info.var.name),
                get_init_value(info)
            ));
        else
			if info.is_struct then
				temp_code_nl(string.format(
					"    memset(&%s,0,sizeof(%s));",
					member_name(info.var.name),
					member_name(info.var.name)
				));
			else
				temp_code_nl(string.format(
					"    this->%s.InitBasic();",
					member_name(info.var.name)
				));
			end
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
    
    print(g_cpp_base_codegen:Code_InitBasic());
    print(get_temp_code());
    code_end_marker("InitBasic");
            
    printnl("    return OK;");
    printnl("}");
end

--??????Init???????????????--
function code_cpp_init(idl_class)
    local task_container = "";
    if code_switch.task_container then
        task_container = "CTaskMgr *_taskmgr";
    end

	printnl(string.format(
        "status_t %s::Init(%s)",
        c_class_name(idl_class.name),
        task_container
    ));    
    printnl("{");
    
    clear_temp_code();
    local need_i = false;
    
    function pc_array_with_array_size(info)
        if info.is_object and not info.is_struct then
            need_i = true;
            temp_code_nl(string.format(
                "    for(i = 0; i < %s; i++)",
                info.array_size
            ));
            temp_code_nl("    {");
            
            temp_code_nl(string.format(
                "        this->%s[i].Init();",
                member_name(info.var.name)
            ));
            
            temp_code_nl("    }");
        end
    end
    
    function pc_not_array(info)
        if info.is_object 
			and not info.is_pointer 
			and not info.is_optional 
			and not info.is_struct
		then
            temp_code_nl(string.format(
                "    this->%s.Init();",
                member_name(info.var.name)
            ));
            
            if info.var.init_value then
            
            temp_code_nl(string.format(
                "    this->%s(%s);",
                setter_name(info.var.name,info),
                info.var.init_value,
                member_name(info.var.name)
            ));
            end            
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
    
	printnl("    this->InitBasic();");    
    code_begin_marker("Init");
    print(g_cpp_base_codegen:Code_Init());    

    if need_i then
        printnl("    int i = 0;");        
        printnl("");
    end
    print(get_temp_code());
    code_end_marker("Init");
    printnl("    return OK;");
    printnl("}");
end

--??????Destroy?????????--
function code_cpp_destroy(idl_class)
	printnl(string.format(
        "status_t %s::Destroy()",
        c_class_name(idl_class.name),
        c_class_name(idl_class.name)
    ));    
    printnl("{");

    code_begin_marker("Destroy");
    print(g_cpp_base_codegen:Code_Destroy());
    
    clear_temp_code();
    local need_i = false;
    
    function pc_array_with_array_size_object(info)
		if info.is_struct then
			return
		end
        need_i = true;
        temp_code_nl(string.format(
            "    for(i = 0; i < %s; i++)",
            info.array_size
        ));
        temp_code_nl("    {");
        
        temp_code_nl(string.format(
            "        this->%s[i].Destroy();",
            member_name(info.var.name)
        ));
        
        temp_code_nl("    }");
    end
    
    function pc_array_no_array_size(info)
        temp_code_nl(string.format(
            "    DEL_ARRAY(%s);",
            member_name(info.var.name)
        ));
    end
    
    function pc_not_array_object(info)
        if info.is_optional then
            temp_code_nl(string.format(
                "    DEL(this->%s);",
                member_name(info.var.name)
            ));
        else
            if not info.is_pointer and not info.is_struct then
                temp_code_nl(string.format(
                    "    this->%s.Destroy();",
                    member_name(info.var.name)
                ));
            end
        end
    end

    function pc_not_array_basic_type(info)
        if info.is_optional then
            temp_code_nl(string.format(
                "    DEL(this->%s);",
                member_name(info.var.name)
            ));
        end
    end
        
    for_each_variables(idl_class.variables,function(info)         
        if info.is_array then        
            if info.array_size then
                if info.is_object then
                    pc_array_with_array_size_object(info);
                end
            else
                pc_array_no_array_size(info);
            end
        else 
            if info.is_object then
                pc_not_array_object(info);
            elseif info.is_basic_type then
                pc_not_array_basic_type(info);
            end
        end    
    end);
    
    if need_i then
        printnl("    int i = 0;");        
        printnl("");
    end
        
    print(get_temp_code());
    code_end_marker("Destroy");
    printnl("    this->InitBasic();");
    printnl("    return OK;");
    printnl("}");
end

--??????Copy???????????????--
function code_cpp_copy(idl_class)
	printnl(string.format(
        "status_t %s::Copy(%s *_p)",
        c_class_name(idl_class.name),
        c_class_name(idl_class.name),
        c_class_name(idl_class.name)
    ));    
    printnl("{");
    printnl("    ASSERT(_p);");
    printnl("    if(this == _p)return OK;");
    printnl("");

    code_begin_marker("Copy");
   
    print(g_cpp_base_codegen:Code_Copy()); 
    
    clear_temp_code();
    local need_i = false;
    
    function pc_array(info)
        need_i = true; 
        local array_size = info.array_size;
        
        if not array_size then
            array_size = member_name_len(info.var.name);
            
            temp_code_nl(string.format(
                "    this->%s(_p->%s);",
                alloc_name(info.var.name),
                member_name_len(info.var.name)
            ));
            
            
        end
        
        temp_code_nl(string.format(
            "    for(i = 0; i < %s; i++)",
            array_size
        ));
        temp_code_nl("    {");
        if info.is_basic_type or info.is_pointer or info.is_struct then
            temp_code_nl(string.format(
                "        this->%s[i] = _p->%s[i];",
                member_name(info.var.name),
                member_name(info.var.name)
            )); 
        else
            temp_code_nl(string.format(
                "        this->%s[i].Copy(&_p->%s[i]);",
                member_name(info.var.name),
                member_name(info.var.name)
            ));
        end
        temp_code_nl("    }");
    end
    
    function pc_not_array(info)
        if info.is_optional then
            temp_code_nl(string.format(
                "    this->%s(_p->%s());",
                setter_name(info.var.name,info),
                getter_name(info.var.name,info)
            ));
        else        
            if info.is_basic_type or info.is_pointer or info.is_struct then
                temp_code_nl(string.format(
                    "    this->%s = _p->%s;",
                    member_name(info.var.name),
                    member_name(info.var.name)
                ));
            else            
                temp_code_nl(string.format(
                    "    this->%s.Copy(&_p->%s);",
                    member_name(info.var.name),
                    member_name(info.var.name)
                ));
            end       
        end
    end
    
    for_each_variables(idl_class.variables,function(info)         
		if info.is_no_copy then return end
        if info.is_array then 
            pc_array(info);
        else 
            pc_not_array(info);
        end    
    end);
    
    if need_i then
        printnl("    int i = 0;");        
        printnl("");
    end
    
    print(get_temp_code());

    code_end_marker("Copy");
        
    printnl("    return OK;");
    printnl("}");
end

--??????Copy???????????????--
function code_cpp_comp(idl_class)
	printnl(string.format(
        "int %s::Comp(%s *_p)",
        c_class_name(idl_class.name),
        c_class_name(idl_class.name),
        c_class_name(idl_class.name)
    ));    
    printnl("{");
    printnl("    ASSERT(_p);");
    printnl("    if(this == _p)return 0;");
    printnl("    ASSERT(0);");
    printnl("    return 0;");
    printnl("}");
    
end


--??????Print???????????????--
function code_cpp_print(idl_class)
	printnl(string.format(
        "status_t %s::Print(CFileBase *_buf)",
        c_class_name(idl_class.name),
        c_class_name(idl_class.name)
    ));    
    printnl("{");

    code_begin_marker("Print");
    
    printnl("    ASSERT(_buf);");
    
    print(g_cpp_base_codegen:Code_Print());
    
    clear_temp_code();
    local need_i = false;
    
    function pc_array_basic_type(info)
        temp_code_nl(string.format(
            "        _buf->Log(\"%s,\",%s[i]);",
            info.is_pointer and "0x%p" or IdlHelper.Type.GetPrintFormat(info.var_type),
            member_name(info.var.name)                        
        )); 
    end
    
    function pc_array_object(info)
        local tab = 2;
        local dot_or_arrow = ".";
        
		if info.is_struct then
			return
		end
		
        if info.is_weak_ptr then        
            temp_code_nl(string.format(
                "%sif(this->%s[i].get())",
                ptab(tab),
                member_name(info.var.name)
            ));
            
            temp_code_nl(string.format(
                "%s{",ptab(tab)
            ));
                
            tab = tab + 1;
            dot_or_arrow = "->";
        end
        
        temp_code_nl(string.format(
            "%s_buf->Log(\"[%%d]={\",i);",
        ptab(tab)));
        
        temp_code_nl(string.format(
            "%s_buf->IncLogLevel(1);",
        ptab(tab)));
        
        temp_code_nl(string.format(
            "%sthis->%s[i]%sPrint(_buf);",
            ptab(tab),
            member_name(info.var.name),
            dot_or_arrow
        ));
        temp_code_nl(string.format(
            "%s_buf->IncLogLevel(-1);",
        ptab(tab)));
        
        temp_code_nl(string.format(
            "%s_buf->Log(\"},\");",
        ptab(tab)));
        
        if info.is_weak_ptr then
            tab = tab - 1;
            temp_code_nl(string.format(
                "%s}",ptab(tab)
            ));
        end        
    end
    
    function pc_array_string(info)
        temp_code_nl(string.format(
            "        _buf->Log(\"[%%d] = %%s\",i,"
        ));
        
        temp_code_nl(string.format(
            "            %s[i].StrLen()>0?%s[i].CStr():\"<null>\"",
            member_name(info.var.name),            
            member_name(info.var.name)
        ));        
        temp_code_nl("        );");
    end
    
    function pc_array(info)
		if info.is_struct then
			return
		end
	
        need_i = true;
        
        temp_code_nl(string.format(
            "    _buf->Log(\"%s = [\");",
            info.var.name
        ));
        temp_code_nl("    _buf->IncLogLevel(1);");
        
        local array_size = info.array_size 
            and info.array_size 
            or member_name_len(info.var.name);

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
        
        temp_code_nl("    _buf->IncLogLevel(-1);");
        temp_code_nl("    _buf->Log(\"]\");");
    end
    
    function pc_not_array_basic_type(info)
        if info.is_optional then            
            temp_code_nl(string.format(
                "    if(%s)",
                member_name(info.var.name)
            ));

            temp_code_nl("    {");
            temp_code_nl(string.format(
                "        _buf->Log(\"%s = %s\",*%s);",
                info.var.name,
                info.is_pointer and "0x%p" or IdlHelper.Type.GetPrintFormat(info.var_type),
                member_name(info.var.name)                        
            ));                 
            temp_code_nl("    }");
        else
            temp_code_nl(string.format(
                "    _buf->Log(\"%s = %s\",%s);",
                info.var.name,
                info.is_pointer and "0x%p" or IdlHelper.Type.GetPrintFormat(info.var_type),
                member_name(info.var.name)                        
            ));                 
        end
    end
    
    function pc_not_array_object(info)
        local tab = 1;
        local arrow_or_dot = ".";

        if info.is_struct then
			return
		end

        if info.is_optional or info.is_weak_ptr then  
            local get_str= info.is_weak_ptr and ".get()" or "";            
            arrow_or_dot = "->";
            temp_code_nl(string.format(
                "%sif(this->%s%s)",
                ptab(tab),member_name(info.var.name),
                get_str
            ));
            
            temp_code_nl(string.format(
                "%s{",
            ptab(tab)));            
            tab = tab + 1;
        end
        
        temp_code_nl(string.format(
            "%s_buf->Log(\"%s = {\");",
            ptab(tab),info.var.name                    
        ));

        temp_code_nl(string.format(
            "%s_buf->IncLogLevel(1);",
        ptab(tab)));        
        
        temp_code_nl(string.format(
            "%sthis->%s%sPrint(_buf);",
            ptab(tab),member_name(info.var.name),
            arrow_or_dot
        ));
        
        temp_code_nl(string.format(
            "%s_buf->IncLogLevel(-1);",
        ptab(tab)));
        
        temp_code_nl(string.format(
            "%s_buf->Log(\"\");",
        ptab(tab)));
        
        temp_code_nl(string.format(
            "%s_buf->Log(\"},\");",
        ptab(tab)));
        
        if info.is_optional or info.is_weak_ptr then
            tab = tab - 1;
            temp_code_nl(string.format(
                "%s}",
            ptab(tab)));
        end
    end
    
    function pc_not_array_string(info)
        temp_code_nl("");
        
        local tab = "    ";
        local arrow_or_dot = ".";
        
        if info.is_optional then        
            arrow_or_dot = "->";
            temp_code_nl(string.format(
                "%sif(this->%s)",
                tab,member_name(info.var.name)
            ));
            
            temp_code_nl(string.format(
                "%s{",
            tab));

            tab = tab.."    ";
        end
        
        temp_code_nl(string.format(
            "%s_buf->Log(\"%s = %%s\",",
            tab,info.var.name
        ));
        
        temp_code_nl(string.format(
            "%s    %s%sStrLen()>0?%s%sCStr():\"<null>\"",
            tab,
            member_name(info.var.name),arrow_or_dot,            
            member_name(info.var.name),arrow_or_dot
        ));
        
        temp_code_nl(string.format(
            "%s);",
        tab));

        if info.is_optional then
            tab = "    ";
            temp_code_nl(string.format(
                "%s}",
            tab));
        end        
    end
    
    for_each_variables(idl_class.variables,function(info)  
		if info.is_no_print then return end
        if info.is_array then        
            pc_array(info);
        else 
            if info.is_basic_type or info.is_pointer then
                pc_not_array_basic_type(info);
            elseif info.is_string then
                pc_not_array_string(info);
            else
                pc_not_array_object(info);
            end        
        end    
    end);
    
    if need_i then
        printnl("    int i = 0;");        
        printnl("");
    end
    
    print(get_temp_code());

    code_end_marker("Print");

    printnl("    return OK;");
    printnl("}");
end

--??????Getter???????????????--
function code_getter_declaration(info,need_class_prefix)

    if info.is_weak_ptr and info.is_array then
        print("CWeakPointer<");
    end

    if info.is_basic_type then
        print(info.var_type.name);
    else
        print(c_class_name_with_ns(info.var_type));
    end
    
    if info.is_weak_ptr and info.is_array then
        print(">");
    end
    
    if info.is_array or info.is_pointer or info.is_object or info.is_optional then
        print("*");
    end
    
    if info.is_array and info.is_pointer then
        print("*");
    end    
    
    local class_prefix=need_class_prefix and 
        c_class_name(info.idl_class.name).."::" or "";
    
    print(string.format(
        " %s%s()",
        class_prefix,
        getter_name(info.var.name,info)
    ));  
end

--??????Getter??????body--
function code_getter_body(info)
    printnl("");
    printnl("{");
    
    if info.is_object and 
       not info.is_pointer and 
       not info.is_array and
       not info.is_optional and 
       not info.is_weak_ptr
    then    
        printnl(string.format(
            "    return &%s;",
            member_name(info.var.name)
        ));     
    elseif info.is_weak_ptr and not info.is_array then
        printnl(string.format(
            "    return %s.get();",
            member_name(info.var.name)
        )); 
    else    
        printnl(string.format(
            "    return %s;",
            member_name(info.var.name)
        )); 
    end
    printnl("}");
end

--?????????????????? string???get????????????--
function code_getter_declaration_string(info,need_class_prefix)
    print("const char*");
    
    local class_prefix=need_class_prefix and 
        c_class_name(info.idl_class.name).."::" or "";


    print(string.format(
        " %s%sStr()",
        class_prefix,
        getter_name(info.var.name,info)
    )); 
end

--?????????????????? string???get?????????--
function code_getter_body_string(info,need_class_prefix)
    printnl("");
    printnl("{");
    
    local tab = "    ";
    local arrow_or_dot = ".";
    
    if info.is_optional then
        arrow_or_dot ="->";
        printfnl("    if(this->%s)",
            member_name(info.var.name)
        );
        printfnl("    {");
        tab = "        ";
    end
    
    printnl(string.format(
        "%sreturn %s%sCStr();",
        tab,member_name(info.var.name),
        arrow_or_dot
    ));

    if info.is_optional then        
        printfnl("    }");
        printnl("");
        printfnl("    return NULL;");
    end
    
    printnl("}");
end

--?????????????????????????????????????????????--
function code_getter_declaration_array_len(info,need_class_prefix)
    print("int");
    local class_prefix=need_class_prefix and 
        c_class_name(info.idl_class.name).."::" or "";
    
    print(string.format(
        " %s%s()",
        class_prefix,
        getter_array_len_name(info.var.name)
    )); 
end

--???????????????????????????????????????body--
function code_getter_body_array_len(info)
    printnl("");
    printnl("{");
    
    local len_name = member_name_len(info.var.name);
    
    if info.array_size then
        len_name = info.array_size;
    end
    
    printnl(string.format(
        "    return %s;",
        len_name
    ));            
    printnl("}");
end

--???????????????????????????????????????????????????--
function code_getter_declaration_get_array_elem(info,need_class_prefix)
    if info.is_basic_type then
        print(info.var_type.name);
    else
        print(c_class_name_with_ns(info.var_type));
    end
    
    if (info.is_array and info.is_pointer) or info.is_object then
        print("*");
    end

    
   local class_prefix=need_class_prefix and 
        c_class_name(info.idl_class.name).."::" or "";
    
    print(string.format(
        " %s%s(int _index)",
        class_prefix,
        getter_array_elem_name(info.var.name)
    )); 
end

--????????????????????????????????????????????????--
function code_getter_body_get_array_elem(info,need_class_prefix)
    printnl("");
    printnl("{");
    
    if not info.array_size then
        printnl(string.format(
            "    ASSERT(this->%s);",
            member_name(info.var.name)
        ));
    end
    
    printnl(string.format(
        "    ASSERT(_index >= 0 && _index < %s);",
        info.array_size and info.array_size or 
        member_name_len(info.var.name)
    ));
    
    if info.is_pointer or info.is_basic_type then    
        printnl(string.format(
            "    return %s[_index];",
            member_name(info.var.name)
        ));
    elseif info.is_weak_ptr then
        printnl(string.format(
            "    return %s[_index].get();",
            member_name(info.var.name)
        ));    
    else
        printnl(string.format(
            "    return &%s[_index];",
            member_name(info.var.name)
        ));    
    end        
    printnl("}");
end

--?????????????????????getter???cpp??????--
function code_all_getter_cpp(idl_class)
    for_each_variables(idl_class.variables,function(info)    
		if info.is_no_getter then return end
        info.idl_class = idl_class;

        code_begin_extra(getter_name(info.var.name,info));
        code_getter_declaration(info,true);
        code_getter_body(info);
        code_end_extra(getter_name(info.var.name,info));
        printnl("");
        if not info.is_array and info.is_string and not info.is_pointer then
            code_begin_extra(getter_name(info.var.name,info).."Str");
            code_getter_declaration_string(info,true);       
            code_getter_body_string(info);
            code_end_extra(getter_name(info.var.name,info).."Str");
            printnl("");
        end
        
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

--?????????????????????getter??????--
function code_all_getter_declaration_h(idl_class)
    for_each_variables(idl_class.variables,function(info)    
		if info.is_no_getter then return end
        info.idl_class = idl_class;
        print("    ");
        code_getter_declaration(info);
        printnl(";");
        
        if not info.is_array and info.is_string then
            print("    ");
            code_getter_declaration_string(info);
            printnl(";");
        end
        
        if info.is_array then
            print("    ");
            code_getter_declaration_array_len(info);
            printnl(";");
            
            print("    ");
            code_getter_declaration_get_array_elem(info);            
            printnl(";");
        end
    end);
end

--??????setter?????????????????????????????????????????????????????????--
function code_setter_declaration_basic_not_array(info,need_class_prefix)

   print("status_t");
    
   local class_prefix=need_class_prefix and 
        c_class_name(info.idl_class.name).."::" or "";
    
    print(string.format(
        " %s%s(%s %s_%s)",
        class_prefix,
        setter_name(info.var.name,info),
        info.var_type.name,
        (info.is_pointer or info.is_optional) and "*" or "",
        string.lower(info.var.name)
    )); 
end

--??????setter??????????????????????????????????????????????????????--
function code_setter_body_basic_not_array(info,need_class_prefix)

    printnl("");
    printnl("{");
    
    if info.is_optional then

        printfnl(
            "    if(_%s == NULL)",
            string.lower(info.var.name)
        );
        printnl("    {");
        printfnl("        DEL(this->%s);",member_name(info.var.name));
        printfnl("        return OK;");
        printnl("    }");
        printnl("");

        printfnl("    if(this->%s == NULL)",member_name(info.var.name));
        printnl("    {");
        printfnl("        NEW(this->%s,%s);",
            member_name(info.var.name),
            info.var_type.name
        );
        printnl("    }");
        printnl("");
        printnl(string.format(
            "    *%s = *_%s;",
            member_name(info.var.name),
            string.lower(info.var.name)
        )); 
    else
        printnl(string.format(
            "    this->%s = _%s;",
            member_name(info.var.name),
            string.lower(info.var.name)
        )); 
    end

    printnl("    return OK;");    
    printnl("}");
end

--??????optional?????? setter?????????????????????????????????????????????????????????--
function code_setter_declaration_basic_not_array_optional(info,need_class_prefix)
    print("status_t");    
    local class_prefix=need_class_prefix and 
        c_class_name(info.idl_class.name).."::" or "";    
    print(string.format(
        " %s%s(%s _%s)",
        class_prefix,
        setter_name(info.var.name,info),
        info.var_type.name,
        string.lower(info.var.name)
    )); 
end

--??????optional??????setter????????????????????????????????????????????????????????????--
function code_setter_body_basic_not_array_optional(info,need_class_prefix)
    printnl("");
    printnl("{");
    printfnl("    return this->%s(&_%s);",
        setter_name(info.var.name,info),
        string.lower(info.var.name)
     );    
    printnl("}");
end

--??????setter???????????????????????????????????????????????????--
function code_setter_declaration_object_not_array(info,need_class_prefix)

   print("status_t");
    
   local class_prefix=need_class_prefix and 
        c_class_name(info.idl_class.name).."::" or "";
    
    print(string.format(
        " %s%s(%s *_%s)",
        class_prefix,
        setter_name(info.var.name,info),
        c_class_name_with_ns(info.var_type),
        string.lower(info.var.name)
    )); 
end

--??????setter????????????????????????????????????????????????--
function code_setter_body_object_not_array(info)

    printnl("");
    printnl("{");

    if info.is_pointer then
        printnl(string.format(
          "    this->%s = _%s;",
          member_name(info.var.name),
          string.lower(info.var.name)
        )); 
        printnl("    return OK;");
	elseif info.is_struct then
		printnl(string.format(
            "    ASSERT(_%s);",
            string.lower(info.var.name)
        ));
		if not info.is_optional then
			printnl(string.format(
			  "    this->%s = *_%s;",
			  member_name(info.var.name),
			  string.lower(info.var.name)
			)); 			
		else
			printfnl("    this->%s();",create_optional_name(info.var.name));
			printnl(string.format(
			  "    *(this->%s) = *_%s;",
			  member_name(info.var.name),
			  string.lower(info.var.name)
			));
		end
        printnl("    return OK;");
    else        
        if not info.is_optional then
            printnl(string.format(
                "    ASSERT(_%s);",
                string.lower(info.var.name)
            ));
        
            local copy_or_weak_ref="Copy";
            if info.is_weak_ptr then
                copy_or_weak_ref="WeakRef";
            end
        
            printnl(string.format(
                "    return this->%s.%s(_%s);",
                member_name(info.var.name),
                copy_or_weak_ref,
                string.lower(info.var.name)
            )); 
        else
            printfnl(
                "    if(_%s == NULL)",
                string.lower(info.var.name)
            );
            printnl("    {");
            printfnl("        DEL(this->%s);",member_name(info.var.name));
            printfnl("        return OK;");
            printnl("    }");
            printnl("");
                
            printfnl("    this->%s();",create_optional_name(info.var.name));
            
            printfnl("    ASSERT(this->%s);",member_name(info.var.name));
            printnl(string.format(
              "    return this->%s->Copy(_%s);",
              member_name(info.var.name),
              string.lower(info.var.name)
            )); 
        end
    end
    printnl("}");
end

--????????????string ?????????setter???????????????????????????--
function code_setter_declaration_string_not_array(info,need_class_prefix)

   print("status_t");
    
   local class_prefix=need_class_prefix and 
        c_class_name(info.idl_class.name).."::" or "";
    
    print(string.format(
        " %s%s(const char *_%s)",
        class_prefix,
        setter_name(info.var.name,info),        
        string.lower(info.var.name)
    )); 
end

--????????????string ?????????setter????????????????????????--
function code_setter_body_string_not_array(info,need_class_prefix)
    printnl("");
    printnl("{");
    
    printnl(string.format(    
        "    CMem tmp(_%s);",
        string.lower(info.var.name)    
    ));
    
    printnl(string.format(    
        "    return this->%s(&tmp);",
        setter_name(info.var.name,info)
    ));
        
    printnl("}");    
end

--??????setter?????????????????????--
function code_setter_declaration_array(info,need_class_prefix,pointer_version)
    print("status_t");
    
    local class_prefix=need_class_prefix and 
        c_class_name(info.idl_class.name).."::" or "";
    
    local type_name = info.is_object 
        and c_class_name_with_ns(info.var_type)
        or info.var_type.name;
    
    print(string.format(
        " %s%s(%s %s_%s[], int _len)",
        class_prefix,
        setter_name(info.var.name,info),
        type_name,
        (info.is_pointer or pointer_version) and "*" or "",
        string.lower(info.var.name)
    )); 
end


--??????setter??????????????????--
function code_setter_body_array(info,need_class_prefix,pointer_version)      
    printnl("");
    printnl("{");
    
    local var_type_name = info.var_type.name;
    if info.is_object then
        var_type_name = c_class_name_with_ns(info.var_type);
    end
    
    if info.is_pointer then
        var_type_name = var_type_name.."*";
    end
    
    printnl(string.format(
        "    ASSERT(_%s);",
        string.lower(info.var.name)
    ));
    
    if not info.array_size then
        printnl(string.format(
            "    this->%s(_len);",
            alloc_name(info.var.name)
        ));
    else
        printnl(string.format(
            "    ASSERT(_len <= %s);"           
        ,info.array_size));
    end
    
    if info.is_basic_type or info.is_pointer 
		or (info.is_struct and not pointer_version)
	then		
        printnl(string.format(        
			"    memcpy(this->%s,_%s,sizeof(%s)*_len);",
			member_name(info.var.name),
			string.lower(info.var.name),
			var_type_name
        ));
		
    else
        local copy_or_weak_ref = "Copy";
        if info.is_weak_ptr then
            copy_or_weak_ref = "WeakRef"
        end
        printnl("    for(int i = 0; i < _len; i++)");
        printnl("    {");
		
		if info.is_struct and pointer_version then
			printfnl("        ASSERT(_%s[i]);",string.lower(info.var.name));
			printfnl("        this->%s[i] = *_%s[i];",
				member_name(info.var.name),
				string.lower(info.var.name)
			);
		else		
			local addr = pointer_version and "" or "&";		
			printnl(string.format(
				"        this->%s[i].%s(%s_%s[i]);",
				member_name(info.var.name),
				copy_or_weak_ref,
				addr,
				string.lower(info.var.name)
			));
		end
		
        printnl("    }");
    end

    printnl("    return OK;");
    printnl("}");
end

--????????????????????????elem???????????????--
function code_setter_declaration_array_elem(info,need_class_prefix)
    print("status_t");
    
    local class_prefix=need_class_prefix and 
        c_class_name(info.idl_class.name).."::" or "";
    
    local type_name = info.is_object 
        and c_class_name_with_ns(info.var_type)
        or info.var_type.name;
    
    local star = (info.is_pointer or info.is_object) and "*" or "";
    
    print(string.format(
        " %s%s(int _index,%s %s_%s)",
        class_prefix,
        setter_array_elem_name(info.var.name),
        type_name,
        star,
        string.lower(info.var.name)
    )); 
end

--????????????????????????elem????????????--
function code_setter_body_array_elem(info)
    printnl("");
    printnl("{");
    
    if not info.array_size then
        printnl(string.format(
            "    ASSERT(this->%s);",
            member_name(info.var.name)
        ));
    end
    
    printnl(string.format(
        "    ASSERT(_index >= 0 && _index < %s);",
        info.array_size and info.array_size or 
        member_name_len(info.var.name)
    ));
    
    if info.is_pointer or info.is_basic_type or info.is_struct then    
        printnl(string.format(
            "    this->%s[_index] = %s_%s;",
            member_name(info.var.name),
			(info.is_struct and "*" or ""),
            string.lower(info.var.name)
        ));
    else
        printnl(string.format(
            "    ASSERT(_%s);",
            string.lower(info.var.name)
        ));
        
        local copy_or_weak_ref = "Copy";
        if info.is_weak_ptr then
            copy_or_weak_ref = "WeakRef"
        end
        
        printnl(string.format(
            "    this->%s[_index].%s(_%s);",
            member_name(info.var.name),
            copy_or_weak_ref,
            string.lower(info.var.name)
        ));    
    end
    
    printnl("    return OK;");
        
    printnl("}");
end

--?????????????????????????????????elem?????????--
function code_setter_declaration_array_string_elem(info,need_class_prefix)
    print("status_t");
    
    local class_prefix=need_class_prefix and 
        c_class_name(info.idl_class.name).."::" or "";
      
     print(string.format(
        " %s%s(int _index,const char *_%s)",
        class_prefix,
        setter_array_elem_name(info.var.name),
        string.lower(info.var.name)
    ));     
end


--?????????????????????????????????elem???????????? ???const char *?????????--
function code_setter_body_array_string_elem(info)
    printnl("");
    printnl("{");
    
    if not info.array_size then
        printnl(string.format(
            "    ASSERT(this->%s);",
            member_name(info.var.name)
        ));
    end
    
    printnl(string.format(
        "    ASSERT(_index >= 0 && _index < %s);",
        info.array_size and info.array_size or 
        member_name_len(info.var.name)
    ));
    
    if info.is_pointer or info.is_basic_type then    
        printnl(string.format(
            "    this->%s[_index] = _%s;",
            member_name(info.var.name),
            string.lower(info.var.name)
        ));
    else
        printnl(string.format(
            "    ASSERT(_%s);",
            string.lower(info.var.name)
        ));
        
        printnl(string.format(
            "    CMem tmp(_%s);",
            string.lower(info.var.name)
        ));
        
        printnl(string.format(
            "    this->%s[_index].Copy(&tmp);",
            member_name(info.var.name)          
        ));
    end
    
    printnl("    return OK;");
        
    printnl("}");
end

--?????????????????????????????????alloc?????????????????????--
function code_alloc_declaration_unknown_array(info,need_class_prefix)

   print("status_t");
    
   local class_prefix=need_class_prefix and 
        c_class_name(info.idl_class.name).."::" or "";
    
    print(string.format(
        " %s%s(int _len)",
        class_prefix,
        alloc_name(info.var.name)
    )); 
end

--?????????????????????????????????alloc???????????????body--
function code_alloc_body_unknown_array(info,need_class_prefix)       
    printnl("");
    printnl("{");
    
    local var_type_name = info.var_type.name;
    if info.is_object then
        var_type_name = c_class_name_with_ns(info.var_type);
    end
    
    if info.is_weak_ptr then
        var_type_name = string.format("CWeakPointer<%s>",var_type_name);
    end
    
    if info.is_pointer then
        var_type_name = var_type_name.."*";
    end
    
    printnl(string.format(
        "    if(%s == _len)",
        member_name_len(info.var.name)
    ));
    
    printnl("        return OK;");
        
    printnl(string.format(
        "    DEL_ARRAY(this->%s);",
        member_name(info.var.name)
    ));
    
	printnl("    if(_len > 0)");
	printnl("    {");
    
    printnl(string.format(
    "        NEW_ARRAY(this->%s,%s,_len);",
        member_name(info.var.name),var_type_name
    ));
    
    if info.is_basic_type or info.is_pointer or info.is_struct then
        printnl(string.format(        
        "        memset(this->%s,0,sizeof(%s)*_len);",
        member_name(info.var.name),
        var_type_name
        ));
    else 
        printnl("        for(int i = 0; i < _len; i++)");
        printnl("        {");
        printnl(string.format(
            "            this->%s[i].Init();",
            member_name(info.var.name)        
        ));
        printnl("        }");
    end
     
	printnl("    }");
    
    printnl(string.format(
    "    this->%s = _len;",
    member_name_len(info.var.name)    
    ));
    
    printnl("    return OK;");
    
    printnl("}");
end

--??????optional?????????create????????????--
function code_create_optional_declaration(info,need_class_prefix)
    print("status_t ");
    
    local class_prefix=need_class_prefix and 
         c_class_name(info.idl_class.name).."::" or "";

    if need_class_prefix then
        print(class_prefix);
    end
    print(create_optional_name(info.var.name));
    print("()");
end

--??????optional?????????create?????????--
function code_create_optional_body(info)    
    printnl("");
    printnl("{");
    printfnl("    if(this->%s) return OK;",member_name(info.var.name));

    printfnl("    NEW(this->%s,%s);",
        member_name(info.var.name),
        c_class_name_with_ns(info.var_type)
    );
	if info.is_struct then
		printfnl("    memset(%s,0,sizeof(%s));",
			member_name(info.var.name),
			c_class_name_with_ns(info.var_type)	
		);		
	else		
		printfnl("    this->%s->Init();",member_name(info.var.name));
	end
    printnl("    return OK;");
    printnl("}");
end


--?????????????????????setter??????--
function code_all_setter_cpp(idl_class)
    for_each_variables(idl_class.variables,function(info)    
		if info.is_no_setter then return end
        info.idl_class = idl_class;
        
        if not info.is_array then
            if info.is_basic_type then
                code_begin_extra(setter_name(info.var.name,info));
                code_setter_declaration_basic_not_array(info,true);
                code_setter_body_basic_not_array(info);
                code_end_extra(setter_name(info.var.name,info));
                printnl("");  
                
                if info.is_optional then
                    code_begin_extra(setter_name(info.var.name,info).."_V2");
                    code_setter_declaration_basic_not_array_optional(info,true);
                    code_setter_body_basic_not_array_optional(info);
                    code_end_extra(setter_name(info.var.name,info).."_V2");
                    printnl("");  
                end                
            elseif info.is_object then
                if info.is_optional then
                    code_begin_extra(setter_name(info.var.name,info).."-Create");
                    code_create_optional_declaration(info,true);
                    code_create_optional_body(info);
                    code_end_extra(setter_name(info.var.name,info).."-Create");
                    printnl("");  
                end

                code_begin_extra(setter_name(info.var.name,info));
                code_setter_declaration_object_not_array(info,true);                
                code_setter_body_object_not_array(info);
                code_end_extra(setter_name(info.var.name,info));
                printnl("");

                if info.is_string and not info.is_pointer then
                    code_begin_extra(setter_name(info.var.name,info).."-CStr");
                    code_setter_declaration_string_not_array(info,true);
                    code_setter_body_string_not_array(info);
                    code_end_extra(setter_name(info.var.name,info).."-CStr");
                    printnl("");  
                end
            end
        else            
            if not info.array_size then
                code_begin_extra(alloc_name(info.var.name));
                code_alloc_declaration_unknown_array(info,true);
                code_alloc_body_unknown_array(info,true);
                code_end_extra(alloc_name(info.var.name));
                printnl("");
            end

            code_begin_extra(setter_name(info.var.name,info));
            code_setter_declaration_array(info,true);            
            code_setter_body_array(info);
            code_end_extra(setter_name(info.var.name,info));
            printnl("");

			if not info.is_pointer then
				code_begin_extra(setter_name(info.var.name,info).."_V2");
				code_setter_declaration_array(info,true,true);
				code_setter_body_array(info,true,true);
				code_end_extra(setter_name(info.var.name,info).."_V2");
				printnl("");			
			end
            
            code_begin_extra(setter_name(info.var.name,info).."Elem");
            code_setter_declaration_array_elem(info,true);
            code_setter_body_array_elem(info);
            code_end_extra(setter_name(info.var.name,info).."Elem");
            printnl("");
            
            if info.is_string and not info.is_pointer then
                code_begin_extra(setter_name(info.var.name,info).."Elem-CStr");
                code_setter_declaration_array_string_elem(info,true);
                code_setter_body_array_string_elem(info);
                code_end_extra(setter_name(info.var.name,info).."Elem-CStr");
                printnl("");
            end
        end
    end);
end

--?????????????????????setter????????????????????????--
function code_all_setter_declaration_h(idl_class)
    for_each_variables(idl_class.variables,function(info)    
		if info.is_no_setter then return end
        info.idl_class = idl_class;
        
        if not info.is_array then
            if info.is_basic_type then
                print("    ");
                code_setter_declaration_basic_not_array(info);
                printnl(";");
                
                if info.is_optional then
                    print("    ");
                    code_setter_declaration_basic_not_array_optional(info);                
                    printnl(";");
                end
                
            elseif info.is_object then
                if info.is_optional then
                    print("    ");
                    code_create_optional_declaration(info);                
                    printnl(";");
                end

                print("    ");
                code_setter_declaration_object_not_array(info);                
                printnl(";");
                if info.is_string then
                    print("    ");
                    code_setter_declaration_string_not_array(info);
                    printnl(";");
                end                
            end
        else            
            if not info.array_size then
                print("    ");
                code_alloc_declaration_unknown_array(info);
                printnl(";");
            end
            
            print("    ");
            code_setter_declaration_array(info);
            printnl(";");
            			
			if not info.is_pointer then
				print("    ");
				code_setter_declaration_array(info,false,true);
				printnl(";");           
			end
			
            print("    ");
            code_setter_declaration_array_elem(info);
            printnl(";");            
			
            if info.is_string and not info.is_pointer then
                print("    ");
                code_setter_declaration_array_string_elem(info);
                printnl(";");
            end
        end
    end);
end

--???????????????cpp??????--
function code_cpp(idl_class)
    g_cpp_base_codegen = CppBaseCodeGen.new(idl_class,code_switch);

    add_include(to_file_name(idl_class.name,name_space));
    
    common_includes_cpp(idl_class);
    
    printnl("");
    
    local ns = g_cpp_base_codegen:Code_NameSpaceBegin();
    if ns then
        if code_switch.code_mark then
            code_begin_marker("namespace_begin");
        end
        printnl(ns);
        if code_switch.code_mark then
            code_end_marker("namespace_begin");
        end        
        printnl("");
    end
    
    printnl(string.format(
        "%s::%s()",
        c_class_name(idl_class.name),
        c_class_name(idl_class.name)
    ));
	
    printnl("{");
    printnl("    this->InitBasic();");
    printnl("}");
    printnl("");
        
    printnl(string.format(
        "%s::~%s()",
        c_class_name(idl_class.name),
        c_class_name(idl_class.name)
    ));
	    
    printnl("{");
    printnl("    this->Destroy();");
    printnl("}");
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
    
    code_all_getter_cpp(idl_class);
    code_all_setter_cpp(idl_class);

    if code_switch.bson then
        code_cpp_save_bson_1(idl_class);
        printnl("");
        code_cpp_save_bson_2(idl_class);
        printnl("");
        code_cpp_load_bson_1(idl_class);
        printnl("");
        code_cpp_load_bson_2(idl_class);
        printnl("");
    end

    if code_switch.lib_config then
        code_cpp_load_config_2(idl_class);        
        printnl("");        
        code_cpp_load_config_1(idl_class);
        printnl("");        
        code_cpp_save_config_2(idl_class);        
        printnl("");        
        code_cpp_save_config_1(idl_class);
        printnl("");        
        
    end

    if code_switch.cjson then
        code_cpp_load_json_2(idl_class);        
        printnl("");        
        code_cpp_load_json_1(idl_class);
        printnl("");        
        code_cpp_save_json_2(idl_class);        
        printnl("");        
        code_cpp_save_json_1(idl_class);
        printnl("");        
    end
    
    if code_switch.xml2 or code_switch.xml then
        code_cpp_load_xml_2(idl_class);
        printnl("");        
        code_cpp_save_xml_2(idl_class);
        printnl("");
    end


    if code_switch.xml then
        code_cpp_load_xml_1(idl_class);
        printnl("");        
        code_cpp_save_xml_1(idl_class);
        printnl("");        
    end

    if code_switch.xml2 then
        code_cpp_load_xml_3(idl_class);
        printnl("");        
        code_cpp_save_xml_3(idl_class);
        printnl("");        
    end
	
    if code_switch.code_mark then
        printnl("/*@@ Insert Function Here @@*/");
    end
    
    local ns = g_cpp_base_codegen:Code_NameSpaceEnd();
    if ns then
        printnl("");
        if code_switch.code_mark then
            code_begin_marker("namespace_end");
        end    
        printnl(ns);
        if code_switch.code_mark then
            code_end_marker("namespace_end");
        end
        printnl("");
    end    
end

--??????SaveBson?????????--
function code_cpp_save_bson_1(idl_class)    	
    printnl(string.format(
        "status_t %s::SaveBson(CMiniBson *_bson)",
        c_class_name(idl_class.name)
    ));

    printnl("{");
    printnl("    ASSERT(_bson);");
	code_begin_marker("SaveBson_1");

    function pc_not_array_basic_type(info)
        if info.is_optional then
            printfnl("    if(%s)",member_name(info.var.name));
            printnl("    {");
            printnl(string.format(
                "        _bson->Put%s(\"%s\",*%s);",
                IdlHelper.Type.GetBsonType(info.var_type),
                info.var.name,member_name(info.var.name)
            ));
            printnl("    }");
        else
            printnl(string.format(
                "    _bson->Put%s(\"%s\",%s);",
                IdlHelper.Type.GetBsonType(info.var_type),
                info.var.name,member_name(info.var.name)
            ));
        end
    end

    function pc_not_array_string(info)        
        if info.is_optional then            
            printfnl("    if(this->%s)",
                member_name(info.var.name)
            );
            
            printfnl("    {");
            printnl(string.format(
                "        _bson->PutString(\"%s\",%s);",           
                info.var.name,member_name(info.var.name)
            ));            
            printfnl("    }");
        else        
            printnl(string.format(
                "    _bson->PutString(\"%s\",&%s);",           
                info.var.name,member_name(info.var.name)
            ));
        end
    end    

    function pc_not_array_object(info)    
        printnl(string.format(
            "    /******%s begin*******/{",
            info.var.name
        ));
        local tab = "    ";
        local arrow_or_dot = ".";
        local addr="&";
		
        if info.is_optional then
            arrow_or_dot = "->";
            tab = "        ";
			addr="";
            printfnl("    if(this->%s)",
                member_name(info.var.name)
            );
            printfnl("    {");
        end
        
		if info.is_struct then
			printfnl("%s_bson->PutBinary(\"%s\",%s%s,sizeof(%s));",tab,
				info.var.name,				
				addr,member_name(info.var.name),
				c_class_name_with_ns(info.var_type)
			);			
		else		
			printfnl("%sfsize_t _off;",tab);
			printnl(string.format(
				"%s_bson->StartDocument(\"%s\",&_off);",
				tab,info.var.name
			));

			printnl(string.format(
				"%s%s%sSaveBson(_bson);",
				tab,member_name(info.var.name),
				arrow_or_dot
			));

			printfnl("%s_bson->EndDocument(_off);",tab);
        end
		
        if info.is_optional then
            printfnl("    }");
        end
        
        printnl(string.format(
            "    /*******%s end********/}",
            info.var.name
        ));
    end

    function pc_array_basic_type(info)
        local array_size = info.array_size and info.array_size or member_name_len(info.var.name);
        
        printfnl("    if(this->%s)",member_name(info.var.name));
        printfnl("    {");
        
        printnl(string.format(
            "        _bson->PutBinary(\"%s\",%s,sizeof(%s)*%s);",
            info.var.name,
            member_name(info.var.name),
            info.var_type.name,
            array_size
        ));
        printfnl("    }");
    end

    function pc_array_object(info)
        local array_size = info.array_size and info.array_size or member_name_len(info.var.name);

        printnl(string.format(
            "    /******%s begin*******/{",
            info.var.name
        ));
		
		if info.is_struct then
			printfnl("    if(%s > 0)",array_size);
			printfnl("    {");
			printfnl("        _bson->PutBinary(\"%s\",%s,",
				info.var.name,member_name(info.var.name)
			);
			printfnl("            sizeof(%s)*%s);",
				c_class_name_with_ns(info.var_type),
				array_size
			);
			
			printfnl("    }");	
		else
			printnl("    fsize_t _off;");   
			printnl("    char _index_name[64];");   

			printnl(string.format(
				"    _bson->StartArray(\"%s\",&_off);",
				info.var.name
			));

			printnl(string.format(
				"    for(int i = 0; i < %s; i++)",
				array_size
			));

			printnl("    {");

			printnl("        sprintf(_index_name,\"%d\",i);");

			if info.is_string then
				printnl(string.format(
					"        _bson->PutString(_index_name,&%s[i]);",
					member_name(info.var.name)
				));
			else
				printnl("        fsize_t __off;");
				printnl(string.format(
					"        _bson->StartDocument(_index_name,&__off);"
				));

				printnl(string.format(
					"        %s[i].SaveBson(_bson);",
					member_name(info.var.name)
				));

				printnl(string.format(
					"        _bson->EndDocument(__off);"
				));
	   
			end

			printnl("    }");


			printnl(string.format(
				"    _bson->EndArray(_off,%s);",
				array_size
			));
		end
        printnl(string.format(
            "    /*******%s end********/}",
            info.var.name
        ));
    end

    for_each_variables_sorted(idl_class.variables,function(info)
        if info.is_pointer or info.is_weak_ptr or info.is_no_bson then
            return
        end

        if info.is_array then
            if info.is_basic_type then
                pc_array_basic_type(info);
            else
                pc_array_object(info);
            end
        else
            if info.is_basic_type then
                pc_not_array_basic_type(info);
            elseif info.is_string then
                pc_not_array_string(info);
            else
                pc_not_array_object(info);
            end
        end
    
    end);

	code_end_marker("SaveBson_1");
    printnl("    return OK;");
    printnl("}");	
end

--??????SaveBson?????????--
function code_cpp_save_bson_2(idl_class)    	
    printnl(string.format(
        "status_t %s::SaveBson(CMem *_mem)",
        c_class_name(idl_class.name)
    ));

    printnl("{");
    printnl("    ASSERT(_mem);");
    printnl("    CMiniBson _bson;");
    printnl("    _bson.Init();");
    printnl("    _bson.SetRawBuf(_mem);");
    printnl("    _bson.StartDocument();");
    printnl("    this->SaveBson(&_bson);");
    printnl("    _bson.EndDocument();");
    printnl("    _mem->SetSize(_bson.GetDocumentSize());");
    printnl("    return OK;")
    printnl("}");	
end

--??????LoadBson?????????--
function code_cpp_load_bson_1(idl_class)
    printnl(string.format(
        "status_t %s::LoadBson(CMiniBson *_bson)",
        c_class_name(idl_class.name)
    ));
    printnl("{");
    printnl("    ASSERT(_bson);");
	code_begin_marker("LoadBson_1");
    function pc_not_array_basic_type_optional(info)
        printnl(string.format(
            "    /******%s begin*******/{",
            info.var.name
        ));

        printfnl("    %s _tmp;",info.var_type.name);
        
        printfnl(
            "    if(_bson->Get%s(\"%s\",&_tmp))",
            IdlHelper.Type.GetBsonType(info.var_type),
            info.var.name
        );
        
        printfnl("    {");
        printnl(string.format(
            "        this->%s(&_tmp);",
            setter_name(info.var.name,info)
        ));
        printfnl("    }");            
        printnl(string.format(
            "    /******%s end*******/}",
            info.var.name
        ));
    end

    function pc_not_array_basic_type(info)
        if info.is_optional then
            return pc_not_array_basic_type_optional(info);
        else
            printnl(string.format(
                "    BSON_CHECK(_bson->Get%s(\"%s\",&%s));",
                IdlHelper.Type.GetBsonType(info.var_type),
                info.var.name,member_name(info.var.name)
            ));
        end
    end

    function pc_not_array_string(info)
        printnl(string.format(
            "    /******%s begin*******/{",
            info.var.name
        ));

        printnl("    CMem _tmp_str;");
        
        if info.is_optional then            
            printfnl(
                "    if(_bson->GetString(\"%s\",&_tmp_str))",
                info.var.name
            );
            
            printfnl("    {");
            printnl(string.format(
                "        this->%s(&_tmp_str);",
                setter_name(info.var.name,info)
            ));
            printfnl("    }");            
        else        
            printnl(string.format(
                "    BSON_CHECK(_bson->GetString(\"%s\",&_tmp_str));",
                info.var.name
            ));

            printnl(string.format(
                "    this->%s(&_tmp_str);",           
                setter_name(info.var.name,info)
            ));
        end
        
        printnl(string.format(
            "    /******%s end*******/}",
            info.var.name
        ));
    end

    function pc_not_array_object(info)    
        printnl(string.format(
            "    /******%s begin*******/{",
            info.var.name
        ));
		
		if info.is_struct then
			if not info.is_optional then
			printfnl("    CMem _bin;");
			printfnl("    BSON_CHECK(_bson->GetBinary(\"%s\",&_bin));",
				info.var.name,
				member_name(info.var.name)
			);
			printfnl("    this->%s((%s*)_bin.GetRawBuf());",
				setter_name(info.var.name),
				c_class_name_with_ns(info.var_type)
			);
			else
			
				printfnl("    %s _tmp;",c_class_name_with_ns(info.var_type));
				printfnl("    if(_bson->GetBinary(\"%s\",&_tmp))",info.var.name);
				printfnl("    {");
				printfnl("        this->%s(&_tmp);",setter_name(info.var.name));
				printfnl("    }");
			
			end
		else 
			printnl("    CMiniBson _doc;");   
			
			if info.is_optional then
				printfnl(
					"    if(_bson->GetDocument(\"%s\",&_doc))",
					info.var.name
				); 
				printfnl("    {");            
				
				printfnl("        %s _tmp_%s;",
					c_class_name_with_ns(info.var_type),
					string.lower(info.var.name)
				);
				
				printfnl("        _tmp_%s.Init();",
					string.lower(info.var.name)
				);

				printfnl("        _tmp_%s.LoadBson(&_doc);",
					string.lower(info.var.name)
				);
				
				printfnl("        this->%s(&_tmp_%s);",
					setter_name(info.var.name,info),
					string.lower(info.var.name)
				);
				
				printfnl("    }");
			else
				printnl(string.format(
					"    BSON_CHECK(_bson->GetDocument(\"%s\",&_doc));",
					info.var.name
				));

				printnl(string.format(
					"    %s.LoadBson(&_doc);",
					member_name(info.var.name)
				));
			end			
        end
		
        printnl(string.format(
            "    /*******%s end********/}",
            info.var.name
        ));
    end
    
    function pc_array_basic_type(info)
        
        printnl(string.format(
            "    /*******%s start********/{",
            info.var.name
        ));

        printnl("    CMem _tmp_bin;");

        printnl(string.format(
            "    if(_bson->GetBinary(\"%s\",&_tmp_bin))",
            info.var.name
        ));
        
        printnl("    {");

        printnl(string.format(
            "        int _tmp_len = (int)_tmp_bin.GetSize()/sizeof(%s);",
            info.var_type.name
        ));
        
        printnl(string.format(
            "        this->%s((%s*)_tmp_bin.GetRawBuf(),_tmp_len);",
            setter_name(info.var.name,info),
            info.var_type.name
        ));
        
        printnl("    }");

        printnl(string.format(
            "    /*******%s end********/}",
            info.var.name
        ));
    end

    function pc_array_object(info)
        local array_size = info.array_size and info.array_size or member_name_len(info.var.name);

        printnl(string.format(
            "    /******%s begin*******/{",
            info.var.name
        ));
        
		if info.is_struct then		
			printfnl("    CMem _bin;");
			
			printfnl("    this->%s(0);",alloc_name(info.var.name));
				
			printfnl("    if(_bson->GetBinary(\"%s\",&_bin))",info.var.name);
			printnl("    {");
			
			printfnl("        int _len = _bin.GetSize()/sizeof(%s);",
				c_class_name_with_ns(info.var_type));
			printfnl("        this->%s((%s*)_bin.GetRawBuf(),_len);",
				setter_name(info.var.name),
				c_class_name_with_ns(info.var_type)
			);
			printnl("    }");
		else
			printnl("    CMiniBson _doc;");
			printnl("    int _array_len = 0;");

			printnl(string.format(
				"    if(_bson->GetArray(\"%s\",&_doc,&_array_len))",
				info.var.name
			));
			printnl("    {");
			if not info.array_size then
				printnl(string.format(
					"        this->%s(_array_len);",
					alloc_name(info.var.name)
				));
			end

			printnl(string.format(
				"        for(int i = 0; i < %s; i++)",
				array_size
			));

			printnl("        {");   

			if info.is_string then
				printnl("            CMem __str;");
				printnl(string.format(
					"            BSON_CHECK(_doc.GetString(NULL,&__str));"
				));

				printnl(string.format(
					"            this->%s(i,&__str);",
					setter_array_elem_name(info.var.name)
				));
			else
				printnl("            CMiniBson __doc;");
				printnl(string.format(
					"            BSON_CHECK(_doc.GetDocument(NULL,&__doc));"
				));
		
				printnl(string.format(
					"            %s[i].LoadBson(&__doc);",
					member_name(info.var.name)
				));
			end

			printnl("        }");
			printnl("    }");
		end
		printnl(string.format(
			"    /*******%s end********/}",
			info.var.name
		));
    end

    for_each_variables_sorted(idl_class.variables,function(info)
        if info.is_pointer or info.is_weak_ptr or info.is_no_bson then
            return
        end

        if info.is_array then
            if info.is_basic_type then
                pc_array_basic_type(info);
            else
                pc_array_object(info);
            end
        else
            if info.is_basic_type  then
                pc_not_array_basic_type(info);
            elseif info.is_string then
                pc_not_array_string(info);
            else
                pc_not_array_object(info);
            end
        end
    end);  

    code_end_marker("LoadBson_1");
    printnl("    return OK;")
    printnl("}");
	
end

--??????LoadBson?????????--
function code_cpp_load_bson_2(idl_class)
    printnl(string.format(
        "status_t %s::LoadBson(CFileBase *_file)",
        c_class_name(idl_class.name)
    ));

    printnl("{");
    printnl("    ASSERT(_file);");
    printnl("    CMiniBson _bson;");
    printnl("    _bson.Init();");    
    printnl("    _bson.LoadBson(_file);");
    printnl("    _bson.ResetPointer();");
    printnl("    return this->LoadBson(&_bson);");
    printnl("}");
end

--??????libconfig_loopup_xxx???????????????--
function libconfig_lookup_name(info)
    local tail = IdlHelper.Type.GetLibConfigType(info.var_type);
    if info.is_string then
        tail = "string";
    end
    return "config_setting_lookup_"..tail;
end

--??????config_setting_set_xxx?????????--
function libconfig_set_func_name(info)
    local tail = IdlHelper.Type.GetLibConfigType(info.var_type);
    if info.is_string then
        tail = "string";
    end
    return "config_setting_set_"..tail;
end

--????????????????????????--
function libconfig_define_type(info)
    if info.is_array then
        return "CONFIG_TYPE_ARRAY";
    end

    if info.is_string then
        return "CONFIG_TYPE_STRING";
    end
    
    if info.is_object then
        return "CONFIG_TYPE_GROUP";
    end
    return IdlHelper.Type.GetLibConfigDefineType(info.var_type);
end

--??????config_setting_set_xxx_elem?????????--
function libconfig_set_elem_func_name(info)
    return libconfig_set_func_name(info).."_elem";
end

--??????config_setting_get_xxx????????? --
function libconfig_get_func_name(info)
    local tail = IdlHelper.Type.GetLibConfigType(info.var_type);
    if info.is_string then
        tail = "string";
    end
    return "config_setting_get_"..tail;
end

--?????? libconfig ???????????????????????????--
function libconfig_c_type_name(info)
    if info.is_string then
        return "const char*","NULL";
    end

    if info.is_object then
        return c_class_name_with_ns(info.var_type),"NULL";
    end

    local t = IdlHelper.Type.GetLibConfigType(info.var_type);

    if t == "float" then
        return "double","0";
    end
    
    if t == "bool" then
        return "int","0";
    end
    
    return t,"0";
end

--??????LoadConfig?????????--
function code_cpp_load_config_1(idl_class)
    printnl(string.format(
        "status_t %s::LoadConfig(const config_setting_t *_settings)",
        c_class_name(idl_class.name)
    ));
    printnl("{");
    printnl("    ASSERT(_settings);");
    
    code_begin_marker("LoadConfig_1");

    function pc_not_array_basic_type(info)
        local c_type,init_value = libconfig_c_type_name(info);

        printfnl("    %s _tmp_%s = %s;",
            c_type, string.lower(info.var.name),init_value
        );

        printfnl("    if(%s(_settings,\"%s\",&_tmp_%s))",
            libconfig_lookup_name(info),
            info.var.name,
            string.lower(info.var.name)
        );

        printnl("    {");

        printfnl("        this->%s(%s_tmp_%s);",
            setter_name(info.var.name,info),
            info.is_optional and "&" or "",
            string.lower(info.var.name)
        );
        printnl("    }");
    end

    function pc_not_array_string(info)
        pc_not_array_basic_type(info);
    end

    function pc_not_array_object(info)    
        
        printfnl("    const config_setting_t *_%s = config_setting_lookup((config_setting_t*)_settings,\"%s\");",
            string.lower(info.var.name),
            info.var.name
        );
        printfnl("    if(_%s)",string.lower(info.var.name));
        printfnl("    {");
        printfnl("        %s _tmp_%s;",
            c_class_name_with_ns(info.var_type),
            string.lower(info.var.name)
        );

        printfnl("        _tmp_%s.Init();",string.lower(info.var.name));
        printfnl("        _tmp_%s.LoadConfig(_%s);",
            string.lower(info.var.name),
            string.lower(info.var.name)
        );

        printfnl("        this->%s(&_tmp_%s);",setter_name(info.var.name,info),string.lower(info.var.name));

        printfnl("    }");
    end
    
    function pc_array(info)

        printfnl("    const config_setting_t *_%s = config_setting_lookup((config_setting_t*)_settings,\"%s\");",
            string.lower(info.var.name),
            info.var.name
        );

        printfnl("    if(_%s)",string.lower(info.var.name));
        printfnl("    {");

        printfnl("        int len = config_setting_length(_%s);",
            string.lower(info.var.name)
        );
        printfnl("        this->%s(len);",alloc_name(info.var.name));

        printfnl("        for(int i = 0; i < len; i++)");
        printfnl("        {");

        printfnl(
            "            const config_setting_t *elem = config_setting_get_elem(_%s,i);",
            string.lower(info.var.name)
        );

        printfnl("            ASSERT(elem);");

        if info.is_basic_type or info.is_string then
            printfnl("            this->%s(i,%s(elem));",
                setter_array_elem_name(info.var.name),
                libconfig_get_func_name(info)
            );
        else
            printfnl("            %s _tmp_%s;",
                c_class_name_with_ns(info.var_type),
                string.lower(info.var.name)
            );

            printfnl("            _tmp_%s.Init();",string.lower(info.var.name));
            printfnl("            _tmp_%s.LoadConfig(elem);",
                string.lower(info.var.name)        
            );
            printfnl("            this->%s(i,&_tmp_%s);",
                setter_array_elem_name(info.var.name),
                string.lower(info.var.name)
            );
        end

        printfnl("        }");
        printfnl("    }");

    end

    for_each_variables(idl_class.variables,function(info)
        if info.is_pointer then
            return
        end

        if info.is_array then
            pc_array(info);
            printnl("");    
        else
            if info.is_basic_type  then
                pc_not_array_basic_type(info);
            elseif info.is_string then
                pc_not_array_string(info);
            else
                pc_not_array_object(info);
            end
        end
    end);  

    code_end_marker("LoadConfig_1");
    printnl("    return OK;")
    printnl("}");
end

--??????LoadConfig?????????--
function code_cpp_load_config_2(idl_class)
    printnl(string.format(
        "status_t %s::LoadConfig(const char *_filename,const char *_path)",
        c_class_name(idl_class.name)
    ));
    printnl("{");
    printnl("    ASSERT(_filename && _path);");
    printnl("");
    
    code_begin_marker("LoadConfig_2");
        
    printnl("    config_t conf;");
    printnl("    config_init(&conf);");
    printnl("");

    printnl("    if(!config_read_file(&conf, _filename))");

    printnl("    {");

    printnl("        XLOG(LOG_MODULE_USER,LOG_LEVEL_ERROR,");
    printnl("            \"error: load config file %s fail!\",");
    printnl("            _filename");
    printnl("        );");

    printnl("        XLOG(LOG_MODULE_USER,LOG_LEVEL_ERROR,");
    printnl("            \"%s at line %d\",");
    printnl("            config_error_text(&conf),");
    printnl("            config_error_line(&conf)");
    printnl("        );");

    printnl("        return ERROR;");
    printnl("    }");

    printnl("");

    printfnl("    status_t ret = ERROR;")
    printfnl("    const config_setting_t *settings = config_lookup(&conf,_path);");
    printfnl("    if(settings)");
    printnl("    {");
    printfnl("        ret = this->LoadConfig(settings);");
    printnl("    }");

    printnl("    config_destroy(&conf);");
    code_end_marker("LoadConfig_2");
    printnl("    return ret;");
    printnl("}");
end

--??????save_config??? ??????--
function code_cpp_save_config_1(idl_class)
    printfnl(
        "status_t %s::SaveConfig(config_setting_t *_settings)",
        c_class_name(idl_class.name)
    );
    printnl("{");
    printnl("    ASSERT(_settings);");
    printnl("");
    
    code_begin_marker("SaveConfig_1");

    function pc_not_array_basic_type(info)
        local tab = 1;
        
        if info.is_optional then
            printfnl("%sif(%s)",ptab(tab),member_name(info.var.name));
            printfnl("%s{",ptab(tab));
            tab = tab + 1;
        end

        printfnl("%sconfig_setting_t *p_%s = config_setting_add(_settings,\"%s\",%s);",
            ptab(tab),
            string.lower(info.var.name),
            info.var.name,
            libconfig_define_type(info)
        );    

        printfnl("%sASSERT(p_%s);",ptab(tab),string.lower(info.var.name));
        
        printfnl("%s%s(p_%s,%sthis->%s);",ptab(tab),
            libconfig_set_func_name(info),
            string.lower(info.var.name),
            info.is_optional and "*" or "",
            member_name(info.var.name)
        );

        if info.is_optional then
            tab = tab - 1;
            printfnl("%s}",ptab(tab));            
        end

    end

    function pc_not_array_string(info)
        local tab = 1;
        local dot_or_arrow = ".";
        
        if info.is_optional then            
            dot_or_arrow = "->";
            printfnl("%sif(this->%s)",ptab(tab),
                member_name(info.var.name)
            );
            printfnl("%s{",ptab(tab));            
            tab = tab + 1;
        end
        
        printfnl("%sconfig_setting_t *p_%s = config_setting_add(_settings,\"%s\",%s);",
            ptab(tab),
            string.lower(info.var.name),
            info.var.name,
            libconfig_define_type(info)
        );    

        printfnl("%sASSERT(p_%s);",ptab(tab),string.lower(info.var.name));

        
        printfnl("%sif(%s%sStrLen()>0)",ptab(tab),
            member_name(info.var.name),
            dot_or_arrow
        );
        printfnl("%s{",ptab(tab));
        
        tab = tab+1;
                
        printfnl("%s%s(p_%s,%s%sCStr());",ptab(tab),
            libconfig_set_func_name(info),
            string.lower(info.var.name),
            member_name(info.var.name),
            dot_or_arrow
        );         
        
        tab = tab - 1;
        printfnl("%s}",ptab(tab));                        

        if info.is_optional then            
            tab = tab - 1;
            printfnl("%s}",ptab(tab));                        
        end        
    end

    function pc_not_array_object(info)        
        local tab = 1;
        local dot_or_arrow = ".";
        
        if info.is_optional then            
            dot_or_arrow = "->";
            printfnl("%sif(this->%s)",ptab(tab),
                member_name(info.var.name)
            );
            printfnl("%s{",ptab(tab));            
            tab = tab + 1;
        end
        
        printfnl("%sconfig_setting_t *p_%s = config_setting_add(_settings,\"%s\",%s);",
            ptab(tab),
            string.lower(info.var.name),
            info.var.name,
            libconfig_define_type(info)
        );    

        printfnl("%sASSERT(p_%s);",ptab(tab),string.lower(info.var.name));
    
        printfnl("%sthis->%s%sSaveConfig(p_%s);",ptab(tab),
            member_name(info.var.name),
            dot_or_arrow,
            string.lower(info.var.name)
        );
    
        if info.is_optional then            
            tab = tab - 1;
            printfnl("%s}",ptab(tab));                        
        end          
    end
    
    function pc_array(info)
        local tab = 1;

        printfnl("%sif(this->%s)",ptab(tab),member_name(info.var.name));
        printfnl("%s{",ptab(tab));
        tab = tab+1;
        printfnl("%sconfig_setting_t *p_%s = config_setting_add(_settings,\"%s\",%s);",
            ptab(tab),
            string.lower(info.var.name),
            info.var.name,
            libconfig_define_type(info)
        );

        printfnl("%sfor(int i = 0; i < this->%s(); i++)",ptab(tab),
            getter_array_len_name(info.var.name)
        );
        printfnl("%s{",ptab(tab));
        tab = tab + 1;

        if info.is_basic_type then        
            printfnl("%s%s(p_%s,-1,this->%s(i));",ptab(tab),
                libconfig_set_elem_func_name(info),
                string.lower(info.var.name),
                getter_array_elem_name(info.var.name)
            );
        elseif info.is_string then
            printfnl("%sif(this->%s(i)->StrLen()>0)",ptab(tab),
                getter_array_elem_name(info.var.name)
            );
            printfnl("%s{",ptab(tab));
            tab = tab + 1;
        
        
            printfnl("%s%s(p_%s,-1,this->%s(i)->CStr());",ptab(tab),
                libconfig_set_elem_func_name(info),
                string.lower(info.var.name),
                getter_array_elem_name(info.var.name)
            ); 
            tab = tab - 1;
            printfnl("%s}",ptab(tab));
        elseif info.is_object then
            info.is_array = false;
            printfnl("%sconfig_setting_t *_p_elem = config_setting_add(p_%s,NULL,%s);",
                ptab(tab),
                string.lower(info.var.name),                
                libconfig_define_type(info)
            );
            info.is_array = true;
            
            printfnl("%sASSERT(_p_elem);",ptab(tab));
            printfnl("%sthis->%s(i)->SaveConfig(_p_elem);",ptab(tab),
                getter_array_elem_name(info.var.name)
            );
            
        end        

        tab = tab - 1;
        printfnl("%s}",ptab(tab));

        tab = tab-1;
        printfnl("%s}",ptab(tab));
    end

    for_each_variables(idl_class.variables,function(info)
        if info.is_pointer then  return end
        
        if info.is_array then
            pc_array(info);
            printnl("");    
        else
            if info.is_basic_type  then
                pc_not_array_basic_type(info);
                printnl("");    
            elseif info.is_string then
                pc_not_array_string(info);
                printnl("");    
            else
                pc_not_array_object(info);
                printnl("");    
            end
        end
    end);  

    code_end_marker("SaveConfig_1");
    
    
    printnl("    return OK;");
    printnl("}");

end

--??????save_config?????????--
function code_cpp_save_config_2(idl_class)

    printnl(string.format(
        "status_t %s::SaveConfig(const char *filename, const char *root_name)",
        c_class_name(idl_class.name)
    ));
    printnl("{");
    printnl("    ASSERT(filename && root_name);");
    printfnl("    config_t conf;");
    printfnl("    config_init(&conf);");    
    
    printfnl("    config_setting_t *settings = config_setting_add(config_root_setting(&conf),root_name,CONFIG_TYPE_GROUP);");
    printnl("    ASSERT(settings);");
       
    printfnl("    this->SaveConfig(settings);"); 
   
    printfnl("    int ret = config_write_file(&conf,filename);");    
    printfnl("    config_destroy(&conf);");
    printnl("    return ret;");
    printnl("}");

end

--??????LoadJson?????????--
function code_cpp_load_json_1(idl_class)
    printnl(string.format(
        "status_t %s::LoadJson(const cJSON *_json)",
        c_class_name(idl_class.name)
    ));
    printnl("{");
    printnl("    ASSERT(_json);");
    
    code_begin_marker("LoadJson_1");

    function pc_not_array_basic_type(info)
        printfnl("    cJSON *p_%s = cJSON_GetObjectItem( _json, \"%s\");",
            string.lower(info.var.name),
            info.var.name
        );

        local tab = "    ";
        if info.is_optional then
            tab = tab.."    ";
            printfnl("    if(p_%s)",string.lower(info.var.name));
            printfnl("    {");            
        else
            printfnl("    ASSERT(p_%s);",string.lower(info.var.name));
        end
    
        local addr = "";
        if info.is_optional then
            addr = "&";
        end

        printfnl("%sthis->%s(%sp_%s->%s);",tab,
            setter_name(info.var.name,info),
            addr,
            string.lower(info.var.name),            
            info.c_json_value
        );
        
        if info.is_optional then
            printfnl("    }");
        end
    end

    function pc_not_array_string(info)
        printfnl("    cJSON *p_%s = cJSON_GetObjectItem( _json, \"%s\");",
            string.lower(info.var.name),
            info.var.name
        );

        local tab = "    ";
        if info.is_optional then
            tab = tab.."    ";
            printfnl("    if(p_%s)",string.lower(info.var.name));
            printfnl("    {");            
        else
            printfnl("    ASSERT(p_%s);",string.lower(info.var.name));
        end
    
        printfnl("%sthis->%s(p_%s->valuestring);",tab,
            setter_name(info.var.name,info),
            string.lower(info.var.name)
        );
        
        if info.is_optional then
            printfnl("    }");
        end        
    end

    function pc_not_array_object(info)    
        printfnl("    cJSON *p_%s = cJSON_GetObjectItem( _json, \"%s\");",
            string.lower(info.var.name),
            info.var.name
        );

        local tab = "    ";
        if info.is_optional then
            tab = tab.."    ";
            printfnl("    if(p_%s)",string.lower(info.var.name));
            printfnl("    {");            
        else
            printfnl("    ASSERT(p_%s);",string.lower(info.var.name));
        end
    
        if info.is_optional then
            printfnl("%sthis->%s();",tab,create_optional_name(info.var.name));
        end

        if info.is_optional then
            printfnl("%sASSERT(this->%s);",tab,member_name(info.var.name));
        end

        local dot_or_arrow = ".";

        if info.is_optional then
            dot_or_arrow = "->";
        end

        printfnl("%sthis->%s%sLoadJson(p_%s);",tab,
            member_name(info.var.name),
            dot_or_arrow,
            string.lower(info.var.name)
        );
        
        if info.is_optional then
            printfnl("    }");
        end
    end
    
    function pc_array(info)

        local tab = "    ";

        printfnl("%scJSON *p_%s = cJSON_GetObjectItem( _json, \"%s\");",tab,
            string.lower(info.var.name),
            info.var.name
        );

        printfnl("%sif(p_%s)",tab,string.lower(info.var.name));
        printfnl("%s{",tab);

        tab = "        ";
        printfnl("%sint _len = cJSON_GetArraySize(p_%s);",tab,string.lower(info.var.name));

        if not info.array_size then
            printfnl("%sthis->%s(_len);",tab,alloc_name(info.var.name));
        end

        printfnl("%sfor(int i = 0; i < _len; i++)",tab);
        printfnl("%s{",tab);
        tab = "            ";
        printfnl("%scJSON *_p_elem = cJSON_GetArrayItem(p_%s, i);",
            tab,string.lower(info.var.name)
        );
        printfnl("%sASSERT(_p_elem);",tab);

        if info.is_basic_type then
            printfnl("%sthis->%s(i,(%s)_p_elem->%s);",tab,
            setter_array_elem_name(info.var.name),
            info.var_type.name,
            info.c_json_value
        );        
        elseif info.is_string then
            printfnl("%sthis->%s(i,_p_elem->valuestring);",tab,
                setter_array_elem_name(info.var.name)
            );
        else
            printfnl("%s%s *_%s = this->%s(i);",tab,
                c_class_name_with_ns(info.var_type),
                string.lower(info.var.name),
                getter_array_elem_name(info.var.name)
            );
            printfnl("%sASSERT(_%s);",tab,string.lower(info.var.name));
            printfnl("%s_%s->LoadJson(_p_elem);",tab,string.lower(info.var.name));
        end

        tab = "        ";
        printfnl("%s}",tab);
        tab = "    ";
        printfnl("%s}",tab);
    end

    for_each_variables(idl_class.variables,function(info)
        if info.is_pointer then
            return 
        end

        if info.is_array then
            pc_array(info);
            printnl("");    
        else
            if info.is_basic_type  then
                pc_not_array_basic_type(info);
                printnl("");    
            elseif info.is_string then
                pc_not_array_string(info);
                printnl("");    
            else
                pc_not_array_object(info);
                printnl("");    
            end
        end
    end);  

    code_end_marker("LoadJson_1");
    printnl("    return OK;")
    printnl("}");
end

--LoadJson?????????--
function code_cpp_load_json_2(idl_class)
    printfnl("status_t %s::LoadJson(const char *_json)",
        c_class_name(idl_class.name)
    );
    printnl("{");
    printnl("    ASSERT(_json);");

    printfnl("    cJSON *p_root = cJSON_Parse(_json);");

    printfnl("    if(!p_root)");
    printfnl("    {");
    
    printnl("        XLOG(LOG_MODULE_USER,LOG_LEVEL_ERROR,");
    printnl("            \"error: load json fail at \\r\\n%s\",");
    printnl("            cJSON_GetErrorPtr()");
    printnl("        );");

    printnl("        return ERROR;");

    printfnl("    }");
    
    printfnl("    status_t ret = this->LoadJson(p_root);");
    printfnl("    cJSON_Delete(p_root);");

    printfnl("    return ret;");
    printnl("}");
end

--??????cJSON_CreateXXX???????????????--
function c_json_create_func_name(name)
    return "cJSON_Create"..name;
end

--??????SaveJson?????????--
function code_cpp_save_json_1(idl_class)
    printnl(string.format(
        "status_t %s::SaveJson(cJSON *_root)",
        c_class_name(idl_class.name)
    ));
    printnl("{");
    printnl("    ASSERT(_root);");
    
    code_begin_marker("SaveJson_1");

    printfnl("    int _is_array = cJSON_IsArray(_root);");
    printnl("");

    function pc_not_array_basic_type(info)
        local tab = 1;
        
        local star="";

        if info.is_optional then
            star = "*";

            printfnl("%sif(%s)",ptab(tab),member_name(info.var.name));
            printfnl("%s{",ptab(tab));
            tab = tab + 1;
        end

        printfnl("%scJSON *p_%s = %s(%s%s);",ptab(tab),
            string.lower(info.var.name),
            c_json_create_func_name(info.c_json_type),            
            star,member_name(info.var.name)
        );
        
        printfnl("%sASSERT(p_%s);",ptab(tab),string.lower(info.var.name));

        printfnl("%sif(_is_array)",ptab(tab));
        printfnl("%s{",ptab(tab));
        tab = tab+1;
        
        printfnl("%scJSON_AddItemToArray(_root,p_%s);",ptab(tab),
            string.lower(info.var.name)
        );        
        
        tab = tab-1;
        printfnl("%s}",ptab(tab));
        printfnl("%selse",ptab(tab));
        printfnl("%s{",ptab(tab));
        tab = tab + 1;

        printfnl("%scJSON_AddItemToObject(_root,\"%s\",p_%s);",ptab(tab),
            info.var.name,
            string.lower(info.var.name)
        );        

        if info.is_optional then        
            tab = tab-1;
            printfnl("%s}",ptab(tab));
        end

        tab = tab-1;
        printfnl("%s}",ptab(tab));

    end

    function pc_not_array_string(info)
        local tab = 1;

        local dot_or_arrow = ".";

        if info.is_optional then
            dot_or_arrow="->";
            printfnl("%sif(this->%s)",ptab(tab),member_name(info.var.name));
            printfnl("%s{",ptab(tab));            
            tab = tab + 1;
        end
        
        printfnl("%sif(%s%sStrLen()>0)",ptab(tab),
            member_name(info.var.name),
            dot_or_arrow
        );
        printfnl("%s{",ptab(tab));
        tab = tab + 1;

        printfnl("%scJSON *p_%s = cJSON_CreateString(%s%sCStr());",ptab(tab),
            string.lower(info.var.name),
            member_name(info.var.name),
            dot_or_arrow
        );        

        printfnl("%sASSERT(p_%s);",ptab(tab),string.lower(info.var.name));

        printfnl("%sif(_is_array)",ptab(tab));
        printfnl("%s{",ptab(tab));
        tab = tab+1;

        printfnl("%scJSON_AddItemToArray(_root,p_%s);",ptab(tab),
            string.lower(info.var.name)
        );  

        tab = tab-1;
        printfnl("%s}",ptab(tab));
        printfnl("%selse",ptab(tab));
        printfnl("%s{",ptab(tab));
        tab = tab + 1;

        printfnl("%scJSON_AddItemToObject(_root,\"%s\",p_%s);",ptab(tab),
            info.var.name,
            string.lower(info.var.name)
        );  

        tab = tab-1;
        printfnl("%s}",ptab(tab));

        tab = tab-1;
        printfnl("%s}",ptab(tab));        
        
        if info.is_optional then
            tab = tab-1;
            printfnl("%s}",ptab(tab));
        end
    end

    function pc_not_array_object(info)    
        local tab = 1;        
        local dot_or_arrow = ".";

        if info.is_optional then
            dot_or_arrow="->";
            printfnl("%sif(this->%s)",ptab(tab),member_name(info.var.name));
            printfnl("%s{",ptab(tab));            
            tab = tab + 1;
        end
        
        printfnl("%scJSON *p_%s = cJSON_CreateObject();",ptab(tab),
            string.lower(info.var.name)
        );        

        printfnl("%sASSERT(p_%s);",ptab(tab),string.lower(info.var.name));

        printfnl("%s%s%sSaveJson(p_%s);",ptab(tab),
            member_name(info.var.name),
            dot_or_arrow,
            string.lower(info.var.name)
        );

        printfnl("%sif(_is_array)",ptab(tab));
        printfnl("%s{",ptab(tab));
        tab = tab+1;

        printfnl("%scJSON_AddItemToArray(_root,p_%s);",ptab(tab),
            string.lower(info.var.name)
        );  

        tab = tab-1;
        printfnl("%s}",ptab(tab));
        printfnl("%selse",ptab(tab));
        printfnl("%s{",ptab(tab));
        tab = tab + 1;

        printfnl("%scJSON_AddItemToObject(_root,\"%s\",p_%s);",ptab(tab),
            info.var.name,
            string.lower(info.var.name)
        );  

        tab = tab-1;
        printfnl("%s}",ptab(tab));

        if info.is_optional then
            tab = tab-1;
            printfnl("%s}",ptab(tab));
        end            
    end
    
    function pc_array(info)
        local tab = 1;

        printfnl("%sif(this->%s)",ptab(tab),member_name(info.var.name));
        printfnl("%s{",ptab(tab));
        tab = tab+1;
        printfnl("%scJSON *p_%s = cJSON_CreateArray();",ptab(tab),
            string.lower(info.var.name)
        );

        printfnl("%sfor(int i = 0; i < this->%s(); i++)",ptab(tab),
            getter_array_len_name(info.var.name)
        );
        printfnl("%s{",ptab(tab));
        tab = tab + 1;

        if info.is_basic_type then
            printfnl("%scJSON *_p_elem = %s(this->%s(i));",ptab(tab),
                c_json_create_func_name(info.c_json_type),
                getter_array_elem_name(info.var.name)
            );
            
            printfnl("%sASSERT(_p_elem);",ptab(tab));

        elseif info.is_string then
            printfnl("%sCMem *_tmp = this->%s(i);",ptab(tab),
                getter_array_elem_name(info.var.name)
            );

            printfnl("%sASSERT(_tmp);",ptab(tab));

            printfnl("%scJSON *_p_elem = %s(_tmp->CStr());",ptab(tab),
                c_json_create_func_name("String")        
            );
            
            printfnl("%sASSERT(_p_elem);",ptab(tab));

        else
            printfnl("%s%s *_tmp = this->%s(i);",ptab(tab),
                c_class_name_with_ns(info.var_type),
                getter_array_elem_name(info.var.name)
            );

            printfnl("%sASSERT(_tmp);",ptab(tab));

            printfnl("%scJSON *_p_elem = %s();",ptab(tab),
                c_json_create_func_name("Object")        
            );
            printfnl("%sASSERT(_p_elem);",ptab(tab));

            printfnl("%s_tmp->SaveJson(_p_elem);",ptab(tab));
        end

        printfnl("%scJSON_AddItemToArray(p_%s,_p_elem);",ptab(tab),            
            string.lower(info.var.name)
        );  

        tab = tab - 1;
        printfnl("%s}",ptab(tab));

        printfnl("%sif(_is_array)",ptab(tab));
        printfnl("%s{",ptab(tab));
        tab = tab+1;

        printfnl("%scJSON_AddItemToArray(_root,p_%s);",ptab(tab),
            string.lower(info.var.name)
        );  

        tab = tab-1;
        printfnl("%s}",ptab(tab));
        printfnl("%selse",ptab(tab));
        printfnl("%s{",ptab(tab));
        tab = tab + 1;
        
        printfnl("%scJSON_AddItemToObject(_root,\"%s\",p_%s);",ptab(tab),                
            info.var.name,
            string.lower(info.var.name)
        );  

        tab = tab - 1;
        printfnl("%s}",ptab(tab));

        tab = tab-1;
        printfnl("%s}",ptab(tab));
    end

    for_each_variables(idl_class.variables,function(info)
        if info.is_pointer then
            return 
        end

        if info.is_array then
            pc_array(info);
            printnl("");    
        else
            if info.is_basic_type  then
                pc_not_array_basic_type(info);
                printnl("");    
            elseif info.is_string then
                pc_not_array_string(info);
                printnl("");    
            else
                pc_not_array_object(info);
                printnl("");    
            end
        end
    end);  

    code_end_marker("SaveJson_1");
    printnl("    return OK;")
    printnl("}");
end

--??????SaveJson?????????--
function code_cpp_save_json_2(idl_class)
    printnl(string.format(
        "status_t %s::SaveJson(CFileBase *_file)",
        c_class_name(idl_class.name)
    ));
    printnl("{");
    printnl("    ASSERT(_file);");

    printfnl("    cJSON *root = cJSON_CreateObject();");
    printfnl("    this->SaveJson(root);");
    printfnl("    char *str = cJSON_Print(root);");
    printfnl("    if(str)");
    printfnl("    {");
    printfnl("        _file->Puts(str);");
    printfnl("        free(str);");
    printfnl("    }");
    printfnl("    cJSON_Delete(root);");
    printnl("    return OK;");
    printnl("}");
end
-----------------------------------------------------------------------
--xml
-----------------------------------------------------------------------
local function xml_get_value_name(info)
	return "Get"..IdlHelper.Type.GetXmlType(info.var_type).."Value";
end
--??????LoadXml?????????--
function code_cpp_load_xml_1(idl_class)
    printnl(string.format(
        "status_t %s::LoadXml(CXmlNode *_root)",
        c_class_name(idl_class.name)
    ));
    printnl("{");
    printnl("    ASSERT(_root);");
    printnl("    CXmlNode *px;");

    code_begin_marker("LoadXml_1");

    function pc_not_array_basic_type(info)
		printfnl("    px = _root->GetChildByName(\"%s\");",info.var.name);
		printfnl("    if(px)");
		printfnl("    {");		
		printfnl("        this->%s(px->%s());",
			setter_name(info.var.name),
			xml_get_value_name(info)
		);
		printfnl("    }");
    end

    function pc_not_array_string(info)     
		printfnl("    px = _root->GetChildByName(\"%s\");",info.var.name);
		printfnl("    if(px)");
		printfnl("    {");		
		printfnl("        LOCAL_MEM(tmp);");
		printfnl("        px->GetStringValue(&tmp);");
		printfnl("        this->%s(&tmp);",
			setter_name(info.var.name),
			xml_get_value_name(info)
		);
		printfnl("    }");	
    end

    function pc_not_array_object(info)    
		printfnl("    px = _root->GetChildByName(\"%s\");",info.var.name);
		printfnl("    if(px)");
		printfnl("    {");		
		if info.is_optional then
			printfnl("        this->%s();",create_optional_name(info.var.name));
			printfnl("        ASSERT(this->%s);",member_name(info.var.name));
			printfnl("        %s->LoadXml(px);",member_name(info.var.name));
		else
			printfnl("        %s.LoadXml(px);",member_name(info.var.name));
		end
		printfnl("    }");	
    end
    
    function pc_array(info)
		printfnl("    px = _root->GetChildByName(\"%s\");",info.var.name);
		printfnl("    if(px)");
		printfnl("    {");				
		printfnl("        LOCAL_MEM(tmp);");
		printfnl("        ASSERT(px->GetAttrib(\"size\",&tmp));");
		printfnl("        int i,size = atoi(tmp.CStr());");
		printfnl("        this->%s(size);",alloc_name(info.var.name));
		printfnl("        CXmlNode *child = px->GetChild();");
		printfnl("        for(i = size-1; i >= 0; i--)");
		printfnl("        {");
		
		if info.is_basic_type then
			printfnl("            this->%s(i,child->%s());",
				setter_array_elem_name(info.var.name),
				xml_get_value_name(info)
			);
		elseif info.is_string then
			printfnl("            child->GetStringValue(&tmp);");
			printfnl("            this->%s(i,&tmp);", setter_array_elem_name(info.var.name));
		elseif info.is_object then
			printfnl("            this->%s(i)->LoadXml(child);",
				getter_array_elem_name(info.var.name)
			);
		end
		
		printfnl("            child = child->next;");
		printfnl("        }");
				
		printfnl("    }");	
    end

    for_each_variables(idl_class.variables,function(info)
        if info.is_pointer then return end
		if info.is_no_xml then return end

        if info.is_array then
            pc_array(info);
            printnl("");    
        else
            if info.is_basic_type  then
                pc_not_array_basic_type(info);
            elseif info.is_string then
                pc_not_array_string(info);
            else
                pc_not_array_object(info); 
            end
        end
    end);  

    code_end_marker("LoadXml_1");
    printnl("    return OK;")
    printnl("}");
end

--??????SaveXml?????????--
function code_cpp_save_xml_1(idl_class)
    printnl(string.format(
        "status_t %s::SaveXml(CFileBase *_xml)",
        c_class_name(idl_class.name)
    ));
    printnl("{");
	
	local need_i = false;
    for_each_variables(idl_class.variables,function(info)
        if info.is_pointer then return end
		if info.is_no_xml then return end
		if info.is_array then need_i = true end
	end);
	
	if need_i then
		printfnl("    int i;");
	end
	
    printnl("    ASSERT(_xml);");
    
    code_begin_marker("SaveXml_1");

    function pc_not_array_basic_type(info)
		printfnl("    _xml->Log(\"<%s>%s</%s>\",this->%s);",
			info.var.name,
			IdlHelper.Type.GetPrintFormat(info.var_type),
			info.var.name,
			member_name(info.var.name)
		);	
    end

    function pc_not_array_string(info)
		local tab = 1;
		
		if info.is_optional then
			printfnl("    if(this->%s)",member_name(info.var.name));
			printnl("    {");
			tab = tab+1;
		end
		
		printfnl("%s_xml->Log(\"<%s>%%s</%s>\",XML_STR(this->%sStr()));",ptab(tab),
			info.var.name,
			info.var.name,
			getter_name(info.var.name,info)
		);		
		
		if info.is_optional then
			printnl("    }");
		end		
    end

    function pc_not_array_object(info)    
		local tab = 1;
		printfnl("%s_xml->Log(\"<%s>\");",ptab(tab),
			info.var.name);
		printfnl("%s_xml->IncLogLevel(1);",ptab(tab));
		
		if info.is_optional then
			printfnl("%sif(this->%s)",ptab(tab),
				member_name(info.var.name));
			printfnl("%s{",ptab(tab));
			tab = tab + 1;
		end
		
		printfnl("%s%s%sSaveXml(_xml);",ptab(tab),
			member_name(info.var.name),
			(info.is_optional and "->" or ".")
		);
			
		if info.is_optional then
			tab = tab - 1;
			printfnl("%s}",ptab(tab));			
		end
		
		printfnl("%s_xml->IncLogLevel(-1);",ptab(tab));
		printfnl("%s_xml->Log(\"</%s>\");",ptab(tab),
			info.var.name);
    end
    
    function pc_array(info)
		local tab = 1;
		local array_size = info.array_size;
		if not array_size then
			array_size = member_name_len(info.var.name);
		end
		
		printfnl("%s_xml->Log(\"<%s size=\\\"%%d\\\">\",%s);",ptab(tab),
			info.var.name, array_size);
		printfnl("%s_xml->IncLogLevel(1);",ptab(tab));
		
		printfnl("%sfor(i = 0; i < %s; i++)",ptab(tab),array_size);
		printfnl("%s{",ptab(tab));
		tab = tab + 1;
		
		if info.is_basic_type then
			printfnl("%s_xml->Log(\"<e>%s</e>\",this->%s[i]);",ptab(tab),
				IdlHelper.Type.GetPrintFormat(info.var_type),
				member_name(info.var.name)
			);	
		elseif info.is_string then
			printfnl("%s_xml->Log(\"<e>%%s</e>\",",ptab(tab));			
			printfnl("%sXML_STR(this->%s(i)->CStr()));",
				ptab(tab+1),
				getter_array_elem_name(info.var.name),
				getter_array_elem_name(info.var.name)
			);
		elseif info.is_object then
			printfnl("%s_xml->Log(\"<e>\");",ptab(tab));
			printfnl("%s_xml->IncLogLevel(1);",ptab(tab));
			
			printfnl("%s%s[i].SaveXml(_xml);",ptab(tab),
				member_name(info.var.name));
			
			printfnl("%s_xml->IncLogLevel(-1);",ptab(tab));
			printfnl("%s_xml->Log(\"</e>\");",ptab(tab));
		end
		
		tab = tab - 1;					
		printfnl("%s}",ptab(tab));
		
		printfnl("%s_xml->IncLogLevel(-1);",ptab(tab));
		printfnl("%s_xml->Log(\"</%s>\");",ptab(tab),
			info.var.name);
    end

    for_each_variables(idl_class.variables,function(info)
        if info.is_pointer then return end
		if info.is_no_xml then return end
		
        if info.is_array then
            pc_array(info);
            printnl(""); 
        else
            if info.is_basic_type  then
                pc_not_array_basic_type(info);
            elseif info.is_string then
                pc_not_array_string(info);                
            else
                pc_not_array_object(info);
            end
        end
    end);  

    code_end_marker("SaveXml_1");
    printnl("    return OK;")
    printnl("}");
end

function code_cpp_load_xml_2(idl_class)
	printfnl("status_t %s::LoadXml(const char *fn, const char *path)",
		c_class_name(idl_class.name));
	printfnl("{");
	printfnl("    ASSERT(fn && path);");
	printfnl("");
	printfnl("    CXml xml;");
	printfnl("    xml.Init();");
	printfnl("    ASSERT(xml.LoadXml(fn));");
	printfnl("");
	printfnl("    CXmlNode *px = xml.GetNodeByPath(path);");
	printfnl("    ASSERT(px);");
	printfnl("");
	printfnl("    return this->LoadXml(px);");
	printfnl("}");
end

function code_cpp_save_xml_2(idl_class)
	printfnl("status_t %s::SaveXml(const char *fn, const char *node_name)",
		c_class_name(idl_class.name));
	printfnl("{");
	printfnl("    ASSERT(fn && node_name);");
	printfnl("");
	printfnl("    CMemFile mf;");
	printfnl("    mf.Init();");
    printfnl("    mf.Log(\"<?xml version=\\\"1.0\\\" encoding=\\\"utf-8\\\"?>\");");
    
    if code_switch.xml2 then
        printfnl("    this->SaveXml(&mf,node_name);");
    else
        printfnl("    mf.Log(\"<%%s>\",node_name);");
        printfnl("    mf.IncLogLevel(1);");
        printfnl("    this->SaveXml(&mf);");
        printfnl("    mf.IncLogLevel(-1);");
        printfnl("    mf.Log(\"</%%s>\",node_name);");
    end

	printfnl("");
	printfnl("    return mf.WriteToFile(fn) > 0;");
	printfnl("}");
end

-----------------------------------------------------------
--xml2
-----------------------------------------------------------

--??????LoadXml2?????????--
function code_cpp_load_xml_3(idl_class)
    printnl(string.format(
        "status_t %s::LoadXml(CXmlNode *_root)",
        c_class_name(idl_class.name)
    ));
    printnl("{");

    code_begin_marker("LoadXml_2");

    function pc_not_array_basic_type(context)        
        local else_str = context.need_else and "else " or "";
        context.need_else = true;
        printfnl("%s%sif(strcmp(name.CStr(),\"%s\") == 0)",
            ptab(context.tab),else_str,context.xml2_info.name);
        printfnl("%s{",ptab(context.tab));
        context.tab = context.tab + 1;
     
        printfnl("%sthis->%s(XML_STRING_TO_%s(val.CStr()));",ptab(context.tab),
            setter_name(context.info.var.name),
            string.upper(IdlHelper.Type.GetXmlType(context.info.var_type))
        );

        context.tab = context.tab - 1;
        printfnl("%s}",ptab(context.tab));
    end

    function pc_not_array_string(context)
        local else_str = context.need_else and "else " or "";
        context.need_else = true;
        printfnl("%s%sif(strcmp(name.CStr(),\"%s\") == 0)",
            ptab(context.tab),else_str,context.xml2_info.name);
        printfnl("%s{",ptab(context.tab));
        context.tab = context.tab + 1;
		printfnl("%sthis->%s(&val);",ptab(context.tab),
			setter_name(context.info.var.name)
        );
        context.tab = context.tab - 1;
        printfnl("%s}",ptab(context.tab));
    end

    function pc_not_array_object(context)   
        local else_str = context.need_else and "else " or "";
        context.need_else = true;
        printfnl("%s%sif(strcmp(px->GetName(),\"%s\") == 0)",
            ptab(context.tab),else_str,context.xml2_info.name);
        printfnl("%s{",ptab(context.tab));
        context.tab = context.tab + 1;
        printfnl("%s%s.LoadXml(px);",ptab(context.tab),
            member_name(context.info.var.name));
        context.tab = context.tab - 1;
        printfnl("%s}",ptab(context.tab));  
    end
    
    function pc_array(context)
        local else_str = context.need_else and "else " or "";
        context.need_else = true;
        printfnl("%s%sif(strcmp(px->GetName(),\"%s\") == 0)",
            ptab(context.tab),else_str,context.xml2_info.name);
        printfnl("%s{",ptab(context.tab));
        context.tab = context.tab + 1;
                
        printfnl("%s%s *tmp;",ptab(context.tab),
            c_class_name(context.xml2_info.array_entry));
        printfnl("%sNEW(tmp,%s);",ptab(context.tab),
            c_class_name(context.xml2_info.array_entry));
        printfnl("%stmp->Init();",ptab(context.tab));
        printfnl("%stmp->LoadXml(px);",ptab(context.tab));
        printfnl("%s%s.PushPtr(tmp);",ptab(context.tab),
            member_name(context.info.var.name));
        context.tab = context.tab - 1;
        printfnl("%s}",ptab(context.tab));            
    end

    function pc_map(context)
        local else_str = context.need_else and "else " or "";
        context.need_else = true;
        printfnl("%s%sif(strcmp(px->GetName(),\"%s\") == 0)",
            ptab(context.tab),else_str,context.xml2_info.name);
        printfnl("%s{",ptab(context.tab));
        context.tab = context.tab + 1;
                
        printfnl("%s%s *tmp;",ptab(context.tab),
            c_class_name(context.xml2_info.map_entry));
        printfnl("%sNEW(tmp,%s);",ptab(context.tab),
            c_class_name(context.xml2_info.map_entry));
        printfnl("%stmp->Init();",ptab(context.tab));
        printfnl("%stmp->LoadXml(px);",ptab(context.tab));
        printfnl("%sif(!%s.PutPtr(tmp))",ptab(context.tab),
            member_name(context.info.var.name));
		printfnl("%s{",ptab(context.tab));            
		printfnl("%s    DEL(tmp);",ptab(context.tab));            
		printfnl("%s}",ptab(context.tab));            
        context.tab = context.tab - 1;
        printfnl("%s}",ptab(context.tab));            
    end


    printnl("    ASSERT(_root);");
    printnl("    CXmlNode *px = _root;");

    printfnl("");
    printfnl("    LOCAL_MEM(name);");
    printfnl("    LOCAL_MEM(val);");
    printfnl("");
    printfnl("    px->RestartAttrib();");
    printfnl("    while(px->GetNextAttrib(&name,&val))");
    printfnl("    {");

    local context={};
    for_each_variables(idl_class.variables,function(info)
        if info.is_pointer then return end
		if info.is_no_xml then return end
        local xml2_info = IdlHelper.Var.GetXml2Info(info.var);
        if not xml2_info then return end

        context.tab = 2;
        context.xml2_info = xml2_info;
        context.info = info;
    
        if not xml2_info.is_array and 
			not info.is_array and 
			not xml2_info.is_value 
		then
            if info.is_basic_type then
                pc_not_array_basic_type(context);
            elseif info.is_string then
                pc_not_array_string(context);
            end
        end
    end);  
    printfnl("    }");

    printfnl("");

    printfnl("    px = px->child;");
    printfnl("    while(px)");
    printfnl("    {");    
    local context={};
    for_each_variables(idl_class.variables,function(info)
        if info.is_pointer then return end
		if info.is_no_xml then return end
        local xml2_info = IdlHelper.Var.GetXml2Info(info.var);
        if not xml2_info then return end

        context.tab = 2;
        context.xml2_info = xml2_info;
        context.info = info;
        
        if xml2_info.is_array then
            pc_array(context);
		elseif xml2_info.is_map then
            pc_map(context);
        elseif info.is_object and 
			not info.is_array and 
			not info.is_string and 
			not xml2_info.is_value 
		then
            pc_not_array_object(context);            
        end
    end);  
    printfnl("        px = px->next;");
    printfnl("    }");

    for_each_variables(idl_class.variables,function(info)
        if info.is_pointer then return end
		if info.is_no_xml then return end
        local xml2_info = IdlHelper.Var.GetXml2Info(info.var);
        if not xml2_info then return end
        if xml2_info.is_value then
            printfnl("");
            printfnl("    px = _root;");
            printfnl("    px->GetStringValue(&val);");
            printfnl("    this->%s(&val);",setter_name(info.var.name));
        end
    end);  

    code_end_marker("LoadXml_2");
    printnl("    return OK;")
    printnl("}");
end

--??????SaveXml2?????????--
function code_cpp_save_xml_3(idl_class)
    printnl(string.format(
        "status_t %s::SaveXml(CFileBase *_xml,const char *node_name)",
        c_class_name(idl_class.name)
    ));
    printnl("{");
	
	local need_i = false;
    for_each_variables(idl_class.variables,function(info)
        if info.is_pointer then return  end
        local xml2_info = IdlHelper.Var.GetXml2Info(info.var);
        if not xml2_info then return end        
        if xml2_info.is_array then need_i = true end
	end);
	
	if need_i then
		printfnl("    int i;");
	end
	    
    code_begin_marker("SaveXml_2");
    printnl("    ASSERT(_xml && node_name);");

    function pc_not_array_basic_type(context)
		printfnl("%s_xml->Printf(\" %s=\\\"%s\\\"\",this->%s);",ptab(context.tab),
			context.xml2_info.name,
			IdlHelper.Type.GetPrintFormat(context.info.var_type),
			member_name(context.info.var.name)
		);	
    end

    function pc_not_array_string(context)
        printfnl("%sif(%s.StrLen() > 0)",ptab(context.tab),
            member_name(context.info.var.name));
        printfnl("%s{",ptab(context.tab));
        context.tab = context.tab + 1;
		
		printfnl("%s_xml->Printf(\" %s=\\\"%%s\\\"\",this->%sStr());",ptab(context.tab),
			context.xml2_info.name,			
			getter_name(context.info.var.name,info)
		);		
        
        context.tab = context.tab - 1;
    	printfnl("%s}",ptab(context.tab));	
    end

    function pc_not_array_object(context)    
        printfnl("%s%s.SaveXml(_xml,\"%s\");",
            ptab(context.tab),
            member_name(context.info.var.name),
            context.xml2_info.name
        );
    end

    function pc_array(context)
        printfnl("%sfor(i = 0; i < %s.GetLen(); i++)",
            ptab(context.tab),
            member_name(context.info.var.name)
        );
        printfnl("%s{",ptab(context.tab));

        context.tab = context.tab + 1;
        printfnl("%s%s.GetElem(i)->SaveXml(_xml,\"%s\");",
            ptab(context.tab),
            member_name(context.info.var.name),
            context.xml2_info.name
        );
        context.tab = context.tab - 1;
        printfnl("%s}",ptab(context.tab));
    end

    function pc_value(context)
        printfnl("%s_xml->Tab();",ptab(context.tab));
        printfnl("%s_xml->Puts(this->%s());",
            ptab(context.tab),getter_name(context.info.var.name));
        printfnl("%s_xml->Eol();",ptab(context.tab));
    end
    
    printfnl("    _xml->Tab();");
    printfnl("    _xml->Printf(\"<%%s\",node_name);");
    local context={};
    for_each_variables(idl_class.variables,function(info)
        if info.is_pointer then return end
		if info.is_no_xml then return end
        local xml2_info = IdlHelper.Var.GetXml2Info(info.var);
        if not xml2_info then return end

        context.info = info;
        context.xml2_info = xml2_info;
        context.tab = 1;

        if not xml2_info.is_array and not xml2_info.is_value then
            if info.is_basic_type then
                pc_not_array_basic_type(context);
            elseif info.is_string then
                pc_not_array_string(context);
            end
        end        
    end);  
    printfnl("    _xml->Printf(\">\");");
    printfnl("    _xml->Eol();");
    printfnl("    _xml->IncLogLevel(1);");
    printfnl("");

    for_each_variables(idl_class.variables,function(info)
        if info.is_pointer then return end
		if info.is_no_xml then return end
        local xml2_info = IdlHelper.Var.GetXml2Info(info.var);
        if not xml2_info then return end

        context.info = info;
        context.xml2_info = xml2_info;
        context.tab = 1;

        if xml2_info.is_array then
            pc_array(context);
        elseif info.is_object and 
            not xml2_info.is_value and 
            not info.is_string 
        then
            pc_not_array_object(context);
        end        
    end);  

    for_each_variables(idl_class.variables,function(info)
        if info.is_pointer then return end
		if info.is_no_xml then return end
        local xml2_info = IdlHelper.Var.GetXml2Info(info.var);
        if not xml2_info then return end

        context.info = info;
        context.xml2_info = xml2_info;
        context.tab = 1;

        if xml2_info.is_value then
            printnl("");
            pc_value(context);
        end        
    end);  

    printfnl("");
    printfnl("    _xml->IncLogLevel(-1);");
    printfnl("    _xml->Log(\"</%%s>\",node_name);");

    code_end_marker("SaveXml_2");
    printnl("    return OK;")
    printnl("}");
end