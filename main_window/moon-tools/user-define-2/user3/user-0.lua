App.ClearScreen();

for_each_line(mem_text_file,function(line)
	local str = line:CStr();
    printfnl("${ETSI_NEW_NET_LAYER_PATH}/%s",str);
end);
