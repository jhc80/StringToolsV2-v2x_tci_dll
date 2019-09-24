#include "luathread.h"
#include "syslog.h"
#include "mem_tool.h"
#include "globals.h"
#include "encoder.h"
#include "dirmgr.h"
#include "tcp.h"
#include "peerglobals.h"
#include "load_dll.h"
#include "lualib_minibson.h"
#include "lualib_stream.h"
#include "lualib_filemanager.h"
#include "lualib_app.h"
#include "lualib_filebase.h"
#include "lualib_mem.h"
#include "lualib_memfile.h"
#include "lualib_file.h"
#include "lualib_mmapfile.h"
#include "lualib_cfunc.h"
#include "lualib_ximage.h"
#include "lualib_ximagehelper.h"
#include "lualib_idlparser.h"
#include "lualib_tasktimer.h"
#include "lualib_messagepeer.h"
#include "lualib_serversidepeer.h"
#include "lualib_screen.h"
#include "lualib_lexer.h"
#include "lualib_lexercpp.h"
#include "lualib_lexerlua.h"
#include "lualib_websocketmessage.h"
#include "lualib_tcpsocket.h"
#include "lualib_websocketserver.h"
#include "lualib_win32.h"
#include "lualib_udpsocket.h"
#include "lualib_luawindowbase.h"
#include "lualib_luabutton.h"
#include "lualib_luaeditbox.h"
#include "lualib_luahdc.h"
#include "lualib_memdc.h"
#include "lualib_ximagegif.h"
#include "lualib_gifencoder.h"
#include "lualib_xml.h"
#include "lualib_xmlnode.h"

extern "C" int _lua_running_flag;

int lua_on_load_library(void *_L,const char*dll_name, void *_hmodule)
{
    GLOBAL_LUA_THREAD(lua_thread);
    ASSERT(lua_thread->IsInThisThread());
    
    GLOBAL_MAIN_FORM(main_form);

    LUA_INIT_FUNC init_func = (LUA_INIT_FUNC)::GetProcAddress(
        (HMODULE)_hmodule,LUA_INIT_FUNC_NAME
    );

    struct lua_dll_init_data init_data;
    memset(&init_data,0,sizeof(init_data));

    init_data.log_ptr = syslog_get_puts_handler();
    init_data.lua_state_size = lua_State_Size;
    init_data.this_size = sizeof(init_data);
    init_data.main_hwnd = (uint32_t)main_form->hwnd;

    if(init_func)
    {
        init_func(&init_data);
    }

    return OK;
}

int lua_on_free_library(void *_hmodule)
{
	GLOBAL_LUA_THREAD(lua_thread);
	
	int i;

	for(i = 0; i < MAX_MODULES_SIZE; i++)
	{
		if(lua_thread->m_DelayUnloadModules[i] == NULL)
			break;
		if(lua_thread->m_DelayUnloadModules[i] == _hmodule)
			return ERROR;
	}

	if(i < MAX_MODULES_SIZE)
	{
		lua_thread->m_DelayUnloadModules[i] =(HMODULE)_hmodule;
	}
	return OK;
}

CLuaThread::CLuaThread()
{
	this->InitBasic();
}
CLuaThread::~CLuaThread()
{
	this->Destroy();
}
status_t CLuaThread::InitBasic()
{
    m_ThreadId = 0;
    p_TreeNode = NULL;
    m_LuaVm.InitBasic();
	m_TaskMgr.InitBasic();
    m_Flags = 0;
    g_peer_globals.InitBasic();
    m_TaskRunner.InitBasic();	
    callback_on_window_message = LUA_REFNIL;
	callback_on_app_event = LUA_REFNIL;
	memset(m_DelayUnloadModules,0,sizeof(m_DelayUnloadModules));
	CThread::InitBasic();
	return OK;
}
status_t CLuaThread::Init()
{
	this->InitBasic();
	CThread::Init();
	return OK;
}
status_t CLuaThread::Destroy()
{ 
	CThread::Destroy();
    g_peer_globals.Destroy();	
	m_TaskMgr.Destroy();
    m_LuaVm.Destroy();
	this->InitBasic();
	return OK;
}

status_t CLuaThread::Run()
{
    ASSERT(p_TreeNode);

    int result;
    
    this->OnThreadBegin();     
        
    LOCAL_MEM(main_lua);
    p_TreeNode->GetMainCodePath(&main_lua);
    if(luaL_loadfile(m_LuaVm.GetLuaState(),main_lua.CStr()) != 0)
    {
        this->Log("load lua file '%s' fail.",main_lua.CStr());
        this->ReportLuaError();
        goto end;
    }

    result = lua_pcall(m_LuaVm.GetLuaState(),0,0, 0);
    if(result && (result != LUA_YIELD))
    {
        this->ReportLuaError();
        goto end;
    }
    
end:
    this->OnThreadEnd();
    return OK;
}

status_t CLuaThread::SetIndexTreeNode(CIndexTreeNode *node)
{
    p_TreeNode = node;
    return OK;
}

bool CLuaThread::IsInThisThread()
{
    return crt_get_current_thread_id() == m_ThreadId;
}

status_t CLuaThread::InitLuaVm()
{
    ASSERT(p_TreeNode);
    m_LuaVm.Init();

    lua_on_load_library_ptr = lua_on_load_library;
	lua_on_free_library_ptr = lua_on_free_library;

    lua_State *L = m_LuaVm.GetLuaState();
        
    luaopen_filemanager(L);
    luaopen_minibson(L);
    luaopen_stream(L);
    luaopen_app(L);
    luaopen_filebase(L);
    luaopen_memfile(L);
    luaopen_mem(L);
    luaopen_file(L);
    luaopen_mmapfile(L);
    luaopen_cfunc(L);
    luaopen_ximage(L);
    luaopen_ximagehelper(L);
    luaopen_idlparser(L);
	luaopen_tasktimer(L);
    luaopen_messagepeer(L);
    luaopen_screen(L);
    luaopen_serversidepeer(L);
	luaopen_lexer(L);
	luaopen_lexercpp(L);
    luaopen_lexerlua(L);
	luaopen_websocketmessage(L);
	luaopen_tcpsocket(L);
    luaopen_websocketserver(L);
    luaopen_win32(L);
    luaopen_udpsocket(L);
    luaopen_luawindowbase(L);
    luaopen_luabutton(L);
    luaopen_luaeditbox(L);
    luaopen_luahdc(L);
	luaopen_memdc(L);
    luaopen_ximagegif(L);
    luaopen_gifencoder(L);
    luaopen_xml(L);
    luaopen_xmlnode(L);

    const char *work_folder = g_globals.GetWorkFolder();

    CMemStk all_common_lua_folders;
    all_common_lua_folders.Init(32);

    g_globals.GetAllCommonLuaFolders(&all_common_lua_folders);

    for(int i = 0; i < all_common_lua_folders.GetLen(); i++)
    {
        CMem *pmem = all_common_lua_folders.GetElem(i);
        g_globals.AddLuaSearchPath(L,pmem->CStr(),"path","lua",true);
        g_globals.AddLuaSearchPath(L,pmem->CStr(),"cpath","dll",true);
    }
    
    const char *path = p_TreeNode->GetPathStr();
    g_globals.AddLuaSearchPath(L,path,"path","lua",true);
    g_globals.AddLuaSearchPath(L,path,"cpath","dll",true);
    return OK;
}

status_t CLuaThread::Log(const char *szFormat, ...)
{   
    ASSERT(szFormat);
    MAKE_VARGS_BUFFER(szFormat);    
    
    if(this->IsInThisThread())
    {        
        BEGIN_NEW_CLOSURE(run_on_main_thread)
        {
            CLOSURE_PARAM_PTR(char*,szBuffer,10);
            syslog_puts(LOG_MODULE_COMMON,LOG_LEVEL_ERROR,szBuffer);     
            return OK;
        }
        END_NEW_CLOSURE(run_on_main_thread);

        run_on_main_thread->Malloc(10,szBuffer,strlen(szBuffer)+1);
        GLOBAL_MAIN_TASK_RUNNER(runner);
        runner->AddClosure(run_on_main_thread,0);
    }
    else
    {
        syslog_puts(LOG_MODULE_COMMON,LOG_LEVEL_ERROR,szBuffer);
    }

    return OK;
}

status_t CLuaThread::Stop()
{
	CThread::Stop();
    _lua_running_flag = 0;
    return OK;
}

status_t CLuaThread::ReportLuaError()
{
    lua_State *L = m_LuaVm.GetLuaState();
    const char *msg = lua_tostring(L, -1);
    if(msg)
    {        
        CMem mem(msg);
        LOCAL_MEM(line);
        mem.Seek(0);

        while(mem.ReadLine(&line))
        {
            this->Log("%s",line.CStr());
        }
        lua_pop(L, 1);
    }
    return OK;
}

status_t CLuaThread::OnThreadBegin()
{
    callback_on_window_message = LUA_REFNIL;
	callback_on_app_event = LUA_REFNIL;
    _lua_running_flag = 1;
	memset(m_DelayUnloadModules,0,sizeof(m_DelayUnloadModules));

	crt_chdir(g_globals.GetWorkFolder());

    m_TaskMgr.Init(1024);
    
    GLOBAL_MAIN_FORM(main_form);    
    main_form->SetStatusText(0,"lua vm is running");

    this->SwitchToPageText();
    m_ThreadId = crt_get_current_thread_id();   

    g_peer_globals.Init(&m_TaskMgr);
    g_peer_globals.SetTrustMode(true);

    m_TaskRunner.Init();

    this->InitLuaVm();
    return OK;
}

status_t CLuaThread::OnThreadEnd()
{
    callback_on_window_message = LUA_REFNIL;
	callback_on_app_event = LUA_REFNIL;   
    GLOBAL_MAIN_FORM(main_form);
    main_form->SetStatusText(0,"lua vm is not running");
    m_TaskRunner.Destroy();
    g_peer_globals.Destroy();	    
    m_TaskMgr.Destroy(); 
    m_LuaVm.Destroy();	
    HideEmbeddedUIWindow();
	FreeAllModules();
	CSocket::EndNet();
    return OK;
}

status_t CLuaThread::LoadText(CMem *utf8)
{
    ASSERT(utf8);

    ASSERT(IsInThisThread());
    int is_complete = 0;

    BEGIN_NEW_CLOSURE(task)
    {
        CLOSURE_PARAM_PTR(CMem*,utf8,10);
        CLOSURE_PARAM_PTR(int*,p_is_complete,11);

        CEditBox *eb = g_globals.GetTheEditBox();
        ASSERT(eb);

        LOCAL_MEM(tmp);
        eb->GetText_File(&tmp);

        utf8->Destroy();
        utf8->Init();
        utf8->Malloc((int)(tmp.GetSize())*3);
        CEncoder::UnicodeToUtf8(&tmp,utf8);
        *p_is_complete = 1;
        return OK;
    }
    END_NEW_CLOSURE(task);

    task->SetParamPointer(10,utf8);
    task->SetParamPointer(11,&is_complete);

    GLOBAL_MAIN_TASK_RUNNER(main_runner);
    main_runner->AddClosure(task,0);

    //wait main thread to complete
    while(!is_complete)
    {
        crt_msleep(10);
    }

    return OK;
}

CLuaVm* CLuaThread::GetLuaVm()
{
	return &m_LuaVm;
}

status_t CLuaThread::MainLoop()
{
    SetIsMainLoopRunning(true);
	while(m_IsRunning)
	{
        m_TaskRunner.Schedule();
		m_TaskMgr.Schedule();
		crt_msleep(10);
	}
    SetIsMainLoopRunning(false);
	return OK;
}

CTaskMgr* CLuaThread::GetTaskMgr()
{
	return &m_TaskMgr;
}

status_t CLuaThread::GetCurrentPath(const char *rpath,CMem *out)
{
    ASSERT(rpath && out);
    ASSERT(p_TreeNode);

    CMem *self_path = p_TreeNode->GetPath();
    ASSERT(self_path);

    out->SetSize(0);
    out->Puts(self_path);
    out->Putc(crt_get_path_splitor());
    out->Puts(rpath);

    CDirMgr::ToAbsPath(out);
    return OK;
}

status_t CLuaThread::SetPrintBufferFlushInterval(uint32_t interval)
{
	ASSERT(IsInThisThread());

	BEGIN_NEW_CLOSURE(c)
	{
		GLOBAL_PRINT_BUFFER(buf);
		CLOSURE_PARAM_INT(interval,10);
		buf->StartAutoSyncTimer(interval);
		return OK;
	}
	END_NEW_CLOSURE(c);
	
	c->SetParamInt(10,interval);
	GLOBAL_MAIN_TASK_RUNNER(runner);
	runner->AddClosure(c,0);
	return OK;
}

status_t CLuaThread::SwitchToPageText()
{
    GLOBAL_MAIN_FORM(form);
    return form->SwitchToPageText();
}

status_t CLuaThread::SwitchToPageImage()
{
    GLOBAL_MAIN_FORM(form);
    return form->SwitchToPageImage();
}

int CLuaThread::GetCurrentUser()
{
    ASSERT(p_TreeNode);
    return p_TreeNode->GetCurrentUser();
}

CTaskRunner* CLuaThread::GetTaskRunner()
{
    return &m_TaskRunner;
}

status_t CLuaThread::OnWin32Message(MSG *msg)
{
    GLOBALS(g);
    ASSERT(g->IsOnMainThread());
    
    if(!m_IsRunning)
        return ERROR;
    if(!IsMainLoopRunning())
        return ERROR;
    if(callback_on_window_message == LUA_REFNIL)
        return ERROR;

    #define INDEX_THIS 10
    #define INDEX_RUN_END 11
    #define INDEX_MSG 12

    BEGIN_NEW_CLOSURE(run)
    {
        CLOSURE_PARAM_PTR(CLuaThread*,self,INDEX_THIS);
        CLOSURE_PARAM_PTR(MSG*,msg,INDEX_MSG);
    
        if(!self->m_IsRunning)return ERROR;
        CLuaVm *vm = &self->m_LuaVm;
        ASSERT(vm);
        
        win32_callback_onwindowmessage(vm->GetLuaState(),
           self->callback_on_window_message,false,
            (uint32_t)msg->hwnd,msg->message,msg->wParam,msg->lParam
        );       
        return OK;
    }
    END_NEW_CLOSURE(run);

    run->SetParamPointer(INDEX_THIS,this);
    run->Malloc(INDEX_MSG,msg,sizeof(MSG));

    m_TaskRunner.AddClosure(run,0);
    return OK;
}

status_t CLuaThread::FreeAllModules()
{
	ASSERT(IsInThisThread());

	for(int i = 0; i < MAX_MODULES_SIZE; i++)
	{
		if(m_DelayUnloadModules[i] == NULL)
			break;
		::FreeLibrary(m_DelayUnloadModules[i]);
		m_DelayUnloadModules[i] = NULL;
	}
	
	return OK;
}

status_t CLuaThread::ShowEmbeddedUIWindow(int height)
{
    ASSERT(IsInThisThread());
	BEGIN_NEW_CLOSURE(on_main_thread)
	{
		CLOSURE_PARAM_INT(height,10);		
        CLOSURE_PARAM_PTR(int*,run_end,11);
		GLOBAL_MAIN_FORM(main_form);
		main_form->ShowEmbeddedUIWindow(height);
		main_form->OnSize(0,0);
        *run_end = 1;
		return OK;
	}
	END_NEW_CLOSURE(on_main_thread);
	
    //only one thread ,so use static variable
    static int run_end = 0;  
    
    run_end = 0;
	on_main_thread->SetParamInt(10,height);	    
    on_main_thread->SetParamPointer(11,&run_end);

	GLOBAL_MAIN_TASK_RUNNER(runner);
	runner->AddClosure(on_main_thread,0);

    while(!run_end && m_IsRunning)
    {
        crt_msleep(10);
    }

	return OK;
}

status_t CLuaThread::HideEmbeddedUIWindow()
{
    ASSERT(IsInThisThread());

	BEGIN_NEW_CLOSURE(on_main_thread)
	{		
        CLOSURE_PARAM_PTR(int*,run_end,11);
		GLOBAL_MAIN_FORM(main_form);
		main_form->HideEmbeddedUIWindow();
		main_form->OnSize(0,0);
        *run_end = 1;
		return OK;
	}
	END_NEW_CLOSURE(on_main_thread);
	
    //only one thread ,so use static variable
    static int run_end = 0;   

    run_end = 0;
    on_main_thread->SetParamPointer(11,&run_end);

	GLOBAL_MAIN_TASK_RUNNER(runner);
	runner->AddClosure(on_main_thread,0);

    while(!run_end && m_IsRunning)
    {
        crt_msleep(10);
    }
	return OK;
}

status_t CLuaThread::OnAppEvent(int event, CMem *mem)
{
	if(!m_IsRunning)
        return ERROR;
    if(!IsMainLoopRunning())
        return ERROR;
    if(callback_on_app_event == LUA_REFNIL)
        return ERROR;
	
	if(this->IsInThisThread())
	{
		app_callback_onappevent(m_LuaVm.GetLuaState(),callback_on_app_event,false,event,mem);
	}
	else
	{
		BEGIN_NEW_CLOSURE(on_lua_thread)
		{
			CLOSURE_PARAM_PTR(CLuaThread*,self,10);
			CLOSURE_PARAM_PTR(char*,buf,11);
			CLOSURE_PARAM_INT(event,12);
			int size = closure->GetMallocSize(11);
			
			ASSERT(size > 0);

			CMem data;
			data.Init();
			data.SetRawBuf(buf,size,true);

			self->OnAppEvent(event,&data);
			return OK;
		}
		END_NEW_CLOSURE(on_lua_thread);

		on_lua_thread->SetParamPointer(10,this);
		on_lua_thread->Malloc(11,mem->GetRawBuf(),(int)mem->GetSize());
		on_lua_thread->SetParamInt(12,event);
		m_TaskRunner.AddClosure(on_lua_thread,0);		
	}
	return OK;
}

