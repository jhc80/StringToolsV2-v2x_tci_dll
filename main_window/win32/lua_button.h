#ifndef __LUA_BUTTON_H
#define __LUA_BUTTON_H

#include "mem.h"
#include "memfile.h"
#include "lua_window_base.h"

class CLuaButton:public CLuaWindowBase{

public:
	status_t Create();
    CLuaButton();
    virtual ~CLuaButton();

    status_t InitBasic();
    status_t Init();
    status_t Destroy();

};

#endif
