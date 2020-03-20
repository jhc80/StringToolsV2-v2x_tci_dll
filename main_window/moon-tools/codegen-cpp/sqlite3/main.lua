require("common")
require("user")
require("code_utils")
require("idl_helper")
require("codegen")
require("print_buffer")
require("cpp_base_codegen")

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

local function is_sqlite3(idl_class)    
    local node_name;
    for_each_hint(idl_class.hint,function(mem)
        mem:SetSplitChars(" ,\t\r\n");
        if mem:NextString() ~= "Sqlite3" then        
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


local pbuf = PrintBuffer.new();

for _,idl_class in ipairs(all_idl_classes) do  
    set_code_switch_by_hint(idl_class.hint,code_switch);
    g_cpp_base_codegen = CppBaseCodeGen.new(idl_class,code_switch);
    g_cpp_base_codegen:SetHowToConvertFileName(to_file_name);
   
    local table_name = idl_class.name;
    local node_name = is_sqlite3(idl_class);
    if not node_name then
        goto continue;
    end
	
	--exchange names
	idl_class.name = node_name;
	node_name = table_name;
	table_name = idl_class.name;
        

    if save_path == "" then
        code_h(idl_class,node_name);
        code_cpp(idl_class,node_name);
    else        
        App.ClearBuffer();
        code_h(idl_class,node_name);
        local save_name = FileManager.ToAbsPath(
            save_path.."/"..to_file_name(table_name)..".h"
        );
                
        if App.SaveBuffer(save_name) then
            pbuf:Log("save to "..save_name);
        else
            pbuf:Log("fail to save "..save_name);
        end

        local save_name = FileManager.ToAbsPath(
            save_path.."/"..to_file_name(table_name)..".cpp"
        );
        
        App.ClearBuffer();
        code_cpp(idl_class,node_name);
          
        if App.SaveBuffer(save_name) then
            pbuf:Log("save to "..save_name);
        else
            pbuf:Log("fail to save "..save_name);
        end        
    end
    ::continue::
end

pbuf:Dump();

