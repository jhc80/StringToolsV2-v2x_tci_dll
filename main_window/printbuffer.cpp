#include "printbuffer.h"
#include "syslog.h"
#include "mem_tool.h"
#include "globals.h"
#include "tasktimer.h"
#include "partfile.h"
#include "encoder.h"

CPrintBuffer::CPrintBuffer()
{
	this->InitBasic();
}
CPrintBuffer::~CPrintBuffer()
{
	this->Destroy();
}
status_t CPrintBuffer::InitBasic()
{
	TASK_CONTAINER_CLEAR();
	this->m_Mutex.InitBasic();
	this->m_PrintPosition = 0;
	this->m_TextData.InitBasic();
	m_Callback.InitBasic();
	m_TaskAutoSyncTimer = 0;
    m_TextSynced = false;
	return OK;
}
status_t CPrintBuffer::Init()
{
	this->InitBasic();
    
	TASK_CONTAINER_INIT(g_globals.GetTaskMgr());
	this->m_Mutex.Init();
	m_TextData.Init();
	m_Callback.Init();
	return OK;
}
status_t CPrintBuffer::Destroy()
{
	this->StopAutoSyncTimer();
	m_Callback.Destroy();
	m_TextData.Destroy();
	this->m_Mutex.Destroy();
	this->InitBasic();
	return OK;
}
int CPrintBuffer::GetPrintPosition()
{
	return this->m_PrintPosition;
}
int CPrintBuffer::GetDataPosition()
{
	return (int)m_TextData.GetSize();
}
status_t CPrintBuffer::SetPrintPosition(int _printposition)
{
	this->m_PrintPosition = _printposition;
	return OK;
}
status_t CPrintBuffer::Lock()
{
	return m_Mutex.Lock();
}

status_t CPrintBuffer::Unlock()
{
	return m_Mutex.Unlock();
}

CMemFile* CPrintBuffer::GetTextData()
{
	return &m_TextData;
}

CClosure* CPrintBuffer::Callback()
{
	return &m_Callback;
}

status_t CPrintBuffer::StartAutoSyncTimer(uint32_t interval)
{
	this->StopAutoSyncTimer();
    if(interval <= 0)return ERROR;

	CTaskTimer *ptimer = CTaskTimer::NewTimer(GetTaskMgr(),interval,false);
	ASSERT(ptimer);

	BEGIN_CLOSURE_FUNC(on_timer)
	{
		CLOSURE_PARAM_PTR(CPrintBuffer*,self,10);
		self->OnAutoSyncTimerFired();        
		return OK;
	}
	END_CLOSURE_FUNC(on_timer);

	ptimer->Callback()->SetFunc(on_timer);
	ptimer->Callback()->SetParamPointer(10,this);
	ptimer->Start();
	m_TaskAutoSyncTimer = ptimer->GetId();

	return OK;
}

status_t CPrintBuffer::StopAutoSyncTimer()
{
	QuitTask(&m_TaskAutoSyncTimer);
	return OK;
}

status_t CPrintBuffer::OnAutoSyncTimerFired()
{
	if(GetDataPosition() == GetPrintPosition())
    {
        m_TextSynced = true;
        return OK;
    }

	this->Lock();

	CPartFile part;
    
    int size = GetDataPosition() - GetPrintPosition();
    if(size > 256*1024) size = 256*1024;
       
    part.Init();
	part.SetHostFile(&m_TextData,
		GetPrintPosition(),
		size
	);

	m_Callback.SetParamPointer(1,&part);
	m_Callback.Run(EVENT_SYNC_NEW_TEXT);
	this->SetPrintPosition(GetPrintPosition() + size);
    
	this->Unlock();
	return OK;
}

status_t CPrintBuffer::ClearAll()
{
	m_TextData.Destroy();
	m_TextData.Init();
	m_PrintPosition = 0;
	return OK;
}

status_t CPrintBuffer::AddDataToEditBox(CFileBase *new_data, CEditBox *eb)
{
	ASSERT(new_data && eb);
	CMem tmp;
	tmp.Init();
	tmp.Malloc((int)(new_data->GetSize())*sizeof(wchar_t));
	CEncoder::Utf8ToUnicode(new_data,&tmp);
	eb->Puts(tmp.CStrW());
	return OK;
}

status_t CPrintBuffer::Save(const char *filename)
{
    fsize_t old_off = m_TextData.GetOffset();
    fsize_t size = m_TextData.WriteToFile(filename);    
    m_TextData.Seek(old_off);    
    return size > 0;
}

status_t CPrintBuffer::SetTextSynced(bool synced)
{
    m_TextSynced = synced;
    return OK;
}

bool CPrintBuffer::IsTextSynced()
{
    return m_TextSynced;
}

int CPrintBuffer::GetDataSize()
{
	return (int)m_TextData.GetSize();
}
