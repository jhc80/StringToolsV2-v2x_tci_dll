#include "lua_window_base.h"
#include "syslog.h"
#include "mem_tool.h"

CLuaWindowBase::CLuaWindowBase()
{
    this->InitBasic();
}

CLuaWindowBase::~CLuaWindowBase()
{
    this->Destroy();
}

status_t CLuaWindowBase::InitBasic()
{
    CWnd::InitBasic();
    return OK;
}

status_t CLuaWindowBase::Init()
{
    this->InitBasic();
    CWnd::Init();
    this->wnd_create->style = WS_VISIBLE|WS_CHILD|WS_TABSTOP;
    return OK;
}

status_t CLuaWindowBase::Destroy()
{
    CWnd::Destroy();
    this->InitBasic();
    return OK;
}

