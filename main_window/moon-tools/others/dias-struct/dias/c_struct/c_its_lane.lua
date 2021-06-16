function ItsLane_to_lua(data)
    local _obj={};
    _obj.laneId = data:GetUInt8();
    _obj.laneAttributes = ItsLaneAttributes_to_lua(data);
    _obj.maneuvers = data:GetUInt16();
    _obj.laneWidth = data:GetUInt16();
    _obj.pointList = ItsPointList_to_lua(data);
    _obj.connectCount = data:GetUInt8();

    _obj.connections={}
    for i=1,_obj.connectCount,1 do
        _obj.connections[i] = ItsConnection_to_lua(data);
    end
    data:Skip((MaxConnectionsNum-_obj.connectCount)*ItsConnection_size());

    _obj.laneSpeedLimitCount = data:GetUInt8();

    _obj.laneSpeedLimitSet={}
    for i=1,_obj.laneSpeedLimitCount,1 do
        _obj.laneSpeedLimitSet[i] = ItsMapSpeedLimit_to_lua(data);
    end
    data:Skip((MaxSpeedLimitNum-_obj.laneSpeedLimitCount)*ItsMapSpeedLimit_size());

    return _obj;
end

function lua_to_ItsLane(_obj,file)
    file:PutUInt8(_obj.laneId);
    lua_to_ItsLaneAttributes(_obj.laneAttributes,file);
    file:PutUInt16(_obj.maneuvers);
    file:PutUInt16(_obj.laneWidth);
    lua_to_ItsPointList(_obj.pointList,file);
    file:PutUInt8(_obj.connectCount);

    for i=1,_obj.connectCount,1 do
        lua_to_ItsConnection(_obj.connections[i],file);
    end
    file:FillBlock((MaxConnectionsNum-_obj.connectCount)*ItsConnection_size(),0);

    file:PutUInt8(_obj.laneSpeedLimitCount);

    for i=1,_obj.laneSpeedLimitCount,1 do
        lua_to_ItsMapSpeedLimit(_obj.laneSpeedLimitSet[i],file);
    end
    file:FillBlock((MaxSpeedLimitNum-_obj.laneSpeedLimitCount)*ItsMapSpeedLimit_size(),0);

end

function ItsLane_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT8;  --laneId
    _size = _size + ItsLaneAttributes_size();  --laneAttributes
    _size = _size + SIZE_OF_UINT16;  --maneuvers
    _size = _size + SIZE_OF_UINT16;  --laneWidth
    _size = _size + ItsPointList_size();  --pointList
    _size = _size + SIZE_OF_UINT8;  --connectCount
    _size = _size + MaxConnectionsNum*ItsConnection_size();  --connections
    _size = _size + SIZE_OF_UINT8;  --laneSpeedLimitCount
    _size = _size + MaxSpeedLimitNum*ItsMapSpeedLimit_size();  --laneSpeedLimitSet
    return _size;
end

