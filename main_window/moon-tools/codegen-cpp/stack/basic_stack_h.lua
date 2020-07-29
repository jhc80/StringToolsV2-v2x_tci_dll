require ("common")

function code_basic_h(names)
    printfnl("#ifndef __%s_H",names.file_name_upper);
    printfnl("#define __%s_H",names.file_name_upper);
    printfnl("");
    printfnl("#include \"mem.h\"");
    printfnl("#include \"memfile.h\"");

    maybe_printnl(g_cpp_base_codegen:Code_Includes());
    maybe_printnl(g_cpp_base_codegen:Code_NameSpaceBegin());

    printfnl("");
    printfnl("class %s{",names.c_class_name);

    maybe_printnl(g_cpp_base_codegen:Code_ClassHeader());

    printfnl("private:");
    printfnl("    %s *m_Data;",names.node_class_name);
    printfnl("    int m_Top,m_Size;");
    printfnl("public:");
    printfnl("    status_t SaveBson(CMiniBson *_bson);");
    printfnl("    status_t SaveBson(CMem *_mem);");
    printfnl("    status_t LoadBson(CMiniBson *_bson);");
    printfnl("    status_t LoadBson(CFileBase *_file);");
    printfnl("    int CompNode(%s node1, %s node2);    ",names.node_class_name,names.node_class_name);
    printfnl("    status_t AutoResize();");
    printfnl("    status_t Sort(int order);");
    printfnl("    status_t Push(%s node);",names.node_class_name);
    printfnl("    %s Pop();",names.node_class_name);
    printfnl("    %s GetElem(int index);",names.node_class_name);
    printfnl("    int BSearchPos(%s node, int order, int *find_flag);",names.node_class_name);
    printfnl("    status_t InsElem(int index, %s node);",names.node_class_name);
    printfnl("    status_t DelElem(int index);");
    printfnl("    status_t InsOrdered(%s node, int order, int unique);",names.node_class_name);
    printfnl("    int SearchPos(%s node);",names.node_class_name);
    printfnl("    %s GetTop();",names.node_class_name);
    printfnl("    status_t SetElem(int index, %s node);",names.node_class_name);
    printfnl("    status_t Clear();");
    printfnl("    int GetLen();");
    printfnl("    bool IsEmpty();");
    printfnl("    bool IsFull();");
    printfnl("");
    printfnl("    %s();",names.c_class_name);
    printfnl("    ~%s();",names.c_class_name);
    printfnl("    status_t InitBasic();");
    
    printfnl("    status_t Init(%sint init_size=256);",
        g_cpp_base_codegen.Code_InitParam({add_comma=true})
    );

    printfnl("    status_t Destroy();");
    printfnl("    status_t Print(CFileBase *_buf);");
    printfnl("    status_t Copy(%s *stk);    ",names.c_class_name);
    printfnl("    int Comp(%s *stk);",names.c_class_name);
    printfnl("};");
    printfnl("");
    maybe_printnl(g_cpp_base_codegen:Code_NameSpaceEnd());
    printfnl("#endif");
    
    printfnl("");
end