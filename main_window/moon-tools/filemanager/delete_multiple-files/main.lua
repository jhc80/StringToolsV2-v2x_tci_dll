require("common");
require("user");

local mem_text = App.LoadText();
local mem_text_file = mem_text:FileBase();

App.ClearScreen();

local line = new_mem();
mem_text_file:Seek(0);

while mem_text_file:ReadLine(line) do
    local filename = FileManager.ToAbsPath(path_prefix.."/"..line:CStr());
    if FileManager.DeleteFile(filename) then
        printnl("\""..filename.."\" deleted");
    end    
end;
