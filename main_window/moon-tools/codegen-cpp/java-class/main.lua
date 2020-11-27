require("common")
require("user")
require("codegen")
require("code_utils")

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

local save_str = "";


for _,idl_class in ipairs(all_idl_classes) do
    set_code_switch_by_hint(idl_class.hint,code_switch);
	update_basic_type_table_by_hint(idl_class);

    if save_path and save_path ~= "" then
        local java_name = FileManager.ToAbsPath(
            save_path.."/"..
            to_file_name(idl_class.name)..".java"            
        );
                        
        App.ClearBuffer();
        code_java(idl_class);
        
        if App.SaveBuffer(java_name) then
            printfnl("save to %s",java_name);
        else
            printfnl("fail to save %s",java_name);
        end

    else       
        code_java(idl_class);
    end    
end


