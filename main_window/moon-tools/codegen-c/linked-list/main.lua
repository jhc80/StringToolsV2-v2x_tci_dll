require("common")
require("user")
require("code_utils")
require("linkedlist_h")
require("linkedlist_c")
require("print_buffer")

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

local function is_linked_list(idl_class)    
    local node_name;
    for_each_hint(idl_class.hint,function(mem)
        mem:SetSplitChars(" ,\t\r\n");
        if mem:NextString() ~= "LinkedList" then        
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

function create_names(map_name,node_name)

    local _c_class_name = c_class_name(map_name);
    local _name_space = name_space;

    return {
        class_name = map_name,
        c_class_name = _c_class_name,
        class_name_upper = string.upper(map_name),
        class_name_lower = string.lower(map_name),
        c_entry_class_name = c_class_name(map_name.."_entry"),
		entry_class_name = string.lower(map_name.."_entry"),
        c_node_class_name = c_class_name(node_name),
        node_class_name = node_name,
		node_class_name_lower= string.lower(node_name),
    }

end

local pbuf = PrintBuffer.new();

for _,idl_class in ipairs(all_idl_classes) do  
    set_code_switch_by_hint(idl_class.hint,code_switch);
    
    local map_name = idl_class.name;
    
    local node_name = is_linked_list(idl_class);
    if not node_name then
        goto continue;
    end
    
    local names = create_names(map_name,node_name);

    if save_path == "" then
        code_h(names);
        code_cpp(names);
    else        
        App.ClearBuffer();
        code_h(names);
        local save_name = FileManager.ToAbsPath(
            save_path.."/"..to_file_name(map_name)..".h"
        );
                
        if App.SaveBuffer(save_name) then
            pbuf:Log("save to "..save_name);
        else
            pbuf:Log("fail to save "..save_name);
        end

        local save_name = FileManager.ToAbsPath(
            save_path.."/"..to_file_name(map_name)..".c"
        );
        
        App.ClearBuffer();
        code_cpp(names);
          
        if App.SaveBuffer(save_name) then
            pbuf:Log("save to "..save_name);
        else
            pbuf:Log("fail to save "..save_name);
        end        
    end
    ::continue::
end

pbuf:Dump();

