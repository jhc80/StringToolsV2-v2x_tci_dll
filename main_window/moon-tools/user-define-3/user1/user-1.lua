for_each_line(mem_text_file,function(line)
local str = line:CStr();
printfnl([["%s="+stat.%s+",&nbsp;"+]],str,str);
end);
