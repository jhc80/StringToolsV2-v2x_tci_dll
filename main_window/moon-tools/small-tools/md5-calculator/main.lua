require("common");
require("user");

if filename == "" then
    local mem_text = App.LoadText();
    if mem_text:GetSize() > 0 then
        local md5 = FileManager.Md5Sum(mem_text);
        App.ClearScreen();
        printnl(md5);
    end
    
    return
end

local _,file = new_file(filename,"rb");

if not file then
    return
end

local md5 = FileManager.Md5Sum(file);
App.ClearScreen();
printnl(md5);

