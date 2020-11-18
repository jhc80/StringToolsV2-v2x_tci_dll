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

for _,idl_class in ipairs(all_idl_classes) do    
	update_basic_type_table_by_hint(idl_class);
	IdlHelper.Class.MakeConnections(idl_class);

	if save_path == "" then
		code_h(idl_class);
		printnl("");
		code_cpp(idl_class);
		printnl("");
		code_java(idl_class);
	else
		local h_file_name = FileManager.ToAbsPath(
			save_path.."/"..jnilib_file_name(idl_class.name)..".h");
		local cpp_file_name = FileManager.ToAbsPath(
			save_path.."/"..jnilib_file_name(idl_class.name)..".cpp");
		local java_file_name = FileManager.ToAbsPath(
			save_path.."/"..java_file_name(idl_class.name)..".java");
		
		App.ClearBuffer();
		code_h(idl_class);
		if App.SaveBuffer(h_file_name) then
			printnl("");
			printfnl("save to %s ok",h_file_name);
			printnl("");
		else
			printnl("");
			printfnl("fail to save %s",h_file_name);
			printnl("");
		end

		App.ClearBuffer();
		code_cpp(idl_class);
		if App.SaveBuffer(cpp_file_name) then
			printnl("");
			printfnl("save to %s ok",cpp_file_name);
			printnl("");
		else
			printnl("");	
			printfnl("fail to save %s ",cpp_file_name);
			printnl("");
		end
		
		App.ClearBuffer();
		code_java(idl_class);
		if App.SaveBuffer(java_file_name) then
			printnl("");
			printfnl("save to %s ok",java_file_name);
			printnl("");
		else
			printnl("");
			printfnl("fail to save %s ",java_file_name);
			printnl("");
		end
		
	end
end



