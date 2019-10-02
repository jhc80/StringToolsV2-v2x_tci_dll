App.ClearScreen();

for_each_line(mem_text_file,function(line)
	local str = line:CStr();
    printfnl("{\"%s\",\"%s\"},",str,to_lower_underline_case(str));
end);
