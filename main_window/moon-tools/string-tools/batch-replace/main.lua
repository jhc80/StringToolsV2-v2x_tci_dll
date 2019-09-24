require("common")
require("user")

if #replace_table <= 0 then
    return
end

local mem_text = App.LoadText();
App.ClearScreen();

if not replace_in_files then         
    local mf,mf_file = new_memfile();
    mf_file:Puts(mem_text:FileBase());        
    batch_replace_in_files({mf_file},replace_table,case_sensitive,word_only);       
    print_whole_file(mf_file);
else
    for_each_line(mem_text:FileBase(),function(line)    
        local fn = line:CStr();
        local mf,mf_file = new_memfile(fn);
        print(fn.."..");
        batch_replace_in_files({mf_file},replace_table,case_sensitive,word_only);               
        mf_file:WriteToFile(fn);
        printnl("ok.");
        mf:Destroy(); --release memory
    end);
end