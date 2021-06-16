function ItsPositionalAccuracy_to_lua(data)
    local _obj={};
    _obj.semiMajor = data:GetInt32();
    _obj.semiMinor = data:GetInt32();
    _obj.orientation = data:GetInt32();
    return _obj;
end

function lua_to_ItsPositionalAccuracy(_obj,file)
    file:PutInt32(_obj.semiMajor);
    file:PutInt32(_obj.semiMinor);
    file:PutInt32(_obj.orientation);
end

function ItsPositionalAccuracy_size()
    local _size = 0;
    _size = _size + SIZE_OF_INT32;  --semiMajor
    _size = _size + SIZE_OF_INT32;  --semiMinor
    _size = _size + SIZE_OF_INT32;  --orientation
    return _size;
end

