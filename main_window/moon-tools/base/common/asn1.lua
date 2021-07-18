function _octet_string(str)
    return "octet_string:"..str;
end

function _bit_string(str)
    return "bit_string:"..str;
end

function _ia5_string(str)
    return "ia5_string:"..str;
end

-----------------------------------------------------------------
asn1 = {};

asn1.build_ia5_string = function(str)
    return "ia5_string:"..str;
end

asn1.build_ia5_string_from_string = function(str)
    local ret = "ia5_string:";
    for i=1,string.len(str),1 do
        ret = ret..string.format("%02x",string.byte(str,i));
    end
    return ret;
end

asn1.build_ia5_string_from_file = function(file)
    local ret = "ia5_string:";    
    file:Seek(0);
    while not file:IsEnd() do
        local b = file:Getc() & 0xff;
        ret = ret..string.format("%02x",b);
    end    
    return ret;
end

asn1.build_ia5_string = function(str)
    return "ia5_string:"..str;
end

asn1.build_ia5_string_from_string = function(str)
    local ret = "ia5_string:";
    for i=1,string.len(str),1 do
        ret = ret..string.format("%02x",string.byte(str,i));
    end
    return ret;
end

asn1.build_ia5_string_from_file = function(file)
    local ret = "ia5_string:";    
    file:Seek(0);
    while not file:IsEnd() do
        local b = file:Getc() & 0xff;
        ret = ret..string.format("%02x",b);
    end    
    return ret;
end

asn1.build_octet_string = function(str,fixed_size)
    return "octet_string:"..str;
end

asn1.build_octet_string_from_string = function(str)
    local ret = "octet_string:";
    for i=1,string.len(str),1 do
        ret = ret..string.format("%02x",string.byte(str,i));
    end
    return ret;
end

asn1.build_octet_string_from_file = function(file)
    local ret = "octet_string:";    
    file:Seek(0);
    while not file:IsEnd() do
        local b = file:Getc() & 0xff;
        ret = ret..string.format("%02x",b);
    end    
    return ret;
end

