function ItsMotionConfidenceSet_to_lua(data)
    local _obj={};
    _obj.speedCfd = data:GetInt32();
    _obj.headingCfd = data:GetInt32();
    _obj.steerCfd = data:GetInt32();
    return _obj;
end

function lua_to_ItsMotionConfidenceSet(_obj,file)
    file:PutInt32(_obj.speedCfd);
    file:PutInt32(_obj.headingCfd);
    file:PutInt32(_obj.steerCfd);
end

function ItsMotionConfidenceSet_size()
    local _size = 0;
    _size = _size + SIZE_OF_INT32;  --speedCfd
    _size = _size + SIZE_OF_INT32;  --headingCfd
    _size = _size + SIZE_OF_INT32;  --steerCfd
    return _size;
end

