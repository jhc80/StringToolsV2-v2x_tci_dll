#include "wndembeddedui.h"
#include "winmisc.h"
#include "syslog.h"
#include "globals.h"
#include "minibson.h"

CWndEmbeddedUI::CWndEmbeddedUI()
{
	this->InitBasic();
}
CWndEmbeddedUI::~CWndEmbeddedUI()
{
	this->Destroy();
}
int CWndEmbeddedUI::InitBasic()
{
	CWnd::InitBasic();
	return OK;
}
int CWndEmbeddedUI::Init()
{
	this->InitBasic();
	CWnd::Init();
	//add your code
	return OK;
}
int CWndEmbeddedUI::Destroy()
{
	//add your code
	CWnd::Destroy();
	this->InitBasic();
	return OK;
}
int CWndEmbeddedUI::OnCreate(WPARAM wparam, LPARAM lparam)
{
	this->OnSize(0,0);
	return OK;
}
int CWndEmbeddedUI::OnClose(WPARAM wparam, LPARAM lparam)
{
	return OK;
}
int CWndEmbeddedUI::OnSize(WPARAM wparam, LPARAM lparam)
{
	RECT r;
	::GetClientRect(hwnd,&r);

	CMiniBson bson;
	bson.Init();
	bson.StartDocument();
	bson.PutInt32("left",r.left);
	bson.PutInt32("top",r.top);
	bson.PutInt32("right",r.right);
	bson.PutInt32("bottom",r.bottom);
	bson.EndDocument();

	GLOBAL_LUA_THREAD(lua_thread);
	lua_thread->OnAppEvent(APP_EVENT_EMBEDDED_UI_WINDOW_RESIZED,bson.GetRawData());
	return OK;
}
int CWndEmbeddedUI::OnCommand(WPARAM wparam, LPARAM lparam)
{
	return OK;
}
int CWndEmbeddedUI::PreTransMsg(MSG *msg)
{
	ASSERT(hwnd);
	HWND hlist[100];
	int i = 0;
	
	return CWinMisc::TabFocus(hwnd,hlist,i,msg);
}

LRESULT CWndEmbeddedUI::ProcessAllMsg(UINT message,WPARAM wparam,LPARAM lparam)
{
    CMiniBson bson;
    bson.Init();
    bson.StartDocument();
    bson.PutInt32("message",message);
    bson.PutInt32("wparam",wparam);
    bson.PutInt32("lparam",lparam);
    bson.EndDocument();
    
    GLOBAL_LUA_THREAD(lua_thread);
    lua_thread->OnAppEvent(APP_EVENT_EMBEDDED_UI_WINDOW_MESSAGE,bson.GetRawData());

    return CWnd::ProcessAllMsg(message,wparam,lparam);
}
