#include "lua_button.h"
#include "syslog.h"
#include "mem_tool.h"
#include "globals.h"

CLuaButton::CLuaButton()
{
    this->InitBasic();
}

CLuaButton::~CLuaButton()
{
    this->Destroy();
}

status_t CLuaButton::InitBasic()
{
    CLuaWindowBase::InitBasic();
    return OK;
}

status_t CLuaButton::Init()
{
    this->InitBasic();
    CLuaWindowBase::Init();
    return OK;
}

status_t CLuaButton::Destroy()
{
    CLuaWindowBase::Destroy();
    this->InitBasic();
    return OK;
}

status_t CLuaButton::Create()
{
    GLOBAL_LUA_THREAD(lua_thread);
    ASSERT(lua_thread->IsInThisThread());

    BEGIN_NEW_CLOSURE(on_main_thread)
    {
        CLOSURE_PARAM_WEAKPTR(CLuaButton*,self,10);        
        CLOSURE_PARAM_PTR(int*,run_end,11);
        self->CreateCtrl(L"BUTTON");    
        *run_end = 1;
        return OK;
    }
    END_NEW_CLOSURE(on_main_thread);
    
    on_main_thread->SetParamWeakPointer(10,this,__weak_ref_id);    

    static int run_end = 0;
    run_end = 0;
    on_main_thread->SetParamPointer(11,&run_end);
    GLOBAL_MAIN_TASK_RUNNER(runner);
    runner->AddClosure(on_main_thread,0);

    while(!run_end && lua_thread->IsRunning())
    {
        crt_msleep(10);
    }

    return OK;
}

