require("common");

App.ClearScreen();
----------------------------------------------------
require("user");

local file = new_file(bin_file,"rb");
if not file then return end

local max_size = file:GetSize() - start_pos;
if max_size <= 0 then return end

if view_size <= 0 or view_size > max_size then
    view_size = max_size;
end

local blocks = math.ceil(view_size / 16);

file:Seek(start_pos);

local function to_char(int)
    if int >= 32 and int < 127 then
        return string.char(int);     
    end
    return string.char(127);
end

local off = 0;
local address = start_pos;

for i=1,blocks,1 do
    local str = "    ";
    print(string.format("%08X  ",address));
    address = address + 16;
    for j=1,16,1 do
        if off >= view_size then
            print("   ");
            str=str.." ";
        else
            local c = (file:GetInt8() & 0xff);
            str = str..to_char(c);
            print(string.format("%02x ", c));  
            if j == 8 then
                print(" ");
            end
        end
        off = off + 1;
    end 
    
    print(str);
    printnl("");
end