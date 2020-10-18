--把一行行的英文单词拆分成一个Lua table--
--方便后续处理--

App.ClearScreen();

function is_chinese(ch)
	return ch > 0x7f;
end

function parse_line(line)

	line:Seek(0);
	line:SetSplitChars(" \t\n\r");
	
	local english = "";
	local type="";
	local chinese = "";
	
	local hit_englist;
	local hit_type;
	local hit_chinese;
	local mem = new_mem();
	
	while not line:IsEnd() do
		mem:SetSize(0);
		line:ReadWordWithEmptyChar(mem);
		local str = mem:CStr();		
		if string.match(str,"%.$") then
			type = str;
			hit_type = true;
			hit_chinese = true;
		else			
			if is_chinese(string.byte(str,1)) then
				hit_chinese = true;
			end
			if string.byte(str,1) == 40  or string.byte(str,1) == 61 then
				hit_chinese = true;
			end
		

			if hit_chinese then
				chinese = chinese..str;
			end
			
			if not hit_type and not hit_chinese then
				english = english..str;		
			end
		end
	end
	
	return {
		english = english,
		type = type,
		chinese = chinese,
	}
end


printfnl("english_table = {");

local i = 0;
for_each_line(mem_text_file,function(line)
	i = i + 1;
	local t = parse_line(line);

	printfnl("{");	
	printfnl("    english = \"%s\",",string.trim(t.english));
	printfnl("    type = \"%s\",",t.type);
	printfnl("    chinese = \"%s\",",t.chinese);	
	printfnl("},");

end);

printfnl("}");


