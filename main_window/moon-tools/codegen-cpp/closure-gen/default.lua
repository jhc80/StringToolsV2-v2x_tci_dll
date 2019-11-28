--生成C++ closure的代码--

--idl源文件，如果为空，则从文本框读取--
idl_source="";

-------------------------------------
--定义基本数据类型的映射表--
-------------------------------------
basic_type_table={
	{"int","Int"},
	{"int8_t","Int"},
	{"int16_t","Int"},
	{"int32_t","Int"},
	{"int64_t","Int64"},
	{"fsize_t","Int64"},
	{"int_ptr_t","Int64"},
	{"intptr_t","Int64"},
	{"char","Int"},
	{"short","Int"},
	{"long","Int"},
	{"uint_t","Int"},
	{"uint8_t","Int"},
	{"uint16_t","Int"},
	{"uint32_t","Int"},
	{"uint64_t","Int"},
	{"uchar","Int"},
	{"ushort","Int"},
	{"ulong","Int"},
	{"float","Double"},
	{"double","Double"},
	{"bool","Int"},
	{"status_t","Int"},
};

