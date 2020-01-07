--idl源文件，如果为空，则从文本框读取--
idl_source="";

--如果不为空就保存到文件--
save_path = "";

--命名空间，如果为空，表示没有namesapce
name_space="";

--代码生成的一些选项--
code_switch={
	code_mark = false,
}
------------------------------
--如何把一个字符串转成文件名
function to_file_name(name)
	return to_lower_underline_case(name);
end

--如何转成c++的类名的方法--
function c_class_name(name)
	return "C"..name;
end
-------------------------------------
--定义基本数据类型的映射表--
-------------------------------------
basic_type_table={
	{"int","LUA_INTEGER"},	
    {"int8_t","LUA_INTEGER"},
	{"int16_t","LUA_INTEGER"},
    {"int32_t","LUA_INTEGER"},
    {"int64_t","LUA_INTEGER"},	
	{"uint64_t","LUA_INTEGER"},	
	{"uint32_t","LUA_INTEGER"},
	{"uint16_t","LUA_INTEGER"},
	{"uint8_t","LUA_INTEGER"},
	{"size_t","LUA_INTEGER"},
	{"char","LUA_INTEGER"},
	{"byte","LUA_INTEGER"},
	{"short","LUA_INTEGER"},
	{"string","LUA_STRING"},
	{"float","LUA_NUMBER_FLOAT"},
	{"double","LUA_NUMBER"},
	{"void","LUA_VOID"},
	{"status_t","LUA_BOOLEAN"},
	{"bool","LUA_BOOLEAN"},
	{"BOOL","LUA_BOOLEAN"},
	{"fsize_t","LUA_INTEGER"},
	{"int_ptr_t","LUA_INTEGER"},
	{"HWND","LUA_INTEGER"},
	{"COLORREF","LUA_INTEGER"},
};

lua_type_table={
	{"LUA_INTEGER","int","lua_pushinteger","lua_tointeger","Int","lua_isinteger"},
	{"LUA_NUMBER","double","lua_pushnumber","lua_tonumber","Number","lua_isnumber"},
	{"LUA_NUMBER_FLOAT","float","lua_pushnumber","lua_tonumber","Float","lua_isnumber"},
	{"LUA_BOOLEAN","int","lua_pushboolean","lua_toboolean","Boolean","lua_isboolean"},
	{"LUA_STRING","const char*","lua_pushstring","lua_tostring","String","lua_isstring"},
};
