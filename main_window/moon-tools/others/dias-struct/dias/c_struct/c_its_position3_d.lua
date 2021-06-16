function ItsPosition3D_to_lua(data)
    local _obj={};
    _obj.latitude = data:GetInt32();
    _obj.longitude = data:GetInt32();
    _obj.elevation = data:GetInt32();
    return _obj;
end

function lua_to_ItsPosition3D(_obj,file)
    file:PutInt32(_obj.latitude);
    file:PutInt32(_obj.longitude);
    file:PutInt32(_obj.elevation);
end

function ItsPosition3D_size()
    local _size = 0;
    _size = _size + SIZE_OF_INT32;  --latitude
    _size = _size + SIZE_OF_INT32;  --longitude
    _size = _size + SIZE_OF_INT32;  --elevation
    return _size;
end

