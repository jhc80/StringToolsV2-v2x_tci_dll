require("common")
require("user")

local mem_text = App.LoadText();
App.ClearScreen();

function put_string(file,str, s,e)
	local sub_str = string.sub(str,s,e);
	if sub_str then
		file:Puts(sub_str);
	end
end

function repleace_one_pattern(str,pattern)
	local tmp = new_memfile();
	local start = 1;
	while true do
		local s,e = string.find(str,pattern,start);
		if not s then 
			break 
		end		
		local capture = string.sub(str,s,e);
		put_string(tmp,str,start,s-1);
		tmp:Puts(how_to_replace(pattern,capture));		
		start = e+1;		
	end
	put_string(tmp,str,start);
	
	local ret = file_to_string(tmp);
	tmp:Destroy();
	return ret;
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

function save_file_string(str, filename)
	local mf = new_memfile();
	mf:Puts(str);
	if mf:WriteToFile(filename) <= 0 then
		printfnl("save file %s FAIL.",filename);
	else
		printfnl("save to %s ok.",filename);
	end
end

if not replace_in_files then
	local str = mem_text:CStr();
	for _,pattern in ipairs(all_patterns) do
		str = repleace_one_pattern(str,pattern);
	end
	print(str);
else	
	for_each_line(mem_text,function(line)
		line:Trim();
		if line:C(0) == 0 then return end
		local str = load_file_string(line:CStr());
		local old_str = str;
		
		if str then
			for _,pattern in ipairs(all_patterns) do
				str = repleace_one_pattern(str,pattern);
			end		
		end
		
		if old_str ~= str then
			save_file_string(str,line:CStr());
		end		
	end);
	printnl("all done");
end

