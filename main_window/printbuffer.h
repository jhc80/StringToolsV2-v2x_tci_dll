#ifndef __S2_PRINTBUFFER_H
#define __S2_PRINTBUFFER_H

#include "cruntime.h"
#include "memfile.h"
#include "mutex.h"
#include "taskmgr.h"
#include "closure.h"
#include "comnctls.h"
#include "partfile.h"

class CPrintBuffer{
public:
	enum{
		EVENT_SYNC_NEW_TEXT = 1,
	};

	TASK_CONTAINER_DEFINE();
public:
	CMutex m_Mutex;
	int m_PrintPosition;
	CMemFile m_TextData;
	CClosure m_Callback;
	int m_TaskAutoSyncTimer;
    bool m_TextSynced;
public:
	int GetDataSize();
	bool IsTextSynced();
	status_t SetTextSynced(bool synced);
	status_t Save(const char *filename);
	static status_t AddDataToEditBox(CFileBase *new_data, CEditBox *eb);
	status_t ClearAll();
	status_t OnAutoSyncTimerFired();
	status_t StopAutoSyncTimer();
	status_t StartAutoSyncTimer(uint32_t interval);
	CClosure* Callback();
	CMemFile* GetTextData();
	status_t Unlock();
	status_t Lock();
	CPrintBuffer();
	virtual ~CPrintBuffer();
	status_t InitBasic();
	status_t Init();
	status_t Destroy();
	int GetPrintPosition();
	int GetDataPosition();
	status_t SetPrintPosition(int _printposition);
};

#endif
