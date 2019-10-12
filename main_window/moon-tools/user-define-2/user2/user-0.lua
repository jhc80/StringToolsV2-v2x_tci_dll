App.ClearScreen();

for_each_line(mem_text_file,function(line)
	local str = line:CStr();
    printfnl("case %s: \n    return \"%s\";\n    break;",str,str);
end);
