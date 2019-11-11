require("common");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();

require("user");

for_each_line(mem_text_file,
	function(line)
		if need_this_line(line) then
			printnl(line:CStr());
		end
	end
);
