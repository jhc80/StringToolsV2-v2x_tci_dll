function ItsPhase_to_lua(data)
    local _obj={};
    _obj.id = data:GetUInt8();
    _obj.phaseStateCnt = data:GetUInt8();

    _obj.phaseStates={}
    for i=1,_obj.phaseStateCnt,1 do
        _obj.phaseStates[i] = ItsPhaseState_to_lua(data);
    end
    data:Skip((16-_obj.phaseStateCnt)*ItsPhaseState_size());

    return _obj;
end

function lua_to_ItsPhase(_obj,file)
    file:PutUInt8(_obj.id);
    file:PutUInt8(_obj.phaseStateCnt);

    for i=1,_obj.phaseStateCnt,1 do
        lua_to_ItsPhaseState(_obj.phaseStates[i],file);
    end
    file:FillBlock((16-_obj.phaseStateCnt)*ItsPhaseState_size(),0);

end

function ItsPhase_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT8;  --id
    _size = _size + SIZE_OF_UINT8;  --phaseStateCnt
    _size = _size + 16*ItsPhaseState_size();  --phaseStates
    return _size;
end

