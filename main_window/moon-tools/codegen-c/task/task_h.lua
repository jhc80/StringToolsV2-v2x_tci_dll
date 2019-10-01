require("common")

function code_h(names)

	printfnl("#ifndef __%s_H",names.file_name_upper);
	printfnl("#define __%s_H",names.file_name_upper);
	printfnl("");
	printfnl("#include \"c_taskmgr.h\"");
	printfnl("");
	printfnl("#define %s_ERROR_NONE   0",names.file_name_upper);
	printfnl("");
	printfnl("%s{",names.c_class_name);
	printfnl("    struct task base_task;");
	printfnl("    int step;");
	printfnl("};");
	printfnl("");
	printfnl("status_t %s_init_basic(%s *self);",names.class_name_lwr,names.c_class_name);
	printfnl("status_t %s_init(%s *self,struct taskmgr *mgr);",names.class_name_lwr,names.c_class_name);
	printfnl("status_t %s_destroy(%s *self);",names.class_name_lwr,names.c_class_name);
	printfnl("status_t %s_report_error(%s *self,int err);",names.class_name_lwr,names.c_class_name);
	printfnl("status_t %s_start(%s *self);",names.class_name_lwr,names.c_class_name);
	printfnl("status_t %s_stop(%s *self,int err);",names.class_name_lwr,names.c_class_name);
	printfnl("status_t %s_run(%s *self, uint32_t interval);",names.class_name_lwr,names.c_class_name);
	printfnl("");
	printfnl("#endif");
end