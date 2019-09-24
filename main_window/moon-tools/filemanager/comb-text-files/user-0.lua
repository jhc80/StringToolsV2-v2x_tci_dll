--合并列表中的文件--

--合并后的文件--
text_file = "z:\\all.txt";

--文件开始的字符串--
function begin_file(filename)
    return string.format("/*** begin %s ***/",filename);
end

--文件结束的字符串--
function end_file(filename)
    return string.format("/*** end %s ***/",filename);
end


