require("common")
require("user")
require("codegen")
require("c_base_codegen");

local ori_code_switch = clone_table(code_switch);

g_idl_class = nil;
g_c_base_codegen = nil;

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
    code_switch = clone_table(ori_code_switch);
    set_code_switch_by_hint(idl_class.hint,code_switch);
    
    g_idl_class = idl_class;
    g_c_base_codegen = CBaseCodeGen.new(idl_class,code_switch);
    
    covert_special_types(idl_class);
    
    if save_path and save_path ~= "" then
        local cpp_name = FileManager.ToAbsPath(
            save_path.."/"..
            class_name(idl_class.name)..".c"            
        );

        local h_name = FileManager.ToAbsPath(
            save_path.."/"..
            class_name(idl_class.name)..".h"
        );
                
        App.ClearBuffer();
        code_h(idl_class);        
        
        if App.SaveBuffer(h_name) then
            save_str = save_str .. "save to "..h_name..EOL;
        else
            save_str = save_str .. "fail to save "..h_name..EOL;
        end
        
        App.ClearBuffer();
        code_cpp(idl_class);
        
        if App.SaveBuffer(cpp_name) then
            save_str = save_str .. "save to "..cpp_name..EOL;
        else
            save_str = save_str .. "fail to save "..cpp_name..EOL;
        end

    else
        code_h(idl_class);
        printnl("");
        code_cpp(idl_class);
    end
    
    if save_str ~= "" then 
        App.ClearScreen();
        printnl(save_str);
    end
    
end


