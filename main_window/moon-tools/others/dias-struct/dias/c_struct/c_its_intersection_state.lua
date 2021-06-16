function ItsIntersectionState_to_lua(data)
    local _obj={};
    _obj.intersectionId = ItsIntersectionState_id_to_lua(data);
    _obj.status = data:GetUInt32();
    _obj.moy = data:GetUInt32();
    _obj.timeStamp = data:GetUInt32();
    _obj.timeConfidence = data:GetInt32();
    _obj.signalGroupsCnt = data:GetUInt8();

    _obj.states={}
    for i=1,_obj.signalGroupsCnt,1 do
        _obj.states[i] = ItsPhase_to_lua(data);
    end
    data:Skip((SIGNAL_GROUPS_NUMBER-_obj.signalGroupsCnt)*ItsPhase_size());

    return _obj;
end

function lua_to_ItsIntersectionState(_obj,file)
    lua_to_ItsIntersectionState_id(_obj.intersectionId,file);
    file:PutUInt32(_obj.status);
    file:PutUInt32(_obj.moy);
    file:PutUInt32(_obj.timeStamp);
    file:PutInt32(_obj.timeConfidence);
    file:PutUInt8(_obj.signalGroupsCnt);

    for i=1,_obj.signalGroupsCnt,1 do
        lua_to_ItsPhase(_obj.states[i],file);
    end
    file:FillBlock((SIGNAL_GROUPS_NUMBER-_obj.signalGroupsCnt)*ItsPhase_size(),0);

end

function ItsIntersectionState_size()
    local _size = 0;
    _size = _size + ItsIntersectionState_id_size();  --intersectionId
    _size = _size + SIZE_OF_UINT32;  --status
    _size = _size + SIZE_OF_UINT32;  --moy
    _size = _size + SIZE_OF_UINT32;  --timeStamp
    _size = _size + SIZE_OF_INT32;  --timeConfidence
    _size = _size + SIZE_OF_UINT8;  --signalGroupsCnt
    _size = _size + SIGNAL_GROUPS_NUMBER*ItsPhase_size();  --states
    return _size;
end

