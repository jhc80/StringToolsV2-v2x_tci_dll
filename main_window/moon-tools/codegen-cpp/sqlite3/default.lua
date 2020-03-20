--idl源文件，如果为空，则从文本框读取--
idl_source="";

--保存的路径， 如果为空则输出到文本框--
save_path="";

--代码生成的一些选项--
code_switch={
	code_mark = false,
}

--如何转换字符串到类的名字--
function c_class_name(str)
    return "C"..str;
end

--如何生成文件名--
function to_file_name(name)
    return to_lower_underline_case(name);
end

--如何生成Sqlite3中的表名--
function table_name(name)
	return name;
end

--如何生成getter函数的名字
function getter_name(name,info)
    return "Get"..to_big_camel_case(name);
end

--如何生成setter函数的名字
function setter_name(name,info)
    return "Set"..to_big_camel_case(name);
end

--如何生成得到数组长度的函数名--
function getter_array_len_name(name)
    return "Get"..to_big_camel_case(name).."Size";
end

---------------------------------------
--基本类型表
basic_type_table={
{"int","INTEGER"},
{"int8_t","INTEGER"},
{"int16_t","INTEGER"},
{"int32_t","INTEGER"},
{"int64_t","INTEGER"},
{"fsize_t","INTEGER"},
{"int_ptr_t","INTEGER"},
{"intptr_t","INTEGER"},
{"char","INTEGER"},
{"short","INTEGER"},
{"long","INTEGER"},
{"uint_t","INTEGER"},
{"uint8_t","INTEGER"},
{"uint16_t","INTEGER"},
{"uint32_t","INTEGER"},
{"uint64_t","INTEGER"},
{"uchar","INTEGER"},
{"ushort","INTEGER"},
{"ulong","INTEGER"},
{"float","REAL"},
{"double","REAL"},
{"bool","INTEGER"},
{"void","VOID"},
{"status_t","INTEGER"},
};


