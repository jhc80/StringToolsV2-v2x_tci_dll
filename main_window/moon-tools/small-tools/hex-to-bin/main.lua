require("common");
require("user");

local file_input;

local file_input = load_from_file_or_editor(hex_in_file);
if not file_input then return end

App.ClearScreen();

local size = file_input:GetSize();
if size == 0 then return end

local file_output = new_memfile();

hex_file_to_bin_file(file_input,file_output);

if file_output:GetSize() > 0 then
	if bin_out_file and bin_out_file~="" then	
		file_output:WriteToFile(bin_out_file);
		printnl("save to "..bin_out_file.." size="..file_output:GetSize());
		return
	end
end

print_whole_file(file_output);

