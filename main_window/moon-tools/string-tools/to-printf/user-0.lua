
--分隔符--
split_chars=" \t\r\n!@#$%^=&*()|+-\\*/{}[];.\":\',?/<>~";

--是否单字搜索--
word_only = false;

--是否大小写敏感--
case_sensive = true;

--输出结果的方式--
function output(format_str, param_str)
    local comma = (param_str ~= "") and "," or "";
    printfnl(
         [[printfnl("%s"%s%s);]],
         format_str,comma,param_str
    );
end

--替换表--
replace_table={
    {"struct normal_stack","%s","names.c_class_name"},
    {"struct test_node","%s","names.c_node_class_name"},
    {"NORMAL_STACK","%s","names.class_name"},
    {"normal_stack","%s","names.class_name_lower"},
    {"test_node","%s","names.node_class_name_lower"},
};
