#include "lua_print.h"
#include "cruntime.h"
#include "syslog.h"
#include "globals.h"

extern "C" int my_lua_writestring(const char *buf, int size)
{
	GLOBAL_PRINT_BUFFER(print_buf);
	print_buf->Lock();
	CMemFile *data = print_buf->GetTextData();
	if(data->GetSize()+size < MAX_BUFFER_SIZE)
    {
        print_buf->SetTextSynced(false);
        data->Write(buf,size);
    }
	print_buf->Unlock();
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
