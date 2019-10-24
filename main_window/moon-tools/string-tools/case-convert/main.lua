require("common");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();

require("user");

for_each_line(mem_text,function(line)
	local str = line:CStr();
	if method == 1 then
		printnl(string.upper(str));
	elseif method == 2 then
		printnl(string.lower(str));
	elseif method == 3 then
		printnl(to_lower_underline_case(str));
	elseif method == 4 then
		printnl(to_upper_underline_case(str));
	elseif method == 5 then
		printnl(to_underline_case(str));
	elseif method == 6 then
		printnl(to_big_camel_case(str));
	elseif method == 7 then
		printnl(to_small_camel_case(str));				
	end
end);