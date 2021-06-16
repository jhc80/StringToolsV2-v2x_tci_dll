function ItsReferenceLink_to_lua(data)
    local _obj={};
    _obj.upRegionID = data:GetUInt16();
    _obj.upNodeID = data:GetUInt16();
    _obj.downRegionID = data:GetUInt16();
    _obj.downNodeID = data:GetUInt16();
    _obj.refenenceLanes = data:GetUInt16();
    return _obj;
end

function lua_to_ItsReferenceLink(_obj,file)
    file:PutUInt16(_obj.upRegionID);
    file:PutUInt16(_obj.upNodeID);
    file:PutUInt16(_obj.downRegionID);
    file:PutUInt16(_obj.downNodeID);
    file:PutUInt16(_obj.refenenceLanes);
end

function ItsReferenceLink_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT16;  --upRegionID
    _size = _size + SIZE_OF_UINT16;  --upNodeID
    _size = _size + SIZE_OF_UINT16;  --downRegionID
    _size = _size + SIZE_OF_UINT16;  --downNodeID
    _size = _size + SIZE_OF_UINT16;  --refenenceLanes
    return _size;
end

