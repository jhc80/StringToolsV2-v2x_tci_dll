#include "idlvariable.h"
#include "syslog.h"
#include "mem_tool.h"

CIdlVariable::CIdlVariable()
{
	this->InitBasic();
}
CIdlVariable::~CIdlVariable()
{
	this->Destroy();
}
status_t CIdlVariable::InitBasic()
{
	this->m_Name.InitBasic();
	this->m_Flags = 0;
	this->m_Hint.InitBasic();
	this->m_Type.InitBasic();
	this->m_InitValue.InitBasic();
	return OK;
}
status_t CIdlVariable::Init()
{
	this->InitBasic();
	this->m_Name.Init();
	this->m_Hint.Init();
	this->m_Type.Init();
	this->m_InitValue.Init();
	return OK;
}
status_t CIdlVariable::Destroy()
{
	this->m_Name.Destroy();
	this->m_Hint.Destroy();
	this->m_Type.Destroy();
	this->m_InitValue.Destroy();
	this->InitBasic();
	return OK;
}
int CIdlVariable::Comp(CIdlVariable *_p)
{
	ASSERT(_p);
	if(this==_p)return 0;
	return 0;
}
status_t CIdlVariable::Copy(CIdlVariable *_p)
{
	ASSERT(_p);
	if(this == _p)return OK;
	this->m_Name.Copy(&_p->m_Name);
	this->m_Flags = _p->m_Flags;
	this->m_Hint.Copy(&_p->m_Hint);
	this->m_Type.Copy(&_p->m_Type);
	this->m_InitValue.Copy(&_p->m_InitValue);
	return OK;
}
status_t CIdlVariable::Print(CFileBase *_buf)
{
	const char* _str_name = "<null>";
	if(this->m_Name.StrLen() > 0)
		_str_name = m_Name.CStr();
	_buf->Log("Name = %s",_str_name);
	_buf->Log("Flags = %d",this->m_Flags);
	_buf->Log("Hint = {");
	_buf->IncLogLevel(1);
	m_Hint.Print(_buf);
	_buf->IncLogLevel(-1);
	_buf->Log("}");
	_buf->Log("Type = {");
	_buf->IncLogLevel(1);
	m_Type.Print(_buf);
	_buf->IncLogLevel(-1);
	_buf->Log("}");
	const char* _str_initvalue = "<null>";
	if(this->m_InitValue.StrLen() > 0)
		_str_initvalue = m_InitValue.CStr();
	_buf->Log("InitValue = %s",_str_initvalue);
	return OK;
}
CMem* CIdlVariable::GetName()
{
	return &this->m_Name;
}
uint32_t CIdlVariable::GetFlags()
{
	return this->m_Flags;
}
CIdlHint* CIdlVariable::GetHint()
{
	return &this->m_Hint;
}
CIdlType* CIdlVariable::GetType()
{
	return &this->m_Type;
}
CMem* CIdlVariable::GetInitValue()
{
	return &this->m_InitValue;
}
const char* CIdlVariable::GetNameStr()
{
	return this->m_Name.CStr();
}
const char* CIdlVariable::GetInitValueStr()
{
	return this->m_InitValue.CStr();
}
status_t CIdlVariable::SetName(CMem* _name)
{
	this->m_Name.Copy(_name);
	return OK;
}
status_t CIdlVariable::SetFlags(uint32_t _flags)
{
	this->m_Flags = _flags;
	return OK;
}
status_t CIdlVariable::SetHint(CIdlHint* _hint)
{
	this->m_Hint.Copy(_hint);
	return OK;
}
status_t CIdlVariable::SetType(CIdlType* _type)
{
	this->m_Type.Copy(_type);
	return OK;
}
status_t CIdlVariable::SetInitValue(CMem* _initvalue)
{
	this->m_InitValue.Copy(_initvalue);
	return OK;
}
status_t CIdlVariable::SetName(const char *_name)
{
	CMem _mem(_name);
	return this->SetName(&_mem);
}
status_t CIdlVariable::SetInitValue(const char *_initvalue)
{
	CMem _mem(_initvalue);
	return this->SetInitValue(&_mem);
}
status_t CIdlVariable::ToLua(CFileBase *buf)
{
    ASSERT(buf);
    buf->Log("name=\"%s\",",GetNameStr());
    
    if(m_Hint.GetHintsLen() > 0)
    {
        buf->Log("hint = {");
        buf->IncLogLevel(1);
        m_Hint.ToLua(buf);
        buf->IncLogLevel(-1);
        buf->Log("},");
    }

    buf->Log("type = {");
    buf->IncLogLevel(1);
    m_Type.ToLua(buf);
    buf->IncLogLevel(-1);
    buf->Log("},");

    if(HasInitValue())
    {
        buf->Log("init_value=[[%s]],",GetInitValueStr());
    }

    buf->Log("flags=0x%x,",m_Flags);
    return OK;
}
