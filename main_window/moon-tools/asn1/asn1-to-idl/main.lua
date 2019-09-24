require("common")
require("asn1_consts");
require("asn1_helper")
require("asn1_utils")
require("codegen");
require("print_buffer");
require("user")

local text = load_from_file_or_editor(lua_asn1_file);

App.ClearScreen();

local asn1_table = string_to_table(text:CStr());

if not asn1_table then
    printnl("load asn1 lua table fail.");
    return
end

asn1_helper = ASN1_Helper.new(asn1_table);

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

--必须在普通结构运行之前运行这段代码--
--因为内部结构体字段的名字会被改动--
local inners = extract_all_inner_members(asn1_table);
if inners then
    for k,v in ipairs(inners) do
        code_idl(v);
    end
end

for_each_module(asn1_table,function(module)
    for_each_member(module,function(m)
        if m.meta_type == AMT_TYPE then                               
            code_idl(m,0);
        end
    end);           
end);


