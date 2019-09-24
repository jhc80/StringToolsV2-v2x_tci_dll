#include "idlparam.h"
#include "syslog.h"
#include "mem_tool.h"

CIdlParam::CIdlParam()
{
	this->InitBasic();
}
CIdlParam::~CIdlParam()
{
	this->Destroy();
}
status_t CIdlParam::InitBasic()
{
	this->m_Name.InitBasic();
	this->m_Hint.InitBasic();
	this->m_Type.InitBasic();
	this->m_DefaultValue.InitBasic();
    m_Flags = 0;
	return OK;
}
status_t CIdlParam::Init()
{
	this->InitBasic();
	this->m_Name.Init();
	this->m_Hint.Init();
	this->m_Type.Init();
	this->m_DefaultValue.Init();
	return OK;
}
status_t CIdlParam::Destroy()
{
	this->m_Name.Destroy();
	this->m_Hint.Destroy();
	this->m_Type.Destroy();
	this->m_DefaultValue.Destroy();
	this->InitBasic();
	return OK;
}
int CIdlParam::Comp(CIdlParam *_p)
{
	ASSERT(_p);
	if(this==_p)return 0;
	return 0;
}
status_t CIdlParam::Copy(CIdlParam *_p)
{
	ASSERT(_p);
	if(this == _p)return OK;
	this->m_Name.Copy(&_p->m_Name);
	this->m_Hint.Copy(&_p->m_Hint);
	this->m_Type.Copy(&_p->m_Type);
    this->m_Flags = _p->m_Flags;
	this->m_DefaultValue.Copy(&_p->m_DefaultValue);
	return OK;
}
status_t CIdlParam::Print(CFileBase *_buf)
{
	const char* _str_name = "<null>";
	if(this->m_Name.StrLen() > 0)
		_str_name = m_Name.CStr();
	_buf->Log("Name = %s",_str_name);
	_buf->Log("Hint = {");
	_buf->IncLogLevel(1);
	m_Hint.Print(_buf);
	_buf->IncLogLevel(-1);
	_buf->Log("}");
	_buf->Log("type = {");
	_buf->IncLogLevel(1);
	m_Type.Print(_buf);
	_buf->IncLogLevel(-1);
	_buf->Log("}");
	const char* _str_defaultvalue = "<null>";
	if(this->m_DefaultValue.StrLen() > 0)
		_str_defaultvalue = m_DefaultValue.CStr();
	_buf->Log("DefaultValue = %s",_str_defaultvalue);
	return OK;
}
CMem* CIdlParam::GetName()
{
	return &this->m_Name;
}
CIdlHint* CIdlParam::GetHint()
{
	return &this->m_Hint;
}
CIdlType* CIdlParam::GetType()
{
	return &this->m_Type;
}
CMem* CIdlParam::GetDefaultValue()
{
	return &this->m_DefaultValue;
}
const char* CIdlParam::GetNameStr()
{
	return this->m_Name.CStr();
}
const char* CIdlParam::GetDefaultValueStr()
{
	return this->m_DefaultValue.CStr();
}
status_t CIdlParam::SetName(CMem* _name)
{
	this->m_Name.Copy(_name);
	return OK;
}
status_t CIdlParam::SetHint(CIdlHint* _hint)
{
	this->m_Hint.Copy(_hint);
	return OK;
}
status_t CIdlParam::SetType(CIdlType* _type)
{
	this->m_Type.Copy(_type);
	return OK;
}
status_t CIdlParam::SetDefaultValue(CMem* _defaultvalue)
{
	this->m_DefaultValue.Copy(_defaultvalue);
	return OK;
}
status_t CIdlParam::SetName(const char *_name)
{
	CMem _mem(_name);
	return this->SetName(&_mem);
}
status_t CIdlParam::SetDefaultValue(const char *_defaultvalue)
{
	CMem _mem(_defaultvalue);
	return this->SetDefaultValue(&_mem);
}

status_t CIdlParam::ClearType()
{
    return m_Type.SetName("");
}

status_t CIdlParam::ToLua(CFileBase *buf)
{
    ASSERT(buf);
    
    buf->Log("name=\"%s\",",GetNameStr());

    if(m_Hint.GetHints() > 0)
    {
        buf->Log("hint = {");
        buf->IncLogLevel(1);
        m_Hint.ToLua(buf);
        buf->IncLogLevel(-1);
        buf->Log("},");
    }

    if(m_Type.GetName()->StrLen() > 0)
    {
        buf->Log("type = {");
        buf->IncLogLevel(1);
        m_Type.ToLua(buf);
        buf->IncLogLevel(-1);
        buf->Log("},");
    }
   
    buf->Log("flags=0x%x,",m_Flags);

    if(HasDefaultValue())
    {
       buf->Log("default_value = \"%s\",",GetDefaultValueStr());
    }
    return OK;
}

status_t CIdlParam::AddHint(CMem *hint)
{
    ASSERT(hint);
    return m_Hint.AddHint(hint);
}
