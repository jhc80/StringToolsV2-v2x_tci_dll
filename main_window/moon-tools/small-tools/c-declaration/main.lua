require("common")
require("ctoken")

local mem_text = App.LoadText();
App.ClearScreen();
----------------------------------------------------
require("user")

local blocks = split_into_blocks(mem_text:FileBase());

for _, b in ipairs(blocks) do
    if is_function_block(b) then
        local str = string.trim(b);
        print(remove_class_prefix(str));
        printnl(";");
    end
end

