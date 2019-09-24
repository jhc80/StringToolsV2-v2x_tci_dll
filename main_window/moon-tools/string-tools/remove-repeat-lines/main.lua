require("common");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();
----------------------------------------------------
require("user");

local all = {};

for_each_line(mem_text_file,function(line)       
    local ori_str = line:CStr();
    local str = ori_str;

    if trim_before_compare then
        line:FileBase():Trim();        
        str = line:CStr();
    end
    
    if not all[str] then
        printnl(ori_str);
        all[str] = 1;
    end    
end);
