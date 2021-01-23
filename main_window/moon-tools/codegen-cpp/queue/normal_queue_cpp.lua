require("common")

function code_normal_cpp(names)
    printfnl("#include \"%s.h\"",names.file_name);
    printfnl("#include \"syslog.h\"");
    printfnl("#include \"mem_tool.h\"");
    printfnl("");    
    maybe_printnl(g_cpp_base_codegen:Code_NameSpaceBegin());    
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

    maybe_printnl(g_cpp_base_codegen:Code_InitBasic());    
	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("InitBasic"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("InitBasic"));
	
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
    printfnl("    int i;");
    printfnl("    this->InitBasic();");

    maybe_printnl(g_cpp_base_codegen:Code_Init());    
	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("Init"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("Init"));

    printfnl("");
    printfnl("    NEW_ARRAY(this->m_Data,%s,init_size);",names.c_node_class_name);
    printfnl("    for(i = 0; i < init_size; i++)");
    printfnl("    {");
    printfnl("        this->m_Data[i].Init();");
    printfnl("    }");
    printfnl("    this->m_Size = init_size;");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("status_t %s::Destroy()",names.c_class_name);
    printfnl("{");
	maybe_printnl(g_cpp_base_codegen:Code_Destroy());
	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("Destroy"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("Destroy"));
    printfnl("    DEL_ARRAY(this->m_Data);");
    printfnl("    this->InitBasic();");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::Clear()",names.c_class_name);
    printfnl("{");
    printfnl("    this->m_Head = 0;");
    printfnl("    this->m_Tail = 0;");
    printfnl("    this->m_IsFull = false;");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("bool %s::IsEmpty()",names.c_class_name);
    printfnl("{");
    printfnl("    return this->GetLen() <= 0;");
    printfnl("}");
    printfnl("bool %s::IsFull()",names.c_class_name);
    printfnl("{");
    printfnl("    return this->m_IsFull;");
    printfnl("}");
    printfnl("");
    printfnl("%s* %s::Enqueue()",names.c_node_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    %s *ret;",names.c_node_class_name);
    printfnl("    if(this->IsFull())return NULL;");
    printfnl("    ret = &this->m_Data[this->m_Tail];");
    printfnl("    this->m_Tail=(this->m_Tail+1) %% this->m_Size;    ");
    printfnl("    if(this->m_Tail == this->m_Head)");
    printfnl("        this->m_IsFull = TRUE;");
    printfnl("    return ret;");
    printfnl("}");
    printfnl("%s* %s::Dequeue()",names.c_node_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    %s *ret;",names.c_node_class_name);
    printfnl("    if(this->IsEmpty())return NULL;");
    printfnl("    ret = &this->m_Data[this->m_Head];");
    printfnl("    this->m_Head = (this->m_Head+1) %% this->m_Size;");
    printfnl("    this->m_IsFull = FALSE;");
    printfnl("    return ret;");
    printfnl("}");
    printfnl("");
    printfnl("int %s::GetLen()",names.c_class_name);
    printfnl("{");
    printfnl("    if(this->IsFull())return this->m_Size;");
    printfnl("    return (this->m_Tail - this->m_Head + this->m_Size) %% this->m_Size;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::Copy(%s *queue)",names.c_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    ASSERT(queue);");
    printfnl("");
    printfnl("    if(m_Size != queue->m_Size)");
    printfnl("    {");
    printfnl("        this->Destroy();");
    printfnl("        this->Init(queue->m_Size);");
    printfnl("    }");
    printfnl("    ");
    printfnl("    this->Clear();");
    printfnl("");
    printfnl("    for(int i = 0; i < queue->GetLen(); i++)");
    printfnl("    {");
    printfnl("        this->Enqueue(queue->GetElem(i));");
    printfnl("    }");
    printfnl("");
	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("Copy"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("Copy"));
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
    printfnl("");
    printfnl("    _buf->Log(\"head=%%d\",this->m_Head);");
    printfnl("    _buf->Log(\"tail=%%d\",this->m_Tail);");
    printfnl("    _buf->Log(\"size=%%d\",this->m_Size);");
    printfnl("    _buf->Log(\"length=%%d\",this->GetLen());");
    printfnl("    _buf->Log(\"is_full=%%d\",this->m_IsFull);");
    printfnl("");
    printfnl("    for(i=0;i<this->GetLen();i++)");
    printfnl("    {");
    printfnl("        %s *p = GetElem(i);",names.c_node_class_name);
    printfnl("        ASSERT(p);");
    printfnl("        _buf->Log(\"[%%d]={\",i);");
    printfnl("        _buf->IncLogLevel(1);");
    printfnl("        p->Print(_buf);");
    printfnl("        _buf->IncLogLevel(-1);");
    printfnl("        _buf->Log(\"}\");");
    printfnl("    }");
    printfnl("");
	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("Print"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("Print"));
    printfnl("    return TRUE;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::Enqueue(%s *pos)",names.c_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    %s *n = this->Enqueue();    ",names.c_node_class_name);
    printfnl("    ASSERT(n);   ");
    printfnl("    n->Copy(pos);");
    printfnl("    return OK;    ");
    printfnl("}");
    printfnl("");
    printfnl("%s* %s::GetHead()",names.c_node_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    if(this->IsEmpty())return NULL;   ");
    printfnl("    return &this->m_Data[this->m_Head];");
    printfnl("}");
    printfnl("");
    printfnl("%s* %s::GetElem(int index)",names.c_node_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    ASSERT(index >= 0 && index < GetLen());   ");
    printfnl("    int i =    (this->m_Head+index) %% m_Size;   ");
    printfnl("    return &m_Data[i];");
    printfnl("}");
    printfnl("");
    printfnl("%s* %s::GetTail()",names.c_node_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    if(this->IsEmpty())return NULL;   ");
    printfnl("    return this->GetElem(GetLen()-1);");
    printfnl("}");
    printfnl("");
    maybe_printnl(g_cpp_base_codegen:Code_NameSpaceEnd());
    printfnl("");
    
end
