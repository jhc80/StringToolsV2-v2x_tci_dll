function ItsParticipant_to_lua(data)
    local _obj={};
    _obj.ptcType = data:GetUInt8();
    _obj.ptcId = data:GetUInt16();
    _obj.source = data:GetUInt8();
    _obj.id = data:GetUInt64();
    _obj.timestamp = data:GetUInt16();
    _obj.posPresent = data:GetUInt8();
    _obj.latitude = data:GetInt32();
    _obj.longitude = data:GetInt32();
    _obj.elevation = data:GetInt32();
    _obj.posCfd = data:GetUInt8();
    _obj.eleCfd = data:GetUInt8();
    _obj.transmission = data:GetUInt8();
    _obj.speed = data:GetUInt16();
    _obj.heading = data:GetUInt16();
    _obj.angle = data:GetInt8();
    _obj.speedCfd = data:GetUInt8();
    _obj.headingCfd = data:GetUInt8();
    _obj.steerCfd = data:GetUInt8();
    _obj.longAccel = data:GetInt16();
    _obj.latAccel = data:GetInt16();
    _obj.vertAccel = data:GetInt8();
    _obj.yawRate = data:GetInt16();
    _obj.height = data:GetUInt8();
    _obj.width = data:GetUInt16();
    _obj.length = data:GetUInt16();
    _obj.classfication = data:GetUInt8();
    _obj.fuelType = data:GetUInt8();
    return _obj;
end

function lua_to_ItsParticipant(_obj,file)
    file:PutUInt8(_obj.ptcType);
    file:PutUInt16(_obj.ptcId);
    file:PutUInt8(_obj.source);
    file:PutUInt64(_obj.id);
    file:PutUInt16(_obj.timestamp);
    file:PutUInt8(_obj.posPresent);
    file:PutInt32(_obj.latitude);
    file:PutInt32(_obj.longitude);
    file:PutInt32(_obj.elevation);
    file:PutUInt8(_obj.posCfd);
    file:PutUInt8(_obj.eleCfd);
    file:PutUInt8(_obj.transmission);
    file:PutUInt16(_obj.speed);
    file:PutUInt16(_obj.heading);
    file:PutInt8(_obj.angle);
    file:PutUInt8(_obj.speedCfd);
    file:PutUInt8(_obj.headingCfd);
    file:PutUInt8(_obj.steerCfd);
    file:PutInt16(_obj.longAccel);
    file:PutInt16(_obj.latAccel);
    file:PutInt8(_obj.vertAccel);
    file:PutInt16(_obj.yawRate);
    file:PutUInt8(_obj.height);
    file:PutUInt16(_obj.width);
    file:PutUInt16(_obj.length);
    file:PutUInt8(_obj.classfication);
    file:PutUInt8(_obj.fuelType);
end

function ItsParticipant_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT8;  --ptcType
    _size = _size + SIZE_OF_UINT16;  --ptcId
    _size = _size + SIZE_OF_UINT8;  --source
    _size = _size + SIZE_OF_UINT64;  --id
    _size = _size + SIZE_OF_UINT16;  --timestamp
    _size = _size + SIZE_OF_UINT8;  --posPresent
    _size = _size + SIZE_OF_INT32;  --latitude
    _size = _size + SIZE_OF_INT32;  --longitude
    _size = _size + SIZE_OF_INT32;  --elevation
    _size = _size + SIZE_OF_UINT8;  --posCfd
    _size = _size + SIZE_OF_UINT8;  --eleCfd
    _size = _size + SIZE_OF_UINT8;  --transmission
    _size = _size + SIZE_OF_UINT16;  --speed
    _size = _size + SIZE_OF_UINT16;  --heading
    _size = _size + SIZE_OF_INT8;  --angle
    _size = _size + SIZE_OF_UINT8;  --speedCfd
    _size = _size + SIZE_OF_UINT8;  --headingCfd
    _size = _size + SIZE_OF_UINT8;  --steerCfd
    _size = _size + SIZE_OF_INT16;  --longAccel
    _size = _size + SIZE_OF_INT16;  --latAccel
    _size = _size + SIZE_OF_INT8;  --vertAccel
    _size = _size + SIZE_OF_INT16;  --yawRate
    _size = _size + SIZE_OF_UINT8;  --height
    _size = _size + SIZE_OF_UINT16;  --width
    _size = _size + SIZE_OF_UINT16;  --length
    _size = _size + SIZE_OF_UINT8;  --classfication
    _size = _size + SIZE_OF_UINT8;  --fuelType
    return _size;
end

