require("common")

function code_h(names)
    printfnl("#ifndef __%s_H",names.file_name_upper);
    printfnl("#define __%s_H",names.file_name_upper);
    printfnl("");
    printfnl("#include \"taskmgr.h\"");
    printfnl("#include \"closure.h\"");
    maybe_printnl(g_cpp_base_codegen:Code_Includes());
	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("Inlcudes"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("Inlcudes"));
    maybe_printnl(g_cpp_base_codegen:Code_NameSpaceBegin());
    printfnl("");
    printfnl("class %s:public CTask{",names.c_class_name);
    printfnl("public:");
    printfnl("    enum{");
    printfnl("        ERROR_NONE = 0,");
    printfnl("    };");
    printfnl("    enum{");
    printfnl("        EVENT_NONE = 0,");
    printfnl("        EVENT_STOPPED,");
    printfnl("    };");
    printfnl("    int m_Step;");
    printfnl("    CClosure m_Callback;");

	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("Members"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("Members"));

    printfnl("public:");
    printfnl("    %s();",names.c_class_name);
    printfnl("    virtual ~%s();",names.c_class_name);
    printfnl("    status_t Init(CTaskMgr *mgr);");
    printfnl("    status_t Destroy();");
    printfnl("    status_t InitBasic();");
    printfnl("    status_t Run(uint32_t interval);");
    printfnl("    const char* ErrStr(int err);");
    printfnl("    status_t ReportError(int err);    ");
    printfnl("    status_t Start();");
    printfnl("    status_t Stop(int err);");
    printfnl("    CClosure* Callback();");

	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("Getter_H"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("Getter_H"));
	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("Setter_H"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("Setter_H"));
	
    printfnl("};");
    printfnl("");
    maybe_printnl(g_cpp_base_codegen:Code_NameSpaceEnd());   
    printfnl("#endif");
    printfnl("");
end