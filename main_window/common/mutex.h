#ifndef __CMUTEX_H
#define __CMUTEX_H

#include "cruntime.h"

class CMutex  
{
public:
    MUTEX_TYPE m_Mutex;
    bool m_Initialized;
public:
    CMutex();
    virtual ~CMutex();
    status_t Unlock();
    status_t Lock();
    status_t Destroy();
    status_t Init();
    status_t InitBasic();
};

#endif 

