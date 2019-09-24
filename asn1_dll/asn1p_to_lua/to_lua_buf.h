#ifndef __TO_LUA_BUF_H
#define __TO_LUA_BUF_H

#include "cruntime.h"

int lua_print_buf_init(int size);
int lua_puts(const char *str);
const char *lua_get_code(void);
int lua_printf(const char *format,...);
int lua_log(const char *format,...);
int lua_inc_level(int inc);
int lua_current_position(void);
int lua_set_position(int pos);
int lua_print_buf_destroy();
char* lua_print_buf_abandon_buf(int *size);

#endif
