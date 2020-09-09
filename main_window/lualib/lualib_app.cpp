#include "lualib_app.h"
#include "mem_tool.h"
#include "syslog.h"
#include "globals.h"
#include "encoder.h"
#include "peerglobals.h"
#include "tasktcpacceptor.h"
#include "taskpeerserver.h"
#include "lualib_mem.h"
#include "lualib_stream.h"
#include "lualib_filebase.h"
#include "lualib_peerproxy.h"
#include "lua_print.h"
#include "lua_helper.h"
/****************************************/
static int app_getsystemtimer(lua_State *L)
{
    int _ret_0 = (int)crt_get_sys_timer();
    lua_pushinteger(L,_ret_0);
    return 1;
}
static int app_addluasearchpath(lua_State *L)
{
    const char* path = (const char*)lua_tostring(L,1);
    const char* type = (const char*)lua_tostring(L,2);
    const char* ext = (const char*)lua_tostring(L,3);
    int recursive = (int)lua_toboolean(L,4);
    GLOBALS(g);
    g->AddLuaSearchPath(L,path,type,ext,recursive!=0);
    return 0;
}
static int app_sleep(lua_State *L)
{
    int sleep_time = (int)lua_tointeger(L,1);    
    int start = crt_get_sys_timer();
    int now = start;

    GLOBAL_LUA_THREAD(lua_thread);
    while(lua_thread->IsRunning())
    {
        now = crt_get_sys_timer();
        if(now - start >= sleep_time)
            break;
        crt_msleep(10);
    }
    return 0;
}
static int app_clear_screen(lua_State *L)
{
	g_globals.ClearScreen();
    return 0;
}
static int app_loadtext(lua_State *L)
{
    GLOBAL_LUA_THREAD(lua_thread);
    CMem *utf8;
    NEW(utf8,CMem);
    utf8->Init();
    lua_thread->LoadText(utf8);
    mem_new_userdata(L,utf8,0);
    return 1;
}
static int app_cleartextbuf(lua_State *L)
{
    GLOBAL_LUA_THREAD(lua_thread);
    ASSERT(lua_thread->IsInThisThread());

    GLOBAL_PRINT_BUFFER(buf);   
    //wait at least one sync timer fired
    buf->SetTextSynced(false);
    while(!buf->IsTextSynced() && lua_thread->IsRunning())
    {
        crt_msleep(1);
    }

    buf->Lock();
    buf->ClearAll();
    buf->Unlock();
    return 0;
}
static int app_savetextbuf(lua_State *L)
{   
    const char* filename = (const char*)lua_tostring(L,1);
	ASSERT(filename);
    GLOBAL_PRINT_BUFFER(buf);
    buf->Lock();
    status_t ret = buf->Save(filename);      
    buf->Unlock();
    lua_pushboolean(L,ret);
    return 1;
}
static int app_mainloop(lua_State *L)
{   
	GLOBAL_LUA_THREAD(lua_thread);
	lua_thread->MainLoop();
    return 0;
}
static int app_quitmainloop(lua_State *L)
{   
    GLOBAL_LUA_THREAD(lua_thread);
    lua_thread->Stop();
    return 0;
}
static int app_getselfpath(lua_State *L)
{
    GLOBAL_LUA_THREAD(lua_thread);
    const char* rpath = "";

    if(lua_isstring(L,1))
    {
        rpath = (const char*)lua_tostring(L,1);
        ASSERT(rpath);
    }

    LOCAL_MEM(mem);
    lua_thread->GetCurrentPath(rpath,&mem);
	lua_push_local_string(L,mem.CStr());
    return 1;
}
static int app_setbufferflushinterval(lua_State *L)
{
	int interval = (int)lua_tointeger(L,1);
	GLOBAL_LUA_THREAD(lua_thread);
	lua_thread->SetPrintBufferFlushInterval(interval);
	return 0;
}
static int app_startbuffer(lua_State *L)
{
    int interval = 30;
    if(lua_isinteger(L,1))
        interval = (int)lua_tointeger(L,1);

    GLOBAL_PRINT_BUFFER(pbuf);
    pbuf->ClearAll();
    GLOBAL_LUA_THREAD(lua_thread);
    lua_thread->SetPrintBufferFlushInterval(interval);
    return 0;
}
static int app_stopbuffer(lua_State *L)
{
    int interval = (int)lua_tointeger(L,1);
    GLOBAL_LUA_THREAD(lua_thread);
    lua_thread->SetPrintBufferFlushInterval(-1);
    return 0;
}
static status_t app_getbuffersize(lua_State *L)
{
	GLOBAL_PRINT_BUFFER(pbuf);
    lua_pushinteger(L,pbuf->GetDataSize());
    return 1;
}
static int app_base64encode(lua_State *L)
{
    CFileBase *infile = get_filebase(L,1);
    ASSERT(infile);
    CFileBase *outfile = get_filebase(L,2);
    ASSERT(outfile);
    
    GLOBAL_LUA_THREAD(lua_thread);
    ASSERT(lua_thread->IsInThisThread());
    
    if(!CEncoder::Base64_Encode_Interruptable(infile,outfile,&lua_thread->m_IsRunning))
        return 0;
    
    lua_pushboolean(L,1);
    return 1;
}
static int app_base64decode(lua_State *L)
{
    CFileBase *infile = get_filebase(L,1);
    ASSERT(infile);
    CFileBase *outfile = get_filebase(L,2);
    ASSERT(outfile);
    
    GLOBAL_LUA_THREAD(lua_thread);
    ASSERT(lua_thread->IsInThisThread());
    
    if(!CEncoder::Base64_Decode_Interruptable(infile,outfile,&lua_thread->m_IsRunning))
        return 0;
    
    lua_pushboolean(L,1);
    return 1;
}
static status_t on_accept(CClosure *closure)
{
    CLOSURE_PARAM_INT(event,0);
    CLOSURE_PARAM_PTR(CTaskMgr*,mgr,10);
	CLOSURE_PARAM_PTR(lua_State*,L,11);
	ASSERT(mgr);
    
    if(event == CTaskTcpAcceptor::EVENT_NEW_CLIENT)
    {
        CLOSURE_PARAM_INT(fd,1);
        CTaskPeerServer *server;
        NEW(server,CTaskPeerServer);
        server->Init(mgr,how_to_get_peer_globals(L));
        server->SetMaxRetries(1);
        server->SetSocket(fd);
        server->Start();
    }
    return OK;
}
static status_t start_message_center(lua_State *L,int port)
{
    CTaskTcpAcceptor *acceptor;   
	
    GLOBAL_LUA_THREAD(lua_thread);
    
	NEW(acceptor,CTaskTcpAcceptor);
    acceptor->Init(lua_thread->GetTaskMgr());
    acceptor->SetListenPort(port);	
    acceptor->Callback()->SetFunc(on_accept);
    acceptor->Callback()->SetParamPointer(10,lua_thread->GetTaskMgr());
	acceptor->Callback()->SetParamPointer(11,L);
    acceptor->Start();
    return OK;
}
//////////////////////////////////////
static int app_startmessagecenter(lua_State *L)
{
    int port = (int)lua_tointeger(L,1);
	int trust_mode = lua_toboolean(L,2);
    GLOBAL_LUA_THREAD(lua_thread);
    CPeerGlobals *g = lua_thread->GetPeerGlobals();
    ASSERT(g);
	g->SetTrustMode(trust_mode!=0);
    int _ret_0 = (int)start_message_center(L,port);
    lua_pushinteger(L,_ret_0);
    return 1;
}


static status_t app_getallpeers(lua_State *L)
{
	GLOBAL_LUA_THREAD(lua_thread);
    CPeerGlobals *g = lua_thread->GetPeerGlobals();
	ASSERT(g);
    
	CPeerProxyManager *mgr = g->GetPeerProxyManager();
	ASSERT(mgr);

    if(mgr->GetTotalPeers() <= 0)
        return 0;

    lua_newtable(L);
    int top = lua_gettop(L);
    
	for(int i = 0; i < mgr->GetTotalPeers(); i++)
	{
        lua_pushinteger(L,i+1);
        peerproxy_new_userdata(L,mgr->GetPeer(i),1);
        lua_settable(L, top);    
	}

    return 1;
}

///////////////////////////////////
static int app_startnet(lua_State *L)
{
    CSocket::StartNet();
    return 0;
}
static int app_endnet(lua_State *L)
{
    CSocket::EndNet();
    return 0;
}
static int app_switchtopagetext(lua_State *L)
{
    GLOBAL_MAIN_FORM(main_form);
    int _ret_0 = (int)main_form->SwitchToPageText();
    lua_pushboolean(L,_ret_0);
    return 1;
}
static int app_switchtopageimage(lua_State *L)
{
    GLOBAL_MAIN_FORM(main_form);
    int _ret_0 = (int)main_form->SwitchToPageImage();
    lua_pushboolean(L,_ret_0);
    return 1;
}
static int app_getcurrentuser(lua_State *L)
{
    GLOBAL_LUA_THREAD(lua_thread);
    lua_pushinteger(L,lua_thread->GetCurrentUser());
    return 1;
}

static int app_dumpfile(lua_State *L)
{
    CFileBase *file = get_filebase(L,1);
    ASSERT(file);

    GLOBAL_PRINT_BUFFER(print_buf);
    print_buf->Lock();
    CMemFile *data = print_buf->GetTextData();
    if(data->GetSize()+file->GetSize() < MAX_BUFFER_SIZE)
        data->WriteFile(file);
	print_buf->Unlock();
    
    return 0;
}

static int app_gc(lua_State *L)
{
    CLuaVm vm;
    vm.Init(L);
    vm.FullGC();
    return 0;
}

static status_t app_quittask(lua_State *L)
{
    int taskid = (int)lua_tointeger(L,1);

	GLOBAL_LUA_THREAD(lua_thread);
	ASSERT(lua_thread->IsInThisThread());
	ASSERT(lua_thread->GetTaskMgr());
	lua_thread->GetTaskMgr()->QuitTask(&taskid);
    return 0;
}

static status_t app_setstatustext(lua_State *L)
{
    int part = (int)lua_tointeger(L,1);
    const char* text = (const char*)lua_tostring(L,2);
    ASSERT(text);

    GLOBAL_MAIN_FORM(main_form);
    status_t ret0 = main_form->SetStatusText(part,text);
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t app_getcurline(lua_State *L)
{   
    LOCAL_MEM_WITH_SIZE(text,16*1024);
    
    BEGIN_NEW_CLOSURE(run)
    {
        CLOSURE_PARAM_PTR(CMem*,ptext,10);
        CLOSURE_PARAM_PTR(int*,prun_end,11);    
        GLOBALS(g);
        g->GetCurLine(ptext);        
        *prun_end = 1;
        return OK;
    }
    END_NEW_CLOSURE(run);
    
    int run_end = 0;
    run->SetParamPointer(10,&text);
    run->SetParamPointer(11,&run_end);

    GLOBAL_MAIN_TASK_RUNNER(task_runner);
    task_runner->AddClosure(run,0);
    
    GLOBAL_LUA_THREAD(lua_thread);
    while(!run_end && lua_thread->IsRunning());
    {
        crt_msleep(10);
    }

    if(!lua_thread->IsRunning())    
        return 0;
    lua_pushlstring(L,text.CStr(),text.StrLen());
    return 1;
}

#define HWND_EDIT_BOX	 1
#define HWND_MAIN_FORM	 2
#define HWND_EMBEDDED_UI 3

static status_t app_gethwnd(lua_State *L)
{
    int type = (int)lua_tointeger(L,1);    
	
	if(type == HWND_MAIN_FORM)
	{
		GLOBAL_MAIN_FORM(main_form);
		lua_pushinteger(L,(uint32_t)main_form->hwnd);	
		return 1;
	}

	if(type == HWND_EDIT_BOX)
	{
		GLOBAL_PAGE_TEXT(page_text);
		lua_pushinteger(L,(uint32_t)page_text->eb_log->hwnd);	
		return 1;
	}

	if(type == HWND_EMBEDDED_UI)
	{
		GLOBAL_MAIN_FORM(main_form);
		if(main_form->m_WndEmbeddedUI)
		{
			lua_pushinteger(L,(uint32_t)main_form->m_WndEmbeddedUI->hwnd);	
			return 1;
		}
	}
   
	return 0;
}

static status_t app_showembeddeduiwindow(lua_State *L)
{
    int height = (int)lua_tointeger(L,1);
	GLOBAL_LUA_THREAD(lua_thread);
	lua_thread->ShowEmbeddedUIWindow(height);
	return 0;
}

static status_t app_hideembeddeduiwindow(lua_State *L)
{	
	GLOBAL_LUA_THREAD(lua_thread);
	lua_thread->HideEmbeddedUIWindow();
    return 0;
}

status_t app_callback_onappevent(lua_State *L, int _funcid, bool _once, int event, CMem *mem)
{

    if(_funcid == LUA_REFNIL)
    {
        return ERROR;
    }
	
    CLuaVm vm;
    vm.Init(L);
    lua_rawgeti(L,LUA_REGISTRYINDEX,_funcid);
    if(_once)
    {
        luaL_unref(L,LUA_REGISTRYINDEX,_funcid);
    }
    lua_pushinteger(L,event);
	if(mem)
    {
		mem_new_userdata(L,mem,1);
		vm.Run(2,0);
	}
	else
	{
		vm.Run(1,0);
	}

    vm.ClearStack();
    return OK;
}

static status_t app_setonappevent(lua_State *L)
{
    int onappevent = CLuaVm::ToFunction(L,1);
	GLOBAL_LUA_THREAD(lua_thread);
	CLuaVm::ReleaseFunction(L,lua_thread->callback_on_app_event);
	lua_thread->callback_on_app_event = onappevent;
    return 0;
}

static status_t app_userstopped(lua_State *L)
{
    GLOBALS(g);
    bool ret0 = g->UserStopped();
    lua_pushboolean(L,ret0);
    return 1;
}

static status_t app_waitbuffer(lua_State *L)
{
    GLOBAL_PRINT_BUFFER(buf);
    GLOBAL_LUA_THREAD(lua_thread);
    while(!buf->IsTextSynced() && lua_thread->IsRunning())
    {
        crt_msleep(1);
    }
    return 0;
}

static const luaL_Reg app_lib[] = {
    {"GetSystemTimer",app_getsystemtimer},
    {"AddLuaSearchPath",app_addluasearchpath},
    {"Sleep",app_sleep},
	{"ClearScreen",app_clear_screen},
	{"LoadText",app_loadtext},
    {"ClearBuffer",app_cleartextbuf},
	{"SaveBuffer",app_savetextbuf},
	{"SetBufferFlushInterval",app_setbufferflushinterval},
    {"StopBuffer",app_stopbuffer},
    {"StartBuffer",app_startbuffer},
    {"GetBufferSize",app_getbuffersize},
	{"MainLoop",app_mainloop},
    {"QuitMainLoop",app_quitmainloop},
	{"GetSelfPath",app_getselfpath},
	{"Base64Encode",app_base64encode},
    {"Base64Decode",app_base64decode},
    {"StartMessageCenter",app_startmessagecenter},
	{"GetAllPeers",app_getallpeers},	
    {"StartNet",app_startnet},
	{"EndNet",app_endnet},
    {"SwitchToPageText",app_switchtopagetext},
	{"SwitchToPageImage",app_switchtopageimage},
    {"GetCurrentUser",app_getcurrentuser},
	{"DumpFile",app_dumpfile},
    {"QuitTask",app_quittask},
    {"Gc",app_gc},
    {"SetStatusText",app_setstatustext},
    {"GetCurLine",app_getcurline},	
    {"GetHWnd",app_gethwnd},	
    {"ShowEmbeddedUIWindow",app_showembeddeduiwindow},
    {"HideEmbeddedUIWindow",app_hideembeddeduiwindow},
    {"SetOnAppEvent",app_setonappevent},    
    {"UserStopped",app_userstopped},    
    {"WaitBuffer",app_waitbuffer},
    {NULL, NULL}
};
static int luaL_register_app(lua_State *L)
{   
    luaL_newmetatable(L, LUA_USERDATA_APP);
    lua_pushvalue(L, -1);   
    lua_setfield(L, -2, "__index"); 
    luaL_setfuncs(L,app_lib,0);
    lua_pop(L, 1);
    luaL_newlib(L,app_lib);
    return 1;
}

int luaopen_app(lua_State *L)
{
    luaL_requiref(L, "App",luaL_register_app,1);
    lua_pop(L, 1);
    return 0;
}
