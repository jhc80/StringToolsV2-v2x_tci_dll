function DiasV2xServiceParam_to_lua(data)
    local _obj={};
    _obj.eDataType = data:GetInt32();
    _obj.u32RecvMsgFlag = data:GetUInt32();
    _obj.u32RawAidListNum = data:GetUInt32();

    _obj.u32RawAidList={}
    for i=1,_obj.u32RawAidListNum,1 do
        _obj.u32RawAidList[i] = data:GetUInt32();
    end
    data:Skip((DIAS_V2X_AID_LIST_MAX_NUM-_obj.u32RawAidListNum)*SIZE_OF_UINT32);

    _obj.pfnRecvCallBack = data:GetInt64();
    return _obj;
end

function lua_to_DiasV2xServiceParam(_obj,file)
    file:PutInt32(_obj.eDataType);
    file:PutUInt32(_obj.u32RecvMsgFlag);
    file:PutUInt32(_obj.u32RawAidListNum);

    for i=1,_obj.u32RawAidListNum,1 do
        file:PutUInt32(_obj.u32RawAidList[i]);
    end
    file:FillBlock((DIAS_V2X_AID_LIST_MAX_NUM-_obj.u32RawAidListNum)*SIZE_OF_UINT32,0);

    file:PutInt64(_obj.pfnRecvCallBack);
end

function DiasV2xServiceParam_size()
    local _size = 0;
    _size = _size + SIZE_OF_INT32;  --eDataType
    _size = _size + SIZE_OF_UINT32;  --u32RecvMsgFlag
    _size = _size + SIZE_OF_UINT32;  --u32RawAidListNum
    _size = _size + DIAS_V2X_AID_LIST_MAX_NUM*SIZE_OF_UINT32;  --u32RawAidList
    _size = _size + SIZE_OF_INT64;  --pfnRecvCallBack
    return _size;
end

