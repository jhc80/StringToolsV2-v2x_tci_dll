require("common")
require("user")
require("lua_to_struct");

mem_text = load_from_file_or_editor(idl_source);

App.ClearScreen();

local parser = IdlParser.new();
parser:LoadSourceFromFile(mem_text:FileBase());
local lua = parser:ParseAll();
if parser:HasErrors() then
	printnl(parser:GetCertainErrors());
	return;
end

local all_idl_classes = string_to_table("{"..lua.."}");
if not all_idl_classes then return end
for _,idl_class in ipairs(all_idl_classes) do
	update_basic_type_table_by_hint(idl_class);
	
	App.ClearBuffer();
	code_struct_to_lua(idl_class);
	printnl("");
	code_lua_to_struct(idl_class);
	printnl("");
	
	if save_path and save_path~="" then
		local file_name = FileManager.ToAbsPath(
            save_path.."/"..
            to_file_name(idl_class.name)..".lua"
        );
		
		if App.SaveBuffer(file_name) then
			printfnl("save to %s ok.",file_name);
		else
			printfnl("fail to save %s.",file_name);
		end
	end
end
