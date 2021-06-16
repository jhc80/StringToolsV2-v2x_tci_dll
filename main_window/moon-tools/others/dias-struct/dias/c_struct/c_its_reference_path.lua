function ItsReferencePath_to_lua(data)
    local _obj={};
    _obj.pathRadius = data:GetUInt16();
    _obj.pathPointNum = data:GetUInt8();

    _obj.pathPoint={}
    for i=1,_obj.pathPointNum,1 do
        _obj.pathPoint[i] = ItsPathPoint_to_lua(data);
    end
    data:Skip((MAX_PATHPOINT_NUMBER-_obj.pathPointNum)*ItsPathPoint_size());

    return _obj;
end

function lua_to_ItsReferencePath(_obj,file)
    file:PutUInt16(_obj.pathRadius);
    file:PutUInt8(_obj.pathPointNum);

    for i=1,_obj.pathPointNum,1 do
        lua_to_ItsPathPoint(_obj.pathPoint[i],file);
    end
    file:FillBlock((MAX_PATHPOINT_NUMBER-_obj.pathPointNum)*ItsPathPoint_size(),0);

end

function ItsReferencePath_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT16;  --pathRadius
    _size = _size + SIZE_OF_UINT8;  --pathPointNum
    _size = _size + MAX_PATHPOINT_NUMBER*ItsPathPoint_size();  --pathPoint
    return _size;
end

