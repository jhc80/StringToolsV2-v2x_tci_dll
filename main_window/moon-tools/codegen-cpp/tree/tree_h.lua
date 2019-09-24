require("utils")

function code_h(names)
    printfnl("#ifndef __%s_H",names.class_name_upper);
    printfnl("#define __%s_H",names.class_name_upper);
    printfnl("");
    printfnl("#include \"filebase.h\"");
    printfnl("#include \"closure.h\"");
    printfnl("#include \"%s.h\"",to_file_name(names.node_class_name));

    printnl(g_cpp_base_codegen:Code_Includes());
	printfnl("");
    printnl(g_cpp_base_codegen:Code_NameSpaceBegin());
    printfnl("");
    
    printfnl("class %s{",names.c_entry_class_name);
    printfnl("public:");
    printfnl("    %s *m_RawPtr;",names.c_node_class_name);
    printfnl("public:");
    printfnl("    %s *parent,*child,*next,*prev;",names.c_entry_class_name);
    printfnl("public:");
    printfnl("    %s();",names.c_entry_class_name);
    printfnl("    ~%s();",names.c_entry_class_name);
    printfnl("    %s *get();",names.c_node_class_name);
    printfnl("    status_t set(%s *node);  ",names.c_node_class_name);
    printfnl("    status_t Traverse(CClosure *closure);");
    printfnl("");    
    printfnl("    static status_t DelNode_Recursive(%s *node);",names.c_entry_class_name);
    printfnl("    static status_t Print_Recursive(%s *node, CFileBase *buf);",names.c_entry_class_name);
    printfnl("    static %s* NewFromPointer(%s *node);",names.c_entry_class_name,names.c_node_class_name);
    printfnl("    static %s* New(%s *node);",names.c_entry_class_name,names.c_node_class_name);
    printfnl("");
    printfnl("    status_t InsertBefore(%s *node);",names.c_entry_class_name);
    printfnl("    status_t InsertAfter(%s *node);",names.c_entry_class_name);
    printfnl("    status_t AddChild(%s *node);",names.c_entry_class_name);
    printfnl("    status_t RemoveFromTheTree();");
	
    if code_switch.bson then
        printfnl("");
        printfnl("    status_t SaveBson(CMiniBson *_bson);");
        printfnl("    status_t LoadBson(CMiniBson *_bson);");
    end
	
    printfnl("};");
    printfnl("");
    printfnl("class %s{",names.c_class_name);
    printnl(g_cpp_base_codegen:Code_ClassHeader());    
    printfnl("private:");
    printfnl("    %s *m_Root;",names.c_entry_class_name);
    printfnl("public:");
    printfnl("    %s();",names.c_class_name);
    printfnl("    virtual ~%s();",names.c_class_name);
    printfnl("    status_t InitBasic();");

    printfnl("    status_t Init(%s);",
        g_cpp_base_codegen:Code_InitParam()
    );
    
    printfnl("    status_t Destroy();");
    printfnl("    status_t Copy(%s *p);",names.c_class_name);
    printfnl("    status_t Comp(%s *p);",names.c_class_name);
    printfnl("    status_t Print(CFileBase *_buf);");
    printfnl("    ");
    printfnl("    %s* GetRoot();",names.c_entry_class_name);
    printfnl("    status_t SetRoot(%s *root);    ",names.c_entry_class_name);

    if code_switch.bson then	
        printfnl("");
        printfnl("    status_t SaveBson(CMiniBson *_bson);");
        printfnl("    status_t SaveBson(CMem *_mem);");
        printfnl("    status_t LoadBson(CMiniBson *_bson);");
        printfnl("    status_t LoadBson(CFileBase *_file);");
    end
	
    printfnl("};");
    printfnl("");
    printnl(g_cpp_base_codegen:Code_NameSpaceEnd());
    printfnl("");
    printfnl("#endif");


end