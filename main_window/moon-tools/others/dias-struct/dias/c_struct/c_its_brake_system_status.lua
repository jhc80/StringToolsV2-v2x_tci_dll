function ItsBrakeSystemStatus_to_lua(data)
    local _obj={};
    _obj.brakePadel = data:GetInt32();
    _obj.wheelBrakes = data:GetInt32();
    _obj.traction = data:GetInt32();
    _obj.abs = data:GetInt32();
    _obj.scs = data:GetInt32();
    _obj.brakeBoost = data:GetInt32();
    _obj.auxBrakes = data:GetInt32();
    return _obj;
end

function lua_to_ItsBrakeSystemStatus(_obj,file)
    file:PutInt32(_obj.brakePadel);
    file:PutInt32(_obj.wheelBrakes);
    file:PutInt32(_obj.traction);
    file:PutInt32(_obj.abs);
    file:PutInt32(_obj.scs);
    file:PutInt32(_obj.brakeBoost);
    file:PutInt32(_obj.auxBrakes);
end

function ItsBrakeSystemStatus_size()
    local _size = 0;
    _size = _size + SIZE_OF_INT32;  --brakePadel
    _size = _size + SIZE_OF_INT32;  --wheelBrakes
    _size = _size + SIZE_OF_INT32;  --traction
    _size = _size + SIZE_OF_INT32;  --abs
    _size = _size + SIZE_OF_INT32;  --scs
    _size = _size + SIZE_OF_INT32;  --brakeBoost
    _size = _size + SIZE_OF_INT32;  --auxBrakes
    return _size;
end

