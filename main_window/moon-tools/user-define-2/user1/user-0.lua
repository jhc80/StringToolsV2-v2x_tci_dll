App.ClearScreen();

for_each_line(mem_text_file,function(line)
	local str = line:CStr();
    printfnl("{\"%s\",\"C_TASK_LINKRPC_%s\"},",str,str);
end);
