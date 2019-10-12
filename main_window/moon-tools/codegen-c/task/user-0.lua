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
    return "c_"..to_lower_underline_case(name);
end

-----------------------------------------------------
--[[

class TaskTimer{
}
 
--]]
