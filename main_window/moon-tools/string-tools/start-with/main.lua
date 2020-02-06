require("common");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();

require("user");

function need_this_line(line)
	local res = line:StartWith(start_with,case_sensitive,skip_empty);

	if remove_the_line then
		res = (not res);
	end

	return res;
end

for_each_line(mem_text_file,
	function(line)
		if need_this_line(line) then
			printnl(line:CStr());
		end
	end
);
