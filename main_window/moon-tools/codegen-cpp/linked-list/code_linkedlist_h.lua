require("common")

function code_h(names)
    printfnl("#ifndef __T_%s_H",names.file_name_upper);
    printfnl("#define __T_%s_H",names.file_name_upper);
    printfnl("");
    printfnl("#include \"cruntime.h\"");
    printfnl("#include \"%s.h\"",names.node_file_name);

    printfnl("");
    printnl(g_cpp_base_codegen:Code_Includes());
    printnl(g_cpp_base_codegen:Code_NameSpaceBegin());
    printfnl("");

	printfnl("class %s{",names.c_entry_class_name);
	printfnl("public:");
	printfnl("    %s *m_RawPtr;",names.c_node_class_name);
	printfnl("    %s *next;",names.c_entry_class_name);
	printfnl("    %s *prev;",names.c_entry_class_name);
	printfnl("public:");
	printfnl("    %s();",names.c_entry_class_name);
	printfnl("    ~%s();",names.c_entry_class_name);
	printfnl("    %s *get();",names.c_node_class_name);
	printfnl("    status_t set(%s *node);",names.c_node_class_name);
	printfnl("};");
	printfnl("");
	printfnl("class %s{",names.c_class_name);

    printnl(g_cpp_base_codegen:Code_ClassHeader());

	printfnl("private:");
	printfnl("    %s *m_Head;",names.c_entry_class_name);
	printfnl("    %s *m_Tail;",names.c_entry_class_name);
	printfnl("    int m_Len;");
	printfnl("private:");
	printfnl("    int CompNode(%s *node1, %s *node2);",names.c_node_class_name,names.c_node_class_name);
	printfnl("    %s * CloneNode(%s *node);",names.c_node_class_name,names.c_node_class_name);
	printfnl("    status_t DelEntry(%s *entry);",names.c_entry_class_name);
	printfnl("public:");
	printfnl("    int GetLen();");
	printfnl("    %s* GetTail();",names.c_entry_class_name);
	printfnl("    %s* GetHead();",names.c_entry_class_name);
	printfnl("    status_t InsertBefore(%s *before, %s *node);",names.c_entry_class_name,names.c_entry_class_name);
	printfnl("    status_t InsertAfter(%s *after,%s *node);",names.c_entry_class_name,names.c_entry_class_name);
	printfnl("    status_t Delete(%s *node);",names.c_entry_class_name);
	printfnl("    %s* Remove(%s *node);",names.c_entry_class_name,names.c_entry_class_name);
	printfnl("    %s* SearchFromTail(%s *node);",names.c_entry_class_name,names.c_node_class_name);
	printfnl("    %s* SearchFromHead(%s *node);",names.c_entry_class_name,names.c_node_class_name);
	printfnl("    bool IsEmpty();");
	printfnl("    status_t AddFromHead(%s *node);",names.c_entry_class_name);
	printfnl("    status_t AddFromTail(%s *node);",names.c_entry_class_name);
	printfnl("    %s();",names.c_class_name);
	printfnl("    virtual ~%s();",names.c_class_name);
	printfnl("    status_t InitBasic();");

    printfnl("    status_t Init(%s);",
        g_cpp_base_codegen:Code_InitParam()
    );

    printfnl("    status_t Destroy();");
    printfnl("    status_t Print(CFileBase *_buf);");
    printfnl("    status_t Copy(%s *_list);",names.c_class_name);
    printfnl("    int Comp(%s *_list);",names.c_class_name);
    printfnl("};");
    printfnl("");
    printnl(g_cpp_base_codegen:Code_NameSpaceEnd());
    printfnl("");    
    printfnl("#endif");
      
end