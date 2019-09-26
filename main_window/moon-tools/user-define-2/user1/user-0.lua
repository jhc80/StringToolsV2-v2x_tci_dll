App.ClearScreen();

for_each_line(mem_text_file,function(line)
	local str = line:CStr();
    printfnl("{\"%s\",\"X%s\"},",str,str);
end);
