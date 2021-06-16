function ItsPathPoint_to_lua(data)
    local _obj={};
    _obj.lat = data:GetInt32();
    _obj.lon = data:GetInt32();
    _obj.elev = data:GetInt32();
    return _obj;
end

function lua_to_ItsPathPoint(_obj,file)
    file:PutInt32(_obj.lat);
    file:PutInt32(_obj.lon);
    file:PutInt32(_obj.elev);
end

function ItsPathPoint_size()
    local _size = 0;
    _size = _size + SIZE_OF_INT32;  --lat
    _size = _size + SIZE_OF_INT32;  --lon
    _size = _size + SIZE_OF_INT32;  --elev
    return _size;
end

