require("common");
require("bson");
require("user");

local binary_data;

if not in_binary_file or in_binary_file=="" then
    local text = App.LoadText();
    if not text then return; end
    if text:GetSize() == 0 then 
        return 
    end
    binary_data = new_mem(text:GetSize());
    hex_file_to_bin_file(text,binary_data);
else
    binary_data = new_mem(in_binary_file);
    if not binary_data then
        printfnl("can not open %s",in_binary_file);
        return;
    end
    if in_format ~= 0 then
        local hex_data = binary_data;
        binary_data = new_mem(hex_data:GetSize());
        hex_file_to_bin_file(hex_data,binary_data);
    end
end

if in_offset > 0 then
    binary_data = binary_data:Slice(in_offset,-1);
end

local bson = Bson.new();
if not bson:LoadBson(binary_data) then
	printfnl("load bson fail.");
	return
end

App.ClearScreen();
print(bson:ToJson());

