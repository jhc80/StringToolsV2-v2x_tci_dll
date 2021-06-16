function ItsConnectingLane_to_lua(data)
    local _obj={};
    _obj.laneId = data:GetUInt32();
    _obj.maueuvers = data:GetUInt16();
    return _obj;
end

function lua_to_ItsConnectingLane(_obj,file)
    file:PutUInt32(_obj.laneId);
    file:PutUInt16(_obj.maueuvers);
end

function ItsConnectingLane_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT32;  --laneId
    _size = _size + SIZE_OF_UINT16;  --maueuvers
    return _size;
end

