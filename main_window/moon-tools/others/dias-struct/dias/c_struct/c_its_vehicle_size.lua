function ItsVehicleSize_to_lua(data)
    local _obj={};
    _obj.width = data:GetUInt16();
    _obj.length = data:GetUInt16();
    _obj.height = data:GetUInt16();
    return _obj;
end

function lua_to_ItsVehicleSize(_obj,file)
    file:PutUInt16(_obj.width);
    file:PutUInt16(_obj.length);
    file:PutUInt16(_obj.height);
end

function ItsVehicleSize_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT16;  --width
    _size = _size + SIZE_OF_UINT16;  --length
    _size = _size + SIZE_OF_UINT16;  --height
    return _size;
end

