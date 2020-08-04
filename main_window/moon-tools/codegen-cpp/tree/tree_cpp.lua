function code_cpp(names)
    printfnl("#include \"%s.h\"",to_file_name(names.class_name));
    printfnl("#include \"syslog.h\"");
    printfnl("#include \"mem_tool.h\"");
    
	printfnl("");
    maybe_printnl(g_cpp_base_codegen:Code_NameSpaceBegin());    
    printfnl("");
    
    printfnl("%s::%s()",names.c_entry_class_name,names.c_entry_class_name);
    printfnl("{");
    printfnl("    m_RawPtr = NULL;");
    printfnl("    parent = NULL;");
    printfnl("    next = NULL;");
    printfnl("    prev = NULL;");
    printfnl("    child = NULL;");
    printfnl("}");
    printfnl("");
    printfnl("%s::~%s()",names.c_entry_class_name,names.c_entry_class_name);
    printfnl("{");
    printfnl("    parent = NULL;");
    printfnl("    next = NULL;");
    printfnl("    child = NULL;");
    printfnl("    prev = NULL;");
    printfnl("    DEL(m_RawPtr);");
    printfnl("}");
    printfnl("    ");
    printfnl("%s* %s::get()",names.c_node_class_name,names.c_entry_class_name);
    printfnl("{");
    printfnl("    return m_RawPtr;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::set(%s *node)",names.c_entry_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    ASSERT(m_RawPtr == NULL);");
    printfnl("    m_RawPtr = node;");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
printfnl("status_t %s::DetachFromTheTree()",names.c_entry_class_name);
    printfnl("{");
    printfnl("    %s *node = this;",names.c_entry_class_name);
    printfnl("");
    printfnl("    if(node->parent)");
    printfnl("    {");
    printfnl("        if(node->parent->child == node)");
    printfnl("        {            ");
    printfnl("            node->parent->child = node->next;");
    printfnl("        }");
    printfnl("    }");
    printfnl("    ");
    printfnl("    if(node->prev)");
    printfnl("    {");
    printfnl("        node->prev->next = node->next;");
    printfnl("    }");
    printfnl("    ");
    printfnl("    if(node->next)");
    printfnl("    {");
    printfnl("        node->next->prev = node->prev;");
    printfnl("    }");
    printfnl("    ");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("status_t %s::DelNode_Recursive(%s *node)",names.c_entry_class_name,names.c_entry_class_name);
    printfnl("{");
    printfnl("    ASSERT(node);");
    printfnl("    ");
    printfnl("    %s *child = node->child;",names.c_entry_class_name);
    printfnl("    while(child)");
    printfnl("    {");
    printfnl("        %s *p = child;",names.c_entry_class_name);
    printfnl("        child = child->next;");
    printfnl("        DelNode_Recursive(p);        ");
    printfnl("    }");
    printfnl("");
printfnl("    node->DetachFromTheTree();    ");
    printfnl("    DEL(node);    ");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::Traverse(CClosure *closure)",names.c_entry_class_name);
    printfnl("{");
    printfnl("    ASSERT(closure);");
    printfnl("    ");
    printfnl("    if(closure->GetParamType(1) != PARAM_TYPE_INT)");
    printfnl("    {");
    printfnl("        closure->SetParamInt(1,0); //level");
    printfnl("    }");
    printfnl("");
    printfnl("    closure->SetParamPointer(0,this);");
    printfnl("    if(!closure->Run())");
    printfnl("        return ERROR;");
    printfnl("");
    printfnl("    if(closure->GetParamPointer(0) == NULL)");
    printfnl("    {");
    printfnl("        return OK;");
    printfnl("    }");
    printfnl("");
    printfnl("    %s *next, *child = this->child;",names.c_entry_class_name);
    printfnl("    while(child)");
    printfnl("    {");
    printfnl("        int level = closure->GetParamInt(1);");
    printfnl("        closure->SetParamInt(1,level+1);        ");
    printfnl("        next = child->next;");
    printfnl("        //child maybe deleted");
    printfnl("        if(!child->Traverse(closure)) ");
    printfnl("            return ERROR;");
    printfnl("        closure->SetParamInt(1,level);");
    printfnl("        child = next;");
    printfnl("    }    ");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::Print_Recursive(%s *node, CFileBase *buf)",names.c_entry_class_name,names.c_entry_class_name);
    printfnl("{");
    printfnl("    ASSERT(node && buf);");
    printfnl("    ");
    printfnl("    BEGIN_CLOSURE(on_traverse)");
    printfnl("    {");
    printfnl("        CLOSURE_PARAM_PTR(CFileBase*,buf,10);");
    printfnl("        CLOSURE_PARAM_PTR(%s*,pn,0);",names.c_entry_class_name);
    printfnl("        CLOSURE_PARAM_INT(level,1);        ");
    printfnl("        buf->SetLogLevel(level);        ");
    printfnl("        ASSERT(pn->get());");
    printfnl("        buf->Log(\"{\");");
    printfnl("        buf->IncLogLevel(1);");
    printfnl("        pn->get()->Print(buf);       ");
    printfnl("        buf->IncLogLevel(-1);");
    printfnl("        buf->Log(\"},\");");
    printfnl("        return OK;");
    printfnl("    }");
    printfnl("    END_CLOSURE(on_traverse);");
    printfnl("    ");
    printfnl("    on_traverse.SetParamPointer(10,buf);");
    printfnl("    return node->Traverse(&on_traverse);");
    printfnl("}");
    printfnl("");
    printfnl("%s* %s::NewFromPointer(%s *node)",names.c_entry_class_name,names.c_entry_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    %s *tmp;",names.c_entry_class_name);
    printfnl("    NEW(tmp,%s);",names.c_entry_class_name);
    printfnl("    tmp->set(node);");
    printfnl("    return tmp;");
    printfnl("}");
    printfnl("");
    printfnl("%s* %s::New(%s *node)",names.c_entry_class_name,names.c_entry_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    %s *p;",names.c_node_class_name);
    printfnl("    NEW(p,%s);",names.c_node_class_name);
    printfnl("    p->Init();");
    printfnl("    p->Copy(node);");
    printfnl("    return NewFromPointer(p);");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::InsertBefore(%s *node)",names.c_entry_class_name,names.c_entry_class_name);
    printfnl("{   ");
    printfnl("    ASSERT(node);");
    printfnl("");
    printfnl("    if(this->prev)");
    printfnl("    {");
    printfnl("        this->prev->next = node;");
    printfnl("        node->prev = this->prev;");
    printfnl("    }");
    printfnl("    ");
    printfnl("    node->next = this;");
    printfnl("    this->prev = node;");
    printfnl("    node->parent = this->parent;");
    printfnl("");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::InsertAfter(%s *node)",names.c_entry_class_name,names.c_entry_class_name);
    printfnl("{");
    printfnl("    ASSERT(node);");
    printfnl("");
    printfnl("    if(this->next)");
    printfnl("    {");
    printfnl("        node->next = this->next;");
    printfnl("        this->next->prev = node;");
    printfnl("    }");
    printfnl("    ");
    printfnl("    this->next = node;");
    printfnl("    node->prev = this;");
    printfnl("    node->parent = this->parent;");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::AddChild(%s *node)",names.c_entry_class_name,names.c_entry_class_name);
    printfnl("{");
    printfnl("    ASSERT(node);");
    printfnl("    if(this->child == NULL)");
    printfnl("    {");
    printfnl("        node->parent = this;");
    printfnl("        this->child = node;");
    printfnl("        return OK;");
    printfnl("    }");
    printfnl("");
    printfnl("    this->child->InsertBefore(node);");
    printfnl("    this->child = node;");
    printfnl("    return OK;");
    printfnl("}");
	printfnl("");
	printfnl("status_t %s::AddChildToTail(%s *node)",names.c_entry_class_name,names.c_entry_class_name);
	printfnl("{");
	printfnl("    ASSERT(node);");
	printfnl("");
	printfnl("    %s *tail = this->GetLastChild();    ",names.c_entry_class_name);
	printfnl("    if(!tail)");
	printfnl("    {");
	printfnl("        this->AddChild(node);");
	printfnl("    }");
	printfnl("    else");
	printfnl("    {");
	printfnl("        tail->InsertAfter(node);");
	printfnl("    }");
	printfnl("    return OK;");
	printfnl("}");
	printfnl("");
	printfnl("%s* %s::GetLastChild()",names.c_entry_class_name,names.c_entry_class_name);
	printfnl("{");
	printfnl("    %s *last = NULL;",names.c_entry_class_name);
	printfnl("    %s *child = this->child;",names.c_entry_class_name);
	printfnl("    while(child)");
	printfnl("    {");
	printfnl("        last = child;");
	printfnl("        child = child->next;");
	printfnl("    }");
	printfnl("    return last;");
	printfnl("}");	
	if code_switch.bson then
		printfnl("");
		printfnl("status_t %s::SaveBson(CMiniBson *_bson)",names.c_entry_class_name);
		printfnl("{");
		printfnl("    ASSERT(_bson);");
		printfnl("    ASSERT(m_RawPtr);");
		printfnl("    ");
		printfnl("    m_RawPtr->SaveBson(_bson);");
		printfnl("    ");
		printfnl("    if(this->child)");
		printfnl("    {");
		printfnl("        fsize_t off;");
		printfnl("        _bson->StartArray(\"children\",&off);");
		printfnl("        int array_len = 0;");
		printfnl("        %s *child = this->child;",names.c_entry_class_name);
		printfnl("        while(child)");
		printfnl("        {    ");
		printfnl("            char name[100];");
		printfnl("            sprintf(name,\"%%d\",array_len);");
		printfnl("            fsize_t _off;");
		printfnl("            ");
		printfnl("            _bson->StartDocument(name,&_off);");
		printfnl("            child->SaveBson(_bson);");
		printfnl("            _bson->EndDocument(_off);");
		printfnl("            ");
		printfnl("            array_len++;");
		printfnl("            child = child->next;");
		printfnl("        }");
		printfnl("        _bson->EndArray(off,array_len);");
		printfnl("    }");
		printfnl("    return OK;");
		printfnl("}");
		printfnl("");
		printfnl("status_t %s::LoadBson(CMiniBson *_bson)",names.c_entry_class_name);
		printfnl("{");
		printfnl("    if(!m_RawPtr)");
		printfnl("    {");
		printfnl("        %s *tmp;",names.c_node_class_name);
		printfnl("        NEW(tmp,%s);",names.c_node_class_name);
		printfnl("        tmp->Init();");
		printfnl("        this->set(tmp);");
		printfnl("    }");
		printfnl("    ");
		printfnl("    ASSERT(m_RawPtr);");
		printfnl("    BSON_CHECK(m_RawPtr->LoadBson(_bson));");
		printfnl("    ");
		printfnl("    CMiniBson children;");
		printfnl("    int array_len = 0;");
		printfnl("    if(_bson->GetArray(\"children\",&children,&array_len))");
		printfnl("    {");
		printfnl("        %s *pre = NULL;",names.c_entry_class_name);
		printfnl("        for(int i = 0; i < array_len; i++)");
		printfnl("        {");
		printfnl("            char name[100];");
		printfnl("            sprintf(name,\"%%d\",i);");
		printfnl("        ");
		printfnl("            CMiniBson elem;");
		printfnl("            BSON_CHECK(children.GetDocument(name,&elem));");
		printfnl("        ");
		printfnl("            %s *entry;",names.c_entry_class_name);
		printfnl("            NEW(entry,%s);        ",names.c_entry_class_name);
		printfnl("            BSON_CHECK(entry->LoadBson(&elem));");
		printfnl("            if(pre == NULL)");
		printfnl("            {");
		printfnl("                pre = entry;");
		printfnl("                ASSERT(this->AddChild(entry));");
		printfnl("            }");
		printfnl("            else");
		printfnl("            {");
		printfnl("                ASSERT(pre->InsertAfter(entry));");
		printfnl("            }");
		printfnl("        }");
		printfnl("    }");
		printfnl("    return OK;");
		printfnl("}");
		printfnl("");
	end
    printfnl("/***********************************************************/");
    printfnl("/***********************************************************/");
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
    printfnl("    m_Root = NULL;");
    printfnl("    return OK;");
    printfnl("}");

    printfnl("status_t %s::Init(%s)",
        names.c_class_name,
        g_cpp_base_codegen:Code_InitParam()
    );
    
    printfnl("{");
    printfnl("    this->InitBasic();");
    maybe_printnl(g_cpp_base_codegen:Code_Init())    
	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("Init"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("Init"));	
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::Destroy()",names.c_class_name);
    printfnl("{");
	maybe_printnl(g_cpp_base_codegen:Code_Destroy());  		
	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("Destroy"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("Destroy"));	    
    printfnl("    if(m_Root)");
    printfnl("    {");
    printfnl("        %s::DelNode_Recursive(m_Root);",names.c_entry_class_name);
    printfnl("        m_Root = NULL;");
    printfnl("    }");
	printfnl("    this->InitBasic();");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::Copy(%s *p)",names.c_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    ASSERT(p);");
	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("Copy"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("Copy"));		
    printfnl("    ASSERT(0);");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::Comp(%s *p)",names.c_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    ASSERT(p);");
    printfnl("    if(p == this)");
    printfnl("        return 0;");
    printfnl("    ASSERT(0);");
    printfnl("    return 0;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::Print(CFileBase *_buf)",names.c_class_name);
    printfnl("{");
	printfnl("    if(m_Root)");
    printfnl("    {");
    printfnl("        %s::Print_Recursive(m_Root,_buf);",names.c_entry_class_name);
    printfnl("    }");
    printfnl("    else");
    printfnl("    {");
    printfnl("        _buf->Log(\"<NULL>\");");
    printfnl("    }");
	maybe_printnl(g_cpp_base_codegen:Code_BeginMarker("Print"));
	maybe_printnl(g_cpp_base_codegen:Code_EndMarker("Print"));	

    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("");
    printfnl("%s* %s::GetRoot()",names.c_entry_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    return m_Root;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::SetRoot(%s *root)",names.c_class_name,names.c_entry_class_name);
    printfnl("{");
    printfnl("    ASSERT(root);");
    printfnl("    ASSERT(m_Root == NULL);");
    printfnl("    m_Root = root;");
    printfnl("    return OK;");
    printfnl("}");

	if code_switch.bson then
		printfnl("status_t %s::SaveBson(CMiniBson *_bson)",names.c_class_name);
		printfnl("{");
		printfnl("    ASSERT(_bson);");
		printfnl("    ASSERT(m_Root);");
		printfnl("    fsize_t off;");
		printfnl("    _bson->StartDocument(\"root\",&off);");
		printfnl("    m_Root->SaveBson(_bson);");
		printfnl("    _bson->EndDocument(off);");
		printfnl("    return OK;");
		printfnl("}");
		printfnl("");
		printfnl("status_t %s::SaveBson(CMem *_mem)",names.c_class_name);
		printfnl("{");
		printfnl("    ASSERT(_mem);");
		printfnl("    CMiniBson _bson;");
		printfnl("    _bson.Init();");
		printfnl("    _bson.SetRawBuf(_mem);");
		printfnl("    _bson.StartDocument();");
		printfnl("    this->SaveBson(&_bson);");
		printfnl("    _bson.EndDocument();");
		printfnl("    _mem->SetSize(_bson.GetDocumentSize());");
		printfnl("    return OK;");
		printfnl("}");
		printfnl("");
		printfnl("status_t %s::LoadBson(CMiniBson *_bson)",names.c_class_name);
		printfnl("{");
		printfnl("    ASSERT(_bson);");
		printfnl("    ");
		printfnl("    CMiniBson doc;");
		printfnl("    BSON_CHECK(_bson->GetDocument(\"root\",&doc));");
		printfnl("    ");
		printfnl("    if(!m_Root)");
		printfnl("    {");
		printfnl("        NEW(m_Root,%s);",names.c_entry_class_name);
		printfnl("    }");
		printfnl("    ");
        printfnl("    m_Root->LoadBson(&doc);");
		printfnl("    return OK;");
		printfnl("}");
		printfnl("");
		printfnl("status_t %s::LoadBson(CFileBase *_file)",names.c_class_name);
		printfnl("{");
		printfnl("    ASSERT(_file);");
		printfnl("    CMiniBson _bson;");
		printfnl("    _bson.Init();");
		printfnl("    _bson.LoadBson(_file);");
		printfnl("    _bson.ResetPointer();");
		printfnl("    return this->LoadBson(&_bson);");
		printfnl("}");
		printfnl("");
	end
	
    maybe_printnl(g_cpp_base_codegen:Code_NameSpaceEnd());
end