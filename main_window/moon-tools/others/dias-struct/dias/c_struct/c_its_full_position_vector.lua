function ItsFullPositionVector_to_lua(data)
    local _obj={};
    _obj.utcTime = ItsDDateTime_to_lua(data);
    _obj.longitute = data:GetInt32();
    _obj.latitude = data:GetInt32();
    _obj.elevation = data:GetUInt16();
    _obj.heading = data:GetInt32();
    _obj.speed = data:GetUInt16();
    _obj.posAccuracy = data:GetUInt32();
    _obj.timeConfidence = data:GetInt32();
    _obj.posConfidence = data:GetUInt8();
    _obj.speedConfidence = data:GetUInt8();
    _obj.headingConfidence = data:GetUInt8();
    _obj.steerConfidence = data:GetUInt8();
    _obj.transmission = data:GetUInt8();
    return _obj;
end

function lua_to_ItsFullPositionVector(_obj,file)
    lua_to_ItsDDateTime(_obj.utcTime,file);
    file:PutInt32(_obj.longitute);
    file:PutInt32(_obj.latitude);
    file:PutUInt16(_obj.elevation);
    file:PutInt32(_obj.heading);
    file:PutUInt16(_obj.speed);
    file:PutUInt32(_obj.posAccuracy);
    file:PutInt32(_obj.timeConfidence);
    file:PutUInt8(_obj.posConfidence);
    file:PutUInt8(_obj.speedConfidence);
    file:PutUInt8(_obj.headingConfidence);
    file:PutUInt8(_obj.steerConfidence);
    file:PutUInt8(_obj.transmission);
end

function ItsFullPositionVector_size()
    local _size = 0;
    _size = _size + ItsDDateTime_size();  --utcTime
    _size = _size + SIZE_OF_INT32;  --longitute
    _size = _size + SIZE_OF_INT32;  --latitude
    _size = _size + SIZE_OF_UINT16;  --elevation
    _size = _size + SIZE_OF_INT32;  --heading
    _size = _size + SIZE_OF_UINT16;  --speed
    _size = _size + SIZE_OF_UINT32;  --posAccuracy
    _size = _size + SIZE_OF_INT32;  --timeConfidence
    _size = _size + SIZE_OF_UINT8;  --posConfidence
    _size = _size + SIZE_OF_UINT8;  --speedConfidence
    _size = _size + SIZE_OF_UINT8;  --headingConfidence
    _size = _size + SIZE_OF_UINT8;  --steerConfidence
    _size = _size + SIZE_OF_UINT8;  --transmission
    return _size;
end

