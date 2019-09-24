--asn1 lua 表文件--
--如果为空则从编辑框中读取--
lua_asn1_file="z:\\tmp\\old_all.lua";

--container生成的代码保存的路径--
save_path = "";

-- 打印的选项 --
switch={
    enum = true,
    bit_string = true,
    bit_string_typedef = true,
    string_typedef = true,
    choice = true,
    choice_enum = true,
    sequence = true,
    basic_type = true,
    container = true,
    container_files = true,
}

--生成文件的命名空间--
name_space = "asn1_plus";

--转换成文件名字,无后缀--
function to_file_name(name)
    return "asn1p_"..to_lower_underline_case(name);
end

--转成C++类的名字--
function c_class_name(name)
    return "C"..class_name(name);
end

--得到普通的object的名字--
function class_name(name)
    return convert_invalid_chars(name);
end

--得到普通对象的成员名字--
function class_member_name(name,parent)
    return convert_invalid_chars(name);
end

--把一个member转换成enum 的名字
function enum_name(name)
    return convert_invalid_chars(name);
end

--转换enum 类型的成员
function enum_member_name(name,parent)
    return string.format("%s_%s",
        parent.Identifier,
        convert_invalid_chars(name)
    );
end

--把一个member转换成bit_string的名字
function bit_string_name(name)
    return convert_invalid_chars(name);
end

--bit string enum 类型的名字--
function bit_string_enum_name(name)
    return convert_invalid_chars(name);
end

--转换bit_string 类型的成员
function bit_string_member_name(name,parent)
    return string.format("%s_%s",
        convert_invalid_chars(parent.Identifier),
        convert_invalid_chars(name)
    );
end

--转换基本数据类型的类型名字--
function basic_type_name(name)
    return convert_invalid_chars(name);
end

--choice enum 类型的名字--
function choice_enum_name(name)
    return convert_invalid_chars(name).."_PR";
end

--转换choice enum 类型的成员名字--
function choice_enum_member_name(name,parent)
    return string.format("%s_PR_%s",
        convert_invalid_chars(parent.Identifier),
        convert_invalid_chars(name)
    );
end

--覆盖默认的方法，基本类型转成原始的C类型--
function expr_type_to_c_type(expr_type)
    if expr_type == ASN_BASIC_BOOLEAN then
        return "bool";
    elseif expr_type == ASN_BASIC_INTEGER then
        return "long";
    elseif expr_type == ASN_BASIC_REAL then
        return "double";
    elseif expr_type == ASN_BASIC_BIT_STRING then
        return "BitString";
    elseif expr_type == ASN_BASIC_OCTET_STRING then
        return "OctetString";
    elseif expr_type == ASN_BASIC_UTCTime then
        return "UtcTime";
    elseif expr_type == ASN_STRING_IA5String then
        return "IA5String";
    elseif expr_type == ASN_STRING_UTF8String then
        return "Utf8String";
    end
end

--实现对名字冲突的修正，比如 long 这个
--名字就和c语言的关键字有冲突
function fix_asn1_member_name(m)
    if m.Identifier == "long" then
        m.Identifier = "Long";
    end
end