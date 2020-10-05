require("common")
require("user")

if #replace_table <= 0 then
    return
end

local mem_text = App.LoadText();
App.ClearScreen();

if not replace_in_files then         
    local mf = new_memfile();
    mf:Puts(mem_text:FileBase());        
    batch_replace_in_files({mf},replace_table,case_sensitive,word_only);       
    print_whole_file(mf);
	mf:Destroy();
else
    for_each_line(mem_text:FileBase(),function(line)    
        local fn = line:CStr();
        local mf = new_memfile(fn);
        print(fn.."..");
        batch_replace_in_files({mf},replace_table,case_sensitive,word_only);               
        mf:WriteToFile(fn);
        printnl("ok.");
        mf:Destroy(); --release memory
    end);
end