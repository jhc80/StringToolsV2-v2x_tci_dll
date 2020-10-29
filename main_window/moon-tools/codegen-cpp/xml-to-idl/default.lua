--如果为true则分析文件列表--
parse_files = true;

--是否自动猜测成员变量类型--
guess_type = true;

--如何生成类的名字--
function class_name(name)
    local str = valid_var_name(name);
	return to_big_camel_case(str);
end

--如何生成成员的名字--
function member_name(name)
    return valid_var_name(name);
end

--如何生成数组类的名字--
function array_class_name(name)
    return class_name(name).."Array";
end

--如何生成数组成员的名字--
function array_member_name(name)
    return member_name(name).."Array";
end

--如何生成value的成员名字--
function value_member_name()
	return "xml_value";
end

--添加自定义的代码开关--
function add_code_switches()
	printnl("[CodeSwitch code_mark=true,weak_ref=true,xml2=true]");
end



