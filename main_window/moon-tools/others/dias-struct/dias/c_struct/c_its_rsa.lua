function ItsRsa_to_lua(data)
    local _obj={};
    _obj.msgCnt = data:GetUInt8();
    _obj.rtesNum = data:GetUInt8();
    _obj.rtssNum = data:GetUInt8();
    _obj.moy = data:GetUInt32();
    _obj.id = data:GetUInt64();
    _obj.latitude = data:GetInt32();
    _obj.longitude = data:GetInt32();
    _obj.elevation = data:GetInt32();

    _obj.rtes={}
    for i=1,_obj.rtesNum,1 do
        _obj.rtes[i] = ItsRte_to_lua(data);
    end
    data:Skip((MAX_RTE_COUNT-_obj.rtesNum)*ItsRte_size());


    _obj.rtss={}
    for i=1,_obj.rtssNum,1 do
        _obj.rtss[i] = ItsRts_to_lua(data);
    end
    data:Skip((MAX_RTS_COUNT-_obj.rtssNum)*ItsRts_size());

    return _obj;
end

function lua_to_ItsRsa(_obj,file)
    file:PutUInt8(_obj.msgCnt);
    file:PutUInt8(_obj.rtesNum);
    file:PutUInt8(_obj.rtssNum);
    file:PutUInt32(_obj.moy);
    file:PutUInt64(_obj.id);
    file:PutInt32(_obj.latitude);
    file:PutInt32(_obj.longitude);
    file:PutInt32(_obj.elevation);

    for i=1,_obj.rtesNum,1 do
        lua_to_ItsRte(_obj.rtes[i],file);
    end
    file:FillBlock((MAX_RTE_COUNT-_obj.rtesNum)*ItsRte_size(),0);


    for i=1,_obj.rtssNum,1 do
        lua_to_ItsRts(_obj.rtss[i],file);
    end
    file:FillBlock((MAX_RTS_COUNT-_obj.rtssNum)*ItsRts_size(),0);

end

function ItsRsa_size()
    local _size = 0;
    _size = _size + SIZE_OF_UINT8;  --msgCnt
    _size = _size + SIZE_OF_UINT8;  --rtesNum
    _size = _size + SIZE_OF_UINT8;  --rtssNum
    _size = _size + SIZE_OF_UINT32;  --moy
    _size = _size + SIZE_OF_UINT64;  --id
    _size = _size + SIZE_OF_INT32;  --latitude
    _size = _size + SIZE_OF_INT32;  --longitude
    _size = _size + SIZE_OF_INT32;  --elevation
    _size = _size + MAX_RTE_COUNT*ItsRte_size();  --rtes
    _size = _size + MAX_RTS_COUNT*ItsRts_size();  --rtss
    return _size;
end

