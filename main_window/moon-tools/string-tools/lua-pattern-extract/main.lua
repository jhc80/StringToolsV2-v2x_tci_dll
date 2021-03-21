require("common")
require("user")

local mem_text = App.LoadText();
App.ClearScreen();
	
for_each_line(mem_text,function(line)
	how_to_extract(line:CStr());
end);

