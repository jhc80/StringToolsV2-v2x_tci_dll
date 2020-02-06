require("common");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();

require("user");

for_each_line(mem_text_file,
	function(line)    
        if from_tail then
            local len = line:StrLen();
            local new_size = len-delete_number;
            if new_size < 0 then new_size = 0 end
            line:SetSize(new_size);
            local new_str = line:CStr();
            printnl(new_str);
        else
            local str = line:CStr();
            local new_str = string.sub(str,1+delete_number);
            printnl(new_str);
        end
	end
);
