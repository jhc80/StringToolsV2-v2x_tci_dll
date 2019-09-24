#ifndef __LUA_PRINT_H
#define __LUA_PRINT_H

#ifdef __cplusplus
extern "C" {
#endif

int my_lua_writestring(const char *buf, int size);
int my_lua_writestringerror(const char *szFormat, ...);

#ifdef __cplusplus
} //extern "C"
#endif

#if !defined(lua_writestring)
#define lua_writestring(s,l)  my_lua_writestring(s,l)
#endif

/* print a newline and flush the output */
#if !defined(lua_writeline)
#define lua_writeline() my_lua_writestring("\r\n",2)
#endif

/* print an error message */
#if !defined(lua_writestringerror)
#define lua_writestringerror my_lua_writestringerror
#endif

#define MAX_BUFFER_SIZE  (64*1024*1024)

#endif
