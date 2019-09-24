require("common");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();

require("user");

function match_n(n)
    for _,v in ipairs(which_words) do
        if v == n then
            return true;
        end
    end
end

function empty_string_table()
    local all={};
    local len = #which_words;
    for i=1,len,1 do
        all[i] = "";
    end
    return all;
end

local function do_from_head(line,line_file)
    line_file:SetSplitChars(split_chars);
    line_file:Seek(0);
    
    local mem,mem_file = new_mem();    
    local all = empty_string_table();
    local k = 1; local c = 1;
    while line_file:ReadString(mem_file) do
        if match_n(c) then
            all[k] = mem:CStr();
            k = k + 1;
        end
        c = c + 1;
    end    
    how_to_combine(all,line:CStr());
end

local function do_from_tail(line,line_file)
    line_file:SetSplitChars(split_chars);
    line_file:SeekEnd();
    
    local mem,mem_file = new_mem();    
    local all = empty_string_table();
    local k = 1; local c = 1;
    while line_file:ReadString_Reverse(mem_file) do
        if match_n(c) then
            all[k] = mem:CStr();
            k = k + 1;
        end
        c = c + 1;
    end    
    how_to_combine(all,line:CStr());
end

local function delete_from_head(line,line_file)
    line_file:SetSplitChars(split_chars);
    line_file:Seek(0);
    local c = 1;

    local mem = new_mem();
    while line_file:ReadWordWithEmptyChar(mem) do
        local ch = mem:CharAt(0);
        if line_file:IsSpChar(ch) or FileBase.IsEmptyChar(ch) then
            print(mem:CStr());
        else
            
            if not match_n(c) then
                print(mem:CStr());
            end
            c = c + 1;
        end
    end    
end

local function delete_from_tail(line,line_file)
    line_file:SetSplitChars(split_chars);
    line_file:SeekEnd();
    local c = 1;

    local str_tab={};

    local mem = new_mem();
    while line_file:ReadWordWithEmptyChar_Reverse(mem) do        
        local ch = mem:CharAt(0);
        if line_file:IsSpChar(ch) or FileBase.IsEmptyChar(ch) then
            table.insert(str_tab,mem:CStr());
        else
            if not match_n(c) then
                table.insert(str_tab,mem:CStr());
            end
            c = c + 1;
        end
    end    

    for i=#str_tab,1,-1 do
        print(str_tab[i]);
    end    
end

if not delete then
    for_each_line(mem_text_file,
        function(line,line_file)
            if not from_tail then
                do_from_head(line,line_file);
            else
                do_from_tail(line,line_file);
            end
        end
    );
else
    for_each_line(mem_text_file,
        function(line,line_file)
            if not from_tail then
                delete_from_head(line,line_file);
            else
                delete_from_tail(line,line_file);
            end
        end
    );
end