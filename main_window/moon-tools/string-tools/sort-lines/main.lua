require("common");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();
----------------------------------------------------
require("user");

local all = {};

for_each_line(mem_text_file,function(line)
    local str = line:CStr();
    line:FileBase():Trim();
    if empty_line_included then
        table.insert(all,str);
    elseif line:C(0) ~= 0 then
        table.insert(all,str);
    end
end);

table.sort(all,how_to_comp);

for _,v in ipairs(all) do
    printnl(v);
end
