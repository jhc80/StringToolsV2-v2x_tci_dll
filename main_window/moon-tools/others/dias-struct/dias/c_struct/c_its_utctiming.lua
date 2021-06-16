function ItsUTCTiming_to_lua(data)
    local _obj={};
    _obj.startTime = data:GetUInt32();
    _obj.minEndTime = data:GetUInt32();
    _obj.maxEndTime = data:GetUInt32();
    _obj.likelyEndTime = data:GetUInt32();
    _obj.timeConfidence = data:GetInt32();
    _obj.nextStartTime = data:GetUInt32();
    _obj.nextEndTime = data:GetUInt32();
    return _obj;
end

function lua_to_ItsUTCTiming(_obj,file)
    file:PutUInt32(_obj.startTime);
    file:PutUInt32(_obj.minEndTime);
    file:PutUInt32(_obj.maxEndTime);
    file:PutUInt32(_obj.likelyEndTime);
    file:PutInt32(_obj.timeConfidence);
    file:PutUInt32(_obj.nextStartTime);
    file:PutUInt32(_obj.nextEndTime);
end

function ItsUTCTiming_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT32;  --startTime
    _size = _size + SIZE_OF_UINT32;  --minEndTime
    _size = _size + SIZE_OF_UINT32;  --maxEndTime
    _size = _size + SIZE_OF_UINT32;  --likelyEndTime
    _size = _size + SIZE_OF_INT32;  --timeConfidence
    _size = _size + SIZE_OF_UINT32;  --nextStartTime
    _size = _size + SIZE_OF_UINT32;  --nextEndTime
    return _size;
end

