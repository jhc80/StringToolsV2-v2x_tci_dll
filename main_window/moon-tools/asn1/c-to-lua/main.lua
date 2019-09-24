require("common")
require("asn1_consts");
require("asn1_helper")
require("asn1_utils")
require("codegen");
require("print_buffer");
require("user")

local text = load_from_file_or_editor(lua_asn1_file);
local text_file = text:FileBase();

App.ClearScreen();

local asn1_table = string_to_table(text:CStr());

if not asn1_table then
    printnl("load asn1 lua table fail.");
    return
end

local asn1_helper = ASN1_Helper.new(asn1_table);

asn1_helper:GenerateFlatHashTable();
if not asn1_helper:FixLinks() then
    printnl("fix links fail.");
    App.Sleep(2000);
end

if not asn1_helper:RebuildReferenceTypes() then
	printnl("rebuild reference types fail.");
    App.Sleep(2000);
end

if not asn1_helper:RebuildContainerEntryTypes() then
    printnl("RebuildContainerEntryTypes fail.");
    App.Sleep(2000);
end

local pbuf = PrintBuffer.new();

for_each_module(asn1_table,function(module)
    for_each_member(module,function(m)
        if m.meta_type == AMT_TYPE then
        
            local h_file_name = FileManager.ToAbsPath(
                save_path.."/"..to_lua_h_filename(m.Identifier)
            );

            local c_file_name = FileManager.ToAbsPath(
                save_path.."/"..to_lua_c_filename(m.Identifier)
            );
        
            if save_path == "" then
                printfnl("//////////////////////");
                code_h(m);            
                printfnl("//////////////////////");
                code_c(m);        
            else
                App.ClearScreen();
                code_h(m);
                if App.SaveBuffer(h_file_name) then
                    pbuf:Log("save to %s ok.",h_file_name);
                else
                    pbuf:Log("fail to save %s!!",h_file_name);
                end

                App.ClearScreen();
                code_c(m);
                if App.SaveBuffer(c_file_name) then
                    pbuf:Log("save to %s.",c_file_name);
                else
                    pbuf:Log("fail to save %s!!",c_file_name);
                end
                               
            end
        end
    end);           
end);

if save_path ~= "" then
    local wireshark_file_name = FileManager.ToAbsPath(
        save_path.."/".."for_wireshark.lua"
    );

    App.ClearScreen();
    code_wireshark_strings(asn1_table);
    if App.SaveBuffer(wireshark_file_name) then
        pbuf:Log("save to %s.",wireshark_file_name);
    else
        pbuf:Log("fail to save %s.",wireshark_file_name);
    end    
else
    code_wireshark_strings(asn1_table);
end

if save_path ~= "" then
    App.ClearScreen();
    printnl(pbuf:GetText());
end



