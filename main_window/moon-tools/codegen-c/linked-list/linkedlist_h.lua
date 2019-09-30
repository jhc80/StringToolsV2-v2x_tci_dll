require("utils")

function code_h(names)
	printfnl("#ifndef __C_%s_H",string.upper(to_file_name(names.class_name)));
	printfnl("#define __C_%s_H",string.upper(to_file_name(names.class_name)));	
	printfnl("");
	
	common_include_h();
	
	printfnl("#include \"%s.h\"",to_file_name(names.node_class_name));
	printfnl("");
	printfnl("%s{",names.c_entry_class_name);
	printfnl("    %s *raw_ptr;",names.c_node_class_name);
	printfnl("    %s *next,*prev;",names.c_entry_class_name);
	printfnl("};");
	printfnl("");
	printfnl("status_t %s_init(%s *self);",names.entry_class_name,names.c_entry_class_name);
	printfnl("status_t %s_destroy(%s *self);",names.entry_class_name,names.c_entry_class_name);
	printfnl("status_t %s_set(%s *self, %s *node);",names.entry_class_name,names.c_entry_class_name,names.c_node_class_name);
	printfnl("%s* %s_get(%s *self);",names.c_node_class_name,names.entry_class_name,names.c_entry_class_name);
	printfnl("");
	printfnl("/******************************************************/");
	printfnl("%s{",names.c_class_name);
	printfnl("    %s *head,*tail;",names.c_entry_class_name);
	printfnl("    int len;");
	printfnl("};");
	printfnl("");
	printfnl("status_t %s_init(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_destroy(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_add_from_head(%s *self,%s *node);",names.class_name_lower,names.c_class_name,names.c_entry_class_name);
	printfnl("status_t %s_add_from_tail(%s *self,%s *node);",names.class_name_lower,names.c_class_name,names.c_entry_class_name);
	printfnl("bool_t %s_is_empty(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("%s* %s_search_from_head(%s *self,%s *node);",names.c_entry_class_name,names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("%s* %s_search_from_tail(%s *self,%s *node);",names.c_entry_class_name,names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("%s* %s_remove(%s *self,%s *node);",names.c_entry_class_name,names.class_name_lower,names.c_class_name,names.c_entry_class_name);
	printfnl("status_t %s_delete(%s *self,%s *node);",names.class_name_lower,names.c_class_name,names.c_entry_class_name);
	printfnl("status_t %s_insert_after(%s *self,%s *after, %s *node);",names.class_name_lower,names.c_class_name,names.c_entry_class_name,names.c_entry_class_name);
	printfnl("status_t %s_insert_before(%s *self,%s *before, %s *node);",names.class_name_lower,names.c_class_name,names.c_entry_class_name,names.c_entry_class_name);
	printfnl("%s* %s_get_head(%s *self);",names.c_entry_class_name,names.class_name_lower,names.c_class_name);
	printfnl("%s* %s_get_tail(%s *self);",names.c_entry_class_name,names.class_name_lower,names.c_class_name);
	printfnl("int %s_get_len(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_del_entry(%s *self,%s *entry);",names.class_name_lower,names.c_class_name,names.c_entry_class_name);
	printfnl("status_t %s_copy(%s *self,%s *_list);",names.class_name_lower,names.c_class_name,names.c_class_name);
	printfnl("status_t %s_print(%s *self,struct log_buffer *buf);",names.class_name_lower,names.c_class_name);
	printfnl("");
	printfnl("#endif");

end