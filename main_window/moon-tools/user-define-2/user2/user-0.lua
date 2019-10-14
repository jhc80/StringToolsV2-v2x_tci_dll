App.ClearScreen();

for_each_line(mem_text_file,function(line)
	local str = line:CStr();
    printfnl("if(event == %s)",str);
	printfnl("{");
	printfnl("}");
end);
