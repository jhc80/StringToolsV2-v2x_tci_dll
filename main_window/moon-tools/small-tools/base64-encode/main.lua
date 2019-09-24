require("common");
require("user");

local file_input;

file_input = load_from_file_or_editor(in_file);
if not file_input then 
	return 
end

file_input = file_input:FileBase();

App.ClearScreen();

local size = file_input:GetSize();

local mem_output, file_output = new_mem(size*2);

if not App.Base64Encode(file_input,file_output) then
	return
end

if max_chars_per_line <= 0 then
	return
end

local save_to_file;
if out_file and out_file~="" then
	save_to_file = true;
	App.StopBuffer();
end

local mem,mem_file = new_mem();
file_output:Seek(0);
while not file_output:IsEnd() do
	mem_file:SetSize(0);
	file_output:Read(mem_file,max_chars_per_line);
	printnl(mem:CStr());
end

if save_to_file then
	App.SaveBuffer(out_file);
	App.StartBuffer();
	printnl("save to "..out_file);
end
