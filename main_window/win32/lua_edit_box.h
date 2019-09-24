#ifndef __LUA_EDIT_BOX_H
#define __LUA_EDIT_BOX_H

#include "mem.h"
#include "memfile.h"
#include "lua_window_base.h"

class CLuaEditBox:public CLuaWindowBase{

public:
	status_t SetMaxText(int max);
    CLuaEditBox();
    virtual ~CLuaEditBox();

    status_t InitBasic();
    status_t Init();
    status_t Destroy();
    status_t Create();

};

#endif
