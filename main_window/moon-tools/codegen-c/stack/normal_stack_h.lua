require("common")

function code_normal_h(names)
	printfnl("#ifndef __C_%s_H",string.upper(to_file_name(names.class_name)));
	printfnl("#define __C_%s_H",string.upper(to_file_name(names.class_name)));
	printfnl("");
	printfnl("#include \"cruntime.h\"");
	printfnl("#include \"log_buffer.h\"");
	printfnl("#include \"%s.h\"",to_file_name(names.node_class_name));
	printfnl("");
	printfnl("%s{",names.c_class_name);
	printfnl("    int top,size;");
	printfnl("    %s **data;",names.c_node_class_name);
	printfnl("};");
	printfnl("");
	printfnl("status_t %s_init_basic(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_init(%s *self, int init_size);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_destroy(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("bool_t %s_is_empty(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("bool_t %s_is_full(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_auto_resize(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_push(%s *self, %s *node);",names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("status_t %s_push_ptr(%s *self,%s *node);",names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("%s * %s_pop_ptr(%s *self);",names.c_node_class_name,names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_pop(%s *self,%s *node);",names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("int %s_get_len(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("int %s_search_pos(%s *self,%s *node);",names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("%s* %s_search(%s *self,%s *node);",names.c_node_class_name,names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("%s* %s_get_top_ptr(%s *self);",names.c_node_class_name,names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_del_top(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_clear(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("%s * %s_get_elem(%s *self,int index);",names.c_node_class_name,names.class_name_lower,names.c_class_name);
	printfnl("int %s_bsearch_pos(%s *self,%s *node, int order, int *find_flag);",names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("%s * %s_bsearch_node(%s *self,%s *node,int order);",names.c_node_class_name,names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("int %s_bsearch(%s *self,%s *node,int order);",names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("status_t %s_insert_elem_ptr(%s *self,int i, %s *node);",names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("status_t %s_insert_elem(%s *self,int i, %s *node);",names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("%s * %s_remove_elem(%s *self,int index);",names.c_node_class_name,names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_del_elem(%s *self,int i);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_insert_ordered_ptr(%s *self,%s *node, int order,int unique);",names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("status_t %s_insert_ordered(%s *self,%s *node, int order,int unique);",names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("status_t %s_sort(%s *self,int order);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_copy(%s *self,%s *stk);",names.class_name_lower,names.c_class_name,names.c_class_name);
	printfnl("status_t %s_print(%s *self,struct log_buffer *buf);",names.class_name_lower,names.c_class_name);
	printfnl("");
	printfnl("#endif");

end