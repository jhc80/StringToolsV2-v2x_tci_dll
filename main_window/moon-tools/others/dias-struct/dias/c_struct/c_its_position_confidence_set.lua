function ItsPositionConfidenceSet_to_lua(data)
    local _obj={};
    _obj.pos = data:GetInt32();
    _obj.elevation = data:GetInt32();
    return _obj;
end

function lua_to_ItsPositionConfidenceSet(_obj,file)
    file:PutInt32(_obj.pos);
    file:PutInt32(_obj.elevation);
end

function ItsPositionConfidenceSet_size()
    local _size = 0;
    _size = _size + SIZE_OF_INT32;  --pos
    _size = _size + SIZE_OF_INT32;  --elevation
    return _size;
end

