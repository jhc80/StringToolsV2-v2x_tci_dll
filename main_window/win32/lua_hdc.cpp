#include "lua_hdc.h"
#include "syslog.h"
#include "mem_tool.h"

CLuaHdc::CLuaHdc()
{
    this->InitBasic();
}

CLuaHdc::~CLuaHdc()
{
    this->Destroy();
}

status_t CLuaHdc::InitBasic()
{
    WEAK_REF_ID_CLEAR();
    hdc = NULL;
    hwnd = NULL;
    return OK;
}

status_t CLuaHdc::Init()
{
    this->InitBasic();
    WEAK_REF_ID_INIT();
    return OK;
}

status_t CLuaHdc::Destroy()
{
    if(hdc)
    {
        ::ReleaseDC(hwnd,hdc);
        hdc = NULL;
    }
    this->InitBasic();
    return OK;
}

status_t CLuaHdc::Set(HWND hwnd, HDC hdc)
{
    ASSERT(this->hdc == NULL);
    this->hwnd = hwnd;
    this->hdc = hdc;
    return OK;
}
