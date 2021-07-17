function ItsBsm_to_lua(data)
    local _obj={};
    _obj.msgCnt = data:GetUInt8();

    local _size = SIZE_OF_UINT8*VEHICLE_ID_LEN;
    _obj.id = new_mem(_size);
    data:Read(_obj.id,_size);

    _obj.plateLen = data:GetUInt8();

    local _size = SIZE_OF_UINT8*_obj.plateLen;
    _obj.plateNo = new_mem(_size);
    data:Read(_obj.plateNo,_size);
    data:Skip((16-_obj.plateLen)*SIZE_OF_UINT8);

    _obj.timeStamp = data:GetUInt32();
    _obj.timeConfidence = data:GetInt32();
    _obj.pos = ItsPosition3D_to_lua(data);
    _obj.posAccuracy = ItsPositionalAccuracy_to_lua(data);
    _obj.posConfidence = ItsPositionConfidenceSet_to_lua(data);
    _obj.transmission = data:GetInt32();
    _obj.Speed = data:GetUInt16();
    _obj.Heading = data:GetUInt16();
    _obj.angle = data:GetInt16();
    _obj.motionCfd = ItsMotionConfidenceSet_to_lua(data);
    _obj.accelSet = ItsAccelerationSet4Way_to_lua(data);
    _obj.brakes = ItsBrakeSystemStatus_to_lua(data);
    _obj.size = ItsVehicleSize_to_lua(data);
    _obj.vehicleClass = ItsVehicleClassification_to_lua(data);
    _obj.safetyExt = ItsVehicleSafetyExtensions_to_lua(data);
    _obj.emergencyExt = ItsVehicleEmergencyExtensions_to_lua(data);
    return _obj;
end

function lua_to_ItsBsm(_obj,file)
    file:PutUInt8(_obj.msgCnt);

    local _size = SIZE_OF_UINT8*VEHICLE_ID_LEN;
    if _obj.id == nil then
        file:FillBlock(_size,0);
    else
        file:Write(_obj.id,_size);
        if _size > _obj.id:GetSize() then
            file:FillBlock(_size-_obj.id:GetSize(),0);
        end
    end

    file:PutUInt8(_obj.plateLen);

    local _size = SIZE_OF_UINT8*_obj.plateLen;
    if _obj.plateNo == nil then
        file:FillBlock(_size,0);
    else
        file:Write(_obj.plateNo,_size);
        if _size > _obj.plateNo:GetSize() then
            file:FillBlock(_size-_obj.plateNo:GetSize(),0);
        end
    end
    file:FillBlock((16-_obj.plateLen)*SIZE_OF_UINT8,0);

    file:PutUInt32(_obj.timeStamp);
    file:PutInt32(_obj.timeConfidence);
    lua_to_ItsPosition3D(_obj.pos,file);
    lua_to_ItsPositionalAccuracy(_obj.posAccuracy,file);
    lua_to_ItsPositionConfidenceSet(_obj.posConfidence,file);
    file:PutInt32(_obj.transmission);
    file:PutUInt16(_obj.Speed);
    file:PutUInt16(_obj.Heading);
    file:PutInt16(_obj.angle);
    lua_to_ItsMotionConfidenceSet(_obj.motionCfd,file);
    lua_to_ItsAccelerationSet4Way(_obj.accelSet,file);
    lua_to_ItsBrakeSystemStatus(_obj.brakes,file);
    lua_to_ItsVehicleSize(_obj.size,file);
    lua_to_ItsVehicleClassification(_obj.vehicleClass,file);
    lua_to_ItsVehicleSafetyExtensions(_obj.safetyExt,file);
    lua_to_ItsVehicleEmergencyExtensions(_obj.emergencyExt,file);
end

function ItsBsm_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT8;  --msgCnt
    _size = _size + VEHICLE_ID_LEN*SIZE_OF_UINT8;  --id
    _size = _size + SIZE_OF_UINT8;  --plateLen
    _size = _size + 16*SIZE_OF_UINT8;  --plateNo
    _size = _size + SIZE_OF_UINT32;  --timeStamp
    _size = _size + SIZE_OF_INT32;  --timeConfidence
    _size = _size + ItsPosition3D_size();  --pos
    _size = _size + ItsPositionalAccuracy_size();  --posAccuracy
    _size = _size + ItsPositionConfidenceSet_size();  --posConfidence
    _size = _size + SIZE_OF_INT32;  --transmission
    _size = _size + SIZE_OF_UINT16;  --Speed
    _size = _size + SIZE_OF_UINT16;  --Heading
    _size = _size + SIZE_OF_INT16;  --angle
    _size = _size + ItsMotionConfidenceSet_size();  --motionCfd
    _size = _size + ItsAccelerationSet4Way_size();  --accelSet
    _size = _size + ItsBrakeSystemStatus_size();  --brakes
    _size = _size + ItsVehicleSize_size();  --size
    _size = _size + ItsVehicleClassification_size();  --vehicleClass
    _size = _size + ItsVehicleSafetyExtensions_size();  --safetyExt
    _size = _size + ItsVehicleEmergencyExtensions_size();  --emergencyExt
    return _size;
end

