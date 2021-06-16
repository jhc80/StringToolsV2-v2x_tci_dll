function ItsPathPrediction_to_lua(data)
    local _obj={};
    _obj.radiusOfCurve = data:GetUInt16();
    _obj.confidence = data:GetUInt16();
    return _obj;
end

function lua_to_ItsPathPrediction(_obj,file)
    file:PutUInt16(_obj.radiusOfCurve);
    file:PutUInt16(_obj.confidence);
end

function ItsPathPrediction_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT16;  --radiusOfCurve
    _size = _size + SIZE_OF_UINT16;  --confidence
    return _size;
end

