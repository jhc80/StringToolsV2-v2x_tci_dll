App.ClearScreen();

local project_name = "simulator";

for_each_line(mem_text_file,function(line)
	local str = string.gsub(line:CStr(),"-","_")
    printfnl("set(%s_%s_DIR \"${%s_SOURCE_DIR}/%s\")",
		string.upper(project_name),
		to_upper_underline_case(str),
		string.upper(project_name),
		line:CStr()
	);
end);

for_each_line(mem_text_file,function(line)
	local str = string.gsub(line:CStr(),"-","_")
	printfnl("aux_source_directory(${%s_%s_DIR} %s_SOURCES)",
		string.upper(project_name),
		to_upper_underline_case(str),
		string.upper(project_name)
	);
end);

for_each_line(mem_text_file,function(line)
	local str = string.gsub(line:CStr(),"-","_")
	printfnl("${%s_%s_DIR}",
		string.upper(project_name),
		to_upper_underline_case(str)
	);
end);
