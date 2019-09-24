require("common")
require("user")
require("cpp_base_codegen")
require("code_linkedlist_h")
require("code_linkedlist_cpp")

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

local function is_list_class(idl_class) 
    local node_name;
    for_each_hint(idl_class.hint,function(mem)
        mem:SetSplitChars(" ,\t\r\n");
        if mem:NextString() ~= "List" then        
            return;        
        end
        
        if mem:NextString() ~= "of" then        
            return;        
        end
        
        node_name = mem:NextString();        
        return true;            
    end);    
    
    return node_name;    
end

function create_names(list_name,node_name)

    return {
        class_name = list_name,
        c_class_name = c_class_name(list_name),
        file_name_upper = string.upper(list_name),
        file_name = to_file_name(list_name),
        c_node_class_name = c_class_name(node_name),
        node_class_name = node_name,
        node_file_name = to_file_name(node_name),
        name_space = name_space,
		c_entry_class_name = list_name.."_Entry",
    }

end

local pbuf = PrintBuffer.new();

for _,idl_class in ipairs(all_idl_classes) do
    set_code_switch_by_hint(idl_class.hint,code_switch);
    g_cpp_base_codegen = CppBaseCodeGen.new(idl_class,code_switch);
    g_cpp_base_codegen:SetHowToConvertFileName(to_file_name);
   
    local node_name,is_basic = is_list_class(idl_class);
    
    if not node_name then 
        goto _continue_; 
    end
    
    local list_name = idl_class.name;

    local names = create_names(list_name,node_name)    

    function save_current_file(ext)
        if save_path == "" then return end
        local save_name = FileManager.ToAbsPath(
            save_path.."/"..to_file_name(list_name)..ext
        );
        if App.SaveBuffer(save_name) then
            pbuf:Log("save to "..save_name);
        else
            pbuf:Log("fail to save "..save_name);
        end
    end

    App.ClearBuffer();
    code_h(names);
    save_current_file(".h");

    App.ClearBuffer();
    code_cpp(names);
    save_current_file(".cpp");
   
    ::_continue_::
end

pbuf:Dump();

