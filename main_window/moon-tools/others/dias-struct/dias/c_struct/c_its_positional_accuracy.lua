function ItsPositionalAccuracy_to_lua(data)
    local _obj={};
    _obj.semiMajor = data:GetInt64();
    _obj.semiMinor = data:GetInt64();
    _obj.orientation = data:GetInt64();
    return _obj;
end

function lua_to_ItsPositionalAccuracy(_obj,file)
    file:PutInt64(_obj.semiMajor);
    file:PutInt64(_obj.semiMinor);
    file:PutInt64(_obj.orientation);
end

function ItsPositionalAccuracy_size()
    local _size = 0;
    _size = _size + SIZE_OF_INT64;  --semiMajor
    _size = _size + SIZE_OF_INT64;  --semiMinor
    _size = _size + SIZE_OF_INT64;  --orientation
    return _size;
end

