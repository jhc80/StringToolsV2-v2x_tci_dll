function ItsVehicleEmergencyExtensions_to_lua(data)
    local _obj={};
    _obj.responseType = data:GetInt32();
    _obj.sirenUse = data:GetInt32();
    _obj.lightsUse = data:GetInt32();
    return _obj;
end

function lua_to_ItsVehicleEmergencyExtensions(_obj,file)
    file:PutInt32(_obj.responseType);
    file:PutInt32(_obj.sirenUse);
    file:PutInt32(_obj.lightsUse);
end

function ItsVehicleEmergencyExtensions_size()
    local _size = 0;
    _size = _size + SIZE_OF_INT32;  --responseType
    _size = _size + SIZE_OF_INT32;  --sirenUse
    _size = _size + SIZE_OF_INT32;  --lightsUse
    return _size;
end

