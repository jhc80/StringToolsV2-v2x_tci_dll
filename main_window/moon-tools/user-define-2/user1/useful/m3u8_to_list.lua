--只要在m3u8文件的第一行写上url前缀即可生成下载列表
--不要带 .m3u8的文件名，注意一定要是第一行，不能有空行

App.ClearScreen();

printfnl("all_urls={");
local url_prefix = "";

local i = 0;
for_each_line(mem_text_file,function(line)
	local str = line:CStr();
	if i == 0 then
		url_prefix = str;
	end

	if string.find(str,"%.ts$") then
		printfnl("{\"wget --read-timeout=30 %s/%s -O %s\"},",url_prefix,str,str);
	end


	i = i + 1;	
end);
printfnl("};");