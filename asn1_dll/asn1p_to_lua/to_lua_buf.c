#include "to_lua_buf.h"

static char *g_lua_print_buf = NULL;
static int g_lua_print_buf_len = 0;
static int g_lua_print_buf_max_size = 0;
static int g_lua_print_level = 0;

int lua_print_buf_init(int size)
{
    if(g_lua_print_buf)
    {
        free(g_lua_print_buf);
        g_lua_print_buf = NULL;
    }
    g_lua_print_buf = (char*)malloc(size);
    g_lua_print_buf_len = 0;
    g_lua_print_buf_max_size = size;
    return 0;
}

int lua_print_buf_destroy()
{   
    if(g_lua_print_buf)
    {
        free(g_lua_print_buf);
        g_lua_print_buf = NULL;
    }
    return 0;
}

char* lua_print_buf_abandon_buf(int *size)
{
    char *buf = g_lua_print_buf;    
    *size = g_lua_print_buf_len;
    g_lua_print_buf = NULL;
    g_lua_print_buf_len = 0;
    g_lua_print_buf_max_size = 0;
    return buf;
}

int lua_puts(const char *str)
{
    int len = strlen(str);
    if(len <= 0)return 0;

    if(g_lua_print_buf_len + len >= g_lua_print_buf_max_size)
        return 0;

    memcpy(g_lua_print_buf + g_lua_print_buf_len ,str,len);
    g_lua_print_buf_len += len;

    return len;
}

const char *lua_get_code(void)
{
    g_lua_print_buf[g_lua_print_buf_len] = 0;
    return g_lua_print_buf;
}

int lua_printf(const char *format,...)
{
    char szBuffer [8*1024]; 

    va_list pArgList;
    va_start(pArgList, format);
    vsprintf(szBuffer, format, pArgList);
    va_end (pArgList);
    
    return lua_puts(szBuffer);
}

int lua_inc_level(int inc)
{
    g_lua_print_level += inc;
    return 0;
}

int lua_log(const char *format,...)
{
    char szBuffer [8*1024]; 

    va_list pArgList;
    va_start(pArgList, format);
    vsnprintf(szBuffer,sizeof(szBuffer),format, pArgList);
    va_end (pArgList);

    int i,n = 0;

    for(i = 0; i < g_lua_print_level*4; i++)
    {
        n+=lua_puts(" ");
    }

    n += lua_puts(szBuffer);
    n += lua_puts("\r\n");
    return n;
}

int lua_current_position(void)
{
    return g_lua_print_buf_len;
}

int lua_set_position(int pos)
{
    return g_lua_print_buf_len = pos;
}