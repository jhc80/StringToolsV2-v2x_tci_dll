require("common")

local mem_text = App.LoadText();
App.ClearScreen();
----------------------------------------------------
require("user");

local big_file = new_file(text_file,"wb+");
if not big_file then return end

for_each_line(mem_text,function(line)
    line:Trim();
    local str = line:CStr();
    local filename = FileManager.ToAbsPath(str);
    
    local file = new_file(filename,"rb");

    if file then
        printfnl("add %s",filename);
        big_file:Puts(begin_file(str));
        big_file:Puts(EOL);
        big_file:WriteFile(file);
        big_file:Puts(end_file(str));
        big_file:Puts(EOL);
        file:Destroy();
    end
end);

printfnl("save to %s",text_file);




