App.ClearScreen();

for_each_line(mem_text_file,function(line)
	local str = line:CStr();
    printfnl("ret.%s = %s();",to_lower_underline_case(str),str);
end);
