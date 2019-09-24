require("utils")

function code_h(names)
	printfnl("#ifndef __C_%s_H",string.upper(to_file_name(names.class_name)));
	printfnl("#define __C_%s_H",string.upper(to_file_name(names.class_name)));
	printfnl("");
	printfnl("#include \"cruntime.h\"");
	printfnl("#include \"log_buffer.h\"");
	printfnl("#include \"cclosure.h\"");
	printfnl("#include \"%s.h\"",to_file_name(names.node_class_name));
	printfnl("");
	printfnl("%s{",names.c_entry_class_name);
	printfnl("    %s *raw_ptr;",names.c_node_class_name);
	printfnl("    %s *next;",names.c_entry_class_name);
	printfnl("};");
	printfnl("");
	printfnl("status_t %s_init(%s *self);",names.entry_class_name,names.c_entry_class_name);
	printfnl("status_t %s_destroy(%s *self);",names.entry_class_name,names.c_entry_class_name);
	printfnl("status_t %s_set(%s *self, %s *node);",names.entry_class_name,names.c_entry_class_name,names.c_node_class_name);
	printfnl("%s* %s_get(%s *self);",names.c_node_class_name,names.entry_class_name,names.c_entry_class_name);
	printfnl("/*****************************************************/");
	printfnl("%s{",names.c_class_name);
	printfnl("    %s **data;",names.c_entry_class_name);
	printfnl("    int capacity;");
	printfnl("    int size;");
	printfnl("};");
	printfnl("");
	printfnl("status_t %s_init_basic(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_init(%s *self,int capacity);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_destroy(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_put_ptr(%s *self,%s *ptr);",names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("status_t %s_put(%s *self,%s *hashentry);",names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("%s* %s_get(%s *self,%s *key);",names.c_node_class_name,names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("status_t %s_enum_all(%s *self,struct closure *callback);",names.class_name_lower,names.c_class_name);
	printfnl("%s* %s_remove(%s *self,%s *key);",names.c_entry_class_name,names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("status_t %s_del(%s *self,%s *key);",names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("int %s_get_size(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("bool_t %s_is_empty(%s *self);",names.class_name_lower,names.c_class_name);
	printfnl("status_t %s_del_entry(%s *self,%s *entry);",names.class_name_lower,names.c_class_name,names.c_entry_class_name);
	printfnl("status_t %s_print(%s *self,struct log_buffer *buf);",names.class_name_lower,names.c_class_name);
	printfnl("int %s_hash_code(%s *self,%s *node);",names.class_name_lower,names.c_class_name,names.c_node_class_name);
	printfnl("");
	printfnl("#endif");
end