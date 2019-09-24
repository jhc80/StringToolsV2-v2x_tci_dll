#include "lua_helper.h"
#include "mem.h"
#include "encoder.h"
#include "syslog.h"

const char* lua_push_local_string(lua_State *L, const char *local_string)
{
    ASSERT(L && local_string);
    CMem mem_local_string(local_string);
    AUTO_LOCAL_MEM(utf8_string,mem_local_string.StrLen()*3);
    CEncoder::EncodingConvert(
        LOCAL_ENCODING,ENCODING_UTF8,
        &mem_local_string,
        &utf8_string
    );
    return lua_pushlstring(L,utf8_string.CStr(),utf8_string.StrLen());
}

const char* lua_to_local_string(lua_State *L, int index)
{
    if(!lua_isstring(L,index))return NULL;

    size_t len = 0;
    const char *utf8_str = lua_tolstring(L,index,&len);
    ASSERT(utf8_str); ASSERT(len > 0);

    CMem tmp;
    tmp.Init();
    tmp.SetRawBuf((void*)utf8_str,len,true);
    
    AUTO_LOCAL_MEM(local_str,len);

    CEncoder::EncodingConvert(ENCODING_UTF8,LOCAL_ENCODING,&tmp,&local_str);

    lua_pushlstring(L,local_str.CStr(),local_str.StrLen());
    lua_replace(L,index);

    return lua_tostring(L,index);;
}