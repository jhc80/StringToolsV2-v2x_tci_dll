--lua和c语言struct的二进制相互转化--

--idl源文件，如果为空，则从文本框读取--
idl_source="";

--如果不为空就保存到文件--
save_path = "z:\\tmp\\gen";

--如何把一个字符串转成文件名
function to_file_name(name,ns)
	return "c_"..to_lower_underline_case(name);
end

--如何生成函数名--
function struct_to_lua_function_name(name)
	return name.."_to_lua";
end

function lua_to_struct_function_name(name)
	return "lua_to_"..name;
end

function lua_size_function_name(name)
	return name.."_size";
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
