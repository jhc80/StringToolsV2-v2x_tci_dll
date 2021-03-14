#include "lua_print.h"
#include "cruntime.h"
#include "syslog.h"

#define MAX_BUFFER_SIZE  (64*1024*1024)

extern "C" int my_lua_writestring(const char *buf, int size)
{
    syslog_puts(LOG_MODULE_USER,LOG_LEVEL_ERROR,buf);
    return OK;
}

extern "C" int my_lua_writestringerror(const char *szFormat, ...)
{   
    ASSERT(szFormat);
    MAKE_VARGS_BUFFER(szFormat);    
    my_lua_writestring(szBuffer,strlen(szBuffer));
    my_lua_writestring("\r\n",2);
    return OK;
}