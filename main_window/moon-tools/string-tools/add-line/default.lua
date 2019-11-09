--是否在文件中进行操作，如果是true，
--则表示操作编辑框中列表中的所有文件。
do_files = false;

--如何匹配特定的行--
function match_line(line)
	return line:StartWith("#",1,1);
end

--找到后如何增加内容--
function add_text(line)
	return "Hello\r\n";
end
