function ItsDDateTime_to_lua(data)
    local _obj={};
    _obj.year = data:GetInt64();
    _obj.month = data:GetInt64();
    _obj.day = data:GetInt64();
    _obj.hour = data:GetInt64();
    _obj.minute = data:GetInt64();
    _obj.second = data:GetInt64();
    _obj.offset = data:GetInt64();
    return _obj;
end

function lua_to_ItsDDateTime(_obj,file)
    file:PutInt64(_obj.year);
    file:PutInt64(_obj.month);
    file:PutInt64(_obj.day);
    file:PutInt64(_obj.hour);
    file:PutInt64(_obj.minute);
    file:PutInt64(_obj.second);
    file:PutInt64(_obj.offset);
end

function ItsDDateTime_size()
    local _size = 0;
    _size = _size + SIZE_OF_INT64;  --year
    _size = _size + SIZE_OF_INT64;  --month
    _size = _size + SIZE_OF_INT64;  --day
    _size = _size + SIZE_OF_INT64;  --hour
    _size = _size + SIZE_OF_INT64;  --minute
    _size = _size + SIZE_OF_INT64;  --second
    _size = _size + SIZE_OF_INT64;  --offset
    return _size;
end

