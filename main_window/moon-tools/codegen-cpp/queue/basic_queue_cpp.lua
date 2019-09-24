require("common")

function code_basic_cpp(names)
    printfnl("#include \"%s.h\"",names.file_name);
    printfnl("#include \"syslog.h\"");
    printfnl("#include \"mem_tool.h\"");
    
    printfnl("");    
    printnl(g_cpp_base_codegen:Code_NameSpaceBegin());    
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

    printnl(g_cpp_base_codegen:Code_InitBasic());    

    printfnl("    this->m_Head = 0;");
    printfnl("    this->m_Tail = 0;");
    printfnl("    this->m_Data = NULL;");
    printfnl("    this->m_Size = 0;");
    printfnl("    this->m_IsFull = 0;");
    printfnl("    return OK;");
    printfnl("}");

    printfnl("status_t %s::Init(%sint init_size)",
        names.c_class_name,
        g_cpp_base_codegen:Code_InitParam({add_comma=true})
    );

    printfnl("{");
    printfnl("    this->InitBasic();");

    printnl(g_cpp_base_codegen:Code_Init());    

    printfnl("    MALLOC(this->m_Data,%s,size);",names.node_class_name);
    printfnl("    this->m_Size = size;");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("status_t %s::Destroy()",names.c_class_name);
    printfnl("{");
    printfnl("    FREE(this->m_Data);");
    printfnl("    this->InitBasic();");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("bool %s::IsEmpty()",names.c_class_name);
    printfnl("{");
    printfnl("    return this->GetLen() <= 0;");
    printfnl("}");
    printfnl("");
    printfnl("bool %s::IsFull()",names.c_class_name);
    printfnl("{");
    printfnl("    return this->m_IsFull;");
    printfnl("}");
    printfnl("status_t %s::Clear()",names.c_class_name);
    printfnl("{");
    printfnl("    this->m_Head = 0;");
    printfnl("    this->m_Tail = 0;");
    printfnl("    this->m_IsFull = 0;");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("status_t %s::Enqueue(%s node)",names.c_class_name,names.node_class_name);
    printfnl("{");
    printfnl("    ASSERT(!this->IsFull());");
    printfnl("    this->m_Data[this->m_Tail] = node;");
    printfnl("    this->m_Tail=(this->m_Tail+1) %% this->m_Size;    ");
    printfnl("    if(this->m_Tail == this->m_Head)");
    printfnl("        this->m_IsFull = TRUE;");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("status_t %s::Dequeue(%s *node)",names.c_class_name,names.node_class_name);
    printfnl("{");
    printfnl("    ASSERT(node && (!this->IsEmpty()));");
    printfnl("    *node = this->m_Data[this->m_Head];");
    printfnl("    this->m_Head = (this->m_Head+1) %% this->m_Size;");
    printfnl("    this->m_IsFull = FALSE;");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("int %s::GetLen()",names.c_class_name);
    printfnl("{");
    printfnl("    if(this->IsFull())");
    printfnl("        return this->m_Size;");
    printfnl("    return (this->m_Tail - this->m_Head + this->m_Size) %% this->m_Size;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::GetHead(%s *node)",names.c_class_name,names.node_class_name);
    printfnl("{");
    printfnl("    ASSERT(node);");
    printfnl("    if(this->IsEmpty())return NULL;   ");
    printfnl("    *node = this->m_Data[this->m_Head];");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::GetElem(int index,%s *node)",names.c_class_name,names.node_class_name);
    printfnl("{");
    printfnl("    ASSERT(node);");
    printfnl("    ASSERT(index >= 0 && index < GetLen());   ");
    printfnl("    int i =    (this->m_Head+index) %% m_Size;   ");
    printfnl("    *node = m_Data[i];");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::GetTail(%s *node)",names.c_class_name,names.node_class_name);
    printfnl("{");
    printfnl("    ASSERT(node);");
    printfnl("    if(this->IsEmpty())return NULL;   ");
    printfnl("    return this->GetElem(GetLen()-1,node);");
    printfnl("}");
    printfnl("/////////////////////////////////////////////////////");
    printfnl("status_t %s::Copy(%s *queue)",names.c_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    ASSERT(queue);");
    printfnl("    ");
    printfnl("    if(m_Size != queue->m_Size)");
    printfnl("    {");
    printfnl("        this->Destroy();");
    printfnl("        this->Init(queue->m_Size);");
    printfnl("    }");
    printfnl("    ");
    printfnl("    this->Clear();");
    printfnl("    ");
    printfnl("    for(int i = 0; i < queue->GetLen(); i++)");
    printfnl("    {");
    printfnl("        %s v;",names.node_class_name);
    printfnl("        queue->GetElem(i,&v);");
    printfnl("        this->Enqueue(v);");
    printfnl("    }");
    printfnl("    ");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::Comp(%s *queue)",names.c_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    ASSERT(0);");
    printfnl("    ASSERT(queue);");
    printfnl("    if(this == queue)");
    printfnl("        return 0;");
    printfnl("    return 0;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::Print(CFileBase *_buf)",names.c_class_name);
    printfnl("{");
    printfnl("    int i;");
    printfnl("    _buf->Log(\"head=%%d\",this->m_Head);");
    printfnl("    _buf->Log(\"tail=%%d\",this->m_Tail);");
    printfnl("    _buf->Log(\"size=%%d\",this->m_Size);");
    printfnl("    _buf->Log(\"length=%%d\",this->GetLen());");
    printfnl("    _buf->Log(\"is_full=%%d\",this->m_IsFull);");
    printfnl("    for(i=0;i<this->GetLen();i++)");
    printfnl("    {");
    printfnl("        //add your code");
    printfnl("    }");
    printfnl("");
    printfnl("    return TRUE;");
    printfnl("}");

    printfnl("");    
    printnl(g_cpp_base_codegen:Code_NameSpaceEnd());    
    printfnl("");
end
