App.ClearScreen();

function is_line(str, target)
	if not str then return end
	return string.trim(str) == target;
end

function convert_file(filename)
	local src = new_mem(filename);
	if not src then return end

	local out = new_memfile();

	src:Seek(0);
	local mem = new_mem();
	local str = last_str;
	local last_line_size = 0;

	local find_maker = false;

	while src:ReadLine(mem) do	
		last_str = str;
		str = mem:CStr();

		if is_line(str,"/*##Begin Init##*/") then
			find_marker = true;
			src:ReadLine(mem);			
			str = mem:CStr();
			if not is_line(str,"this->InitBasic();") then
				if not is_line(last_str,"this->InitBasic();") then
					out:Puts("    this->InitBasic();\r\n");
				end
				out:Puts("/*##Begin Init##*/\r\n");
				out:Puts(str);out:Puts("\r\n");
			else
				out:Puts(str);out:Puts("\r\n");
				out:Puts("/*##Begin Init##*/\r\n");
			end

		elseif is_line(str,"/*##End Destroy##*/") then
			find_marker = true;
			src:ReadLine(mem);
			local next_str = mem:CStr();
			
			if is_line(last_str,"this->InitBasic();") then
				out:SetSize(last_line_size);out:SeekEnd();
				out:Puts(str);out:Puts("\r\n");
				
				if not is_line(next_str,"this->InitBasic();") then				
					out:Puts("    this->InitBasic();\r\n");
				end
				out:Puts(next_str);out:Puts("\r\n");
			else
				out:Puts(str);out:Puts("\r\n");
				if not is_line(next_str,"this->InitBasic();") then				
					out:Puts("    this->InitBasic();\r\n");
				end
				out:Puts(next_str);out:Puts("\r\n");
			end
		else
			last_line_size = out:GetSize();
			out:Puts(str);out:Puts("\r\n");			
		end
	end	

	if find_marker then
		out:WriteToFile(filename);
	end
	
	src:Destroy();
	out:Destroy();

	printfnl("%s ok",filename);
	return true;
end



for_each_line(mem_text_file,function(line)
	if not convert_file(line:CStr()) then
		printfnl("%s fail.",line:CStr());
		return true;
	end
end);
