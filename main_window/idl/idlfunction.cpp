#include "idlfunction.h"
#include "syslog.h"
#include "mem_tool.h"

CIdlFunction::CIdlFunction()
{
	this->InitBasic();
}
CIdlFunction::~CIdlFunction()
{
	this->Destroy();
}
status_t CIdlFunction::InitBasic()
{
	this->m_Name.InitBasic();
	this->m_ParamList.InitBasic();
	this->m_RetTypeList.InitBasic();
	this->m_Hint.InitBasic();
    this->m_RawSource.InitBasic();
	return OK;
}
status_t CIdlFunction::Init()
{
	this->InitBasic();
	this->m_Name.Init();
	this->m_ParamList.Init();
	this->m_RetTypeList.Init();
	this->m_Hint.Init();
    m_RawSource.Init();
	return OK;
}
status_t CIdlFunction::Destroy()
{
    m_RawSource.Destroy();
	this->m_Name.Destroy();
	this->m_ParamList.Destroy();
	this->m_RetTypeList.Destroy();
	this->m_Hint.Destroy();
	this->InitBasic();
	return OK;
}
int CIdlFunction::Comp(CIdlFunction *_p)
{
	ASSERT(_p);
	if(this==_p)return 0;
	return 0;
}
status_t CIdlFunction::Copy(CIdlFunction *_p)
{
	ASSERT(_p);
	if(this == _p)return OK;
	this->m_Name.Copy(&_p->m_Name);
	this->m_ParamList.Copy(&_p->m_ParamList);
	this->m_RetTypeList.Copy(&_p->m_RetTypeList);
	this->m_Hint.Copy(&_p->m_Hint);    
    this->m_RawSource.Copy(&_p->m_RawSource);
	return OK;
}
status_t CIdlFunction::Print(CFileBase *_buf)
{
	const char* _str_name = "<null>";
	if(this->m_Name.StrLen() > 0)
		_str_name = m_Name.CStr();
	_buf->Log("Name = %s",_str_name);
	_buf->Log("ParamList = {");
	_buf->IncLogLevel(1);
	m_ParamList.Print(_buf);
	_buf->IncLogLevel(-1);
	_buf->Log("}");
	_buf->Log("RetTypeList = {");
	_buf->IncLogLevel(1);
	m_RetTypeList.Print(_buf);
	_buf->IncLogLevel(-1);
	_buf->Log("}");
	_buf->Log("Hint = {");
	_buf->IncLogLevel(1);
	m_Hint.Print(_buf);
	_buf->IncLogLevel(-1);
	_buf->Log("}");
	return OK;
}
CMem* CIdlFunction::GetName()
{
	return &this->m_Name;
}
CIdlParamList* CIdlFunction::GetParamList()
{
	return &this->m_ParamList;
}
CIdlTypeList* CIdlFunction::GetRetTypeList()
{
	return &this->m_RetTypeList;
}
CIdlHint* CIdlFunction::GetHint()
{
	return &this->m_Hint;
}
const char* CIdlFunction::GetNameStr()
{
	return this->m_Name.CStr();
}
status_t CIdlFunction::SetName(CMem* _name)
{
	this->m_Name.Copy(_name);
	return OK;
}
status_t CIdlFunction::SetParamList(CIdlParamList* _paramlist)
{
	this->m_ParamList.Copy(_paramlist);
	return OK;
}
status_t CIdlFunction::SetRetTypeList(CIdlTypeList* _rettypelist)
{
	this->m_RetTypeList.Copy(_rettypelist);
	return OK;
}
status_t CIdlFunction::SetHint(CIdlHint* _hint)
{
	this->m_Hint.Copy(_hint);
	return OK;
}
status_t CIdlFunction::SetName(const char *_name)
{
	CMem _mem(_name);
	return this->SetName(&_mem);
}

status_t CIdlFunction::ToLua(CFileBase *buf)
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

    buf->Log("ret_type = {");
    buf->IncLogLevel(1);
    m_RetTypeList.ToLua(buf);
    buf->IncLogLevel(-1);
    buf->Log("},");

    if(m_ParamList.GetLen() > 0)
    {
        buf->Log("params = {");
        buf->IncLogLevel(1);
        m_ParamList.ToLua(buf);
        buf->IncLogLevel(-1);
        buf->Log("},");
    }

    if(m_RawSource.StrLen() > 0)
    {
        CMem tmp;
        tmp.Init();
        tmp.Copy(&m_RawSource);
        tmp.Trim();
        buf->Log("raw_source=[[");
        buf->Puts(&tmp);
        buf->Printf("]],\n");
    }

    return OK;
}

CMem* CIdlFunction::GetRawSource()
{
    return &m_RawSource;
}

const char* CIdlFunction::GetRawSourceStr()
{
    return m_RawSource.CStr();
}

status_t CIdlFunction::SetRawSource(CMem *_rawsource)
{
    ASSERT(_rawsource);
    return this->m_RawSource.Copy(_rawsource);
}

status_t CIdlFunction::SetRawSource(const char *_rawsource)
{
    CMem tmp(_rawsource);
    return this->SetRawSource(&tmp);
}

