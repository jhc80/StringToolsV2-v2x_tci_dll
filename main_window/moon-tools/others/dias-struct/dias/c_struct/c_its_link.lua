function ItsLink_to_lua(data)
    local _obj={};
    _obj.upstreamNodeId = ItsIntersectionReferenceId_to_lua(data);
    _obj.linkWidth = data:GetUInt32();
    _obj.speedLimitCount = data:GetUInt8();

    _obj.speedLimitSet={}
    for i=1,_obj.speedLimitCount,1 do
        _obj.speedLimitSet[i] = ItsMapSpeedLimit_to_lua(data);
    end
    data:Skip((MaxSpeedLimitNum-_obj.speedLimitCount)*ItsMapSpeedLimit_size());

    _obj.inlaneCount = data:GetUInt32();

    _obj.inlaneSet={}
    for i=1,_obj.inlaneCount,1 do
        _obj.inlaneSet[i] = ItsLane_to_lua(data);
    end
    data:Skip((MaxInLaneNum-_obj.inlaneCount)*ItsLane_size());

    _obj.linkPointCount = data:GetUInt8();

    _obj.linkPointSet={}
    for i=1,_obj.linkPointCount,1 do
        _obj.linkPointSet[i] = ItsRoadPoint_to_lua(data);
    end
    data:Skip((MaxLinkPointNum-_obj.linkPointCount)*ItsRoadPoint_size());

    _obj.movementCount = data:GetUInt8();

    _obj.movementSet={}
    for i=1,_obj.movementCount,1 do
        _obj.movementSet[i] = ItsMovement_to_lua(data);
    end
    data:Skip((MaxMovementNum-_obj.movementCount)*ItsMovement_size());

    return _obj;
end

function lua_to_ItsLink(_obj,file)
    lua_to_ItsIntersectionReferenceId(_obj.upstreamNodeId,file);
    file:PutUInt32(_obj.linkWidth);
    file:PutUInt8(_obj.speedLimitCount);

    for i=1,_obj.speedLimitCount,1 do
        lua_to_ItsMapSpeedLimit(_obj.speedLimitSet[i],file);
    end
    file:FillBlock((MaxSpeedLimitNum-_obj.speedLimitCount)*ItsMapSpeedLimit_size(),0);

    file:PutUInt32(_obj.inlaneCount);

    for i=1,_obj.inlaneCount,1 do
        lua_to_ItsLane(_obj.inlaneSet[i],file);
    end
    file:FillBlock((MaxInLaneNum-_obj.inlaneCount)*ItsLane_size(),0);

    file:PutUInt8(_obj.linkPointCount);

    for i=1,_obj.linkPointCount,1 do
        lua_to_ItsRoadPoint(_obj.linkPointSet[i],file);
    end
    file:FillBlock((MaxLinkPointNum-_obj.linkPointCount)*ItsRoadPoint_size(),0);

    file:PutUInt8(_obj.movementCount);

    for i=1,_obj.movementCount,1 do
        lua_to_ItsMovement(_obj.movementSet[i],file);
    end
    file:FillBlock((MaxMovementNum-_obj.movementCount)*ItsMovement_size(),0);

end

function ItsLink_size()
    local _size = 0;
    _size = _size + ItsIntersectionReferenceId_size();  --upstreamNodeId
    _size = _size + SIZE_OF_UINT32;  --linkWidth
    _size = _size + SIZE_OF_UINT8;  --speedLimitCount
    _size = _size + MaxSpeedLimitNum*ItsMapSpeedLimit_size();  --speedLimitSet
    _size = _size + SIZE_OF_UINT32;  --inlaneCount
    _size = _size + MaxInLaneNum*ItsLane_size();  --inlaneSet
    _size = _size + SIZE_OF_UINT8;  --linkPointCount
    _size = _size + MaxLinkPointNum*ItsRoadPoint_size();  --linkPointSet
    _size = _size + SIZE_OF_UINT8;  --movementCount
    _size = _size + MaxMovementNum*ItsMovement_size();  --movementSet
    return _size;
end

