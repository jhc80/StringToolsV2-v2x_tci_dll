#include "taskrunner.h"
#include "syslog.h"
#include "mem_tool.h"

struct closure_extra_info{
    uint32_t total_delay;
    uint32_t cur_delay;
};

CTaskRunner::CTaskRunner()
{
    this->InitBasic();
}
CTaskRunner::~CTaskRunner()
{
    this->Destroy();
}
status_t CTaskRunner::InitBasic()
{
    m_ClosureList.InitBasic();
    m_LastTimerVal = 0;
    m_Mutex.InitBasic();
    return OK;
}
status_t CTaskRunner::Init()
{
    this->InitBasic();
    m_ClosureList.Init(1024);
    m_LastTimerVal = crt_get_sys_timer();
    m_Mutex.Init();
    return OK;
}
status_t CTaskRunner::Destroy()
{
    m_ClosureList.Destroy();
    m_Mutex.Destroy();
    this->InitBasic();
    return OK;
}
status_t CTaskRunner::Copy(CTaskRunner *p)
{
    ASSERT(0);
    return OK;
}

status_t CTaskRunner::Print(CFileBase *_buf)
{
    ASSERT(0);
    return OK;
}

status_t CTaskRunner::AddClosure(CClosure *closure,uint32_t delay)
{
    ASSERT(closure);
    ASSERT(closure->IsOnHeap());

    struct closure_extra_info *info = (struct closure_extra_info *)
        closure->Malloc(MAX_PARAMS-1,sizeof(struct closure_extra_info));
    
    ASSERT(info);
    info->cur_delay = 0;
    info->total_delay = delay;

    m_Mutex.Lock();
    status_t ret = m_ClosureList.PushPtr(closure);
    m_Mutex.Unlock();

    return ret;
}

int CTaskRunner::Schedule()
{
    uint32_t now = crt_get_sys_timer();
    uint32_t interval = now - m_LastTimerVal;
    m_LastTimerVal = now;

    int has_zero_delay_tasks = 0;

    for(int i = 0; i < m_ClosureList.GetLen(); i++)
    {
        CClosure *closure = m_ClosureList.GetElem(i);
        CLOSURE_PARAM_PTR(struct closure_extra_info *,info,MAX_PARAMS-1);

        if(info->total_delay == 0)
            has_zero_delay_tasks ++;

        info->cur_delay += interval;
        if(info->cur_delay >= info->total_delay)
        {
            closure->Run();
            
            m_Mutex.Lock();
            m_ClosureList.DelElem(i);
            m_Mutex.Unlock();

            i--;
        }
    }

    return has_zero_delay_tasks;
}

