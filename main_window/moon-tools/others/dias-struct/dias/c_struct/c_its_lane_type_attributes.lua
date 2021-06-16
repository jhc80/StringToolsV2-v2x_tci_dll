function ItsLaneTypeAttributes_to_lua(data)
    local _obj={};
    _obj.present = data:GetUInt8();
    _obj.value = data:GetUInt16();
    return _obj;
end

function lua_to_ItsLaneTypeAttributes(_obj,file)
    file:PutUInt8(_obj.present);
    file:PutUInt16(_obj.value);
end

function ItsLaneTypeAttributes_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT8;  --present
    _size = _size + SIZE_OF_UINT16;  --value
    return _size;
end

