require("common");
require("user");

local mem_text = App.LoadText();

App.ClearScreen();

for_each_line(mem_text:FileBase(),function(line)
    local fn = line:CStr();
    if FileManager.IsFileExist(fn) then
        local path = FileManager.SliceFileName(fn,FN_PATH);
        local filename = FileManager.SliceFileName(fn,FN_FILENAME);
        if not path or path=="" then return end
        if not filename or filename == "" then return end

        local mem = new_mem();
        mem:Puts(filename);    
        batch_replace_in_files({mem},replace_table,case_sensitive,word_only);

        local new_name = FileManager.ToAbsPath(mem:CStr(),path);
        if new_name ~= fn then
            
            if FileManager.Rename(fn,new_name) then
                printfnl("%s => %s",fn,new_name);
            end
        end

        mem:Destroy();
    end
end);
