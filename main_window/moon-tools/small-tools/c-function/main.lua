require("common")
require("ctoken")

local mem_text = App.LoadText();
App.ClearScreen();
----------------------------------------------------
require("user")

local blocks = split_into_blocks(mem_text:FileBase());

local need = false;
for _, b in ipairs(blocks) do
    if is_function_block(b) then
        local name = string.trim(b);
		if need_this_function(name) then
			need = true;
			print(b);
		end        		
	elseif need then
		need = false;			
		print(b);
    end
end

