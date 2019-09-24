#include "mutex.h"
#include "syslog.h"

CMutex::CMutex()
{
    this->InitBasic();
}

CMutex::~CMutex()
{
    this->Destroy();
}

status_t CMutex::InitBasic()
{
    this->m_Initialized = false;
    return OK;
}
status_t CMutex::Init()
{
    if(!this->m_Initialized)
    {
        crt_init_mutex(&m_Mutex);
        this->m_Initialized = true;
    }
    
    return OK;
}

status_t CMutex::Destroy()
{
    if(this->m_Initialized)
    {
        crt_destroy_mutex(&m_Mutex);
    }
    this->InitBasic();
    return OK;
}

status_t CMutex::Lock()
{
    ASSERT(m_Initialized);
    crt_lock_mutex(&m_Mutex);
    return OK;
}

status_t CMutex::Unlock()
{
    ASSERT(m_Initialized);
    crt_unlock_mutex(&m_Mutex);
    return OK;
}
