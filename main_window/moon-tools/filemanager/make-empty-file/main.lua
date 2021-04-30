require("common");

K = 1024;
M = 1024*1024;
G = 1024*1024*1024;

require("user");

local BLOCK_SIZE=4*1024*1024;

App.ClearScreen();

local file = new_file(out_file,"w+");
if not file then return end

local block_size = BLOCK_SIZE;
if file_size < BLOCK_SIZE then
    block_size = file_size;
end

local block = new_mem(block_size);
block:FillBlock(block_size,file_char);

local size = 0;
local left_size = file_size
while left_size > 0 do
    local ws = left_size;
    if ws > block_size then
        ws = block_size;
    end
    
    file:Write(block,ws);
    left_size = left_size - ws;
    printfnl("ws = %d",file_size-left_size);
end

printfnl("ALL DONE");






