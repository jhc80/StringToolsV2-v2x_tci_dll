require("common");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();

require("user");

function need_this_line(line,line_file)
    local need = (logic_op=="and") and true or false;
    for _,str in ipairs(string_table) do
        line_file:Seek(0);
        local flag = line_file:SearchStr(str,case_sensitive,word_only) >= 0;        
        if logic_op == "and" then            
            need = need and flag;    
        elseif logic_op == "or" then
            need = need or flag;
        end        
    end
    
    if reverse_op then
        need = not need;
    end
    
    return need;
end

for_each_line(mem_text_file,
	function(line,line_file)
		if need_this_line(line, line_file) then
			printnl(line:CStr());
		end
	end
);
