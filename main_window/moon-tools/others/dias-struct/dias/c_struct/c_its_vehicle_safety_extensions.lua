function ItsVehicleSafetyExtensions_to_lua(data)
    local _obj={};
    _obj.events = data:GetInt32();
    _obj.lights = data:GetInt32();
    _obj.pathHistory = ItsPathHistory_to_lua(data);
    _obj.pathPrediction = ItsPathPrediction_to_lua(data);
    return _obj;
end

function lua_to_ItsVehicleSafetyExtensions(_obj,file)
    file:PutInt32(_obj.events);
    file:PutInt32(_obj.lights);
    lua_to_ItsPathHistory(_obj.pathHistory,file);
    lua_to_ItsPathPrediction(_obj.pathPrediction,file);
end

function ItsVehicleSafetyExtensions_size()
    local _size = 0;
    _size = _size + SIZE_OF_INT32;  --events
    _size = _size + SIZE_OF_INT32;  --lights
    _size = _size + ItsPathHistory_size();  --pathHistory
    _size = _size + ItsPathPrediction_size();  --pathPrediction
    return _size;
end

