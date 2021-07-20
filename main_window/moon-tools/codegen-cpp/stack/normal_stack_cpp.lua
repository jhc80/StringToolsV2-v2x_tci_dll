require ("common")

function code_normal_cpp(names)
    printfnl("#include \"%s.h\"",names.file_name);
    printfnl("#include \"mem_tool.h\"");
    printfnl("#include \"syslog.h\"");
    printfnl("");
    maybe_printnl(g_cpp_base_codegen:Code_NameSpaceBegin());    
    printfnl("");
    printfnl("%s::%s()",names.c_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    this->InitBasic();  ");
    printfnl("}");
    printfnl("%s::~%s()",names.c_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    this->Destroy();");
    printfnl("}");
    printfnl("status_t %s::InitBasic()",names.c_class_name);
    printfnl("{");
    
    maybe_printnl(g_cpp_base_codegen:Code_InitBasic());    

    printfnl("    this->m_Index = NULL;");
    printfnl("    this->m_Top = 0;");
    printfnl("    this->m_Size = 0;    ");
    printfnl("    return OK;");
    printfnl("}");
    
    printfnl("status_t %s::Init(%sint init_size)",
        names.c_class_name,
        g_cpp_base_codegen:Code_InitParam({add_comma=true})
    );

    printfnl("{");
    printfnl("    int i;");
    printfnl("    this->InitBasic();  ");
    maybe_printnl(g_cpp_base_codegen:Code_Init());
    printfnl("    this->m_Size = init_size;");
    printfnl("    MALLOC(this->m_Index,%s* ,this->m_Size);",names.c_node_class_name);
    printfnl("    for(i = 0; i < this->m_Size; i++)");
    printfnl("        this->m_Index[i] = NULL;");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::Destroy()",names.c_class_name);
    printfnl("{");
    printfnl("    int i;");
	
	maybe_printnl(g_cpp_base_codegen:Code_Destroy());
	
    printfnl("    if(this->m_Index == NULL)");
    printfnl("        return ERROR;");
    printfnl("");
    printfnl("    for(i = 0; i < this->m_Top; i++)");
    printfnl("    {");
    printfnl("        this->DelNode(this->m_Index[i]);");
    printfnl("    }");
    printfnl("    FREE(this->m_Index);");
    printfnl("    this->InitBasic();    ");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("bool %s::IsEmpty()",names.c_class_name);
    printfnl("{");
    printfnl("    return this->m_Top <= 0;");
    printfnl("}");
    printfnl("bool %s::IsFull()",names.c_class_name);
    printfnl("{");
    printfnl("    return this->m_Top >= this->m_Size;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::AutoResize()",names.c_class_name);
    printfnl("{");
    printfnl("    int i;");
    printfnl("");
    printfnl("    if(this->IsFull())");
    printfnl("    {");
    printfnl("        REALLOC(this->m_Index,%s*,this->m_Size,this->m_Size*2);",names.c_node_class_name);
    printfnl("        this->m_Size *= 2;");
    printfnl("        for(i = this->m_Top; i < this->m_Size; i++)");
    printfnl("        {");
    printfnl("            this->m_Index[i] = NULL;");
    printfnl("        }");
    printfnl("    }");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::Push(%s *node)",names.c_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    %s *tmp;",names.c_node_class_name);
    printfnl("    ASSERT(node);");
    printfnl("    tmp = this->CloneNode(node);");
    printfnl("    if(!this->PushPtr(tmp))");
    printfnl("    {");
    printfnl("        this->DelNode(tmp);");
    printfnl("        return ERROR;");
    printfnl("    }");
    printfnl("    ");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::PushPtr(%s *node)",names.c_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    ASSERT(node);    ");
    printfnl("    this->AutoResize();");
    printfnl("    ASSERT(!this->IsFull());");
    printfnl("    this->m_Index[this->m_Top] = node;");
    printfnl("    this->m_Top++;");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("%s * %s::PopPtr()",names.c_node_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    if(this->IsEmpty())");
    printfnl("        return NULL;");
    printfnl("    this->m_Top--;");
    printfnl("    return this->m_Index[this->m_Top];");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::Pop(%s *node)",names.c_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    ASSERT(!this->IsEmpty());    ");
    printfnl("    this->m_Top--;");
    printfnl("    this->CopyNode(node,this->m_Index[this->m_Top]);");
    printfnl("    this->DelNode(this->m_Index[this->m_Top]);");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("int %s::GetLen()",names.c_class_name);
    printfnl("{");
    printfnl("    return this->m_Top;");
    printfnl("}");
    printfnl("");
    printfnl("int %s::SearchPos(%s *node)",names.c_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    int i;");
    printfnl("    for(i=0;i<this->m_Top;i++)");
    printfnl("    {");
    printfnl("        if(this->CompNode(this->m_Index[i],node) == 0)");
    printfnl("            return i;");
    printfnl("    }");
    printfnl("    return -1;");
    printfnl("}");
    printfnl("");
    printfnl("%s* %s::Search(%s *node)",names.c_node_class_name,names.c_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    int pos = this->SearchPos(node);");
    printfnl("    if(pos >= 0 && pos < this->m_Top)");
    printfnl("        return this->m_Index[pos];;");
    printfnl("    return NULL;");
    printfnl("}");
    printfnl("%s* %s::GetTopPtr()",names.c_node_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    if(this->IsEmpty())");
    printfnl("        return NULL;");
    printfnl("    return this->m_Index[this->m_Top - 1];");
    printfnl("}");
    printfnl("status_t %s::DelTop()",names.c_class_name);
    printfnl("{");
    printfnl("    if(this->IsEmpty())");
    printfnl("        return ERROR;");
    printfnl("    this->m_Top--;");
    printfnl("    this->DelNode(this->m_Index[this->m_Top]);");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("status_t %s::Clear()",names.c_class_name);
    printfnl("{");
    printfnl("    while(this->DelTop());");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("%s* %s::GetElem(int index)",names.c_node_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    if(index < 0 || index >= this->m_Top)");
    printfnl("        return NULL;");
    printfnl("    return this->m_Index[index];");
    printfnl("}");
    printfnl("");
    printfnl("%s* %s::BSearchNode(%s *node,int order)",names.c_node_class_name,names.c_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    return this->GetElem(this->BSearch(node,order));");
    printfnl("}");
    printfnl("int %s::BSearch(%s *node,int order)",names.c_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    int find,pos;");
    printfnl("    pos = this->BSearchPos(node,order,&find);");
    printfnl("    if(find) return pos;");
    printfnl("    return -1;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::InsElemPtr(int i, %s *node)",names.c_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    int k;");
    printfnl("");
    printfnl("    ASSERT(node);");
    printfnl("    ASSERT(i >= 0 && i <= this->m_Top);");
    printfnl("");
    printfnl("    this->AutoResize();");
    printfnl("    ASSERT(!this->IsFull());");
    printfnl("    for(k = this->m_Top; k > i; k--)");
    printfnl("    {");
    printfnl("        this->m_Index[k] = this->m_Index[k - 1];");
    printfnl("    }");
    printfnl("    this->m_Index[i] = node;");
    printfnl("    this->m_Top++;");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::InsElem(int i, %s *node)",names.c_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    %s *tmp;",names.c_node_class_name);
    printfnl("    ASSERT(node);");
    printfnl("    tmp = this->CloneNode(node);");
    printfnl("    if(!this->InsElemPtr(i,tmp))");
    printfnl("    {");
    printfnl("        this->DelNode(tmp);");
    printfnl("        return ERROR;");
    printfnl("    }");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("%s* %s::RemoveElem(int index)",names.c_node_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    %s *p;",names.c_node_class_name);
    printfnl("    int k;");
    printfnl("    ");
    printfnl("    ASSERT(index >= 0 && index < this->m_Top);");
    printfnl("    p = this->GetElem(index);");
    printfnl("");
    printfnl("    for(k = index; k < this->m_Top-1; k++)");
    printfnl("    {");
    printfnl("        this->m_Index[k] = this->m_Index[k + 1];");
    printfnl("    }");
    printfnl("    this->m_Top --;");
    printfnl("    this->m_Index[this->m_Top] = NULL;");
    printfnl("    return p;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::DelElem(int i)",names.c_class_name);
    printfnl("{");
    printfnl("    %s *p = this->RemoveElem(i);",names.c_node_class_name);
    printfnl("    if(p != NULL)");
    printfnl("    {");
    printfnl("        this->DelNode(p);");
    printfnl("        return OK;");
    printfnl("    }");
    printfnl("    return ERROR;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::InsOrderedPtr(%s *node, int order,int unique)",names.c_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    int pos,find;");
    printfnl("    pos = this->BSearchPos(node,order,&find);");
    printfnl("    if(find && unique)");
    printfnl("        return ERROR;");
    printfnl("    return this->InsElemPtr(pos,node);");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::InsOrdered(%s *node, int order,int unique)",names.c_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    int pos,find;");
    printfnl("    ASSERT(node);");
    printfnl("    pos = this->BSearchPos(node,order,&find);");
    printfnl("    if(find && unique)");
    printfnl("        return ERROR;");
    printfnl("    return this->InsElem(pos,node);");
    printfnl("}");
    printfnl("");
    printfnl("int %s::BSearchPos(%s *node, int order, int *find_flag)",names.c_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    int low,high,mid,comp;");
    printfnl("    ");
    printfnl("    low = 0; ");
    printfnl("    high = this->GetLen() - 1;");
    printfnl("");
    printfnl("    while(low<=high)");
    printfnl("    {");
    printfnl("        mid = (low+high) >> 1;");
    printfnl("");
    printfnl("        comp = this->CompNode(this->m_Index[mid],node);");
    printfnl("        if(comp == 0)");
    printfnl("        {");
    printfnl("            *find_flag = TRUE;");
    printfnl("            return mid;");
    printfnl("        }");
    printfnl("    ");
    printfnl("        if(order != 0) comp = -comp;");
    printfnl("        if(comp>0)high=mid-1;else low=mid+1;");
    printfnl("    }");
    printfnl("    *find_flag = FALSE;");
    printfnl("    return low;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::Sort(int order)",names.c_class_name);
    printfnl("{");
    printfnl("    int i,len;");
    printfnl("    %s tmp;",names.c_class_name);
    printfnl("");
    printfnl("    len = this->GetLen();");
	
	if code_switch.task_container then
		printfnl("    tmp.Init(GetTaskMgr(),len);");
	else
		printfnl("    tmp.Init(len);");
	end
	
    printfnl("");
    printfnl("    for(i = 0; i < len; i++)");
    printfnl("    {");
    printfnl("        tmp.PushPtr(this->GetElem(i));");
    printfnl("    }");
    printfnl("");
    printfnl("    this->m_Top = 0;");
    printfnl("    for(i = 0; i < len; i++)");
    printfnl("    {");
    printfnl("        this->InsOrderedPtr(tmp.PopPtr(),order,0);");
    printfnl("    }");
    printfnl("    ");
    printfnl("    for(i = 0; i < len; i++)");
    printfnl("    {");
    printfnl("        tmp.m_Index[i] = NULL;");
    printfnl("    }");
    printfnl("");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("int %s::Comp(%s *stk)",names.c_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    ASSERT(stk);");
    printfnl("    if(this == stk)");
    printfnl("        return 0;");
    printfnl("    ASSERT(0);");
    printfnl("    return 0;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::Copy(%s *_p)",names.c_class_name,names.c_class_name);
    printfnl("{");
    printfnl("    int i;");
    printfnl("");
    printfnl("    ASSERT(_p);");

    printfnl("    this->Clear();");
	
    printfnl("    for(i = 0; i < _p->GetLen(); i++)");
    printfnl("    {");
    printfnl("        %s *p = _p->GetElem(i);",names.c_node_class_name);
    printfnl("        ASSERT(p);");
    printfnl("        this->Push(p);");
    printfnl("    }");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("status_t %s::Print(CFileBase *_buf)",names.c_class_name);
    printfnl("{");
    printfnl("    for(int i = 0; i < this->m_Top; i++)");
    printfnl("    {");
    printfnl("        if(this->m_Index[i])");
    printfnl("        {");
    printfnl("            _buf->Log(\"[%%d]={\",i);");
    printfnl("            _buf->IncLogLevel(1);");
    printfnl("            this->m_Index[i]->Print(_buf);");
    printfnl("            _buf->IncLogLevel(-1);");
    printfnl("            _buf->Log(\"}\");");
    printfnl("        }");
    printfnl("    }");
    printfnl("    _buf->Log(\"top = %%d\",this->m_Top);");
    printfnl("    _buf->Log(\"size = %%d\",this->m_Size);");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");

if code_switch.bson then    
    printfnl("status_t %s::SaveBson(CMiniBson *_bson)",names.c_class_name);
    printfnl("{");
    printfnl("    ASSERT(_bson);");
    printfnl("    ");
    printfnl("    fsize_t off;");
    printfnl("    _bson->StartArray(\"_array_\",&off);");
    printfnl("    char name[256];");
    printfnl("    for(int i = 0; i < this->GetLen(); i++)");
    printfnl("    {");
    printfnl("        %s *p = this->GetElem(i);",names.c_node_class_name);
    printfnl("        ASSERT(p);        ");
    printfnl("        sprintf(name,\"%%d\",i);");
    printfnl("        fsize_t _off;");
    printfnl("        _bson->StartDocument(name,&_off);");
    printfnl("        p->SaveBson(_bson);");
    printfnl("        _bson->EndDocument(_off);");
    printfnl("    }");
    printfnl("    _bson->EndArray(off,this->GetLen());    ");
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
    printfnl("");
    printfnl("    CMiniBson doc;");
    printfnl("    doc.Init();");
    printfnl("");
    printfnl("    int len = 0;");
    printfnl("    BSON_CHECK(_bson->GetArray(\"_array_\",&doc,&len));");
    printfnl("    this->Clear();");
    printfnl("    ");
    printfnl("    doc.ResetPointer();");
    printfnl("    for(int i = 0; i < len; i++)");
    printfnl("    {");
    printfnl("        CMiniBson sub_doc;");
    printfnl("        sub_doc.Init();");
    printfnl("        doc.GetDocument(NULL,&sub_doc);");
    printfnl("        %s tmp;",names.c_node_class_name);
    printfnl("        tmp.Init();");
    printfnl("        BSON_CHECK(tmp.LoadBson(&sub_doc));");
    printfnl("        this->Push(&tmp);");
    printfnl("    }");
    printfnl("");
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
end

if code_switch.cjson then
    printfnl("status_t %s::LoadJson(const char *_json)",names.c_class_name);
    printfnl("{");
    printfnl("    ASSERT(_json);");
    printfnl("    cJSON *p_root = cJSON_Parse(_json);");
    printfnl("    if(!p_root)");
    printfnl("    {");
    printfnl("        XLOG(LOG_MODULE_USER,LOG_LEVEL_ERROR,");
    printfnl("            \"error: load json fail at %%s\",");
    printfnl("            cJSON_GetErrorPtr()");
    printfnl("        );");
    printfnl("        return ERROR;");
    printfnl("    }");
    printfnl("    status_t ret = this->LoadJson(p_root);");
    printfnl("    cJSON_Delete(p_root);");
    printfnl("    return ret;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::LoadJson(const cJSON *_json)",names.c_class_name);
    printfnl("{");
    printfnl("    ASSERT(_json);");

    printfnl("    this->Clear();    ");
    printfnl("    int _len = cJSON_GetArraySize(_json);");
    printfnl("    for(int i = 0; i < _len; i++)");
    printfnl("    {");
    printfnl("        cJSON *json_obj = cJSON_GetArrayItem(_json,i);");
    printfnl("        ASSERT(json_obj);");
    printfnl("        %s tmp;",names.c_node_class_name);
    printfnl("        tmp.Init();");
    printfnl("        ASSERT(tmp.LoadJson(json_obj));");
    printfnl("        this->Push(&tmp);");
    printfnl("    }");
    
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::SaveJson(CFileBase *_file)",names.c_class_name);
    printfnl("{");
    printfnl("    ASSERT(_file);");
    printfnl("    cJSON *root = cJSON_CreateObject();");
    printfnl("    this->SaveJson(root);");
    printfnl("    char *str = cJSON_Print(root);");
    printfnl("    if(str)");
    printfnl("    {");
    printfnl("        _file->Puts(str);");
    printfnl("        free(str);");
    printfnl("    }");
    printfnl("    cJSON_Delete(root);");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::SaveJson(cJSON *_root)",names.c_class_name);
    printfnl("{");
    printfnl("    ASSERT(_root);");
    printfnl("    _root->type = cJSON_Array;");
    printfnl("    for(int i = 0;i < GetLen(); i++)");
    printfnl("    {");
    printfnl("        %s *_p = GetElem(i);",names.c_node_class_name);
    printfnl("        cJSON *json_obj = cJSON_CreateObject();");
    printfnl("        ASSERT(json_obj);");
    printfnl("        _p->SaveJson(json_obj);");
    printfnl("        cJSON_AddItemToArray(_root,json_obj);");
    printfnl("    }");  
    printfnl("    return OK;");
    printfnl("}");
end

    printfnl("/////////////////////////////////////////////////////////////////////////////////////");
    printfnl("/////////////////////////////////////////////////////////////////////////////////////");
    printfnl("status_t %s::CopyNode(%s *dst, %s *src)",names.c_class_name,names.c_node_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    return dst->Copy(src);");
    printfnl("}");
    printfnl("");
    printfnl("%s* %s::CloneNode(%s *node)",names.c_node_class_name,names.c_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    %s *tmp;",names.c_node_class_name);
    printfnl("    NEW(tmp,%s);",names.c_node_class_name);
    printfnl("    tmp->Init();");
    printfnl("    this->CopyNode(tmp,node);");
    printfnl("    return tmp;");
    printfnl("}");
    printfnl("");
    printfnl("status_t %s::DelNode(%s *node)",names.c_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    DEL(node);");
    printfnl("    return OK;");
    printfnl("}");
    printfnl("");
    printfnl("int %s::CompNode(%s *node1, %s *node2)",names.c_class_name,names.c_node_class_name,names.c_node_class_name);
    printfnl("{");
    printfnl("    ASSERT(node1 && node2);");
    printfnl("    return node1->Comp(node2);");
    printfnl("}");
    printfnl("/////////////////////////////////////////////////////////////////////////////////////");
    printfnl("");
    maybe_printnl(g_cpp_base_codegen:Code_NameSpaceEnd());
    printfnl("");

end