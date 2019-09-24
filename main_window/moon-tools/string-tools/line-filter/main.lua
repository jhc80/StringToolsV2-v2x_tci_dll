require("common");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();

require("user");

for_each_line(mem_text_file,
	function(line,line_file)
		if need_this_line(line, line_file) then
			printnl(line:CStr());
		end
	end
);
