function ItsConnection_to_lua(data)
    local _obj={};
    _obj.remoteIntersectionId = ItsIntersectionReferenceId_to_lua(data);
    _obj.connectingLane = ItsConnectingLane_to_lua(data);
    _obj.signalGroupId = data:GetUInt32();
    return _obj;
end

function lua_to_ItsConnection(_obj,file)
    lua_to_ItsIntersectionReferenceId(_obj.remoteIntersectionId,file);
    lua_to_ItsConnectingLane(_obj.connectingLane,file);
    file:PutUInt32(_obj.signalGroupId);
end

function ItsConnection_size()
    local _size = 0;
    _size = _size + ItsIntersectionReferenceId_size();  --remoteIntersectionId
    _size = _size + ItsConnectingLane_size();  --connectingLane
    _size = _size + SIZE_OF_UINT32;  --signalGroupId
    return _size;
end

