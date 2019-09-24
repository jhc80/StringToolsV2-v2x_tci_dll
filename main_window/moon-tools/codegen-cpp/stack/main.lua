require("common");
require("user");
require("cpp_base_codegen");
require("code_utils");
require("normal_stack_h")
require("normal_stack_cpp")
require("basic_stack_h")
require("basic_stack_cpp")

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

local function is_stack_class(idl_class)
    local node_name,fixed_stack,is_basic;
    
    for_each_hint(idl_class.hint,function(mem)
        mem:SetSplitChars(" ,\t\r\n");
        if mem:NextString() ~= "Stack" then
            return; 
        end
        
        if mem:NextString() ~= "of" then
            return;
        end
        
        node_name = mem:NextString();
        local str = mem:NextString();
        
        fixed_stack = str=="fixed";
        is_basic = str == "basic";     
        return true;
    end);
    
    return node_name,fixed_stack,is_basic;
end

function create_names(stack_name,node_name)
    return {
        c_class_name = c_class_name(stack_name),
        file_name_upper = string.upper(stack_name),
        file_name = to_file_name(stack_name),
        c_node_class_name = c_class_name(node_name),
        node_class_name = node_name,
        node_file_name = to_file_name(node_name),
        name_space = name_space,
    }
end

local pbuf = PrintBuffer.new();

for _,idl_class in ipairs(all_idl_classes) do   
    set_code_switch_by_hint(idl_class.hint,code_switch);
    g_cpp_base_codegen = CppBaseCodeGen.new(idl_class,code_switch);
    g_cpp_base_codegen:SetHowToConvertFileName(to_file_name);
   
    local node_name,is_fixed,is_basic = is_stack_class(idl_class);
    
    if not node_name then 
        goto _continue_
    end
    
    local stack_name = idl_class.name;
    local names = create_names(stack_name,node_name)    

    function save_current_file(ext)
        if save_path == "" then return end
        local save_name = FileManager.ToAbsPath(
            save_path.."/"..to_file_name(stack_name)..ext
        );
        if App.SaveBuffer(save_name) then
            pbuf:Log("save to "..save_name);
        else
            pbuf:Log("fail to save "..save_name);
        end
    end

    
    if is_basic then
        App.ClearBuffer();
        code_basic_h(names);
        save_current_file(".h");

        App.ClearBuffer();
        code_basic_cpp(names);
        save_current_file(".cpp");   
    else
        App.ClearBuffer();
        code_normal_h(names);
        save_current_file(".h");

        App.ClearBuffer();
        code_normal_cpp(names);
        save_current_file(".cpp");
    end

    ::_continue_::
end

pbuf:Dump();
