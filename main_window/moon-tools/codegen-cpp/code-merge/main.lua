require("common");
require("user");
require("make_file_list")
require("code_splitor");

App.ClearScreen();

for _,folder in ipairs(from_folders) do
    AddFolder(folder);
end

local from_files = CurrentFilesList();

ClearFilesList();

for _,folder in ipairs(to_folders) do
    AddFolder(folder);
end

local to_files = CurrentFilesList();

-----------------------------------------
function find_from_file(to_name)
    local to_name_no_path = FileManager.SliceFileName(to_name,FN_FILENAME);
    for fn in pairs(from_files) do    
        local fn_no_path = FileManager.SliceFileName(fn,FN_FILENAME);
        if fn_no_path == to_name_no_path then
            return fn;
        end    
    end
end
-----------------------------------------
function find_block_by_name(blocks, name)
    for _,block in ipairs(blocks) do    
        if block.name and block.name == name then
            return block;
        end
    end
end
-----------------------------------------
function find_all_extra_block_by_name1(blocks,name1)
    local all={};
    
    for _,block in ipairs(blocks) do    
        if block.extra_name and block.extra_name.name1 == name1 then
            table.insert(all,block);
        end
    end
    
    if #all > 0 then
        return all;
    end
end
-----------------------------------------
function find_all_extra_block_by_extra_name(blocks,extra_name)
    local all={};
    
    for _,block in ipairs(blocks) do    
        if  block.extra_name and 
            block.extra_name.name2 == extra_name.name2 and
            block.extra_name.name1 == extra_name.name1            
        then
            table.insert(all,block);
        end
    end
    
    if #all > 0 then
        return all;
    end
end
-----------------------------------------
function insert_extra_code(to_blocks,from_blocks,insert_point,out)
    local out_file = out:FileBase();
    local all = find_all_extra_block_by_name1(from_blocks,insert_point);
    if not all then return end
    
    for _,extra_block in ipairs(all) do   
        local exist = find_all_extra_block_by_extra_name(to_blocks,extra_block.extra_name);
        if not exist then
            out_file:Puts(EOL);
            out_file:Puts(extra_block.code);
            out_file:Puts(EOL);
        end    
    end    
end
-----------------------------------------
function merge_two_file(to_fn, from_fn)
    local cs = CodeSplitor.new();
    local from_blocks = cs:SplitSourceFile(from_fn);
    local to_blocks = cs:SplitSourceFile(to_fn);

    local out, out_file = new_memfile();    
    
    for _,block in ipairs(to_blocks) do        
        if not block.name then
            if block.insert_point then
                insert_extra_code(to_blocks,from_blocks,block.insert_point,out);
            end                    
            out_file:Puts(block.code);                        
        else
            local from_block = find_block_by_name(from_blocks,block.name);
            if from_block then
                out_file:Puts(from_block.code);
            else
                out_file:Puts(block.code);
            end                    
        end
    end
    return out,out_file;    
end
-----------------------------------------
function auto_save_file(file, filename)
    local old_file,old_file_file = new_file(filename);
    if not old_file then return end

    if FileManager.IsFileSame(file,old_file_file) then
        return
    end
    
    if file:WriteToFile(filename) then
        return true;
    end
end
-----------------------------------------
for to_name in pairs(to_files) do        
    local from_file = find_from_file(to_name);
    if from_file then            
        local mf, mf_file = merge_two_file(to_name,from_file);        
        if auto_save_file(mf_file,to_name) then
            printfnl("merged file: %s ==> %s ",from_file,to_name);
        end        
        
        if delete_source_file then
            if FileManager.DeleteFile(from_file) then
                printfnl("delete file: %s",from_file);
            end
        end
    end
end

