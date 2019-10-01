require("common")

function code_cpp(names)
printfnl("#include \"%s.h\"",to_file_name(names.class_name));
printfnl("#include \"mem_tool.h\"");
printfnl("#include \"syslog.h\"");
printfnl("");
printfnl("static status_t %s_how_to_destroy(struct task *base)",names.class_name_lwr);
printfnl("{");
printfnl("    CONTAINER_OF(%s, self, base, base_task);",names.c_class_name);
printfnl("    return %s_destroy(self);",names.class_name_lwr);
printfnl("}");
printfnl("");
printfnl("static status_t %s_how_to_run(struct task *base, uint32_t interval)",names.class_name_lwr);
printfnl("{    ");
printfnl("    CONTAINER_OF(%s, self, base, base_task);",names.c_class_name);
printfnl("    return %s_run(self,interval);",names.class_name_lwr);
printfnl("}");
printfnl("/*********************************************/");
printfnl("status_t %s_init_basic(%s *self)",names.class_name_lwr,names.c_class_name);
printfnl("{");
printfnl("    task_init_basic(&self->base_task);");
printfnl("    self->step = 0;");
printfnl("    return OK;");
printfnl("}");
printfnl("status_t %s_init(%s *self,struct taskmgr *mgr)",names.class_name_lwr,names.c_class_name);
printfnl("{");
printfnl("    %s_init_basic(self);",names.class_name_lwr);
printfnl("    task_init(&self->base_task,mgr);");
printfnl("    self->base_task.run = %s_how_to_run;",names.class_name_lwr);
printfnl("    self->base_task.destroy = %s_how_to_destroy;",names.class_name_lwr);
printfnl("    return OK;");
printfnl("}");
printfnl("status_t %s_destroy(%s *self)",names.class_name_lwr,names.c_class_name);
printfnl("{");
printfnl("    %s_init_basic(self);",names.class_name_lwr);
printfnl("    return OK;");
printfnl("}");
printfnl("");
printfnl("status_t %s_report_error(%s *self,int err)",names.class_name_lwr,names.c_class_name);
printfnl("{");
printfnl("    const char *err_str=\"unknown error\";");
printfnl("    switch(err)");
printfnl("    {");
printfnl("        case %s_ERROR_NONE: ",names.file_name_upper);
printfnl("            err_str = \"none\"; ");
printfnl("        break;");
printfnl("    }");
printfnl("    XLOG(LOG_MODULE_USER,LOG_LEVEL_ERROR,");
printfnl("        \"task_test(%%d): exit with error \\\"%%s\\\"\",");
printfnl("        task_get_id(&self->base_task),err_str);");
printfnl("    return OK;");
printfnl("}");
printfnl("");
printfnl("status_t %s_start(%s *self)",names.class_name_lwr,names.c_class_name);
printfnl("{");
printfnl("    task_resume(&self->base_task);");
printfnl("    self->step = 1;");
printfnl("    return OK;");
printfnl("}");
printfnl("");
printfnl("status_t %s_stop(%s *self,int err)",names.class_name_lwr,names.c_class_name);
printfnl("{");
printfnl("    if(task_is_dead(&self->base_task))");
printfnl("        return ERROR;");
printfnl("    task_quit(&self->base_task);");
printfnl("    %s_report_error(self,err);",names.class_name_lwr);
printfnl("    return OK;");
printfnl("}");
printfnl("");
printfnl("status_t %s_run(%s *self, uint32_t interval)",names.class_name_lwr,names.c_class_name);
printfnl("{");
printfnl("    C_BEGIN_FSM();");
printfnl("    /**********************************/");
printfnl("    ");
printfnl("    C_BEGIN_STATE(1)");
printfnl("    {");
printfnl("        LOG(\"Hello\");");
printfnl("        C_GOTO_STATE(1000,2);");
printfnl("    }");
printfnl("    C_END_STATE(1);");
printfnl("    //////////////");
printfnl("");
printfnl("    C_BEGIN_STATE(2)");
printfnl("    {");
printfnl("        LOG(\"World\");");
printfnl("        C_GOTO_STATE(1000,1);");
printfnl("    }");
printfnl("    C_END_STATE(2);");
printfnl("    /**********************************/");
printfnl("    C_END_FSM();");
printfnl("    return OK;");
printfnl("}");
end