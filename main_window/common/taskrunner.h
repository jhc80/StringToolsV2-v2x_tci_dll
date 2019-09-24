#ifndef __S2_TASKRUNNER_H
#define __S2_TASKRUNNER_H

#include "cruntime.h"
#include "filebase.h"
#include "closurelist.h"
#include "mutex.h"

class CTaskRunner{
public:
    CClosureList m_ClosureList;
    uint32_t m_LastTimerVal;
    CMutex m_Mutex;
public:
    int Schedule();
    status_t AddClosure(CClosure *closure,uint32_t delay);
    CTaskRunner();
    virtual ~CTaskRunner();
    status_t InitBasic();
    status_t Init();
    status_t Destroy();

    status_t Copy(CTaskRunner *p);
    status_t Print(CFileBase *_buf);
};

#endif
