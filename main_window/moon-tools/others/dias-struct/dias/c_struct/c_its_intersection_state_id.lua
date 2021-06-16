function ItsIntersectionState_id_to_lua(data)
    local _obj={};
    _obj.region_id = data:GetUInt16();
    _obj.id = data:GetUInt16();
    return _obj;
end

function lua_to_ItsIntersectionState_id(_obj,file)
    file:PutUInt16(_obj.region_id);
    file:PutUInt16(_obj.id);
end

function ItsIntersectionState_id_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT16;  --region_id
    _size = _size + SIZE_OF_UINT16;  --id
    return _size;
end

