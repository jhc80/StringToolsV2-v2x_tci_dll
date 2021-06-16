function ItsPsm_to_lua(data)
    local _obj={};
    _obj.msgCnt = data:GetUInt8();
    _obj.participantNum = data:GetUInt8();
    _obj.id = data:GetUInt64();
    _obj.latitude = data:GetInt32();
    _obj.longitude = data:GetInt32();
    _obj.elevation = data:GetInt32();

    _obj.participants={}
    for i=1,_obj.participantNum,1 do
        _obj.participants[i] = ItsParticipant_to_lua(data);
    end
    data:Skip((MAX_PARTICIPANT_NUMBER-_obj.participantNum)*ItsParticipant_size());

    return _obj;
end

function lua_to_ItsPsm(_obj,file)
    file:PutUInt8(_obj.msgCnt);
    file:PutUInt8(_obj.participantNum);
    file:PutUInt64(_obj.id);
    file:PutInt32(_obj.latitude);
    file:PutInt32(_obj.longitude);
    file:PutInt32(_obj.elevation);

    for i=1,_obj.participantNum,1 do
        lua_to_ItsParticipant(_obj.participants[i],file);
    end
    file:FillBlock((MAX_PARTICIPANT_NUMBER-_obj.participantNum)*ItsParticipant_size(),0);

end

function ItsPsm_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT8;  --msgCnt
    _size = _size + SIZE_OF_UINT8;  --participantNum
    _size = _size + SIZE_OF_UINT64;  --id
    _size = _size + SIZE_OF_INT32;  --latitude
    _size = _size + SIZE_OF_INT32;  --longitude
    _size = _size + SIZE_OF_INT32;  --elevation
    _size = _size + MAX_PARTICIPANT_NUMBER*ItsParticipant_size();  --participants
    return _size;
end

