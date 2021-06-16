function ItsDDateTime_to_lua(data)
    local _obj={};
    _obj.year = data:GetInt32();
    _obj.month = data:GetInt32();
    _obj.day = data:GetInt32();
    _obj.hour = data:GetInt32();
    _obj.minute = data:GetInt32();
    _obj.second = data:GetInt32();
    _obj.offset = data:GetInt32();
    return _obj;
end

function lua_to_ItsDDateTime(_obj,file)
    file:PutInt32(_obj.year);
    file:PutInt32(_obj.month);
    file:PutInt32(_obj.day);
    file:PutInt32(_obj.hour);
    file:PutInt32(_obj.minute);
    file:PutInt32(_obj.second);
    file:PutInt32(_obj.offset);
end

function ItsDDateTime_size()
    local _size = 0;
    _size = _size + SIZE_OF_INT32;  --year
    _size = _size + SIZE_OF_INT32;  --month
    _size = _size + SIZE_OF_INT32;  --day
    _size = _size + SIZE_OF_INT32;  --hour
    _size = _size + SIZE_OF_INT32;  --minute
    _size = _size + SIZE_OF_INT32;  --second
    _size = _size + SIZE_OF_INT32;  --offset
    return _size;
end

