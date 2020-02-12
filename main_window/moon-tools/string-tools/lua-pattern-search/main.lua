require("common")
require("user")

local mem_text = App.LoadText();
App.ClearScreen();

function find_one_pattern(str,pattern,out)
	local start = 1;
	
	while true do
		local s,e = string.find(str,pattern,start);
		if not s then break  end		

		if print_found_string then
			local capture = string.sub(str,s,e);
			if not out then
				printnl(capture)
			else
				out:Puts(capture);
				out:Puts(EOL);
			end
		end
		start = e+1;		
	end
	
	return found;
end

function load_file_string(filename)
	local mem = new_mem(filename);
	if not mem then
		printfnl("load file %s fail.");
		return
	end
	local ret = mem:CStr();
	mem:Destroy();
	return ret;
end

if not find_in_files  then
	local str = mem_text:CStr();
	for _,pattern in ipairs(all_patterns) do
		find_one_pattern(str,pattern);
	end
else	
	local out_file = new_memfile();

	for_each_line(mem_text,function(line)
		line:Trim();
		if line:C(0) == 0 then return end
		local str = load_file_string(line:CStr());
	
		if str then
			for _,pattern in ipairs(all_patterns) do
				out_file:SetSize(0);
				find_one_pattern(str,pattern,out_file);
				if out_file:GetSize() > 0 then
					printfnl(line:CStr());
					print_whole_file(out_file);
					printnl("");
				end
			end		
		end
	end);
end

