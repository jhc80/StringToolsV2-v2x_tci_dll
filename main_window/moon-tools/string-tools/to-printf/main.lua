require("common");

mem_text = App.LoadText();
App.ClearScreen();

require("user");

function escape_c_string(mem)
    mem:Seek(0); 
    local mf = new_memfile();
    while not mem:IsEnd() do
        local ch = mem:Getc();
        if ch == 34 or ch == 39 or ch == 92 then
            mf:Puts("\\");
            mf:Putc(ch);
		elseif ch == 13 then
			mf:Puts("\\r");
        elseif ch == 10 then
			mf:Puts("\\n");
		elseif ch == 9 then
            mf:Puts("    ");
		elseif ch == 37 then
			mf:Puts("%%");         
		else 
			mf:Putc(ch);	            
        end
    end
    return mf;
end

function parse_line(line)
    local format_str = new_memfile();;
    local params_str = "";

    line:SetSplitChars(split_chars);
    line:Seek(0);

    local len = line:StrLen();
    local pos = 0;

    local tmp_mf = new_memfile();

    while pos < len do
        local min = len; 
        local hit = -1;
        
        for i , rep in ipairs(replace_table) do
            line:Seek(pos);
            local t = line:SearchStr(rep[1],case_sensive, word_only);
            if t >= 0 and t < min then
                min = t;
                hit = i;
            end
        end

        if hit >= 0 then
            local tab = replace_table[hit];    
            tmp_mf:SetSize(0);      
            tmp_mf:WriteFile(line,pos,min-pos);
            local escaped = escape_c_string(tmp_mf);
            format_str:Puts(escaped);
            escaped:Destroy();
            format_str:Puts(tab[2]);
            if string.len(params_str) > 0 then
                params_str = params_str..","
            end
            params_str = params_str..tab[3];
            pos = min + string.len(tab[1]);
        else
            tmp_mf:SetSize(0);      
            tmp_mf:WriteFile(line,pos,1);
            local escaped = escape_c_string(tmp_mf);
            format_str:Puts(escaped);
            escaped:Destroy();            
            pos = pos + 1;
        end
    end

    return format_str, params_str;
end

function do_single_line_mode()
    for_each_line(mem_text,function(line,line_file)
        local format_str, params_str = parse_line(line_file);
        output(file_to_string(format_str),params_str);
        format_str:Destroy();
    end);
end

do_single_line_mode();
