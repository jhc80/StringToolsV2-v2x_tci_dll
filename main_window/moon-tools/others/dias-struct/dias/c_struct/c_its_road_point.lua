function ItsRoadPoint_to_lua(data)
    local _obj={};
    _obj.offsetLLPresent = data:GetUInt8();
    _obj.pointLat = data:GetInt32();
    _obj.pointLon = data:GetInt32();
    _obj.offsetVPresent = data:GetUInt8();
    _obj.pointElv = data:GetInt32();
    _obj.attributesLocalPointCount = data:GetUInt8();

    _obj.attributesLocalPoint={}
    for i=1,_obj.attributesLocalPointCount,1 do
        _obj.attributesLocalPoint[i] = data:GetInt32();
    end
    data:Skip((MaxPointAttributesNum-_obj.attributesLocalPointCount)*SIZE_OF_INT32);

    return _obj;
end

function lua_to_ItsRoadPoint(_obj,file)
    file:PutUInt8(_obj.offsetLLPresent);
    file:PutInt32(_obj.pointLat);
    file:PutInt32(_obj.pointLon);
    file:PutUInt8(_obj.offsetVPresent);
    file:PutInt32(_obj.pointElv);
    file:PutUInt8(_obj.attributesLocalPointCount);

    for i=1,_obj.attributesLocalPointCount,1 do
        file:PutInt32(_obj.attributesLocalPoint[i]);
    end
    file:FillBlock((MaxPointAttributesNum-_obj.attributesLocalPointCount)*SIZE_OF_INT32,0);

end

function ItsRoadPoint_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT8;  --offsetLLPresent
    _size = _size + SIZE_OF_INT32;  --pointLat
    _size = _size + SIZE_OF_INT32;  --pointLon
    _size = _size + SIZE_OF_UINT8;  --offsetVPresent
    _size = _size + SIZE_OF_INT32;  --pointElv
    _size = _size + SIZE_OF_UINT8;  --attributesLocalPointCount
    _size = _size + MaxPointAttributesNum*SIZE_OF_INT32;  --attributesLocalPoint
    return _size;
end

