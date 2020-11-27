require("common")
require("user")
require("codegen");
require("codegen_lua");
require("codegen_js");
require("codegen_java");

function make_file_name(idl_class,ext,postfix)
    if not postfix then postfix="" end
    return FileManager.ToAbsPath(
        save_path.."/"..
        to_lower_underline_case(idl_class.name)..
        postfix.."."..ext          
    );
end

--生成java的文件名，因为java的类名要求和文件名一致--
function make_java_file_name(idl_class,ext,postfix)
    if not postfix then postfix="" end
    return FileManager.ToAbsPath(
        save_path.."/"..
        java_class_name(idl_class.name)..
        postfix.."."..ext          
    );
end

function make_client_idl_class(idl_class)    
    local name,start_id = IdlHelper.Class.GetClientName(idl_class);    
    if not name then return end
    
    local client_idl_class = clone_table(idl_class);
    
    client_idl_class.name = name;
    client_idl_class.start_id = start_id;
    
    if not client_idl_class.functions then
        return client_idl_class;
    end
    
    for _,func in ipairs(client_idl_class.functions) do
        if func.hint then
            for k,hint in ipairs(func.hint) do        
                if hint == "service" then
                    func.hint[k]="";
                else
                    func.hint[k] = "service";
                end
            end
        else
            func.hint={"service"};
        end
    end
    return client_idl_class;
end

function check_idl_class_hints(idl_class)
    if not idl_class.peer_name then
        printfnl("idl class '%s' has no [Peer]",idl_class.name);
        return;
    end       

    if not idl_class.start_id then
        printfnl("idl class '%s' has no [StartId]",idl_class.name);
        return;
    end

    if not idl_class.name then
        printfnl("idl class '%s' has no [Client]",idl_class.name);
        return;
    end           

    return true;
end
-----------------------------------------------------------------
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

local all_idl_classes_len = #all_idl_classes;
for k=1,all_idl_classes_len,1 do  
    local ori_idl_class = all_idl_classes[k];

    ori_idl_class.peer_name = IdlHelper.Class.GetPeerName(ori_idl_class);
    ori_idl_class.start_id = IdlHelper.Class.GetStartId(ori_idl_class);

    local client_idl_class = make_client_idl_class(ori_idl_class);
    if client_idl_class then
        table.insert(all_idl_classes,client_idl_class);
    end
end
--------------------h and cpp files-------------------------------
for _,idl_class in ipairs(all_idl_classes) do    
	update_basic_type_table_by_hint(idl_class);              
    if not check_idl_class_hints(idl_class) then        
        App.Sleep(2000);
        goto continue;
    end       

    local cpp_name = make_file_name(idl_class,"cpp");
    local h_name = make_file_name(idl_class,"h");        
    local lua_name = make_file_name(idl_class,"lua");
    local message_h_name = make_file_name(idl_class,"h","_messages");
    local message_lua_name = make_file_name(idl_class,"lua","_messages");
	local js_name = make_file_name(idl_class,"js");
	local message_js_name = make_file_name(idl_class,"js","_messages");
	local java_name = make_java_file_name(idl_class,"java");
	local message_java_name = make_java_file_name(idl_class,"java","Messages");

    if save_path and save_path ~= "" then
        App.ClearBuffer();
        code_h(idl_class);                
        if App.SaveBuffer(h_name) then
			printfnl("save to %s ok.",h_name);
        else            
			printfnl("fail to save %s.",h_name);
        end
        
        App.ClearBuffer();
        code_cpp(idl_class);        
        if App.SaveBuffer(cpp_name) then
            printfnl("save to %s ok.",cpp_name);
        else
            printfnl("fail to save %s.",cpp_name);
        end
        
        App.ClearBuffer();
        code_lua(idl_class);        
        if App.SaveBuffer(lua_name) then
            printfnl("save to %s ok.",lua_name);
        else
            printfnl("fail to save %s.",lua_name);
        end

        App.ClearBuffer();
        code_js(idl_class);		

        if App.SaveBuffer(js_name) then
			printfnl("save to %s ok.",js_name);
        else
            printfnl("fail to save %s.",js_name);
        end

        App.ClearBuffer();
        code_java(idl_class);		

        if App.SaveBuffer(java_name) then
			printfnl("save to %s ok.",java_name);
        else
            printfnl("fail to save %s.",java_name);
        end
		
        App.ClearBuffer();
        code_message_define_h(idl_class);        
        if App.SaveBuffer(message_h_name) then
			printfnl("save to %s ok.",message_h_name);
        else            
			printfnl("fail to save %s.",message_h_name);
        end
        
        App.ClearBuffer();
        code_lua_message_define(idl_class);        
        if App.SaveBuffer(message_lua_name) then
			printfnl("save to %s ok.",message_lua_name);
        else
            printfnl("fail to save %s.",message_lua_name);
        end
		
        App.ClearBuffer();
        code_js_message_define(idl_class);        
        if App.SaveBuffer(message_js_name) then
            printfnl("save to %s ok.",message_js_name);
        else
            printfnl("fail to save %s.",message_js_name);
        end		
		
        App.ClearBuffer();
        code_java_message_define(idl_class);        
        if App.SaveBuffer(message_java_name) then
            printfnl("save to %s ok.",message_java_name);
        else
            printfnl("fail to save %s.",message_java_name);
        end			
    else
        printfnl("////////////////%s///////////////",message_h_name);
        code_message_define_h(idl_class);
        
        printfnl("////////////////%s///////////////",h_name);
        code_h(idl_class);
        
        printfnl("////////////////%s///////////////",cpp_name);
        code_cpp(idl_class);

        printfnl("////////////////%s///////////////",lua_name);
        code_lua(idl_class);

        printfnl("////////////////%s///////////////",js_name);
        code_js(idl_class);

        printfnl("////////////////%s///////////////",java_name);
        code_java(idl_class);
		
        printfnl("////////////////%s///////////////",message_lua_name);
        code_lua_message_define(idl_class);
		
        printfnl("////////////////%s///////////////",message_js_name);
        code_js_message_define(idl_class);
		
        printfnl("////////////////%s///////////////",message_java_name);
        code_java_message_define(idl_class);		
    end
    ::continue::    
end

-------------------idl file---------------
App.ClearBuffer();
for _,idl_class in ipairs(all_idl_classes) do
    code_idl(idl_class);
end

if save_path and save_path ~= "" then
    local idl_name = make_file_name({name="linkrpc_all"},"idl"); 
    if App.SaveBuffer(idl_name) then
        printfnl("save to %s ok.",idl_name);
    else
        printfnl("fail to save %s.",idl_name);
    end
end

-------------- common inlcude file----------
local peer_name_idl_table = {};

for _,idl_class in ipairs(all_idl_classes) do
    if not peer_name_idl_table[idl_class.peer_name] then
        peer_name_idl_table[idl_class.peer_name] = {};
    end
    table.insert(peer_name_idl_table[idl_class.peer_name],idl_class);
end

for peer_name, idl_class_tab in pairs(peer_name_idl_table) do
    local common_h_file;

    if save_path and save_path ~= "" then
        common_h_file = FileManager.ToAbsPath(
            save_path.."/"..common_cpp_include_name(peer_name)..".h"
        );
    end

    if common_h_file then
        App.ClearBuffer();
    end

    local h_name = common_cpp_include_name(peer_name);
    printfnl("#ifndef __%s_H",to_upper_underline_case(h_name));
    printfnl("#define __%s_H",to_upper_underline_case(h_name));
    printnl("");

    printnl(begin_cpp_marker("Includes_H"));

    for _,idl_class in ipairs(idl_class_tab) do
        code_common_includes(idl_class);
    end
    
    printnl(end_cpp_marker("Includes_H"));

    printnl("");
    printfnl("#endif");

    if common_h_file then
        if App.SaveBuffer(common_h_file) then
			printfnl("save to %s ok.",common_h_file);
        else
			printfnl("fail to save %s.",common_h_file);
        end
    end    
end
--------------------------------------------
for peer_name, idl_class_tab in pairs(peer_name_idl_table) do
    local common_lua_file;

    if save_path and save_path ~= "" then
        common_lua_file = FileManager.ToAbsPath(
            save_path.."/"..common_cpp_include_name(peer_name)..".lua"
        );
    end

    if common_lua_file then
        App.ClearBuffer();
    end

    local lua_name = common_cpp_include_name(peer_name);

    for _,idl_class in ipairs(idl_class_tab) do
        code_common_requires_lua(idl_class);
    end
    
    if common_lua_file then
        if App.SaveBuffer(common_lua_file) then
			printfnl("save to %s ok.",common_lua_file);
        else
            printfnl("fail to save %s.",common_lua_file);
        end
    end    
end
--------------------------------------------

