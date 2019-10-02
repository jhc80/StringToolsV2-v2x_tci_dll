App.ClearScreen();

for_each_line(mem_text_file,function(line)
	local str = line:CStr();
    printfnl("self->base_file_base.%s = mem_virtual_%s;",str,str);
end);
