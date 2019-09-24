require("common")

local mem_text = App.LoadText();
App.ClearScreen();
----------------------------------------------------
require("user");

function convert(str,dec)
    if radix == 16 then
        printnl(string.format("%s -> 0x%x",str,dec));    
    elseif radix == 10 then
        printnl(string.format("%s -> %d",str,dec)); 
    elseif radix == 8 then
        printnl(string.format("%s -> 0%o",str,dec));
    elseif radix == 2 then
        printnl(string.format("%s -> 0b%s",str,binary_to_string(dec)));     
    end
end

function string_to_binary(str)
    local len = string.len(str);    
    local v = 0;    
    for i=len,3,-1 do
        if string.byte(str,i) == 49 then
            v = v | (1<<(len-i));
        elseif string.byte(str,i) ~= 48 then
            return
        end
    end    
    return v;
end

function binary_to_string(bin)    
    local str="";
    local flag = false;
    for i=63,0,-1 do    
        if (bin & (1<<i)) ~= 0 then
            flag = true;
            str = str.."1";
        else
            if flag then
                str = str.."0";
            end
        end    
    end    
    return str;
end

for_each_line(mem_text:FileBase(),function(line)
    local str = line:CStr();
    
    local dec;
    
    if  string.byte(str,1)==48 and (
        string.byte(str,2)==66 or 
        string.byte(str,2)==98 )
    then
        dec = string_to_binary(str);
    else
        dec = tonumber(str);
    end
      
    if dec then
        convert(str,dec);
    end
end);