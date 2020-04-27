#include "globals.h"
#include "syslog.h"
#include "mem_tool.h"
#include "winmisc.h"
#include "dirmgr.h"
#include "encoder.h"
#include "lua_helper.h"

#define WND_TITLE_PREFIX "Moon string tools"
#define WND_TITLE_PREFIX_W L"Moon string tools"

CGlobals g_globals;

static CTaskMgr* get_global_taskmgr()
{
	return g_globals.GetTaskMgr();
}

static CLuaVm* get_global_luavm()
{
    return g_globals.GetLuaVm();
}

static int* get_lua_running_flag()
{
    GLOBAL_LUA_THREAD(thread);
    return &thread->m_IsRunning;
}

static const void* get_peer_globals()
{
    GLOBAL_LUA_THREAD(thread);
    return &thread->m_PeerGlobals;
}
///////////////////////////////////////////
///////////////////////////////////////////
CGlobals::CGlobals()
{
	this->InitBasic();
}
CGlobals::~CGlobals()
{
	this->Destroy();
}
status_t CGlobals::InitBasic()
{
	m_TaskAutoLuaGc = 0;
	m_Flags = 0;
	m_TaskMgr.InitBasic();
	m_MainForm.InitBasic();
	m_MainLoopRunning = false;
	i_PageText.InitBasic();
    i_PageImage.InitBasic();
    m_IndexTree.InitBasic();
    m_WndProperty.InitBasic();
    m_WorkFolder.InitBasic();
    m_MainTaskRunner.InitBasic();
    m_LuaThread.InitBasic();
    p_CurTreeNode = NULL;
	m_PrintBuffer.InitBasic();
    m_ScreenBuffer.InitBasic();
	m_WndSearch.InitBasic();
    m_PeerGlobals.InitBasic();
	return OK;
}
status_t CGlobals::Init()
{
	this->InitBasic();
	SetIsInitiated(true);
	m_TaskMgr.Init(1024);
    m_PeerGlobals.Init(&m_TaskMgr);
    this->SetWorkFolder("moon-tools");
    m_MainTaskRunner.Init();
	i_PageText.Init();
	m_MainForm.Init();		
    m_LuaThread.Init();
	m_MainLoopRunning = true;
    m_MainThreadId = crt_get_current_thread_id();
	this->InitPrintBuffer();
    m_ScreenBuffer.Init();
	this->CreateMainForm();

	how_to_get_global_taskmgr = get_global_taskmgr;
	how_to_get_global_luavm = get_global_luavm;
    how_to_get_lua_running_flag = get_lua_running_flag;
    how_to_get_peer_globals = get_peer_globals;
	return OK;
}
status_t CGlobals::Destroy()
{
	SetIsInitiated(false);
    m_ScreenBuffer.Destroy();
	m_PrintBuffer.Destroy();
    m_MainTaskRunner.Destroy();
    m_WndProperty.Destroy();
	m_WndSearch.Destroy();
    m_IndexTree.Destroy();
	i_PageText.Destroy();
    i_PageImage.Destroy();
	m_TaskMgr.Destroy();
    m_PeerGlobals.Destroy();
	m_MainForm.Destroy();
    m_LuaThread.Destroy();
	this->InitBasic();
	return OK;
}

status_t CGlobals::CreateMainForm()
{
	int sw,sh;	
	CWinMisc::GetScreenRes(&sw,&sh);

	int w = sw*3/4;
	int h = sh*3/4;

	m_MainForm.SetStyle(WS_VISIBLE|WS_BORDER|WS_SYSMENU|WS_MINIMIZEBOX|WS_OVERLAPPEDWINDOW);
	m_MainForm.MoveWindow((sw-w)/2,(sh-h)/2,w,h);
	m_MainForm.SetText(WND_TITLE_PREFIX_W);
	m_MainForm.SetVirtualSize(w,h);
	m_MainForm.Create();

	return OK;
}

status_t CGlobals::MainLoop()
{
	MSG msg;

	while(m_MainLoopRunning)
	{
		while (PeekMessageW(&msg,NULL,0,0,PM_REMOVE))
		{           
			if(m_MainForm.hwnd)
			{
				if(m_MainForm.PreTransMsg(&msg))
					continue;
			}
			
			if(msg.message == WM_QUIT)
			{
				m_MainLoopRunning = false;
				break;
			}
			
			TranslateMessage(&msg);
            m_LuaThread.OnWin32Message(&msg);
			DispatchMessageW(&msg);   
		}
		
        m_MainTaskRunner.Schedule();
    	m_TaskMgr.Schedule();
		crt_msleep(1);
	}

	return OK;
}

status_t CGlobals::QuitMainLoop()
{
	m_MainLoopRunning = false;
	return OK;
}	
static status_t escape_windows_path(const char *path,CMem *out)
{
    ASSERT(path && out);
    int len = strlen(path);
    
    for(int i = 0; i < len; i++)
    {
        if(path[i]=='\\')
        {
            out->Puts("/"); //escape
        }
        else
        {
            out->Putc(path[i]);
        }
    }
    return OK;
}

status_t CGlobals::AddLuaSearchPath(lua_State *L,const char *path, const char *type, const char *ext, bool recursive)
{
    ASSERT(L && path && type && ext);
    ASSERT(path && type && ext);
    
    LOCAL_MEM(abs_path);
    abs_path.StrCpy(path);
    CDirMgr::ToAbsPath(&abs_path);
    
    if(!CDirMgr::IsDirExist(&abs_path))
    {
        LOG("path \"%s\" is not exist",abs_path.CStr());
        return ERROR;
    }
    
    LOCAL_MEM_WITH_SIZE(code,32*1024);
    LOCAL_MEM(tmp);
    
    code.Printf("package.%s=package.%s..\";",type,type);
    
    escape_windows_path(abs_path.CStr(),&tmp);
    code.Puts(&tmp);
    
    code.Printf("/?.%s;",ext);
    BEGIN_CLOSURE(search_dir)
    {
        CLOSURE_PARAM_INT(event,0);
        CLOSURE_PARAM_PTR(const char*, fullname,2);
        CLOSURE_PARAM_PTR(CMem*,code,10);
        CLOSURE_PARAM_PTR(const char*,ext,11);
        CLOSURE_PARAM_PTR(CGlobals*,self,12);
        
        if(event == CDirMgr::EVENT_BEGIN_DIR)
        {
            LOCAL_MEM(tmp);
            escape_windows_path(fullname,&tmp);
            code->Puts(&tmp);
            code->Printf("/?.%s;",ext);
        }
        return OK;
    }
    END_CLOSURE(search_dir);
    
    search_dir.SetParamPointer(10,&code);
    search_dir.SetParamPointer(11,(void*)ext);
    search_dir.SetParamPointer(12,this);
    
    CDirMgr::SearchDir(abs_path.CStr(),recursive,&search_dir);
    code.Puts("\"\n");
    
    CLuaVm tmp_vm;
    tmp_vm.Init(L);
    
    tmp_vm.LoadMem(&code,"lua_package_path");
    tmp_vm.Run(0,0);
    tmp_vm.ClearStack();
    return OK;
}

status_t CGlobals::PlaySound(const char *filename)
{
	ASSERT(filename);
	return ::PlaySound(filename,NULL,SND_ASYNC|SND_FILENAME);
}

status_t CGlobals::ShowPropertyWindow(CIndexTreeNode *node)
{
    if(!m_WndProperty.hwnd)
    {
        m_WndProperty.Init();
        m_WndProperty.SetParent(m_MainForm.hwnd);
        m_WndProperty.Create();
        this->DelaySetPropertyWindowFocus(200);
    }
    m_WndProperty.LoadNode(node);    
    return OK;
}

status_t CGlobals::ShowSearchWindow()
{
	if(m_LuaThread.IsRunning())
    {
        MessageBoxW(m_MainForm.hwnd,L"current Lua vm is running!!",L"can not search",MB_OK);
        return ERROR;
    }

	if(!m_WndSearch.hwnd)
	{
		m_WndSearch.Init();
		m_WndSearch.SetText(L"Search");
		m_WndSearch.SetParent(m_MainForm.hwnd);
		m_WndSearch.SetStyle(WS_CAPTION|WS_VISIBLE|WS_SYSMENU);
		m_WndSearch.Create();
	}
	return OK;
}

const char* CGlobals::GetWorkFolder()
{
    return m_WorkFolder.CStr();
}

status_t CGlobals::StartLuaThread()
{   
    if(m_WndProperty.hwnd)
    {
        m_WndProperty.AutoSave();	
        m_WndProperty.Close();
    }

	if(!p_CurTreeNode)return ERROR;
	

    if(m_LuaThread.IsRunning())
    {
        MessageBoxW(m_MainForm.hwnd,L"current Lua vm is running!!",L"can not start",MB_OK|MB_ICONEXCLAMATION);
        return ERROR;
    }

    ASSERT(p_CurTreeNode);
	this->SetCurIndexTreeNode(p_CurTreeNode); //just update title
	m_PrintBuffer.StartAutoSyncTimer(30);
    m_ScreenBuffer.DestroyImageBuffer();

    this->SetUserStopped(false);
    m_LuaThread.Init();
    m_LuaThread.SetIndexTreeNode(p_CurTreeNode);
    m_LuaThread.Start();

    return OK;
}

status_t CGlobals::StopLuaThread()
{
    m_LuaThread.Stop();
    m_LuaThread.WaitComplete();
    m_LuaThread.Destroy();
	m_PrintBuffer.StopAutoSyncTimer();
	m_PrintBuffer.ClearAll();
    return OK;
}

status_t CGlobals::TryStopLuaThread()
{
    if(!this->UserStopped())
    {
        if(m_LuaThread.IsRunning())
        {
            m_MainForm.SetStatusText(0,"lua vm is stopping, press ESC again to force stop.");
        }
        this->SetUserStopped(true);
    }
    else
    {
        return this->StopLuaThread();
    }
    return OK;
}


status_t CGlobals::SetCurIndexTreeNode(CIndexTreeNode *node)
{
    p_CurTreeNode = node;

	if(node)
	{

		LOCAL_MEM(name);
		name.Puts(WND_TITLE_PREFIX);
		name.Puts(" - ");
		name.Puts(node->GetName());
		name.Printf(" (%d)",node->GetCurrentUser()+1);
		
		CEncoder::Utf8ToUnicode(&name);
		m_MainForm.SetText(name.CStrW());
	}
	else
	{
		m_MainForm.SetText(WND_TITLE_PREFIX_W);
	}
    return OK;
}

status_t CGlobals::SetWorkFolder(const char *folder)
{
    ASSERT(folder);
    LOCAL_MEM(mem);
    mem.StrCpy(folder);
    CDirMgr::ToAbsPath(&mem);
    m_WorkFolder.Destroy();
    m_WorkFolder.Init();
    m_WorkFolder.Copy(&mem);
    return OK;
}

bool CGlobals::IsOnMainThread()
{
    return m_MainThreadId == crt_get_current_thread_id();
}

status_t CGlobals::InitPrintBuffer()
{
	m_PrintBuffer.Init();

	BEGIN_CLOSURE_FUNC(on_pb_event)
	{
		CLOSURE_PARAM_PTR(CGlobals*,self,10);
		CLOSURE_PARAM_PTR(CPartFile*,new_data,1);
		CEditBox *eb = self->GetTheEditBox();
		ASSERT(eb);
		CPrintBuffer::AddDataToEditBox(new_data,eb);
		return OK;
	}
	END_CLOSURE_FUNC(on_pb_event);

	m_PrintBuffer.Callback()->SetParamPointer(10,this);
	m_PrintBuffer.Callback()->SetFunc(on_pb_event);
	return OK;
}

CEditBox* CGlobals::GetTheEditBox()
{
	ASSERT(i_PageText.IsValid());
	CEditBox *eb = i_PageText->eb_log;
	return eb;
}

status_t CGlobals::ClearScreen()
{
	CEditBox *eb = GetTheEditBox();
	ASSERT(eb);
	eb->SetText(L"");
    m_PrintBuffer.Lock();
	m_PrintBuffer.ClearAll();
    m_PrintBuffer.Unlock();
	return OK;
}

status_t CGlobals::DelaySetPropertyWindowFocus(int delay)
{
    BEGIN_NEW_CLOSURE(focus)
    {
        CLOSURE_PARAM_INT(hwnd,10);
        SetForegroundWindow((HWND)hwnd);
        return OK;
    }
    END_NEW_CLOSURE(focus);
    focus->SetParamInt(10,(int)(m_WndProperty.hwnd));
    m_MainTaskRunner.AddClosure(focus,delay);
    return OK;
}

CTaskMgr* CGlobals::GetTaskMgr()
{
	if(m_LuaThread.IsInThisThread())
		return m_LuaThread.GetTaskMgr();
	else
		return &m_TaskMgr;
}

status_t CGlobals::GetAllCommonLuaFolders(CMemStk *all)
{
    ASSERT(all);

    CIndexTreeNode *root = m_IndexTree.GetRoot();
    ASSERT(root);

    CMem *config = root->GetConfig();
    ASSERT(config);

    LOCAL_MEM(line);
    LOCAL_MEM(mem);
    LOCAL_MEM(fullpath);

    config->Seek(0);   
    while(config->ReadLine(&line))
    {
        line.Trim();
        line.Seek(0);

        if(line.ReadKeyValue("common",&mem))
        {
            fullpath.StrCpy(root->GetPath());
            fullpath.Putc(crt_get_path_splitor());
            fullpath.Puts(&mem);
            all->Push(&fullpath);
        }
    }
    return OK;
}

status_t CGlobals::CloseSearchWindow()
{
	if(m_WndSearch.hwnd)
	{
		m_WndSearch.Close();
	}
	return OK;
}

status_t CGlobals::GetCurLine(CMem *utf8)
{
    ASSERT(utf8);
    ASSERT(i_PageText.get());
    ASSERT(IsOnMainThread());    

    CEditBox eb;
    eb.Init();
    eb.AttachWnd(i_PageText->eb_log->hwnd);
    
    int start,end;
    eb.GetSel(&start,&end);
    
    int line = ::SendMessageW(eb.hwnd,EM_LINEFROMCHAR,end,0);
    utf8->SetSize(0);
    ASSERT(utf8->GetMaxSize() > 4);

    uint16_t *pbuf = (uint16_t*)utf8->GetRawBuf();
    ASSERT(pbuf);

    uint16_t buf_size = (uint16_t)utf8->GetMaxSize()/sizeof(uint16_t);
    pbuf[0] = buf_size;
    
    int line_count = ::SendMessageW(eb.hwnd,EM_GETLINECOUNT,0,0);
    if(line >= line_count)line = line_count-1;

    int len = ::SendMessageW(eb.hwnd,EM_GETLINE,line-1,(LPARAM)pbuf);
    utf8->SetSize(len*sizeof(int16_t));

    CEncoder::UnicodeToUtf8(utf8);
    return OK;
}

CLuaVm* CGlobals::GetLuaVm()
{
	if(m_LuaThread.IsInThisThread())
		return m_LuaThread.GetLuaVm();
	else
		return NULL;
}

status_t CGlobals::ShowHelp()
{
    ASSERT(i_PageText.get());
    ASSERT(p_CurTreeNode);

    CEditBox eb;
    eb.Init();
    eb.AttachWnd(i_PageText->eb_log->hwnd);
    
    LOCAL_MEM(path);
    p_CurTreeNode->GetHelpFile(&path);
    
    eb.SetText(L"");
    if(!CDirMgr::IsFileExist(&path))
    {
        LOG("can not find %s",path.CStr());
        return ERROR;
    }

    CMem help;
    help.Init();
    help.LoadFile(path.CStr());
    help.Realloc((int)help.GetSize()*4);
    
    CEncoder::Utf8ToUnicode(&help);
    eb.SetText(help.CStrW());

    return OK;
}

status_t CGlobals::OpenTheFolder()
{
    ASSERT(p_CurTreeNode);
    LOCAL_MEM(cmd);
    cmd.Printf("explorer \"%s\"",p_CurTreeNode->GetPathStr());
    WinExec(cmd.CStr(),SW_SHOW);
    return OK;
}

status_t CGlobals::ShowLuaDoc()
{
    LOCAL_MEM(path);
    this->GetHelpPath(&path);
    path.StrCat("\\lua-doc\\index.html");
    ShellExecute(m_MainForm.hwnd,"open",path.CStr(),NULL,NULL,SW_SHOW);
    return OK;
}   

status_t CGlobals::GetHelpPath(CMem *path)
{
    ASSERT(path);
    CDirMgr::GetFileName(&m_WorkFolder,path,FN_PATH);
    path->StrCat("\\help");
    return OK;
}

status_t CGlobals::ShowLuaPatternHelp()
{
    ASSERT(i_PageText.get());

    LOCAL_MEM(path);
    this->GetHelpPath(&path);
    path.StrCat("\\lua-pattern.txt");
    
    CEditBox eb;
    eb.Init();
    eb.AttachWnd(i_PageText->eb_log->hwnd);
 
    CMem help;
    help.Init();
    help.LoadFile(path.CStr());
    help.Realloc((int)help.GetSize()*4);
    
    CEncoder::Utf8ToUnicode(&help);
    eb.SetText(help.CStrW());
    return OK;
}
