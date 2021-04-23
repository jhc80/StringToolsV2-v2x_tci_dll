require("common")

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

function get_total_members(idl_class)
	local total = 0;
	for_each_variables(idl_class.variables,function(info)	
		total = total + 1;
	end);
	return total;
end

function for_each_variables(variables,callback)
    if not variables then return end

    for i ,var in ipairs(variables) do	
        local var_type = var.type;
        local is_pointer = IdlHelper.Type.IsPointer(var_type);
        local is_array,array_size = IdlHelper.Type.IsArray(var_type);
        local is_string = IdlHelper.Type.IsString(var_type);
        local is_basic_type = IdlHelper.Type.IsBasicType(var_type);
        
        local info = {};
		info.index = i;
        info.var = var;
        info.var_type = var_type;
        info.is_pointer = is_pointer;
        info.is_array = is_array;
        info.array_size = array_size;
        info.is_string = is_string;
        info.is_basic_type = is_basic_type;
        info.is_object = not is_basic_type;		
		
		if info.is_array then
			info.is_blob = true;
		end
		
        if callback(info) then
			break;
		end
    end
end

function sqlite_type_to_func_name(sql_type)	
	if sql_type == "INTEGER" then
		return "Int";
	elseif sql_type == "INTEGER64" then		
		return "Int64";
	elseif sql_type == "REAL" then
		return "Double";
	end
end

function c_type_to_sqlite_func_name(c_type)
	local sqlite_type = IdlHelper.Type.GetSqliteType(c_type);
	return sqlite_type_to_func_name(sqlite_type);
end

function code_h(idl_class,node_name)
	printfnl("#ifndef __%s_H",string.upper(idl_class.name));
	printfnl("#define __%s_H",string.upper(idl_class.name));
	printfnl("");
	printfnl("#include \"sqlite3database.h\"");
	printfnl("#include \"sqlite3stmt.h\"");
	printfnl("#include \"%s.h\"",to_file_name(node_name));
	printfnl("");
	printfnl("class %s{",c_class_name(idl_class.name));
	printfnl("public:");
	printfnl("    CSQLite3DataBase *p_DataBase;");
	printfnl("    CSQLite3Stmt m_TmpStmt;");
	printfnl("public:");
	printfnl("    bool IsTableExist();");
	printfnl("    const char* GetTableName();");
	printfnl("    status_t Delete(const char *where);");
	printfnl("    status_t Update(const char *where, %s *row);",c_class_name(node_name));
	printfnl("    int32_t RowCount();");
	printfnl("    int32_t RowCount(const char *where);");
	printfnl("    status_t Select(const char *where);");
	printfnl("    status_t Select(const char *where, CSQLite3Stmt *stmt);");
	printfnl("    status_t ReadNextRow(%s *row);",c_class_name(node_name));
	printfnl("    status_t SelectAll();");
	printfnl("    status_t Insert(%s *row);",c_class_name(node_name));
	printfnl("    status_t BindRow(CSQLite3Stmt *stmt, %s *row);",c_class_name(node_name));
	printfnl("    status_t ReadRow(CSQLite3Stmt *stmt,%s *row);",c_class_name(node_name));
	printfnl("    status_t SelectAll(CSQLite3Stmt *stmt);");
	printfnl("    status_t DropTable();");
	printfnl("    status_t CreateTable();");
	printfnl("    %s();",c_class_name(idl_class.name));
	printfnl("    virtual ~%s();",c_class_name(idl_class.name));
	printfnl("    status_t Init(CSQLite3DataBase *db);");
	printfnl("    status_t Destroy();");
	printfnl("    status_t InitBasic();");
	printfnl("};");
	printfnl("");
	printfnl("#endif");
end

function code_cpp(idl_class,node_name)
	printfnl("#include \"%s.h\"",to_file_name(idl_class.name));
	printfnl("#include \"syslog.h\"");
	printfnl("#include \"mem_tool.h\"");
	printfnl("");
	printfnl("%s::%s()",c_class_name(idl_class.name),c_class_name(idl_class.name));
	printfnl("{");
	printfnl("    this->InitBasic();");
	printfnl("}");
	printfnl("%s::~%s()",c_class_name(idl_class.name),c_class_name(idl_class.name));
	printfnl("{");
	printfnl("    this->Destroy();");
	printfnl("}");
	printfnl("status_t %s::InitBasic()",c_class_name(idl_class.name));
	printfnl("{");
	printfnl("    this->p_DataBase = NULL;");
	printfnl("    this->m_TmpStmt.InitBasic();");
	printfnl("    return OK;");
	printfnl("}");
	printfnl("status_t %s::Init(CSQLite3DataBase *db)",c_class_name(idl_class.name));
	printfnl("{");
	printfnl("    this->InitBasic();");
	printfnl("    this->p_DataBase = db;");
	printfnl("    this->m_TmpStmt.Init();");
	printfnl("    return OK;");
	printfnl("}");
	printfnl("status_t %s::Destroy()",c_class_name(idl_class.name));
	printfnl("{");
	printfnl("    m_TmpStmt.Destroy();");
	printfnl("    this->InitBasic();");
	printfnl("    return OK;");
	printfnl("}");
	printfnl("");
	
	code_begin_marker("IsTableExist");	
	printfnl("bool %s::IsTableExist()",c_class_name(idl_class.name));
	printfnl("{");
	printfnl("    ASSERT(p_DataBase);");
	printfnl("    return p_DataBase->IsTableExist(\"%s\");",table_name(idl_class.name));
	printfnl("}");
	code_end_marker("IsTableExist");	
	printfnl("");
	
	code_begin_marker("GetTableName");	
	printfnl("const char* %s::GetTableName()",c_class_name(idl_class.name));
	printfnl("{");
	printfnl("    return \"%s\";",table_name(idl_class.name));
	printfnl("}");
	code_end_marker("GetTableName");	
	printfnl("");
	
	code_begin_marker("DropTable");	
	printfnl("status_t %s::DropTable()",c_class_name(idl_class.name));
	printfnl("{");
	printfnl("    const char *sql = \"DROP TABLE IF EXISTS %s\";",table_name(idl_class.name));
	printfnl("    ASSERT(this->p_DataBase);");
	printfnl("    return this->p_DataBase->RunSqlCommand(sql);");
	printfnl("}");	
	code_end_marker("DropTable");
	printfnl("");
	
	code_begin_marker("ReadRow");
	printfnl("status_t %s::ReadRow(CSQLite3Stmt *stmt, %s *row)",c_class_name(idl_class.name),c_class_name(node_name));
	printfnl("{");
	printfnl("    ASSERT(stmt && row);");
	printnl("");
	printfnl("    row->Destroy();");
	printfnl("    row->Init();");
	printnl("");		
	local need_mem = false;
	for_each_variables(idl_class.variables,function(info)
		if info.is_string or info.is_blob then
			need_mem = true;
		end
	end);
	
	if need_mem then
		printfnl("    LOCAL_MEM_WITH_SIZE(mem,64*1024);");
		printfnl("");
	end
	
	local col = 0;
	for_each_variables(idl_class.variables,function(info)
		if info.is_blob then			
			printfnl("    stmt->ColumnBlob(%d,&mem);",col);		
			printfnl("    row->%s((%s*)mem.GetRawBuf(),(int)mem.GetSize()/sizeof(%s));",
				setter_name(info.var.name),
				info.var_type.name,info.var_type.name);
			
		elseif info.is_string then			
			printfnl("    stmt->ColumnText(%d,&mem);",col);		
			printfnl("    row->%s(&mem);",setter_name(info.var.name));
		elseif info.is_basic_type then
			printfnl("    row->%s(stmt->Column%s(%d));",
				setter_name(info.var.name),
				c_type_to_sqlite_func_name(info.var_type),
				col
			);
		end
		col = col + 1;
	end);
		
	printfnl("");
	printfnl("    return OK;");
	printfnl("}");
	code_end_marker("ReadRow");	
	printfnl("");
	
	code_begin_marker("BindRow");
	printfnl("status_t %s::BindRow(CSQLite3Stmt *stmt, %s *row)",c_class_name(idl_class.name),c_class_name(node_name));
	printfnl("{");
	printfnl("    ASSERT(stmt && row);");
	
	local col = 1;
	for_each_variables(idl_class.variables,function(info)
		if info.is_blob then
			printfnl("    stmt->BindBlob(%d,row->%s(),row->%s()*sizeof(%s));",
				col, getter_name(info.var.name),
				getter_array_len_name(info.var.name),
				info.var_type.name			
			);
		elseif info.is_string then
			printfnl("    stmt->BindText(%d,row->%s());",
				col, getter_name(info.var.name)
			);
		elseif info.is_basic_type then
			printfnl("    stmt->Bind%s(%d,row->%s());",
				c_type_to_sqlite_func_name(info.var_type),
				col, getter_name(info.var.name)
			);
		end
		col = col + 1;
	end);
	
	
	printfnl("    return OK;");
	printfnl("}");
	code_end_marker("BindRow");
	
	printfnl("");
	
	code_begin_marker("Insert");	
	printfnl("status_t %s::Insert(%s *row)",c_class_name(idl_class.name),c_class_name(node_name));
	printfnl("{");
	printfnl("    ASSERT(row && this->p_DataBase);");
	printfnl("    CSQLite3Stmt stmt;");
		
	printf("    this->p_DataBase->Prepare(\"INSERT INTO %s VALUES("
		,table_name(idl_class.name));
		
	local total = get_total_members(idl_class);
	for i=1,total,1 do
		print("?");
		if i < total then
			print(",");
		end
	end	
	printnl(")\",&stmt);");
			
	printfnl("    this->BindRow(&stmt,row);");
	printfnl("    status_t ret = stmt.Step();");
	printfnl("    stmt.Finish();");
	printfnl("    return ret;");
	printfnl("}");
	code_end_marker("Insert");
	
	printfnl("");
	code_begin_marker("ReadNextRow");
	printfnl("status_t %s::ReadNextRow(%s *row)",c_class_name(idl_class.name),c_class_name(node_name));
	printfnl("{");
	printfnl("    ASSERT(row);");
	printfnl("    if(this->m_TmpStmt.Next())");
	printfnl("    {");
	printfnl("        return this->ReadRow(&m_TmpStmt,row);");
	printfnl("    }");
	printfnl("    return ERROR;");
	printfnl("}");
	code_end_marker("ReadNextRow");
	
	printfnl("");
	code_begin_marker("Select");
	printfnl("status_t %s::Select(const char *where, CSQLite3Stmt *stmt)",c_class_name(idl_class.name));
	printfnl("{");
	printfnl("    ASSERT(where && stmt && this->p_DataBase);");
	printfnl("    LOCAL_MEM(sql);");
	printfnl("    sql.Puts(\"SELECT * FROM %s \");",table_name(idl_class.name));
	printfnl("    sql.Puts(where);");
	printfnl("    return this->p_DataBase->Prepare(sql.CStr(),stmt);");
	printfnl("}");
	code_end_marker("Select");
	printfnl("");
	
	printfnl("status_t %s::Select(const char *where)",c_class_name(idl_class.name));
	printfnl("{");
	printfnl("    m_TmpStmt.Finish();");
	printfnl("    return this->Select(where,&m_TmpStmt);");
	printfnl("}");
	printfnl("");
	printfnl("status_t %s::SelectAll(CSQLite3Stmt *stmt)",c_class_name(idl_class.name));
	printfnl("{");
	printfnl("    ASSERT(stmt);");
	printfnl("    return this->Select(\"\",stmt);");
	printfnl("}");
	printfnl("");
	printfnl("status_t %s::SelectAll()",c_class_name(idl_class.name));
	printfnl("{");
	printfnl("    m_TmpStmt.Finish();");
	printfnl("    return this->SelectAll(&m_TmpStmt);");
	printfnl("}");
	printfnl("");
	
	code_begin_marker("RowCount");
	printfnl("int32_t %s::RowCount(const char *where)",c_class_name(idl_class.name));
	printfnl("{");
	printfnl("    ASSERT(where && this->p_DataBase);");
	printfnl("    LOCAL_MEM(sql);");
	printfnl("    sql.Puts(\"SELECT count(*) FROM %s \");",table_name(idl_class.name));
	printfnl("    sql.Puts(where);");
	printfnl("    CSQLite3Stmt stmt;");
	printfnl("    this->p_DataBase->Prepare(sql.CStr(),&stmt);");
	printfnl("    stmt.Step();");
	printfnl("    return stmt.ColumnInt(0);");
	printfnl("}");
	code_end_marker("RowCount");
	printfnl("");
	printfnl("int32_t %s::RowCount()",c_class_name(idl_class.name));
	printfnl("{");
	printfnl("    return this->RowCount(\"\");");
	printfnl("}");
	printfnl("");
	
	code_begin_marker("Update");
	printfnl("status_t %s::Update(const char *where, %s *row)",c_class_name(idl_class.name),c_class_name(node_name));
	printfnl("{");
	printfnl("    ASSERT(row && where && this->p_DataBase);");
	printfnl("");
	printfnl("    LOCAL_MEM(sql);");
	printfnl("    sql.Puts(\"UPDATE %s SET \");",table_name(idl_class.name));		
	printfnl("    sql.Puts(");
	
	local total = get_total_members(idl_class);
	
	for_each_variables(idl_class.variables,function(info)	
		printfnl("        \"%s=?%s\"",
			to_big_camel_case(info.var.name),
			((info.index==total) and "" or ",")
		);
	end);
	
	printfnl("    );");
	
	printfnl("    sql.Puts(where);");
	printfnl("");
	printfnl("    CSQLite3Stmt stmt;");
	printfnl("    this->p_DataBase->Prepare(sql.CStr(),&stmt);");
	printfnl("    this->BindRow(&stmt,row);");
	printfnl("    return stmt.Step();");
	printfnl("}");
	code_end_marker("Update");
	
	printfnl("");
	
	code_begin_marker("Delete");
	printfnl("status_t %s::Delete(const char *where)",c_class_name(idl_class.name));
	printfnl("{");
	printfnl("    ASSERT(where && this->p_DataBase);");
	printfnl("");
	printfnl("    LOCAL_MEM(sql);");
	printfnl("    sql.Puts(\"DELETE FROM %s \");",table_name(idl_class.name));
	printfnl("    sql.Puts(where);");
	printfnl("    return this->p_DataBase->RunSqlCommand(sql.CStr());");
	printfnl("}");
	code_end_marker("Delete");
	printfnl("");
	
	code_begin_marker("CreateTable");
	printfnl("status_t %s::CreateTable()",c_class_name(idl_class.name));
	printfnl("{");
	printfnl("    const char *sql = ");
	printfnl("        \"CREATE TABLE IF NOT EXISTS %s (\"",table_name(idl_class.name));
	
	for_each_variables(idl_class.variables,function(info)	
		local comma = (info.index==total) and "" or ",";
		
		if info.is_blob then
			printfnl("        \"%s BLOB%s\"",
				to_big_camel_case(info.var.name),
				comma
			);
		elseif info.is_string then		
			printfnl("        \"%s TEXT%s\"",
				to_big_camel_case(info.var.name),
				comma
			);
		elseif info.is_basic_type then
			printfnl("        \"%s %s%s\"",
				to_big_camel_case(info.var.name),
				IdlHelper.Type.GetSqliteType_2(info.var_type),
				comma
			);
		end
		
	end);
	
	printfnl("    \")\";");
	printfnl("    ASSERT(this->p_DataBase);");
	printfnl("    return this->p_DataBase->RunSqlCommand(sql);");
	printfnl("}");
	code_end_marker("CreateTable");
	printfnl("");
end

