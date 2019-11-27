--idl源文件，如果为空，则从文本框读取--
idl_source="";

--如果不为空就保存到文件--
save_path = "";

--代码生成的一些选项--
code_switch={
    copy_comp_print = true,
    code_mark = false,
	weak_ref = false,
	lib_config = false,
}
------------------------
--如何转成c的类名的方法--
function class_name(name)
    return to_lower_underline_case(name);
end

--如何转换成文件名--
function to_file_name(name)
	return "c_"..class_name(name);
end

--如何转成c的类型名字
function c_class_name(name)
	return "struct "..class_name(name);
end

--本类的函数如何转换成函数的名字--
function this_function_name(name)
    return string.lower(g_idl_class.name).."_"
        ..to_lower_underline_case(name);
end

--如何转换成函数名--
function function_name(var_type,name)
    return string.lower(var_type.name).."_"
        ..to_lower_underline_case(name);
end

--如何转成成员变量名字的方法--
function member_name(name)
	return to_lower_underline_case(name);
end

--如何转成成员变量长度的名字--
function member_name_len(name)
	return member_name(name).."_size";
end

--如何生成getter函数的名字
function getter_name(name)
    return this_function_name("get_"..
        to_lower_underline_case(name));
end

--如何生成setter函数的名字
function setter_name(name)
    return this_function_name("set_"..
        to_lower_underline_case(name));
end

--如何生成alloc函数的名字--
function alloc_name(name)
    return this_function_name("alloc_"..
        to_lower_underline_case(name));
end

--如何生成得到数组长度的函数名--
function getter_array_len_name(name)
    return this_function_name("get_"..
        to_lower_underline_case(name).."_size");
end

--如何生成得到数组每一个元素的函数名--
function getter_array_elem_name(name)
    return this_function_name("get_"..
        to_lower_underline_case(name).."_elem");
end

--如何生成设置数组每一个元素的函数名--
function setter_array_elem_name(name)
    return this_function_name("set_"..
        to_lower_underline_case(name).."_elem");
end

--如何生成optional成员的Create方法名--
function create_optional_name(name)
	return this_function_name(
	    "create_"..to_lower_underline_case(name));
end

function common_include_h()
    printfnl("#include \"cruntime.h\"");
    printfnl("#include \"%s.h\"",to_file_name("log_buffer"));
end

function common_include_c()
    printnl("#include \"syslog.h\"");
    printnl("#include \"mem_tool.h\"");    
end
-------------------------------------
--定义基本数据类型的映射表--
basic_type_table={
	{"int","%d","Int32","int","CONFIG_TYPE_INT"},
	{"int8_t","%d","Int32","int","CONFIG_TYPE_INT"},
	{"int16_t","%d","Int32","int","CONFIG_TYPE_INT"},
	{"int32_t","%d","Int32","int","CONFIG_TYPE_INT"},
	{"status_t","%d","Int32","int","CONFIG_TYPE_INT"},
	{"int64_t","%lld","Int64","int64","CONFIG_TYPE_INT64"},
    {"fsize_t","%lld","Int64","int64","CONFIG_TYPE_INT64"},
	{"int_ptr_t","%d","Int32","int","CONFIG_TYPE_INT"},
	{"intptr_t","%d","Int32","int","CONFIG_TYPE_INT"},
	{"char","%d","Int32","int","CONFIG_TYPE_INT"},
	{"short","%d","Int32","int","CONFIG_TYPE_INT"},
	{"long","%d","Int32","int","CONFIG_TYPE_INT"},
	{"uint_t","%d","Int32","int","CONFIG_TYPE_INT"},
	{"uint8_t","%d","Int32","int","CONFIG_TYPE_INT"},
	{"uint16_t","%d","Int32","int","CONFIG_TYPE_INT"},
	{"uint32_t","%d","Int32","int","CONFIG_TYPE_INT"},
	{"uint64_t","%lld","Int64","int64","CONFIG_TYPE_INT64"},
	{"uchar","%d","Int32","int","CONFIG_TYPE_INT"},
	{"ushort","%d","Int32","int","CONFIG_TYPE_INT"},
	{"ulong","%ld","Int32","int","CONFIG_TYPE_INT"},
	{"float","%f","Double","float","CONFIG_TYPE_FLOAT"},
	{"double","%f","Double","float","CONFIG_TYPE_FLOAT"},
	{"bool","%d","Boolean","bool","CONFIG_TYPE_BOOL"},
	{"void","%x","Int32","int","CONFIG_TYPE_INT"},
	{"bool_t","%d","Int32","bool","CONFIG_TYPE_BOOL"},
};


