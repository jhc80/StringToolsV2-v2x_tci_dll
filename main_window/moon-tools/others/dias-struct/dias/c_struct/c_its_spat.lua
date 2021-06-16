function ItsSpat_to_lua(data)
    local _obj={};
    _obj.msgCnt = data:GetUInt8();
    _obj.moy = data:GetUInt32();
    _obj.timeStamp = data:GetUInt32();

    local _size = SIZE_OF_UINT8*MAX_NAME_LEN;
    local _tmp = new_mem(_size);
    data:Read(_tmp,_size);
    _obj.name = _tmp:CStr();

    _obj.intersectionCnt = data:GetUInt8();

    _obj.intersections={}
    for i=1,_obj.intersectionCnt,1 do
        _obj.intersections[i] = ItsIntersectionState_to_lua(data);
    end
    data:Skip((MAX_INTERSECTION_NUMBER-_obj.intersectionCnt)*ItsIntersectionState_size());

    return _obj;
end

function lua_to_ItsSpat(_obj,file)
    file:PutUInt8(_obj.msgCnt);
    file:PutUInt32(_obj.moy);
    file:PutUInt32(_obj.timeStamp);

    local _mem = Mem.new();
    _mem:SetRawBuf(_obj.name);
    local _size = SIZE_OF_UINT8*MAX_NAME_LEN;
    file:Write(_mem,_size);
    if _size > _mem:GetSize() then
        file:FillBlock(_size-_mem:GetSize(),0);
    end

    file:PutUInt8(_obj.intersectionCnt);

    for i=1,_obj.intersectionCnt,1 do
        lua_to_ItsIntersectionState(_obj.intersections[i],file);
    end
    file:FillBlock((MAX_INTERSECTION_NUMBER-_obj.intersectionCnt)*ItsIntersectionState_size(),0);

end

function ItsSpat_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT8;  --msgCnt
    _size = _size + SIZE_OF_UINT32;  --moy
    _size = _size + SIZE_OF_UINT32;  --timeStamp
    _size = _size + MAX_NAME_LEN*SIZE_OF_UINT8;  --name
    _size = _size + SIZE_OF_UINT8;  --intersectionCnt
    _size = _size + MAX_INTERSECTION_NUMBER*ItsIntersectionState_size();  --intersections
    return _size;
end

