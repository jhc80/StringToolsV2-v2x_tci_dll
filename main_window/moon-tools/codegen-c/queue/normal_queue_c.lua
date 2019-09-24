require("common")

function code_normal_cpp(names)
	printfnl("#include \"%s.h\"",to_file_name(names.class_name));
	printfnl("#include \"syslog.h\"");
	printfnl("#include \"mem_tool.h\"");
	printfnl("");
	printfnl("status_t %s_init_basic(%s *self)",names.class_name_lower,names.c_class_name);
	printfnl("{");
	printfnl("    self->head = 0;");
	printfnl("    self->tail = 0;");
	printfnl("    self->data = NULL;");
	printfnl("    self->size = 0;");
	printfnl("    self->is_full = 0;");
	printfnl("    return OK;");
	printfnl("}");
	printfnl("status_t %s_init(%s *self,int size)",names.class_name_lower,names.c_class_name);
	printfnl("{");
	printfnl("    int i;");
	printfnl("    %s_init_basic(self);",names.class_name_lower);
	printfnl("    X_MALLOC(self->data,%s,size);",names.c_node_class_name);
	printfnl("    for(i = 0; i < size; i++)");
	printfnl("    {");
	printfnl("        %s_init(&self->data[i]);",names.node_class_name_lower);
	printfnl("    }");
	printfnl("    self->size = size;");
	printfnl("    return OK;");
	printfnl("}");
	printfnl("status_t %s_destroy(%s *self)",names.class_name_lower,names.c_class_name);
	printfnl("{");
	printfnl("    int i;");
	printfnl("    if(self == NULL)return ERROR;");
	printfnl("    if(self->data)");
	printfnl("    {");
	printfnl("        for(i = 0; i < self->size; i++)");
	printfnl("        {");
	printfnl("            %s_destroy(&self->data[i]);",names.node_class_name_lower);
	printfnl("        }");
	printfnl("        X_FREE(self->data);");
	printfnl("    }");
	printfnl("    %s_init_basic(self);",names.class_name_lower);
	printfnl("    return OK;");
	printfnl("}");
	printfnl("");
	printfnl("bool_t %s_is_empty(%s *self)",names.class_name_lower,names.c_class_name);
	printfnl("{");
	printfnl("    return %s_get_len(self) <= 0;",names.class_name_lower);
	printfnl("}");
	printfnl("bool_t %s_is_full(%s *self)",names.class_name_lower,names.c_class_name);
	printfnl("{");
	printfnl("    return self->is_full;");
	printfnl("}");
	printfnl("status_t %s_clear(%s *self)",names.class_name_lower,names.c_class_name);
	printfnl("{");
	printfnl("    self->head = 0;");
	printfnl("    self->tail = 0;");
	printfnl("    self->is_full = 0;");
	printfnl("    return OK;");
	printfnl("}");
	printfnl("%s* %s_enqueue(%s *self)",names.c_node_class_name,names.class_name_lower,names.c_class_name);
	printfnl("{");
	printfnl("    %s *ret;",names.c_node_class_name);
	printfnl("    if(%s_is_full(self))return NULL;",names.class_name_lower);
	printfnl("    ret = &self->data[self->tail];");
	printfnl("    self->tail=(self->tail+1) %% self->size;    ");
	printfnl("    if(self->tail == self->head)");
	printfnl("        self->is_full = TRUE;");
	printfnl("    return ret;");
	printfnl("}");
	printfnl("%s* %s_dequeue(%s *self)",names.c_node_class_name,names.class_name_lower,names.c_class_name);
	printfnl("{");
	printfnl("    %s *ret;",names.c_node_class_name);
	printfnl("    if(%s_is_empty(self))return NULL;",names.class_name_lower);
	printfnl("    ret = &self->data[self->head];");
	printfnl("    self->head = (self->head+1) %% self->size;");
	printfnl("    self->is_full = FALSE;");
	printfnl("    return ret;");
	printfnl("}");
	printfnl("int %s_get_len(%s *self)",names.class_name_lower,names.c_class_name);
	printfnl("{");
	printfnl("    if(%s_is_full(self))",names.class_name_lower);
	printfnl("        return self->size;");
	printfnl("    return (self->tail - self->head + self->size) %% self->size;");
	printfnl("}");
	printfnl("");

	printfnl("status_t %s_print(%s *self,struct log_buffer *buf)",names.class_name_lower,names.c_class_name);
	printfnl("{");
	printfnl("    int i;");
	printfnl("    ");
	printfnl("    for(i=0;i<self->size;i++)");
	printfnl("    {");
	printfnl("        log_buffer_log(buf,\"{\");");
	printfnl("        log_buffer_inc_level(buf,1);");
	printfnl("        %s_print(&self->data[i],buf);",names.node_class_name_lower);
	printfnl("        log_buffer_inc_level(buf,-1);");
	printfnl("        log_buffer_log(buf,\"}<-->\");");
	printfnl("    }");
	printfnl("    ");
	printfnl("    log_buffer_log(buf,\"head=%%d\",self->head);");
	printfnl("    log_buffer_log(buf,\"tail=%%d\",self->tail);");
	printfnl("    log_buffer_log(buf,\"size=%%d\",self->size);");
	printfnl("    log_buffer_log(buf,\"length=%%d\",%s_get_len(self));",names.class_name_lower);
	printfnl("    log_buffer_log(buf,\"is_full=%%d\",self->is_full);");
	printfnl("    return OK;");
	printfnl("}");

end
