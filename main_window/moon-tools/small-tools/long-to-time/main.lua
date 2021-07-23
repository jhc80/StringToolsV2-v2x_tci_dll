require("common")

local mem_text = App.LoadText();
App.ClearScreen();
----------------------------------------------------
require("user");

local tm = CommonTime.new();

for_each_line(mem_text:FileBase(),function(line)
    local str = line:CStr();
    local sec = tonumber(str)
    if not sec then return end
    tm:Set(sec*1000);
    printfnl("%s -> %s",str,tm:ToString());
end);

