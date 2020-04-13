--查找字符串的模板
all_patterns = {
	[["http.-"]]
};

--是否在文件中进行替换，如果是true，则替换在
--编辑框中列表的所有文件。
replace_in_files = true;

--替换函数,返回替换后的字符串--
function how_to_replace(pattern,str)


	local tail = nil;
	for v in string.gmatch(str,[["http.-#(.-)"]]) do
		tail = "\"#"..v.."\"";
	end

	if tail then 
		return tail;
	else	
		return str;	
	end


end
