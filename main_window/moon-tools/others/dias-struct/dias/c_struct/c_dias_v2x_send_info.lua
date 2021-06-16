function DiasV2xSendInfo_to_lua(data)
    local _obj={};
    _obj.bIsEvent = data:GetUInt8();
    _obj.eMsgType = data:GetInt32();
    _obj.u32Aid = data:GetUInt32();
    _obj.u32Priority = data:GetUInt32();
    _obj.u32Reserved = data:GetUInt32();
    return _obj;
end

function lua_to_DiasV2xSendInfo(_obj,file)
    file:PutUInt8(_obj.bIsEvent);
    file:PutInt32(_obj.eMsgType);
    file:PutUInt32(_obj.u32Aid);
    file:PutUInt32(_obj.u32Priority);
    file:PutUInt32(_obj.u32Reserved);
end

function DiasV2xSendInfo_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT8;  --bIsEvent
    _size = _size + SIZE_OF_INT32;  --eMsgType
    _size = _size + SIZE_OF_UINT32;  --u32Aid
    _size = _size + SIZE_OF_UINT32;  --u32Priority
    _size = _size + SIZE_OF_UINT32;  --u32Reserved
    return _size;
end

