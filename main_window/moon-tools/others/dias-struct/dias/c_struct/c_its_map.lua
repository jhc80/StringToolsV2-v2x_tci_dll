function ItsMap_to_lua(data)
    local _obj={};
    _obj.standardId = data:GetUInt8();
    _obj.msgCount = data:GetUInt32();
    _obj.layerId = data:GetUInt32();
    _obj.layerType = data:GetInt64();
    _obj.timestamp = data:GetUInt32();
    _obj.intersectionCount = data:GetUInt32();

    _obj.intersections={}
    for i=1,_obj.intersectionCount,1 do
        _obj.intersections[i] = ItsIntersection_to_lua(data);
    end
    data:Skip((MaxIntersectionGeometryNum-_obj.intersectionCount)*ItsIntersection_size());

    return _obj;
end

function lua_to_ItsMap(_obj,file)
    file:PutUInt8(_obj.standardId);
    file:PutUInt32(_obj.msgCount);
    file:PutUInt32(_obj.layerId);
    file:PutInt64(_obj.layerType);
    file:PutUInt32(_obj.timestamp);
    file:PutUInt32(_obj.intersectionCount);

    for i=1,_obj.intersectionCount,1 do
        lua_to_ItsIntersection(_obj.intersections[i],file);
    end
    file:FillBlock((MaxIntersectionGeometryNum-_obj.intersectionCount)*ItsIntersection_size(),0);

end

function ItsMap_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT8;  --standardId
    _size = _size + SIZE_OF_UINT32;  --msgCount
    _size = _size + SIZE_OF_UINT32;  --layerId
    _size = _size + SIZE_OF_INT64;  --layerType
    _size = _size + SIZE_OF_UINT32;  --timestamp
    _size = _size + SIZE_OF_UINT32;  --intersectionCount
    _size = _size + MaxIntersectionGeometryNum*ItsIntersection_size();  --intersections
    return _size;
end

