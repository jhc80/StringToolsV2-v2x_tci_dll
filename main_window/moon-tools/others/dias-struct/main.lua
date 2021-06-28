require("common");
require("user");
require("dias");
require("lua_to_lua");

function string_to_global(str)
	return string_to_table(str);
end

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

App.ClearScreen();

local name = struct_name.."_size";
local size_func = string_to_global(name);
if size_func then
	printfnl("%s = %d;",name,size_func());
end

printnl("");
printf("%s = ",struct_name);

local name = struct_name.."_to_lua";
local to_lua = string_to_global(name);
if not to_lua then
	printfnl("can not find function %s",name);
	return
end

binary_data:Seek(0);
local t = to_lua(binary_data);

printnl(lua_table_to_lua(t));
