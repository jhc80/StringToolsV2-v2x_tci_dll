App.ClearScreen();

for_each_line(mem_text_file,function(line)
	local str = line:CStr();

	printfnl("aux_source_directory(${ETSI_DIR_PATH}/%s SRC_V2X_SERVICE)",str);
end);
