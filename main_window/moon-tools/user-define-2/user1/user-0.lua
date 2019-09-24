App.ClearScreen();

local i = 0;

for_each_line(mem_text_file,function(line)
	local str = line:CStr();
    printfnl("%d %s",i,str);
	i = i + 1;
end);
