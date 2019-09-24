require("common");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

trim_at_same_time = false;
App.ClearScreen();
----------------------------------------------------
require("user");

for_each_line(mem_text_file,function(line)       
    local str = line:CStr();

    line:FileBase():Trim();
    local c = line:C(0);
    
    if c ~= 0 then
        if trim_at_same_time then
            printnl(line:CStr());
        else
            printnl(str);
        end
    end
end);
