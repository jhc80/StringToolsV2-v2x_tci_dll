require("common");

remove_tail = true;
remove_head = true;

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();

require("user");

function remove_space_at_tail(file,new_file)
    file:Seek(0);
    new_file:SetSize(0);

    local pos = -1;
    local len = file:StrLen();

    for i=len-1,0,-1 do
        local ch = file:CharAt(i);
        if not is_white_char(ch) then
            pos = i;
            break;
        end
    end
    
    if pos < 0 then return end
    new_file:WriteFile(file,0,pos+1);
end

function remove_space_at_head(file,new_file)
    file:Seek(0);
    new_file:SetSize(0);

    local pos = -1;
    local len = file:StrLen();

    for i=0,len-1,1 do
        local ch = file:CharAt(i);
        if is_white_char(ch) then
            pos = i;
            break;
        end
    end
    
    if pos < 0 then return end
    new_file:WriteFile(file,0,pos);
end

----------------------------------------------------
local mem,mem_file = new_mem();

for_each_line(mem_text_file,function(line)   
    if remove_tail and remove_head then
        line:FileBase():Trim();
        printnl(line:CStr());
        return
    end

    if remove_tail then
        remove_space_at_tail(line:FileBase(),mem_file);
        printnl(mem:CStr());
    end

    if remove_head then
        remove_space_at_head(line:FileBase(),mem_file);
        printnl(mem:CStr());
    end
    
end);
