--lua和c语言struct的二进制相互转化--

--idl源文件，如果为空，则从文本框读取--
idl_source="z:\\tmp\\1.idl";

--如何生成函数名--

function struct_to_lua_function_name(name)
	return to_lower_underline_case(name).."_to_lua";
end

-------------------------------------
--定义基本数据类型的映射表--
-------------------------------------
basic_type_table={
	{"int","Int32"},
	{"int8_t","Int8"},
	{"int16_t","Int16"},
	{"int32_t","Int32"},
	{"int64_t","Int64"},
	{"fsize_t","Int64"},
	{"int_ptr_t","Int64"},
	{"intptr_t","Int64"},
	{"char","Int8"},
	{"short","Int16"},
	{"long","Int32"},
	{"uint_t","UInt32"},
	{"uint8_t","UInt8"},
	{"uint16_t","UInt16"},
	{"uint32_t","UInt32"},
	{"uint64_t","UInt64"},
	{"uchar","UInt8"},
	{"ushort","UInt16"},
	{"ulong","UInt32"},
	{"float","Double"},
	{"double","Double"},
};
