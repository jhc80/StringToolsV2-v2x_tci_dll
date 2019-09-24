require("common");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();

require("user");

function need_this_line(line,line_file)
	local res = line_file:EndWith(end_with,case_sensitive,skip_empty);

	if remove_the_line then
		res = (not res);
	end

	return res;
end

for_each_line(mem_text_file,
	function(line,line_file)
		if need_this_line(line, line_file) then
			printnl(line:CStr());
		end
	end
);
