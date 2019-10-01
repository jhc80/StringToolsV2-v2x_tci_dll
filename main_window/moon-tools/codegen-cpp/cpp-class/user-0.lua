--idl源文件，如果为空，则从文本框读取--
idl_source="";

--如果不为空就保存到文件--
save_path = "z:\\tmp\\gen";

--代码生成的一些选项--
code_switch={
    copy_comp_print = true,    
    weak_ref = false,
    task_container = false,
	bson = false,
	cjson = false,
	lib_config = false,
    c_struct = false,
    raw_asn1 = false,
    code_mark = false,
}

--命名空间，如果为空，表示没有namesapce
name_space="";
------------------------------
--如何把一个字符串转成文件名
function to_file_name(name)
	return "asn1p_"..to_lower_underline_case(name);
end

--如何转成c++的类名的方法--
function c_class_name(name)
	return "C"..name;
end

--如何转成成员变量名字的方法--
function member_name(name)
	return "m_"..name;
end

--如何转成成员变量长度的名字--
function member_name_len(name)
	return member_name(name).."Size";
end

--如何生成getter函数的名字
function getter_name(name,info)
    return "Get"..to_big_camel_case(name);
end

--如何生成setter函数的名字
function setter_name(name,info)
    return "Set"..to_big_camel_case(name);
end

--如何生成alloc函数的名字--
function alloc_name(name)
    return "Alloc"..to_big_camel_case(name);
end

--如何生成得到数组长度的函数名--
function getter_array_len_name(name)
    return "Get"..to_big_camel_case(name).."Size";
end

--如何生成得到数组每一个元素的函数名--
function getter_array_elem_name(name)
    return "Get"..to_big_camel_case(name).."Elem";
end

--如何生成设置数组每一个元素的函数名--
function setter_array_elem_name(name)
    return "Set"..to_big_camel_case(name).."Elem";
end

--如何生成optional成员的Create方法名--
function create_optional_name(name)
	return "Create"..to_big_camel_case(name);
end

--如何生成对应c struct的结构名--
function c_struct_name(name)
    return "struct "..to_lower_underline_case(name);
end

--如何转换c结构体的成员名字--
function c_member_name(name)
	return name;
end

--生成save c struct的函数名--
function save_struct_name(info)
	return "SaveStruct";
end

--生成load c struct的函数名--
function load_struct_name(info)
	return "LoadStruct";
end

--生成save raw asn1 的函数名--
function save_asn1_name(info)
	return "SaveRawAsn1";
end

--生成load c struct的函数名--
function load_asn1_name(info)
	return "LoadRawAsn1";
end
-------------------------------------
--定义了通用的头文件
-------------------------------------
function add_include(name,angle_bracket)    
    if angle_bracket then
        printfnl("#include <%s.h>",name);
    else
        printfnl("#include \"%s.h\"",name);
    end    
end

function common_includes_h()
    add_include("mem");
    add_include("memfile");
end

function common_includes_cpp()
    add_include("syslog");
    add_include("mem_tool");
end
-------------------------------------
--定义基本数据类型的映射表--
-------------------------------------
basic_type_table={
	{"int","%d","Int32","int","valueint","Number","CONFIG_TYPE_INT"},
	{"int8_t","%d","Int8","int","valueint","Number","CONFIG_TYPE_INT"},
	{"int16_t","%d","Int16","int","valueint","Number","CONFIG_TYPE_INT"},
	{"int32_t","%d","Int32","int","valueint","Number","CONFIG_TYPE_INT"},
	{"int64_t","%lld","Int64","int64","valueint","Number","CONFIG_TYPE_INT64"},
    {"fsize_t","%lld","Int64","int64","valueint","Number","CONFIG_TYPE_INT64"},
	{"int_ptr_t","%d","Int32","int","valueint","Number","CONFIG_TYPE_INT"},
	{"intptr_t","%d","Int32","int","valueint","Number","CONFIG_TYPE_INT"},
	{"char","%c","Int8","int","valueint","Number","CONFIG_TYPE_INT"},
	{"short","%d","Int16","int","valueint","Number","CONFIG_TYPE_INT"},
	{"long","%d","Int32","int","valueint","Number","CONFIG_TYPE_INT"},
	{"uint_t","%d","UInt32","int","valueint","Number","CONFIG_TYPE_INT"},
	{"uint8_t","%d","UInt8","int","valueint","Number","CONFIG_TYPE_INT"},
	{"uint16_t","%d","UInt16","int","valueint","Number","CONFIG_TYPE_INT"},
	{"uint32_t","%u","UInt32","int","valueint","Number","CONFIG_TYPE_INT"},
	{"uint64_t","%lld","UInt64","int","valueint","Number","CONFIG_TYPE_INT64"},
	{"uchar","%d","UInt8","int","valueint","Number","CONFIG_TYPE_INT"},
	{"ushort","%d","UInt16","int","valueint","Number","CONFIG_TYPE_INT"},
	{"ulong","%ld","UInt32","int","valueint","Number","CONFIG_TYPE_INT"},
	{"float","%f","Double","float","valuedouble","Number","CONFIG_TYPE_FLOAT"},
	{"double","%f","Double","float","valuedouble","Number","CONFIG_TYPE_FLOAT"},
	{"bool","%d","Boolean","bool","valueint!=0","Bool","CONFIG_TYPE_BOOL"},
	{"void","%x","Int32","int","valueint","Number","CONFIG_TYPE_INT"},
    {"status_t","%d","Int32","int","valueint","Number","CONFIG_TYPE_INT"},
};

