function ItsPathHistory_to_lua(data)
    local _obj={};
    _obj.initialPosition = ItsFullPositionVector_to_lua(data);
    _obj.currGPSstatus = data:GetUInt8();
    _obj.itemCnt = data:GetInt64();

    _obj.pointSets={}
    for i=1,_obj.itemCnt,1 do
        _obj.pointSets[i] = ItsPathHistoryPointSet_to_lua(data);
    end
    data:Skip((PATH_HISTORY_POINTS_MAX-_obj.itemCnt)*ItsPathHistoryPointSet_size());

    return _obj;
end

function lua_to_ItsPathHistory(_obj,file)
    lua_to_ItsFullPositionVector(_obj.initialPosition,file);
    file:PutUInt8(_obj.currGPSstatus);
    file:PutInt64(_obj.itemCnt);

    for i=1,_obj.itemCnt,1 do
        lua_to_ItsPathHistoryPointSet(_obj.pointSets[i],file);
    end
    file:FillBlock((PATH_HISTORY_POINTS_MAX-_obj.itemCnt)*ItsPathHistoryPointSet_size(),0);

end

function ItsPathHistory_size()
    local _size = 0;
    _size = _size + ItsFullPositionVector_size();  --initialPosition
    _size = _size + SIZE_OF_UINT8;  --currGPSstatus
    _size = _size + SIZE_OF_INT64;  --itemCnt
    _size = _size + PATH_HISTORY_POINTS_MAX*ItsPathHistoryPointSet_size();  --pointSets
    return _size;
end

