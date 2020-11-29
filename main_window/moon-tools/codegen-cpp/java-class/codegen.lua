require("common")
require("idl_helper");

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
        local is_array,array_size = IdlHelper.Type.IsArray(var_type);
        local is_string = IdlHelper.Type.IsString(var_type);
        local is_basic_type = IdlHelper.Type.IsBasicType(var_type);
     
        local info = {};
        info.var = var;
        info.var_type = var_type;
        info.is_array = is_array;
        info.array_size = array_size;
        info.is_string = is_string;
        info.is_basic_type = is_basic_type;
        info.is_object = not is_basic_type;
		info.is_no_setter = IdlHelper.Var.IsNoSetter(var);
		info.is_no_getter = IdlHelper.Var.IsNoGetter(var);
		info.java_type = IdlHelper.Type.GetJavaType(var_type);
		info.bson_type = IdlHelper.Type.GetBsonType(var_type);
	    callback(info);
    end
end

--按字典顺序排序
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

--生成成员的类型名字--
function java_type_name(info, no_arr)
	local str = "";
	
	if info.is_string then
		str = str.."String";
	elseif info.is_basic_type then
		str = str..info.java_type;
	elseif info.is_object then
		str = str..java_class_name(info.var_type.name);
	end
	
	if info.is_array and not no_arr then
		str = str.."[]";
	end
	
	return str;
end

--生成所有的成员变量的代码--
function code_java_all_members(idl_class)
	code_begin_marker("Members");
	for_each_variables(idl_class.variables,function(info)	
		printf("    private %s ",java_type_name(info));					
		printf("%s",member_name(info.var.name));		
		if info.var.init_value then
			printf(" = %s",info.var.init_value);
		end		
		printnl(";");		
	end)
	code_end_marker("Members");
end

--生成一个构造函数
function code_java_ctor_function(idl_class)
	printfnl("    public %s()",java_class_name(idl_class.name));
	printfnl("    {");
	code_begin_marker("InitMembers");	
	for_each_variables(idl_class.variables,function(info)
		if not info.is_array and info.is_object and not info.is_string then
			printfnl("        this.%s = new %s();",
				member_name(info.var.name),
				java_type_name(info));
		end	
	end);
	code_end_marker("InitMembers");
	printfnl("    }");
end

function code_all_java_array_alloc_function(idl_class)
	for_each_variables(idl_class.variables,function(info)
		if info.is_array then	
			code_begin_extra(alloc_name(info.var.name));
			printfnl("    public %s %s(int size)",
				java_type_name(info),
				alloc_name(info.var.name)
			);
			printfnl("    {");
			printfnl("        if(size <= 0)");
			printfnl("        {");
			printfnl("             this.%s = null;",member_name(info.var.name));
			printfnl("             return null;");
			printfnl("        }");
			printf("        this.%s = new %s",
				member_name(info.var.name),
				java_type_name(info,true)
			);
					
			printfnl("[size];");
			printfnl("        return this.%s;",member_name(info.var.name));
			printfnl("    }");		
			code_end_extra(alloc_name(info.var.name));
			printnl("");			
		end		
	end);
end

function code_java_all_getter_function(idl_class)
	for_each_variables(idl_class.variables,function(info)	
		code_begin_extra(getter_name(info.var.name));
		printfnl("    public %s %s()",
			java_type_name(info),
			getter_name(info.var.name));
		printfnl("    {");
		printfnl("        return this.%s;",member_name(info.var.name));
		printfnl("    }");		
		code_end_extra(getter_name(info.var.name));
		printnl("");
	end);
end

function code_java_all_setter_function(idl_class)
	for_each_variables(idl_class.variables,function(info)	
		code_begin_extra(setter_name(info.var.name));
		printfnl("    public void %s(%s _%s)",			
			setter_name(info.var.name),
			java_type_name(info),
			string.lower(info.var.name)
		);
		printfnl("    {");
		printfnl("        this.%s = _%s;",
			member_name(info.var.name), 
			string.lower(info.var.name)
		);
		printfnl("    }");		
		code_end_extra(setter_name(info.var.name));
		printnl("");
	end);
end

function code_java_to_string_1(idl_class)
	printfnl("    public String toString()");
    printfnl("    {");
    printfnl("        StringBuilder _buf = new StringBuilder();");
    printfnl("        this.toString(_buf);");
    printfnl("        return _buf.toString();");
    printfnl("    }");
end

function code_java_to_string_2(idl_class)
	printfnl("    public void toString(StringBuilder _buf)");
	printfnl("    {");
	code_begin_marker("toString");
	for_each_variables(idl_class.variables,function(info)	
		if info.is_array then			
			printfnl("        if(this.%s != null)",member_name(info.var.name));
			printfnl("        {");			
			printfnl("             _buf.append(\"%s = [\\n\");",info.var.name);
			printfnl("             for(int i = 0; i < this.%s.length;i++)",member_name(info.var.name));
			printfnl("             {");			
				
			if info.is_string or info.is_basic_type then
				printfnl("                  _buf.append(\"[\"+i+\"]=\"+this.%s[i]+\",\\n\");",member_name(info.var.name));
			elseif info.is_object then
				printfnl("                 if(this.%s[i] != null)",member_name(info.var.name));
				printfnl("                 {");
				printfnl("                     _buf.append(\"[\"+i+\"]\"+\" = {\\n\");",info.var.name);
				printfnl("                     this.%s[i].toString(_buf);",member_name(info.var.name));
				printfnl("                     _buf.append(\"}\\n\");");
				printfnl("                 }");
				printfnl("                 else");
				printfnl("                 {");
				printfnl("                      _buf.append(\"[\"+i+\"]=null,\\n\");");
				printfnl("                 }");							
			end
			
			printfnl("             }");			
			printfnl("             _buf.append(\"]\\n\");");

			printfnl("        }");
			printfnl("        else");
			printfnl("        {");
			printfnl("            _buf.append(\"%s = null;\\n\");",info.var.name);
			printfnl("        }");			
		else		
			if info.is_string then				
				printfnl("        _buf.append(\"%s = \"+this.%s+\"\\n\");",
					info.var.name,
					member_name(info.var.name));
					
			elseif info.is_basic_type then
				printfnl("        _buf.append(\"%s = \"+this.%s+\"\\n\");",
					info.var.name,
					member_name(info.var.name)
				);
			elseif info.is_object then
				printfnl("        if(this.%s != null)",member_name(info.var.name));
				printfnl("        {");
				printfnl("            _buf.append(\"%s = {\\n\");",info.var.name);
				printfnl("            this.%s.toString(_buf);",member_name(info.var.name));
				printfnl("            _buf.append(\"}\\n\");");
				printfnl("        }");
				printfnl("        else");
				printfnl("        {");
				printfnl("            _buf.append(\"%s = null;\\n\");",info.var.name);
				printfnl("        }");
			end		
		end
	end);
	code_end_marker("toString");
	printfnl("    }");
end

function code_java_clone(idl_class)
	printfnl("    public %s clone()", java_class_name(idl_class.name));
	printfnl("    {");
	
	printfnl("        %s _tmp = new %s();",
		java_class_name(idl_class.name),
		java_class_name(idl_class.name)
	);
	code_begin_marker("clone");
	for_each_variables(idl_class.variables,function(info)		
		if info.is_array then		
			printfnl("        if(this.%s() != null)", getter_name(info.var.name));
			printfnl("        {");
			
			printfnl("            %s _this_%s = this.%s();", 
				java_type_name(info),
				string.lower(info.var.name),
				getter_name(info.var.name)
			);
			
			printfnl("            %s _tmp_%s = _tmp.%s(_this_%s.length);", 
				java_type_name(info),
				string.lower(info.var.name),
				alloc_name(info.var.name),
				string.lower(info.var.name)
			);
			
			printfnl("            for(int i = 0; i < _this_%s.length; i++)",
				string.lower(info.var.name));
			printfnl("            {");
			
			if info.is_string or info.is_basic_type then			
				printfnl("                 _tmp_%s[i] = _this_%s[i];",
					string.lower(info.var.name),
					string.lower(info.var.name)
				);
			elseif info.is_object then
				printfnl("                 if(_this_%s[i] != null)",
					string.lower(info.var.name));
				printfnl("                 {");
				printfnl("                     _tmp_%s[i] = _this_%s[i].clone();",
					string.lower(info.var.name),
					string.lower(info.var.name)				
				);		
				printfnl("                 }");
			end
			
			printfnl("            }");			
			printfnl("        }");
		else			
			if info.is_string then
				printfnl("        _tmp.%s(this.%s());",
					setter_name(info.var.name),
					getter_name(info.var.name));
			elseif info.is_basic_type then
				printfnl("        _tmp.%s(this.%s());",
					setter_name(info.var.name),
					getter_name(info.var.name));
			elseif info.is_object then
			
				printfnl("        if(this.%s() != null)", getter_name(info.var.name));
				printfnl("        {");
				printfnl("             _tmp.%s(this.%s().clone());",
					setter_name(info.var.name),
					getter_name(info.var.name));					
				printfnl("        }");
			end
			
		end	
	end);
	code_end_marker("clone");
	printfnl("        return _tmp;");
	printfnl("    }");
end

function code_java_save_bson_1(idl_class)
	printfnl("    public boolean saveBson(CMiniBson _bson)");
	printfnl("    {");
	code_begin_marker("saveBson");
	local tab = 2;
	for_each_variables_sorted(idl_class.variables,function(info)			
		if info.is_array then
			printfnl("%sif(this.%s != null)",ptab(tab),member_name(info.var.name));
			printfnl("%s{",ptab(tab));
			tab = tab + 1;
			
			if not info.is_basic_type then
				printfnl("%slong _offset = _bson.startArray(\"%s\");",ptab(tab),info.var.name);			
				printfnl("%sfor(int i = 0; i < this.%s.length; i++)",ptab(tab),
					member_name(info.var.name));
				printfnl("%s{",ptab(tab));
				tab = tab + 1;
			end
			
			if info.is_string then
				printfnl("%s_bson.putString(\"\"+i,CMiniBson.BsonString(this.%s[i]));",ptab(tab),
					member_name(info.var.name));
			elseif info.is_basic_type then
				printfnl("%s_bson.putBinary(\"%s\",this.%s);",ptab(tab),
					info.var.name,member_name(info.var.name));				
			elseif info.is_object then				
				printfnl("%slong _off = _bson.startDocument(\"\"+i);",ptab(tab));
				printfnl("%sthis.%s[i].saveBson(_bson);",ptab(tab),member_name(info.var.name));
				printfnl("%s_bson.endDocument(_off);",ptab(tab));			
			end
			
			if not info.is_basic_type then
				tab = tab - 1;
				printfnl("%s}",ptab(tab));
				printfnl("%s_bson.endArray(_offset,this.%s.length);",ptab(tab),
					member_name(info.var.name));
			end
			tab = tab - 1;
			printfnl("%s}",ptab(tab));
		else
			if info.is_string then			
				printfnl("%s_bson.putString(\"%s\",CMiniBson.BsonString(this.%s));",ptab(tab),
					info.var.name,
					member_name(info.var.name)
				);	
			elseif info.is_basic_type then
				printfnl("%s_bson.put%s(\"%s\",this.%s);",ptab(tab),
					info.bson_type,
					info.var.name,
					member_name(info.var.name)
				);	
			elseif info.is_object then
				printfnl("%sif(this.%s != null)",ptab(tab),member_name(info.var.name));
				printfnl("%s{",ptab(tab));
				tab = tab+1;
				printfnl("%slong _off = _bson.startDocument(\"%s\");",ptab(tab),info.var.name);
				printfnl("%sthis.%s.saveBson(_bson);",ptab(tab),
					member_name(info.var.name));
				printfnl("%s_bson.endDocument(_off);",ptab(tab));	
				tab = tab-1;
				printfnl("%s}",ptab(tab));
			end
		end
	end);
	code_end_marker("saveBson");
	printfnl("        return true;");
	printfnl("    }");
end

function code_java_save_bson_2(idl_class)
	printfnl("    public boolean saveBson(CMem _mem)");
	printfnl("    {");
	printfnl("        CMiniBson bson = new CMiniBson();");
	printfnl("        bson.setRawBuf(_mem);");
	printfnl("        bson.startDocument();");
	printfnl("        boolean ret = this.saveBson(bson);");
	printfnl("        bson.endDocument();        ");
	printfnl("        _mem.setSize(bson.getDocumentSize());        ");
	printfnl("        return ret;");
	printfnl("    }");
end

function code_java_load_bson_1(idl_class)
	local tab = 1;
	printfnl("%spublic boolean loadBson(CMiniBson _bson)",ptab(tab));
	printfnl("%s{",ptab(tab));
	tab = tab + 1;
	code_begin_marker("loadBson");
	for_each_variables_sorted(idl_class.variables,function(info)			
		if info.is_array then
			
			if not info.is_basic_type then
				printfnl("%sCMiniBson _doc_%s = new CMiniBson();",ptab(tab),
					string.lower(info.var.name));
				printfnl("%sint _len_%s = _bson.getArray(\"%s\",_doc_%s);",ptab(tab),
					string.lower(info.var.name),
					info.var.name,
					string.lower(info.var.name)
				);
				printfnl("%s%s _arr_%s = this.%s(_len_%s);",ptab(tab),
					java_type_name(info),
					string.lower(info.var.name),
					alloc_name(info.var.name),
					string.lower(info.var.name));
				printfnl("%sfor(int i = 0; i < _len_%s; i++)",ptab(tab),
					string.lower(info.var.name));
				printfnl("%s{",ptab(tab));
				tab = tab + 1;
			end
		
			if info.is_string then
				printfnl("%s_arr_%s[i] = _doc_%s.getString(null);",ptab(tab),
					string.lower(info.var.name),
					string.lower(info.var.name));
			elseif info.is_basic_type then
				printfnl("%sthis.%s(_bson.getBinary%sArray(\"%s\"));",ptab(tab),
					setter_name(info.var.name),
					string.upper_first_char(info.java_type),
					info.var.name);
			elseif info.is_object then
				printfnl("%sCMiniBson _doc = new CMiniBson();",ptab(tab));
				printfnl("%s_doc_%s.getDocument(null,_doc);",ptab(tab),
					string.lower(info.var.name));
				
				printfnl("%s_arr_%s[i] = new %s();",ptab(tab),
					string.lower(info.var.name),
					java_class_name(info.var.type.name));
				printfnl("%s_arr_%s[i].loadBson(_doc);",ptab(tab),
					string.lower(info.var.name));
			end
			
			if not info.is_basic_type then
				tab = tab - 1;
				printfnl("%s}",ptab(tab));				
			end		
		else
		
			if info.is_string then
				printfnl("%sthis.%s(_bson.getString(\"%s\"));",ptab(tab),
					setter_name(info.var.name),
					info.var.name
				);				
			elseif info.is_basic_type then			
				printfnl("%sthis.%s(_bson.get%s(\"%s\"));",ptab(tab),
					setter_name(info.var.name),
					info.bson_type,
					info.var.name
				);				
			elseif info.is_object then							
				printfnl("%sCMiniBson _doc_%s = new CMiniBson();",ptab(tab),
					string.lower(info.var.name));
					
				printfnl("%sif(_bson.getDocument(\"%s\",_doc_%s))",ptab(tab),
					info.var.name,
					string.lower(info.var.name)
				);
				printfnl("%s{",ptab(tab));
				tab = tab + 1;			
				printfnl("%s%s _tmp_obj = new %s();",ptab(tab),
					java_class_name(info.var_type.name),
					java_class_name(info.var_type.name)
				);
				printfnl("%s_tmp_obj.loadBson(_doc_%s);",ptab(tab),
					string.lower(info.var.name));			
				printfnl("%sthis.%s(_tmp_obj);",ptab(tab),
					setter_name(info.var.name));
				tab = tab - 1;
				printfnl("%s}",ptab(tab));
			end
		end
	end);	
	code_end_marker("loadBson");
	printfnl("%sreturn true;",ptab(tab));
	tab = tab - 1;
	printfnl("%s}",ptab(tab));

end

function code_java_load_bson_2(idl_class)
	printfnl("    public boolean loadBson(CFileBase _file)");
	printfnl("    {");
	printfnl("        CMiniBson bson = new CMiniBson();");
	printfnl("        bson.loadBson(_file);");
	printfnl("        bson.resetPointer();");
	printfnl("        return this.loadBson(bson);");
	printfnl("    }");
	printfnl("    ");
	printfnl("    public boolean loadBson(CMem _mem)");
	printfnl("    {");
	printfnl("        CMiniBson bson = new CMiniBson();");
	printfnl("        bson.loadRawBuf(_mem);");
	printfnl("        bson.resetPointer();");
	printfnl("        return this.loadBson(bson);");
	printfnl("    }");
end

--生成所有的java代码--
function code_java(idl_class)	
	code_begin_marker("Header");	
	printfnl("package %s;",java_package_name);		
	printnl("");
	printfnl("import com.jni.common.CMiniBson;");
	printfnl("import com.jni.common.CMem;");
	printfnl("import com.jni.common.CFileBase;");
	code_end_marker("Header");
	printnl("");
	
	printf("public class %s",java_class_name(idl_class.name));
	
	local all_bases = IdlHelper.Class.GetAllBases(idl_class);	
	if all_bases then	
		print(" extends ");
		for i, base in ipairs(all_bases) do
			if i > 1 then print(",");end
			print(java_class_name(base.name));
		end	
	end
	printnl("{");	
	code_java_all_members(idl_class);
	printnl("");
	code_java_ctor_function(idl_class);
	printnl("");
	code_all_java_array_alloc_function(idl_class);
	printnl("");
	code_java_all_getter_function(idl_class);
	printnl("");
	code_java_all_setter_function(idl_class);
	printnl("");
	code_java_to_string_1(idl_class);
	printnl("");
	code_java_to_string_2(idl_class);
	printnl("");
	code_java_clone(idl_class);
	printnl("");	
	if code_switch.bson then
		code_java_save_bson_1(idl_class);
		printnl("");	
		code_java_save_bson_2(idl_class);	
		printnl("");	
		code_java_load_bson_1(idl_class);
		printnl("");
		code_java_load_bson_2(idl_class);
	end
	
	printnl("");	
	printfnl("    /*@@ Insert Function Here @@*/");
	printnl("");	
	
	printnl("}");
	
end
