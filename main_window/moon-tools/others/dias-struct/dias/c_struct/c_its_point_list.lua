function ItsPointList_to_lua(data)
    local _obj={};
    _obj.pointCount = data:GetInt32();
    _obj.present = data:GetInt32();

    _obj.points={}
    for i=1,_obj.pointCount,1 do
        _obj.points[i] = ItsRoadPoint_to_lua(data);
    end
    data:Skip((MaxPointNum-_obj.pointCount)*ItsRoadPoint_size());

    _obj.computedLane = ItsComputedLane_to_lua(data);
    return _obj;
end

function lua_to_ItsPointList(_obj,file)
    file:PutInt32(_obj.pointCount);
    file:PutInt32(_obj.present);

    for i=1,_obj.pointCount,1 do
        lua_to_ItsRoadPoint(_obj.points[i],file);
    end
    file:FillBlock((MaxPointNum-_obj.pointCount)*ItsRoadPoint_size(),0);

    lua_to_ItsComputedLane(_obj.computedLane,file);
end

function ItsPointList_size()
    local _size = 0;
    _size = _size + SIZE_OF_INT32;  --pointCount
    _size = _size + SIZE_OF_INT32;  --present
    _size = _size + MaxPointNum*ItsRoadPoint_size();  --points
    _size = _size + ItsComputedLane_size();  --computedLane
    return _size;
end

