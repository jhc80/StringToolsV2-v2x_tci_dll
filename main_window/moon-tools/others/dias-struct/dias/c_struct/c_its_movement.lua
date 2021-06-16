function ItsMovement_to_lua(data)
    local _obj={};
    _obj.downstreamIntersectionId = ItsIntersectionReferenceId_to_lua(data);
    _obj.phaseId = data:GetUInt8();
    return _obj;
end

function lua_to_ItsMovement(_obj,file)
    lua_to_ItsIntersectionReferenceId(_obj.downstreamIntersectionId,file);
    file:PutUInt8(_obj.phaseId);
end

function ItsMovement_size()
    local _size = 0;
    _size = _size + ItsIntersectionReferenceId_size();  --downstreamIntersectionId
    _size = _size + SIZE_OF_UINT8;  --phaseId
    return _size;
end

