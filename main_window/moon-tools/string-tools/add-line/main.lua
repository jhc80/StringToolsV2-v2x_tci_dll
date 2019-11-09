require("common");
require("user");

mem_text = App.LoadText();

App.ClearScreen();

function process_single_file(file)
	local ret = new_memfile();
	for_each_line(file,function(line)  
		local str = line:CStr();	
		ret:Puts(str..EOL);
		if match_line(line) then
			ret:Puts(add_text(line));
		end
	end);
	return ret;
end

if not do_files then
	local new_file=process_single_file(mem_text);
	print_whole_file(new_file);
else
	for_each_line(mem_text,function(line)		
		local file = new_file(line:CStr(),"rb");
		if not file then
			printfnl("open file %s fail.", line:CStr());
			return
		end
		
		local new_file = process_single_file(file);		
		if new_file:WriteToFile(line:CStr()) > 0 then
			printfnl("save %s ok.",line:CStr());
		else
			printfnl("save %s FAIL.",line:CStr());
		end
		new_file:Destroy();
		file:Destroy();
	end);

end

