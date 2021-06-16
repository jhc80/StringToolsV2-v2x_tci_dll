function ItsIntersection_to_lua(data)
    local _obj={};
    _obj.id = ItsIntersectionReferenceId_to_lua(data);
    _obj.revision = data:GetUInt32();
    _obj.refPoint = ItsMapPosition3D_to_lua(data);
    _obj.linkCount = data:GetUInt8();

    _obj.linkSet={}
    for i=1,_obj.linkCount,1 do
        _obj.linkSet[i] = ItsLink_to_lua(data);
    end
    data:Skip((MaxLinkNum-_obj.linkCount)*ItsLink_size());

    return _obj;
end

function lua_to_ItsIntersection(_obj,file)
    lua_to_ItsIntersectionReferenceId(_obj.id,file);
    file:PutUInt32(_obj.revision);
    lua_to_ItsMapPosition3D(_obj.refPoint,file);
    file:PutUInt8(_obj.linkCount);

    for i=1,_obj.linkCount,1 do
        lua_to_ItsLink(_obj.linkSet[i],file);
    end
    file:FillBlock((MaxLinkNum-_obj.linkCount)*ItsLink_size(),0);

end

function ItsIntersection_size()
    local _size = 0;
    _size = _size + ItsIntersectionReferenceId_size();  --id
    _size = _size + SIZE_OF_UINT32;  --revision
    _size = _size + ItsMapPosition3D_size();  --refPoint
    _size = _size + SIZE_OF_UINT8;  --linkCount
    _size = _size + MaxLinkNum*ItsLink_size();  --linkSet
    return _size;
end

