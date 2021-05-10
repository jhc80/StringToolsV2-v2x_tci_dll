#ifndef __S2_LUATHREAD_H
#define __S2_LUATHREAD_H

#include "cruntime.h"
#include "filebase.h"
#include "thread.h"
#include "luavm.h"
#include "indextreenode.h"
#include "taskmgr.h"
#include "taskrunner.h"
#include "basicarray.h"
#include "mem.h"
#include "epoll.h"
#include "peerglobals.h"

#define LUA_THREAD_FLAG_FUNC(func,bit) FLAG_FUNC(m_Flags,func, bit)

#define MAX_MODULES_SIZE 1024

enum{
	APP_EVENT_EMBEDDED_UI_WINDOW_RESIZED=1,
    APP_EVENT_EMBEDDED_UI_WINDOW_MESSAGE=2,
};

class CLuaThread:public CThread{
public:
	CTaskMgr m_TaskMgr;
    CLuaVm m_LuaVm;
    CIndexTreeNode *p_TreeNode;
    CTaskRunner m_TaskRunner;
    int_ptr_t m_ThreadId;
    uint32_t m_Flags;
	CEpoll m_Epoll;
    CPeerGlobals m_PeerGlobals;
	int m_TaskAutoLuaGc;

	HMODULE m_DelayUnloadModules[MAX_MODULES_SIZE];
    int callback_on_window_message;
	int callback_on_app_event;
public:
	status_t StartLuaAutoGcTask();
    CPeerGlobals *GetPeerGlobals();
	status_t OnAppEvent(int event, CMem *mem);
	status_t HideEmbeddedUIWindow();
	status_t ShowEmbeddedUIWindow(int height);
	status_t FreeAllModules();
	status_t OnWin32Message(MSG *msg);
    CTaskRunner *GetTaskRunner();
	int GetCurrentUser();
	status_t SwitchToPageImage();
	status_t SwitchToPageText();
	status_t SetPrintBufferFlushInterval(uint32_t interval);
	status_t GetCurrentPath(const char *rpath,CMem *out);
	CTaskMgr* GetTaskMgr();
	status_t MainLoop(int sleep_time);
	CLuaVm* GetLuaVm();
	status_t LoadText(CMem *utf8);
	status_t OnThreadEnd();
	status_t OnThreadBegin();
    status_t ReportLuaError();
	status_t Stop();
	status_t InitLuaVm();
	bool IsInThisThread();
	status_t SetIndexTreeNode(CIndexTreeNode *node);
	status_t Run();
	CLuaThread();
	virtual ~CLuaThread();
	status_t InitBasic();
	status_t Init();
	status_t Destroy();

    LUA_THREAD_FLAG_FUNC(IsMainLoopRunning,0x00000001);
};

#endif
