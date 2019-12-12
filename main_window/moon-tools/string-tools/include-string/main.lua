require("common");

mem_text = App.LoadText();
mem_text_file = mem_text:FileBase();

App.ClearScreen();

require("user");

function do_single_file(filename)
	local mf = new_memfile(filename);
	if not mf then
		printf("open file %s fail.",filename);
		return
	end
	
	local out = new_memfile();
	local line = new_mem();
	local eol = new_mem();
	
	mf:Seek(0);
	while mf:ReadLineWithEol(line,eol) do
		if need_this_line(line) then
			out:Puts(line);
			out:Puts(eol);
		end	
	end
	
	local modified = false;
	if not FileManager.IsFileSame(out,mf) then
		out:WriteToFile(filename);
		modified = true;
	end
	
	out:Destroy();
	line:Destroy();
	mf:Destroy();
	eol:Destroy();	
	
	return modified;
end

if do_in_files then
	for_each_line(mem_text_file,
		function(filename)
			filename:Trim();
			if filename:GetSize() >= 0 then
				if do_single_file(filename:CStr()) then
					printnl(filename:CStr().."..modified");
				end
			end
		end
	);	
else
	for_each_line(mem_text_file,
		function(line,line_file)
			if need_this_line(line, line_file) then
				printnl(line:CStr());
			end
		end
	);
end