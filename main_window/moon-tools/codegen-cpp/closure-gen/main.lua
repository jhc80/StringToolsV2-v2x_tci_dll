require("common")
require("user")
require("closure_gen");

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
	code_closure(idl_class);
	printnl("");
end


