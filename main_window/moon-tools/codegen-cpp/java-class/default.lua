--idl源文件，如果为空，则从文本框读取--
idl_source="";

--如果不为空就保存到文件--
save_path = "";

--java的package名字--
java_package_name="com.yueyuesoft.globals";

--代码生成的一些选项--
code_switch={
	bson = false,
    code_mark = false,
}
------------------------------
--如何转成c++的类名的方法--
function java_class_name(name)
	return name;
end

--如何把一个字符串转成文件名
function to_file_name(name,ns)
	return java_class_name(name);
end

--如何转成成员变量名字的方法--
function member_name(name)
	return "m_"..name;
end

--如何生成getter函数的名字
function getter_name(name,info)
    return "get"..to_big_camel_case(name);
end

--如何生成setter函数的名字
function setter_name(name,info)
    return "set"..to_big_camel_case(name);
end

--如何生成alloc函数的名字--
function alloc_name(name)
    return "alloc"..to_big_camel_case(name);
end
-------------------------------------
--定义基本数据类型的映射表--
-------------------------------------
basic_type_table={
	{"int","int","Int32"},
	{"int8_t","byte","Int8"},
	{"int16_t","short","Int16"},
	{"int32_t","int","Int32"},
	{"int64_t","long","Int64"},
    {"fsize_t","long","Int64"},
	{"int_ptr_t","long","Int64"},
	{"intptr_t","long","Int64"},
	{"char","byte","Int8"},
	{"short","short","Int16"},
	{"long","int","Int32"},
	{"uint_t","int","UInt32"},
	{"uint8_t","byte","UInt8"},
	{"uint16_t","short","UInt16"},
	{"uint32_t","int","UInt32"},
	{"uint64_t","long","UInt64"},
	{"uchar","byte","Uint8"},
	{"ushort","short","UInt16"},
	{"ulong","int","UInt32"},
	{"float","float","Float"},
	{"double","double","Double"},
	{"bool","boolean","Boolean"},
	{"void","void","Void"},
    {"status_t","boolean","Boolean"},
};

--通过类名找package的名字--
class_package_table={
	["RpcParamBase"]="com.cvtest.common.RpcParamBase",
}
