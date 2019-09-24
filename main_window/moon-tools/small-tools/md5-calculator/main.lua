require("common");

App.ClearScreen();
----------------------------------------------------
require("user");

local _,file = new_file(filename,"rb");

if not file then
    return
end

local md5 = FileManager.Md5Sum(file);

printnl(md5);

