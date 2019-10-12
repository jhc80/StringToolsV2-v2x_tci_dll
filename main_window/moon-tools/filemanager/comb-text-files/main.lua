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
		local tag = begin_file(str);
		if tag then
			big_file:Puts(tag);
			big_file:Puts(EOL);
		end
		
        big_file:WriteFile(file);
		big_file:Puts(EOL);
        
		local tag = end_file(str);
		if tag then			
			big_file:Puts(tag);
			big_file:Puts(EOL);
		end
		
        file:Destroy();
    end
end);

printfnl("save to %s",text_file);




