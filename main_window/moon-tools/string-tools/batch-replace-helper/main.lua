require("common");
require("utils");

CHAR_MINUS = 45;
CHAR_SPACE = 32;

function to_upper_minus_case(str)
    return string.upper(to_lower_minus_case(str));
end

function to_lower_minus_case(str)
    local t = to_lower_underline_case(str);
    return string.gsub(t,"_","-");
end

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

