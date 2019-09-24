#include "idlword.h"
#include "syslog.h"
#include "mem_tool.h"

CIdlWord::CIdlWord()
{
	this->InitBasic();
}
CIdlWord::~CIdlWord()
{
	this->Destroy();
}
status_t CIdlWord::InitBasic()
{
	this->m_Name.InitBasic();
	return OK;
}
status_t CIdlWord::Init()
{
	this->InitBasic();
	this->m_Name.Init();
	return OK;
}
status_t CIdlWord::Destroy()
{
	this->m_Name.Destroy();
	this->InitBasic();
	return OK;
}
int CIdlWord::Comp(CIdlWord *_p)
{
	ASSERT(_p);
	if(this==_p)return 0;
	return m_Name.StrCmp(&_p->m_Name);
}
status_t CIdlWord::Copy(CIdlWord *_p)
{
	ASSERT(_p);
	if(this == _p)return OK;
	this->m_Name.Copy(&_p->m_Name);
	return OK;
}
status_t CIdlWord::Print(CFileBase *_buf)
{
	const char* _str_name = "<null>";
	if(this->m_Name.StrLen() > 0)
		_str_name = m_Name.CStr();
	_buf->Log("Name = %s",_str_name);
	return OK;
}
CMem* CIdlWord::GetName()
{
	return &this->m_Name;
}
const char* CIdlWord::GetNameStr()
{
	return this->m_Name.CStr();
}
status_t CIdlWord::SetName(CMem* _name)
{
	this->m_Name.Copy(_name);
	return OK;
}
status_t CIdlWord::SetName(const char *_name)
{
	CMem _mem(_name);
	return this->SetName(&_mem);
}
const char * CIdlWord::CStr()
{
    return m_Name.CStr();
}
