--idl源文件，如果为空，则从文本框读取--
idl_source="";

--保存的路径， 如果为空则输出到文本框--
save_path="";

--如何转换字符串到类的名字--
function c_class_name(str)
    return "struct "..to_lower_underline_case(str);
end

--如何生成文件名--
function to_file_name(name)
    return to_lower_underline_case(name);
end

--h文件中的通用include
function common_include_h()
    printfnl("#include \"cruntime.h\"");
    printfnl("#include \"%s.h\"",to_file_name("log_buffer"));
end

--c文件中的通用include
function common_include_c()
    printnl("#include \"syslog.h\"");
    printnl("#include \"mem_tool.h\"");    
end

--代码生成的一些选项--
code_switch={
    weak_ref = false,
}
-----------------------------------------------------
--[[ idl的一些例子 --

[Queue of MyNode]
class MyQueue{}

[Queue of float,basic]
class MyFloatQueue{}

--]]