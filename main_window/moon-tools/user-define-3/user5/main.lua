require("common");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();

function for_each(mem,opt,callback)
    local tmp = new_mem();    
	
	if opt == 1 then
		while mem:ReadString(tmp) do        
			if callback(tmp) then
				break;
			end        
		end
	end

	if opt == 2 then
		while mem:ReadWord(tmp) do        
			if callback(tmp) then
				break;
			end        
		end
	end
	
	if opt == 3 then
		while mem:ReadWordWithEmptyChar(tmp) do        
			if callback(tmp) then
				break;
			end        
		end
	end
end

mem_text:Seek(0);

require("user");

