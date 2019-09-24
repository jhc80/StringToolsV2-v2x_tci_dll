require("common");

local mem = App.LoadText();
App.ClearScreen();
----------------------------------------------------
require("user");

local mem_file = mem:FileBase();

local len = mem_file:GetSize();

for i=0,len-1,1 do
    local byte = mem_file:CharAt(i)&0xff;
    printnl(string.format(
        "%c --> %d(0x%x)",
        byte,byte,byte
    ));   
end


