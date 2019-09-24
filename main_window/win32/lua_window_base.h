#ifndef __LUA_WINDOW_BASE_H
#define __LUA_WINDOW_BASE_H

#include "mem.h"
#include "memfile.h"
#include "wnd.h"

class CLuaWindowBase:public CWnd{

public:
    CLuaWindowBase();
    virtual ~CLuaWindowBase();

    status_t InitBasic();
    status_t Init();
    status_t Destroy();

};

#endif
