require("common");
require("user");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();

local mem,mem_file = new_mem();

for_each_line(mem_text_file,function(line,line_file)  
    line_file:SetSplitChars(split_chars);
    line_file:Seek(0);
    while line_file:ReadWord(mem_file) do
        printnl(mem:CStr());
    end
end);
