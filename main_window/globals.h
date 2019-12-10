#ifndef __S2_GLOBALS_H
#define __S2_GLOBALS_H

#include "cruntime.h"
#include "filebase.h"
#include "taskmgr.h"
#include "mainform.h"
#include "pagetext.h"
#include "pageimage.h"
#include "weakptr.h"
#include "luavm.h"
#include "indextree.h"
#include "wndproperty.h"
#include "taskrunner.h"
#include "luathread.h"
#include "printbuffer.h"
#include "screenbuffer.h"
#include "memstk.h"
#include "wndsearch.h"

#define GLOBALS_FLAG_FUNC(func,bit) FLAG_FUNC(m_Flags,func,bit)

class CGlobals{
public:
	CMainForm m_MainForm;
    CWndProperty m_WndProperty;
	CWndSearch m_WndSearch;
	CTaskMgr m_TaskMgr;
	bool m_MainLoopRunning;
	CWeakPtr<CPageText> i_PageText;
    CWeakPtr<CPageImage> i_PageImage;
	uint32_t m_Flags;
	int m_TaskAutoLuaGc;
    CIndexTree m_IndexTree;
    CMem m_WorkFolder;
    CTaskRunner m_MainTaskRunner;
    CIndexTreeNode *p_CurTreeNode;
    CLuaThread m_LuaThread;
    int_ptr_t m_MainThreadId;
	CPrintBuffer m_PrintBuffer;
    CScreenBuffer m_ScreenBuffer;
public:
	status_t OpenTheFolder();
	status_t ShowHelp();
	CLuaVm *GetLuaVm();
	status_t GetCurLine(CMem *utf8);
	status_t CloseSearchWindow();
	status_t GetAllCommonLuaFolders(CMemStk *all);
	CTaskMgr* GetTaskMgr();
	status_t DelaySetPropertyWindowFocus(int delay);
	status_t ClearScreen();
	CEditBox* GetTheEditBox();
	status_t InitPrintBuffer();
	bool IsOnMainThread();
	status_t SetWorkFolder(const char *folder);
	status_t SetCurIndexTreeNode(CIndexTreeNode *node);
	status_t StopLuaThread();
    status_t TryStopLuaThread();
	status_t StartLuaThread();
	const char* GetWorkFolder();
	status_t ShowPropertyWindow(CIndexTreeNode *node);
	status_t ShowSearchWindow();
	status_t PlaySound(const char *filename);
    status_t AddLuaSearchPath(lua_State *L,const char *path, const char *type, const char *ext, bool recursive);
	status_t QuitMainLoop();
	status_t MainLoop();
	status_t CreateMainForm();
	CGlobals();
	virtual ~CGlobals();
	status_t InitBasic();
	status_t Init();
	status_t Destroy();

	GLOBALS_FLAG_FUNC(IsLuaRunning,0x00000001);
	GLOBALS_FLAG_FUNC(IsInitiated,0x00000002);
    GLOBALS_FLAG_FUNC(UserStopped,0x00000004);
};
//////////////////////////////////////////
extern CGlobals g_globals;
#define GLOBALS(g) CGlobals *g = &g_globals
#define GLOBAL_PAGE_TEXT(page_text) CPageText *page_text = g_globals.i_PageText.get()
#define GLOBAL_PAGE_IMAGE(page_image) CPageImage *page_image = g_globals.i_PageImage.get()
#define GLOBAL_INDEX_TREE(tree) CIndexTree *tree = &g_globals.m_IndexTree
#define GLOBAL_TREE_VIEW(tv) CTreeView *tv = g_globals.GetTreeView()
#define GLOBAL_WND_PROPERTY(win) CWndProperty *win = &g_globals.m_WndProperty
#define GLOBAL_MAIN_TASK_RUNNER(runner) CTaskRunner *runner = &g_globals.m_MainTaskRunner
#define GLOBAL_LUA_THREAD(thread) CLuaThread *thread = &g_globals.m_LuaThread
#define GLOBAL_MAIN_FORM(form) CMainForm *form = &g_globals.m_MainForm
#define GLOBAL_PRINT_BUFFER(buf) CPrintBuffer *buf = &g_globals.m_PrintBuffer
#define GLOBAL_SCREEN_BUFFER(buf) CScreenBuffer *buf = &g_globals.m_ScreenBuffer
#define GLOBAL_WND_SEARCH(win) CWndSearch *win = &g_globals.m_WndSearch
//////////////////////////////////////////
#endif
