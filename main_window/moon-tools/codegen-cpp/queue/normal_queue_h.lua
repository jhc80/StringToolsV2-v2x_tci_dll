require("common")

function code_normal_h(names)
    printfnl("#ifndef __T_%s_H",names.file_name_upper);
    printfnl("#define __T_%s_H",names.file_name_upper);
    printfnl("");
    printfnl("#include \"%s.h\"",names.node_file_name);
    printfnl("#include \"filebase.h\"");

    printnl(g_cpp_base_codegen:Code_Includes());
    printnl(g_cpp_base_codegen:Code_NameSpaceBegin());

    printfnl("");
    printfnl("class %s{",names.c_class_name);

    printnl(g_cpp_base_codegen:Code_ClassHeader());

    printfnl("private:");
    printfnl("    %s *m_Data;",names.c_node_class_name);
    printfnl("    int m_Head, m_Tail;");
    printfnl("    int m_Size;");
    printfnl("    bool m_IsFull;");
    printfnl("public:");
    printfnl("    status_t Clear();");
    printfnl("    int GetLen();");
    printfnl("    %s* Enqueue();",names.c_node_class_name);
    printfnl("    %s* Dequeue();",names.c_node_class_name);
    printfnl("    %s* GetHead();    ",names.c_node_class_name);
    printfnl("    %s* GetTail();",names.c_node_class_name);
    printfnl("    %s* GetElem(int index);",names.c_node_class_name);
    printfnl("    status_t EnQueue(%s *pos);",names.c_node_class_name);
    printfnl("    bool IsFull();");
    printfnl("    bool IsEmpty();");
    printfnl("");
    printfnl("    %s();",names.c_class_name);
    printfnl("    virtual ~%s();",names.c_class_name);

    printfnl("    status_t Init(%sint init_size=256);",
        g_cpp_base_codegen:Code_InitParam({add_comma=true})
    );

    printfnl("    status_t Destroy();");
    printfnl("    status_t Copy(%s *queue);",names.c_class_name);
    printfnl("    status_t Comp(%s *queue);",names.c_class_name);
    printfnl("    status_t Print(CFileBase *_buf);");
    printfnl("    status_t InitBasic();");
    printfnl("};");
    
    printfnl("");
    printnl(g_cpp_base_codegen:Code_NameSpaceEnd());
    printfnl("");

    printfnl("#endif");
    printfnl("");
end