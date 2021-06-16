function ItsVehicleClassification_to_lua(data)
    local _obj={};
    _obj.classification = data:GetUInt16();
    _obj.fuelType = data:GetUInt16();
    return _obj;
end

function lua_to_ItsVehicleClassification(_obj,file)
    file:PutUInt16(_obj.classification);
    file:PutUInt16(_obj.fuelType);
end

function ItsVehicleClassification_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT16;  --classification
    _size = _size + SIZE_OF_UINT16;  --fuelType
    return _size;
end

