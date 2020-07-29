require("common")

function code_cpp(names)
    printfnl("#include \"%s.h\"",names.file_name);
    printfnl("#include \"mem_tool.h\"");
    printfnl("#include \"syslog.h\"");
	
    maybe_printnl(g_cpp_base_codegen:Code_NameSpaceBegin());
	
    printfnl("");
    printfnl("enum{");
    printfnl("    STEP_NONE = 0,");
    printfnl("};");
    printfnl("");
    printfnl("#define FIRST_STEP STEP_NONE");
    printfnl("");
    printfnl("%s::%s()",names.c_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    this->InitBasic();");
    printfnl("}");
    printfnl("%s::~%s()",names.c_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    this->Destroy();");
    printfnl("}");
    printfnl("status_t %s::InitBasic()",names.c_class_name);
    printfnl("{");
    printfnl("    CTask::InitBasic();");
    printfnl("    this->m_Step = 0;");
    printfnl("    this->m_Callback.InitBasic();");

	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("InitBasic"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("InitBasic"));

    printfnl("    return OK;");
    printfnl("}");
    printfnl("status_t %s::Init(CTaskMgr *mgr)",names.c_class_name);
    printfnl("{");
    printfnl("    CTask::Init(mgr);");
    printfnl("    this->m_Callback.Init();");
	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("Init"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("Init"));
    printfnl("    return OK;");
    printfnl("}");
    printfnl("status_t %s::Destroy()",names.c_class_name);
    printfnl("{");
	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("Destroy"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("Destroy"));
    printfnl("    this->m_Callback.Destroy();");
    printfnl("    CTask::Destroy();");
    printfnl("    this->InitBasic();");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("const char * %s::ErrStr(int err)",names.c_class_name);
    printfnl("{");
    printfnl("    ERR_STR(ERROR_NONE,\"no error\");");
    printfnl("    return \"unknown error\";");
    printfnl("}");
    printfnl("status_t %s::ReportError(int err)",names.c_class_name);
    printfnl("{");
    printfnl("    XLOG(LOG_MODULE_USER,LOG_LEVEL_ERROR,");
    printfnl("        \"%s(%%d): exit with error:%%s\",",names.c_class_name);
    printfnl("        this->GetId(),this->ErrStr(err)");
    printfnl("    );");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("status_t %s::Start()",names.c_class_name);
    printfnl("{");
    printfnl("    this->Resume();");
    printfnl("    GOTO_STATE(0,FIRST_STEP);");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("status_t %s::Stop(int err)",names.c_class_name);
    printfnl("{");
    printfnl("    if(this->IsDead())return OK;");
    printfnl("    this->Quit();");
    printfnl("    this->ReportError(err);");
    printfnl("    ");
    printfnl("    m_Callback.SetParamInt(1,err);");
    printfnl("    m_Callback.SetParamPointer(2,(void*)ErrStr(err));");
    printfnl("    m_Callback.Run(EVENT_STOPPED);");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("CClosure* %s::Callback()",names.c_class_name);
    printfnl("{");
    printfnl("    return &this->m_Callback;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::Run(uint32_t interval)",names.c_class_name);
    printfnl("{");
    printfnl("    BEGIN_FSM();");
    printfnl("///////////////");
    printfnl("///////////////");
    printfnl("    END_FSM();");
    printfnl("    return OK;");
    printfnl("}");
	
	maybe_printnl(g_cpp_base_codegen:Code_InsertPoint("Function"));
    printfnl("");
	
    printnl(g_cpp_base_codegen:Code_NameSpaceEnd());
end
