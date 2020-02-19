require("common");
require("user");

local file_input;

local file_input = load_from_file_or_editor(bin_in_file);
if not file_input then return end

App.ClearScreen();

local size = file_input:GetSize();
if size == 0 then return end

local file_output = new_memfile();

bin_file_to_hex_file(file_input,file_output,line_width);

if file_output:GetSize() > 0 then
	if hex_out_file and hex_out_file~="" then	
		file_output:WriteToFile(hex_out_file);
		printnl("save to "..hex_out_file.." size="..file_output:GetSize());
		return
	end
end

print_whole_file(file_output);

