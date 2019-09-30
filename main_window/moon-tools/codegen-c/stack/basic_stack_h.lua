require("common")

function code_basic_h(names)
	printfnl("#ifndef __C_%s_H",string.upper(to_file_name(names.class_name)));
	printfnl("#define __C_%s_H",string.upper(to_file_name(names.class_name)));
	printfnl("");
	
	common_include_h();
	
	printfnl("");
	printfnl("%s{",names.c_class_name);
	printfnl("    double *data;");
	printfnl("    int top,size;");
	printfnl("};");
	printfnl("");
	printfnl("status_t %s_init_basic(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_init(%s *self,int init_size);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_destroy(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("bool_t %s_is_empty(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("bool_t %s_is_full(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("int %s_get_len(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_clear(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_auto_resize(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_push(%s *self,double node);",names.class_name_lower,names.c_class_name);
	printfnl("double %s_pop(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("double %s_get_elem(%s *self,int index);",names.class_name_lower,names.c_class_name);
	printfnl("int %s_bsearch_pos(%s *self,double node, int order, int *find_flag);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_insert_elem(%s *self,int index, double node);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_del_elem(%s *self,int index);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_insert_ordered(%s *self,double node, int order, int unique);",names.class_name_lower,names.c_class_name);
	printfnl("int %s_search_pos(%s *self,double node);",names.class_name_lower,names.c_class_name);
	printfnl("double %s_get_top(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_set_elem(%s *self,int index, double node);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_sort(%s *self,int order);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_copy(%s *self,%s *stk);",names.class_name_lower,names.c_class_name,names.c_class_name);
	printfnl("status_t %s_print(%s *self,struct log_buffer *buf);",names.class_name_lower,names.c_class_name);
	printfnl("");
	printfnl("#endif");
end
