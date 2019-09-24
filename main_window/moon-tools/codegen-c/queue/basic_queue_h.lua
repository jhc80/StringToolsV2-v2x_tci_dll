require("common")

function code_basic_h(names)
	printfnl("#ifndef __C_%s_H",string.upper(to_file_name(names.class_name)));
	printfnl("#define __C_%s_H",string.upper(to_file_name(names.class_name)));
	printfnl("");
	printfnl("#include \"cruntime.h\"");
	printfnl("#include \"log_buffer.h\"");
	printfnl("");
	printfnl("%s{",names.c_class_name);
	printfnl("    double *data;");
	printfnl("    int head, tail;");
	printfnl("    int size;");
	printfnl("    bool_t is_full;");
	printfnl("};");
	printfnl("");
	printfnl("status_t %s_init_basic(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_init(%s *self,int size);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_destroy(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("bool_t %s_is_empty(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("bool_t %s_is_full(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_clear(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_enqueue(%s *self,double node);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_dequeue(%s *self,double *node);",names.class_name_lower,names.c_class_name);
	printfnl("int %s_get_len(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_print(%s *self,struct log_buffer *buf);",names.class_name_lower,names.c_class_name);
	
	printfnl("");
	printfnl("#endif");

end
