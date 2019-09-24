--idl源文件，如果为空，则从文本框读取--
idl_source="";

--如果不为空就保存到文件--
save_path = "";

--命名空间，如果为空，表示没有namesapce
name_space="";
------------------------------
--如何把一个字符串转成文件名
function to_file_name(name)
	return to_lower_underline_case(name);
end

--如何转成c++的类名的方法--
function c_class_name(name)
	return name;
end

--特殊类型返回值的说明--
function more_ret_comments(ret)
    local name = ret.type.name;
    if name == "status_t" then    
        return "true表示成功，false表示失败"
    end
    
    if name == "bool" then    
        return "true表示是，false表示否"
    end
    
    return "";
end
-------------------------------------
--定义基本数据类型的映射表--
-------------------------------------
basic_type_table={
    {"int"},
    {"int8_t"},
    {"int16_t"},
    {"int32_t"},
    {"int64_t"},
    {"fsize_t"},
    {"int_ptr_t"},
    {"intptr_t"},
    {"char"},
    {"short"},
    {"long"},
    {"uint_t"},
    {"uint8_t"},
    {"uint16_t"},
    {"uint32_t"},
    {"uint64_t"},
    {"uchar"},
    {"ushort"},
    {"ulong"},
    {"float"},
    {"double"},
    {"bool"},
    {"void"},
    {"status_t"},
};

