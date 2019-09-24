require("common");
require("user");

local mem_text = App.LoadText();
local mem_text_file = mem_text:FileBase();

App.ClearScreen();

local all_copy_ok={};
function auto_get_new_name(old_name)    
    if not all_copy_ok[old_name] then
        all_copy_ok[old_name] = 0;
        return old_name;
    end
    
    local n = all_copy_ok[old_name]+1;    
    all_copy_ok[old_name] = n;
    
    local fn_and_path = FileManager.SliceFileName(old_name,FN_PATH|FN_SINGLE);
    local ext = FileManager.SliceFileName(old_name,FN_EXT);
    
    local new_name = FileManager.ToAbsPath(fn_and_path.."-"..n);
    
    if ext and ext ~="" then
        new_name = new_name.."."..ext;
    end
 
    return new_name;
end

function remove_path_prefix_no_case(full_name,prefix)    
    full_name = string.lower(full_name);
    prefix = string.lower(prefix);
    if string.find(full_name,prefix,1,true) ~= 1 then
        return
    end
    
    local len = string.len(prefix);
    if len == 0 then return full_name end
    local rpath = string.sub(full_name,len+1);
    return rpath;
end


local line,line_file = new_mem();
mem_text_file:Seek(0);

local flags = 0;

if overwrite then
    flags = flags | MODE_OVERWRITE;
end

if check_same then
    flags = flags | MODE_CHECKSAME;
end

while mem_text_file:ReadLine(line_file) do
    local in_file = line:CStr();
    
    local out_file 
    
    if without_path then            
        out_file = FileManager.ToAbsPath(
            dest_folder.."/"..
            FileManager.SliceFileName(in_file,FN_FILENAME)
        );
    else    
        local rpath = remove_path_prefix_no_case(in_file,strip_prefix);            
        if rpath then
            out_file = FileManager.ToAbsPath(
                dest_folder.."/"..rpath                
            );
        end
    end
    
    if out_file then           
        
        if auto_rename then
            out_file = auto_get_new_name(out_file);
        end
        
        local ret = FileManager.CopySingleFile(
            in_file,out_file,
            0,-1,0,
            flags
        );
        
        if ret == OK then
            print("copy "..in_file.."..");        
        end
                
        if ret == ERROR then        
            printnl("fail");
            if stop_when_fail then
                break;
            end        
        end
        
        if ret == OK then
            printnl("ok.");
        end
    end
end;
