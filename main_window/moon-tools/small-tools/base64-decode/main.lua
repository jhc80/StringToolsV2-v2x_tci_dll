require("common");
require("user");

local file_input;

if not base64_in_file or base64_in_file=="" then
	file_input = App.LoadText():FileBase();
else
	_,file_input = new_mmapfile(base64_in_file,"r");
end

if not file_input then
	return
end

App.ClearScreen();

local size = file_input:GetSize();

local mem_output, file_output = new_mem(size);

if not App.Base64Decode(file_input,file_output) then
	return
end

if bin_out_file and bin_out_file~="" then
	file_output:WriteToFile(bin_out_file);
	printnl("save to "..bin_out_file);
	return
end

print_whole_file(file_output);
