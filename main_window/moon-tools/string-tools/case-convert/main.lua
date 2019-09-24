require("common");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();

require("user");

if method == 1 then
    local str = mem_text:CStr();
	print(string.upper(str));
elseif method == 2 then
    local str = mem_text:CStr();
	print(string.lower(str));
end