#include "idlmodule.h"
#include "syslog.h"
#include "mem_tool.h"

CIdlModule::CIdlModule()
{
	this->InitBasic();
}
CIdlModule::~CIdlModule()
{
	this->Destroy();
}
status_t CIdlModule::InitBasic()
{
	this->m_AllClasses.InitBasic();
	return OK;
}
status_t CIdlModule::Init()
{
	this->InitBasic();
	this->m_AllClasses.Init(64);
	return OK;
}
status_t CIdlModule::Destroy()
{
	this->m_AllClasses.Destroy();
	this->InitBasic();
	return OK;
}
int CIdlModule::Comp(CIdlModule *_p)
{
	ASSERT(_p);
	if(this==_p)return 0;
	return 0;
}
status_t CIdlModule::Copy(CIdlModule *_p)
{
	ASSERT(_p);
	if(this == _p)return OK;
	this->m_AllClasses.Copy(&_p->m_AllClasses);
	return OK;
}
status_t CIdlModule::Print(CFileBase *_buf)
{
	_buf->Log("AllClasses = {");
	_buf->IncLogLevel(1);
	m_AllClasses.Print(_buf);
	_buf->IncLogLevel(-1);
	_buf->Log("}");
	return OK;
}
CIdlClassList* CIdlModule::GetAllClasses()
{
	return &this->m_AllClasses;
}
status_t CIdlModule::SetAllClasses(CIdlClassList* _allclasses)
{
	this->m_AllClasses.Copy(_allclasses);
	return OK;
}

status_t CIdlModule::AddIdlClass(CIdlClass *idl_class)
{
    return this->m_AllClasses.PushPtr(idl_class);
}

status_t CIdlModule::ToLua(CFileBase *buf)
{
    return m_AllClasses.ToLua(buf);
}