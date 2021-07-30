require("common");
require("user");
require("asn1");

local file_input = load_from_file_or_editor(lua_in_file);
if not file_input then return end

App.ClearScreen();

local ASN1 = nil;

if message_type == 1 then
    require("asn1_v2x_gb2017");
    ASN1 = Asn1V2xGb2017;
elseif message_type == 2 then
    require("asn1_v2x_gb2019");
    ASN1 = Asn1V2xGb2019;
elseif message_type == 3 then
    require("asn1_v2x_gb2020");
    ASN1 = Asn1V2xGb2020;
elseif message_type == 4 then
    require("asn1_gxx_obu");
    ASN1 = Asn1GxxObu;
elseif message_type == 5 then
    require("asn1_v2x_gb2020_day2");
    ASN1 = Asn1V2xGb2020Day2;
elseif message_type == 6 then
    require("asn1_v2x_gb2020_security");
    ASN1 = Asn1V2xGb2020Security;
elseif message_type == 7 then
    require("asn1_v2x_tci");
    ASN1 = Asn1V2xTci;    
end

if not ASN1 then
    printfnl("unknown message type %d",message_type);
    return;
end

local descriptor = ASN1.GetDescriptor(descriptor_name);

if not descriptor then
    printfnl("can not find descriptor %s",descriptor_name);
    return;
end

if file_input:GetSize() <= 0 then
    return;
end

local t = string_to_table(file_input:CStr());
if not t then
    printfnl("table is nil.");
    return;
end

local asn1 = ASN1.FromLua(t,descriptor);

if string.len(asn1) <= 0 then
    return;
end

local mem = Mem.new();
mem:SetRawBuf(asn1);

if save_file ~= "" then
    if mem:WriteToFile(save_file) > 0 then
        printfnl("save encoded asn.1 data to %s",save_file);
    else
        printfnl("save %s fail.", save_file);
    end
else
    local file_output = new_memfile();
    bin_file_to_hex_file(mem,file_output,20);
    print_whole_file(file_output);
end
