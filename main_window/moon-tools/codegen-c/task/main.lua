require("common")
require("user")
require("code_utils")
require("task_h")
require("task_c")

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


function create_names(task_name)
    return {
        c_class_name = c_class_name(task_name),        
        file_name = to_file_name(task_name),
		file_name_upper = string.upper(to_file_name(task_name)),
		class_name = task_name,
		class_name_lwr = string.lower(task_name),
    }
end

for _,idl_class in ipairs(all_idl_classes) do    
    set_code_switch_by_hint(idl_class.hint,code_switch);
    local task_name = idl_class.name;
    
    function save_current_file(ext)
        if save_path == "" then return end
        local save_name = FileManager.ToAbsPath(
            save_path.."/"..to_file_name(task_name)..ext
        );
        if App.SaveBuffer(save_name) then
            printnl("save to "..save_name);
        else
            printnl("fail to save "..save_name);
        end
    end

    local names = create_names(task_name);

    App.ClearBuffer();
    code_h(names);
    save_current_file(".h");

    App.ClearBuffer();
    code_cpp(names);
    save_current_file(".c");

end

