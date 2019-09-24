require("common")

function code_normal_h(names)
    printfnl("#ifndef __T_%s_H",names.file_name_upper);
    printfnl("#define __T_%s_H",names.file_name_upper);
    printfnl("");
    printfnl("#include \"mem.h\"");
    printfnl("#include \"%s.h\"",names.node_file_name);
    
    printnl(g_cpp_base_codegen:Code_Includes());
    printnl(g_cpp_base_codegen:Code_NameSpaceBegin());

    printfnl("");
    printfnl("class %s{",names.c_class_name);

    printnl(g_cpp_base_codegen:Code_ClassHeader());

    printfnl("private:");
    printfnl("    %s **m_Index;",names.c_node_class_name);
    printfnl("    int m_Top;");
    printfnl("    int m_Size;");
    printfnl("public:");

if code_switch.bson then
    printfnl("    status_t SaveBson(CMiniBson *_bson);");
    printfnl("    status_t SaveBson(CMem *_mem);");
    printfnl("    status_t LoadBson(CMiniBson *_bson);");
    printfnl("    status_t LoadBson(CFileBase *_file);");
end

    printfnl("    %s* RemoveElem(int index);",names.c_node_class_name);
    printfnl("    status_t InsElemPtr(int i, %s *node);",names.c_node_class_name);
    printfnl("    %s* PopPtr();",names.c_node_class_name);
    printfnl("    status_t AutoResize();");
    printfnl("    status_t PushPtr(%s *node);",names.c_node_class_name);
    printfnl("    status_t InitBasic();  ");
    printfnl("    int BSearchPos(%s *node,int order,int *find_flag);",names.c_node_class_name);
    printfnl("    status_t InsOrderedPtr(%s *node,int order,int unique);",names.c_node_class_name);
    printfnl("    status_t InsOrdered(%s *node,int order,int unique);",names.c_node_class_name);
    printfnl("    status_t DelElem(int i);");
    printfnl("    status_t InsElem(int i,%s *node);",names.c_node_class_name);
    printfnl("    int BSearch(%s *node,int order);",names.c_node_class_name);
    printfnl("    %s* BSearchNode(%s *node,int order);",names.c_node_class_name,names.c_node_class_name);
    printfnl("    status_t Sort(int order);");
    printfnl("    %s* GetElem(int index);",names.c_node_class_name);
    printfnl("    %s* GetTopPtr();",names.c_node_class_name);
    printfnl("    %s* Search(%s *node);",names.c_node_class_name,names.c_node_class_name);
    printfnl("    int SearchPos(%s *node);",names.c_node_class_name);
    printfnl("    status_t Clear();");
    printfnl("    status_t DelTop();");
    printfnl("    status_t Pop(%s *node);",names.c_node_class_name);
    printfnl("    status_t Push(%s *node);",names.c_node_class_name);
    printfnl("    int GetLen();");
    printfnl("    bool IsEmpty();");
    printfnl("    bool IsFull();");
    printfnl("");
    printfnl("    int CompNode(%s *node1, %s *node2);",names.c_node_class_name,names.c_node_class_name);
    printfnl("    status_t CopyNode(%s *dst, %s *src);",names.c_node_class_name,names.c_node_class_name);
    printfnl("    status_t DelNode(%s *node);",names.c_node_class_name);
    printfnl("    %s* CloneNode(%s *node);",names.c_node_class_name,names.c_node_class_name);
    printfnl("");
    printfnl("    %s();",names.c_class_name);
    printfnl("    ~%s();",names.c_class_name);
    printfnl("    status_t Destroy();");
    
    printfnl("    status_t Init(%sint init_size=256);",
        g_cpp_base_codegen:Code_InitParam({add_comma=true})
    );

    printfnl("    status_t Print(CFileBase *_buf);");
    printfnl("      status_t Copy(%s *stk);",names.c_class_name);
    printfnl("    int Comp(%s *stk);",names.c_class_name);
    printfnl("};");
    printfnl("");

    printnl(g_cpp_base_codegen:Code_NameSpaceEnd());   
    printfnl("");
    printfnl("#endif");

    printnl("");
end