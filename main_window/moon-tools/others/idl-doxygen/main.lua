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
local pbuf = PrintBuffer.new();

for _,idl_class in ipairs(all_idl_classes) do

    function save_current_file(ext)
        if save_path == "" then return end
        local save_name = FileManager.ToAbsPath(
            save_path.."/"..to_file_name(idl_class.name)..ext
        );
        if App.SaveBuffer(save_name) then
            pbuf:Log("save to "..save_name);
        else
            pbuf:Log("fail to save "..save_name);
        end
    end
    
    App.ClearBuffer();
    code_doxygen(idl_class);
    save_current_file(".h");
end

pbuf:Dump();
