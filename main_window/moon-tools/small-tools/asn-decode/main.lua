require("common");
require("user");


local binary_data;

if not in_binary_file or in_binary_file=="" then
    local text = App.LoadText();
    if not text then return; end
    if text:GetSize() == 0 then 
        return 
    end
    binary_data = new_mem(text:GetSize());
    hex_file_to_bin_file(text,binary_data);
else
    binary_data = new_mem(in_binary_file);
    if not binary_data then
        printfnl("can not open %s",in_binary_file);
        return;
    end
    if in_format ~= 0 then
        local hex_data = binary_data;
        binary_data = new_mem(hex_data:GetSize());
        hex_file_to_bin_file(hex_data,binary_data);
    end
end

if in_offset > 0 then
    binary_data = binary_data:Slice(in_offset,-1);
end

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

App.ClearScreen();

local str = ASN1.ToLua(binary_data:CStr(),descriptor);

if str then
    printnl(str);
end

