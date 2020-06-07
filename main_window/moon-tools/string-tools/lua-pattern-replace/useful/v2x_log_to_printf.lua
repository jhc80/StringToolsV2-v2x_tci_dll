--把V2X_LOG 替换为printf函数的替换
--在debug的时候很有用

all_patterns = {
	[[V2X_%u+%(".-"]],
	[[D_ERROR%(".-"]]
};

--是否在文件中进行替换，如果是true，则替换在
--编辑框中列表的所有文件。
replace_in_files = false;

--替换函数,返回替换后的字符串--
function how_to_replace(pattern,str)
	local s,e = string.find(str,"\".-\"");
	if not s then return str end
	local quote = string.sub(str,s+1,e-1);
	return "printf(\""..quote.."\\n\"";
end
