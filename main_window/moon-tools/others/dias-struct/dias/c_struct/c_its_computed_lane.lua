function ItsComputedLane_to_lua(data)
    local _obj={};
    _obj.referenceLandId = data:GetUInt32();
    _obj.offsetXaxis = data:GetInt32();
    _obj.offsetYaxis = data:GetInt32();
    return _obj;
end

function lua_to_ItsComputedLane(_obj,file)
    file:PutUInt32(_obj.referenceLandId);
    file:PutInt32(_obj.offsetXaxis);
    file:PutInt32(_obj.offsetYaxis);
end

function ItsComputedLane_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT32;  --referenceLandId
    _size = _size + SIZE_OF_INT32;  --offsetXaxis
    _size = _size + SIZE_OF_INT32;  --offsetYaxis
    return _size;
end

