require("common")
require("user")
require("codegen")

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

local save_log = "";

function make_full_file_name(name)
	return FileManager.ToAbsPath(save_path.."/"..lualib_file_name(name));
end

for _,idl_class in ipairs(all_idl_classes) do    
	update_basic_type_table_by_hint(idl_class);
	IdlHelper.Class.MakeConnections(idl_class);

	if save_path == "" then
		code_h(idl_class);
		printnl("");
		code_cpp(idl_class);
	else
		local h_file_name = make_full_file_name(idl_class.name..".h");
		local cpp_file_name = make_full_file_name(idl_class.name..".cpp");
		
		App.ClearScreen();
		code_h(idl_class);
		if App.SaveBuffer(h_file_name) then
			save_log = save_log.."save to "..h_file_name.." ok"..EOL;
		else
			save_log = save_log.."fail to save "..h_file_name..EOL;
		end

		App.ClearScreen();
		code_cpp(idl_class);
		if App.SaveBuffer(cpp_file_name) then
			save_log = save_log.."save to "..cpp_file_name.." ok"..EOL;
		else
			save_log = save_log.."fail to save "..cpp_file_name..EOL;
		end
	end
end

if save_log ~= "" then
	App.ClearScreen();
	printnl(save_log);
end


