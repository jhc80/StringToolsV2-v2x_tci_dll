require("utils")

function code_h(names)
	printfnl("#ifndef __%s_H",string.upper(to_file_name(names.class_name)));
	printfnl("#define __%s_H",string.upper(to_file_name(names.class_name)));
	printfnl("");
	printfnl("#include \"filebase.h\"");
	printfnl("#include \"closure.h\"");
	printfnl("#include \"%s.h\"",to_file_name(names.node_class_name));
    
	maybe_printnl(g_cpp_base_codegen:Code_Includes());
	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("Inlcudes"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("Inlcudes"));	
	
    maybe_printnl(g_cpp_base_codegen:Code_Includes());
	printfnl("");
    maybe_printnl(g_cpp_base_codegen:Code_NameSpaceBegin());

	printfnl("");
	printfnl("class %s{",names.c_entry_class_name);
    maybe_printnl(g_cpp_base_codegen:Code_ClassHeader());
	printfnl("public:");
	printfnl("    %s *m_RawPtr;",names.c_node_class_name);
	printfnl("    %s *next;",names.c_entry_class_name);
	printfnl("public:");
	printfnl("    %s();",names.c_entry_class_name);
	printfnl("    ~%s();",names.c_entry_class_name);
	printfnl("    %s *get();",names.c_node_class_name);
	printfnl("    status_t set(%s *node);",names.c_node_class_name);
	printfnl("};");
	printfnl("");
	printfnl("class %s{",names.c_class_name);
	maybe_printnl(g_cpp_base_codegen:Code_ClassHeader());    	
	printfnl("private:");
	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("Members"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("Members"));	
	printfnl("    %s **m_Data;",names.c_entry_class_name);
	printfnl("    int m_Capacity;");
	printfnl("    int m_Size;");
	printfnl("public:    ");
	printfnl("    status_t Clear();");
	printfnl("    status_t DiscardAll();");
	printfnl("    bool IsEmpty();");
	printfnl("    int GetSize();");
	printfnl("    int GetCapacity();");
	printfnl("    status_t Del(%s *key);",names.c_node_class_name);
	printfnl("    %s* Remove(%s *key);",names.c_entry_class_name,names.c_node_class_name);
	printfnl("    status_t EnumAll(CClosure *closure);        ");
	printfnl("    %s* Get(%s *key);    ",names.c_node_class_name,names.c_node_class_name);
	printfnl("    status_t Put(%s *hashentry);",names.c_node_class_name);
	printfnl("    status_t PutPtr(%s *ptr);",names.c_node_class_name);
	printfnl("    int HashCode(%s *hashentry);",names.c_node_class_name);
	printfnl("    status_t ToArray(%s *arr[], int *len);",names.c_node_class_name);
	printfnl("");
	printfnl("    static int HashCode(%s *hashentry,int capacity);",names.c_node_class_name);
	printfnl("    static bool Equals(%s *hashentry1, %s *hashentry2);    ",names.c_node_class_name,names.c_node_class_name);
	printfnl("    static %s * CloneNode(%s *hashentry);",names.c_node_class_name,names.c_node_class_name);
	printfnl("");
	printfnl("    %s();",names.c_class_name);
	printfnl("    virtual ~%s();",names.c_class_name);
	printfnl("    status_t InitBasic();");
	
    printfnl("    status_t Init(%sint capacity=1024);",
        g_cpp_base_codegen:Code_InitParam({add_comma=true})
    );
    
	printfnl("    status_t Destroy();");
	printfnl("    status_t Copy(%s *p);",names.c_class_name);
	printfnl("    status_t Comp(%s *p);",names.c_class_name);
	printfnl("    status_t Print(CFileBase *_buf);    ");

	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("Getter_H"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("Getter_H"));
	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("Setter_H"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("Setter_H"));
	
	printfnl("};");
	printfnl("");

    printnl(g_cpp_base_codegen:Code_NameSpaceEnd());
	
	printfnl("");
	printfnl("#endif");
	printfnl("");
	printfnl("");
end