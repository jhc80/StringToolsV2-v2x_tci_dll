function ItsPhaseState_to_lua(data)
    local _obj={};
    _obj.light = data:GetUInt32();
    _obj.timingFlag = data:GetUInt32();
    _obj.timing = ItsTimeCountingDown_to_lua(data);
    _obj.utcTiming = ItsUTCTiming_to_lua(data);
    return _obj;
end

function lua_to_ItsPhaseState(_obj,file)
    file:PutUInt32(_obj.light);
    file:PutUInt32(_obj.timingFlag);
    lua_to_ItsTimeCountingDown(_obj.timing,file);
    lua_to_ItsUTCTiming(_obj.utcTiming,file);
end

function ItsPhaseState_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT32;  --light
    _size = _size + SIZE_OF_UINT32;  --timingFlag
    _size = _size + ItsTimeCountingDown_size();  --timing
    _size = _size + ItsUTCTiming_size();  --utcTiming
    return _size;
end

