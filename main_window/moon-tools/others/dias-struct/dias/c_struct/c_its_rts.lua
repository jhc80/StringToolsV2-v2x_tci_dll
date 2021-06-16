function ItsRts_to_lua(data)
    local _obj={};
    _obj.rtsId = data:GetUInt8();
    _obj.signType = data:GetUInt8();
    _obj.referencePathNum = data:GetUInt8();
    _obj.referenceLinkNum = data:GetUInt8();
    _obj.latitude = data:GetInt32();
    _obj.longitude = data:GetInt32();
    _obj.elevation = data:GetInt32();
    _obj.startTime = data:GetUInt32();
    _obj.endTime = data:GetUInt32();
    _obj.endTimeCfd = data:GetUInt8();
    _obj.priority = data:GetUInt8();
    _obj.descriptType = data:GetUInt8();
    _obj.descriptLength = data:GetUInt8();

    _obj.referencePath={}
    for i=1,_obj.referencePathNum,1 do
        _obj.referencePath[i] = ItsReferencePath_to_lua(data);
    end
    data:Skip((MAX_REFERENCEPATH_COUNT-_obj.referencePathNum)*ItsReferencePath_size());


    _obj.referenceLink={}
    for i=1,_obj.referenceLinkNum,1 do
        _obj.referenceLink[i] = ItsReferenceLink_to_lua(data);
    end
    data:Skip((MAX_REFERENCELINK_COUNT-_obj.referenceLinkNum)*ItsReferenceLink_size());


    local _size = SIZE_OF_INT8*_obj.descriptLength;
    local _tmp = new_mem(_size);
    data:Read(_tmp,_size);
    _obj.description = _tmp:CStr();
    data:Skip((MAX_DESCRIPTION_LENGTH-_obj.descriptLength)*SIZE_OF_INT8);

    return _obj;
end

function lua_to_ItsRts(_obj,file)
    file:PutUInt8(_obj.rtsId);
    file:PutUInt8(_obj.signType);
    file:PutUInt8(_obj.referencePathNum);
    file:PutUInt8(_obj.referenceLinkNum);
    file:PutInt32(_obj.latitude);
    file:PutInt32(_obj.longitude);
    file:PutInt32(_obj.elevation);
    file:PutUInt32(_obj.startTime);
    file:PutUInt32(_obj.endTime);
    file:PutUInt8(_obj.endTimeCfd);
    file:PutUInt8(_obj.priority);
    file:PutUInt8(_obj.descriptType);
    file:PutUInt8(_obj.descriptLength);

    for i=1,_obj.referencePathNum,1 do
        lua_to_ItsReferencePath(_obj.referencePath[i],file);
    end
    file:FillBlock((MAX_REFERENCEPATH_COUNT-_obj.referencePathNum)*ItsReferencePath_size(),0);


    for i=1,_obj.referenceLinkNum,1 do
        lua_to_ItsReferenceLink(_obj.referenceLink[i],file);
    end
    file:FillBlock((MAX_REFERENCELINK_COUNT-_obj.referenceLinkNum)*ItsReferenceLink_size(),0);


    local _mem = Mem.new();
    _mem:SetRawBuf(_obj.description);
    local _size = SIZE_OF_INT8*_obj.descriptLength;
    file:Write(_mem,_size);
    if _size > _mem:GetSize() then
        file:FillBlock(_size-_mem:GetSize(),0);
    end
    file:FillBlock((MAX_DESCRIPTION_LENGTH-_obj.descriptLength)*SIZE_OF_INT8,0);

end

function ItsRts_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT8;  --rtsId
    _size = _size + SIZE_OF_UINT8;  --signType
    _size = _size + SIZE_OF_UINT8;  --referencePathNum
    _size = _size + SIZE_OF_UINT8;  --referenceLinkNum
    _size = _size + SIZE_OF_INT32;  --latitude
    _size = _size + SIZE_OF_INT32;  --longitude
    _size = _size + SIZE_OF_INT32;  --elevation
    _size = _size + SIZE_OF_UINT32;  --startTime
    _size = _size + SIZE_OF_UINT32;  --endTime
    _size = _size + SIZE_OF_UINT8;  --endTimeCfd
    _size = _size + SIZE_OF_UINT8;  --priority
    _size = _size + SIZE_OF_UINT8;  --descriptType
    _size = _size + SIZE_OF_UINT8;  --descriptLength
    _size = _size + MAX_REFERENCEPATH_COUNT*ItsReferencePath_size();  --referencePath
    _size = _size + MAX_REFERENCELINK_COUNT*ItsReferenceLink_size();  --referenceLink
    _size = _size + MAX_DESCRIPTION_LENGTH*SIZE_OF_INT8;  --description
    return _size;
end

