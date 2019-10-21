require("common");
require("utils");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();

local result_table={};

function add(src,dst)
	if not result_table[src] then
		result_table[src] = dst;
	end
end

require("user");

for k,v in pairs(result_table) do
	printfnl("{\"%s\",\"%s\"},",k,v);
end

