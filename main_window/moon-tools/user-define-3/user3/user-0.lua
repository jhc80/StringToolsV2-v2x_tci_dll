--分隔符--
split_chars=" \t\r\n!@#$%^=&*()|+-\\*/{}[];.\":\',?/<>~";

--选项 1:不包括符合，2:包括符合, 3:包括符合和空字符
option = 3;

mem_text:SetSplitChars(split_chars);
for_each(mem_text, option, function(mem)
	local str = mem:CStr();
	printfnl("%s",str);
end);

