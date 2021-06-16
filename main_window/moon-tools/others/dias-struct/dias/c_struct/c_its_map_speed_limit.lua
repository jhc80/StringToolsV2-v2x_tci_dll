function ItsMapSpeedLimit_to_lua(data)
    local _obj={};
    _obj.type = data:GetUInt8();
    _obj.value = data:GetUInt32();
    return _obj;
end

function lua_to_ItsMapSpeedLimit(_obj,file)
    file:PutUInt8(_obj.type);
    file:PutUInt32(_obj.value);
end

function ItsMapSpeedLimit_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT8;  --type
    _size = _size + SIZE_OF_UINT32;  --value
    return _size;
end

