require("common");
require("user");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();

local split_string_len = string.len(split_string);

function split_line(line,line_file,pos)    

    local mem,mem_file = new_mem();
    line_file:Seek(pos+split_string_len);
    line_file:ReadLeftStr(mem_file,true);
    mem_file:Trim();
    local part2 = mem:CStr();
    mem:Destroy();
    
    line_file:SetSize(pos);
    line_file:Trim();
    local part1 = line:CStr();
    
    if option == 1 then    
        printnl(part2);        
    elseif option == 2 then
        printnl(part1);
    elseif option == 3 then 
        print(part2);
        print(" ");
        print(split_string);
        print(" ");
        printnl(part1);
    end        
end

for_each_line(mem_text_file,function(line,line_file)  

    line_file:Seek(0);
    local pos = line_file:SearchStr(split_string,true,false);
    if pos >= 0 then
        split_line(line,line_file,pos);
    end
end);
