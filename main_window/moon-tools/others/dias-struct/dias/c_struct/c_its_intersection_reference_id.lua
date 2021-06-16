function ItsIntersectionReferenceId_to_lua(data)
    local _obj={};
    _obj.region = data:GetUInt32();
    _obj.intersectionId = data:GetUInt32();
    return _obj;
end

function lua_to_ItsIntersectionReferenceId(_obj,file)
    file:PutUInt32(_obj.region);
    file:PutUInt32(_obj.intersectionId);
end

function ItsIntersectionReferenceId_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT32;  --region
    _size = _size + SIZE_OF_UINT32;  --intersectionId
    return _size;
end

