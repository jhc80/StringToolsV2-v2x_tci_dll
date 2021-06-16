function ItsAccelerationSet4Way_to_lua(data)
    local _obj={};
    _obj.Long = data:GetInt16();
    _obj.lat = data:GetInt16();
    _obj.vert = data:GetInt16();
    _obj.yaw = data:GetInt16();
    return _obj;
end

function lua_to_ItsAccelerationSet4Way(_obj,file)
    file:PutInt16(_obj.Long);
    file:PutInt16(_obj.lat);
    file:PutInt16(_obj.vert);
    file:PutInt16(_obj.yaw);
end

function ItsAccelerationSet4Way_size()
    local _size = 0;
    _size = _size + SIZE_OF_INT16;  --Long
    _size = _size + SIZE_OF_INT16;  --lat
    _size = _size + SIZE_OF_INT16;  --vert
    _size = _size + SIZE_OF_INT16;  --yaw
    return _size;
end

