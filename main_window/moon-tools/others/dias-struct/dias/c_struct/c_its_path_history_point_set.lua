function ItsPathHistoryPointSet_to_lua(data)
    local _obj={};
    _obj.latitude = data:GetInt32();
    _obj.longitute = data:GetInt32();
    _obj.elevationOffset = data:GetInt32();
    _obj.timeOffset = data:GetUInt16();
    _obj.speed = data:GetUInt16();
    _obj.positionConfidence = data:GetUInt8();
    _obj.elevationConfidence = data:GetUInt8();
    _obj.coarseHeading = data:GetUInt8();
    return _obj;
end

function lua_to_ItsPathHistoryPointSet(_obj,file)
    file:PutInt32(_obj.latitude);
    file:PutInt32(_obj.longitute);
    file:PutInt32(_obj.elevationOffset);
    file:PutUInt16(_obj.timeOffset);
    file:PutUInt16(_obj.speed);
    file:PutUInt8(_obj.positionConfidence);
    file:PutUInt8(_obj.elevationConfidence);
    file:PutUInt8(_obj.coarseHeading);
end

function ItsPathHistoryPointSet_size()
    local _size = 0;
    _size = _size + SIZE_OF_INT32;  --latitude
    _size = _size + SIZE_OF_INT32;  --longitute
    _size = _size + SIZE_OF_INT32;  --elevationOffset
    _size = _size + SIZE_OF_UINT16;  --timeOffset
    _size = _size + SIZE_OF_UINT16;  --speed
    _size = _size + SIZE_OF_UINT8;  --positionConfidence
    _size = _size + SIZE_OF_UINT8;  --elevationConfidence
    _size = _size + SIZE_OF_UINT8;  --coarseHeading
    return _size;
end

