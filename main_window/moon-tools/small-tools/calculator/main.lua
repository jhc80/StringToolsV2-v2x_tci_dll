require("common")

local mem_text = App.LoadText();
App.ClearScreen();
----------------------------------------------------
require("user");

for_each_line(mem_text:FileBase(),function(line)
    line:Trim();
    if line:StrLen() > 0 then
    
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