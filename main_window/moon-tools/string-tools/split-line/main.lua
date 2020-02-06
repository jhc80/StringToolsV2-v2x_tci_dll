require("common");
require("user");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();

local mem,mem_file = new_mem();

for_each_line(mem_text_file,function(line)  
    line:SetSplitChars(split_chars);
    line:Seek(0);
    while line:ReadWord(mem_file) do
        printnl(mem:CStr());
    end
end);
