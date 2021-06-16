function ItsLaneAttributes_to_lua(data)
    local _obj={};
    _obj.laneDirection = data:GetUInt8();
    _obj.sharedWith = data:GetUInt16();
    _obj.laneType = ItsLaneTypeAttributes_to_lua(data);
    return _obj;
end

function lua_to_ItsLaneAttributes(_obj,file)
    file:PutUInt8(_obj.laneDirection);
    file:PutUInt16(_obj.sharedWith);
    lua_to_ItsLaneTypeAttributes(_obj.laneType,file);
end

function ItsLaneAttributes_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT8;  --laneDirection
    _size = _size + SIZE_OF_UINT16;  --sharedWith
    _size = _size + ItsLaneTypeAttributes_size();  --laneType
    return _size;
end

