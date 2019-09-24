require("common")

local mem_text = App.LoadText();
App.ClearScreen();
----------------------------------------------------
require("user");

for_each_line(mem_text:FileBase(),function(line,line_file)
    line_file:Trim();
    if line_file:StrLen() > 0 then
    
        local code = line:CStr();  
        local ret;
        
        local r,errors = pcall(function()
            ret = load("return "..code)();
        end);
        
        print(code);
        
        if r then        
            print(" = "..ret);
        end        
        
        printnl("");
    end
end);