#include "idlclass.h"
#include "syslog.h"
#include "mem_tool.h"

CIdlClass::CIdlClass()
{
	this->InitBasic();
}
CIdlClass::~CIdlClass()
{
	this->Destroy();
}
status_t CIdlClass::InitBasic()
{
	this->m_ClassName.InitBasic();
	this->m_Hint.InitBasic();
	this->m_BaseClasses.InitBasic();
	this->m_VariableList.InitBasic();
	this->m_FunctionList.InitBasic();    
    this->m_RawSource.InitBasic();
	return OK;
}
status_t CIdlClass::Init()
{
	this->InitBasic();
	this->m_ClassName.Init();
	this->m_Hint.Init();
	this->m_BaseClasses.Init();
	this->m_VariableList.Init();
	this->m_FunctionList.Init();    
    this->m_RawSource.Init();
	return OK;
}
status_t CIdlClass::Destroy()
{
    this->m_RawSource.Destroy();
	this->m_ClassName.Destroy();
	this->m_Hint.Destroy();
	this->m_BaseClasses.Destroy();
	this->m_VariableList.Destroy();
	this->m_FunctionList.Destroy();
	this->InitBasic();
	return OK;
}
int CIdlClass::Comp(CIdlClass *_p)
{
	ASSERT(_p);
	if(this==_p)return 0;
	return 0;
}
status_t CIdlClass::Copy(CIdlClass *_p)
{
	ASSERT(_p);
	if(this == _p)return OK;
	this->m_ClassName.Copy(&_p->m_ClassName);
	this->m_Hint.Copy(&_p->m_Hint);
	this->m_BaseClasses.Copy(&_p->m_BaseClasses);
	this->m_VariableList.Copy(&_p->m_VariableList);
	this->m_FunctionList.Copy(&_p->m_FunctionList);    
    this->m_RawSource.Copy(&_p->m_RawSource);
	return OK;
}
status_t CIdlClass::Print(CFileBase *_buf)
{
	const char* _str_classname = "<null>";
	if(this->m_ClassName.StrLen() > 0)
		_str_classname = m_ClassName.CStr();
	_buf->Log("ClassName = %s",_str_classname);
	_buf->Log("Hint = {");
	_buf->IncLogLevel(1);
	m_Hint.Print(_buf);
	_buf->IncLogLevel(-1);
	_buf->Log("}");
	_buf->Log("BaseClasses = {");
	_buf->IncLogLevel(1);
	m_BaseClasses.Print(_buf);
	_buf->IncLogLevel(-1);
	_buf->Log("}");
	_buf->Log("VariableList = {");
	_buf->IncLogLevel(1);
	m_VariableList.Print(_buf);
	_buf->IncLogLevel(-1);
	_buf->Log("}");
	_buf->Log("FunctionList = {");
	_buf->IncLogLevel(1);
	m_FunctionList.Print(_buf);
	_buf->IncLogLevel(-1);
	_buf->Log("}");    
    _buf->Log("RawSource = %s",
        m_RawSource.StrLen()>0?m_RawSource.CStr():"<null>"
    );
	return OK;
}
CMem* CIdlClass::GetClassName()
{
	return &this->m_ClassName;
}
CIdlHint* CIdlClass::GetHint()
{
	return &this->m_Hint;
}
CIdlSentenceList* CIdlClass::GetBaseClasses()
{
	return &this->m_BaseClasses;
}
CIdlVariableList* CIdlClass::GetVariableList()
{
	return &this->m_VariableList;
}
CIdlFunctionList* CIdlClass::GetFunctionList()
{
	return &this->m_FunctionList;
}
const char* CIdlClass::GetClassNameStr()
{
	return this->m_ClassName.CStr();
}
status_t CIdlClass::SetClassName(CMem* _classname)
{
	this->m_ClassName.Copy(_classname);
	return OK;
}
status_t CIdlClass::SetHint(CIdlHint* _hint)
{
	this->m_Hint.Copy(_hint);
	return OK;
}
status_t CIdlClass::SetBaseClasses(CIdlSentenceList* _baseclasses)
{
	this->m_BaseClasses.Copy(_baseclasses);
	return OK;
}
status_t CIdlClass::SetVariableList(CIdlVariableList* _variablelist)
{
	this->m_VariableList.Copy(_variablelist);
	return OK;
}
status_t CIdlClass::SetFunctionList(CIdlFunctionList* _functionlist)
{
	this->m_FunctionList.Copy(_functionlist);
	return OK;
}
status_t CIdlClass::SetClassName(const char *_classname)
{
	CMem _mem(_classname);
	return this->SetClassName(&_mem);
}

status_t CIdlClass::AddHint(CMem *hint)
{
    ASSERT(hint);
    return m_Hint.AddHint(hint);
}

status_t CIdlClass::AddVariableList(CIdlVariableList *list)
{
    ASSERT(list);
    return m_VariableList.Combine(list);
}

status_t CIdlClass::AddFunction(CIdlFunction *func)
{
    ASSERT(func);
    return m_FunctionList.Push(func);
}

status_t CIdlClass::ToLua(CFileBase *buf)
{
    ASSERT(buf);

    buf->Log("name=\"%s\",",GetClassNameStr());
    
    if(m_Hint.GetHintsLen() > 0)
    {
        buf->Log("hint={");
        buf->IncLogLevel(1);
        m_Hint.ToLua(buf);
        buf->IncLogLevel(-1);
        buf->Log("},");
    }

    if(m_BaseClasses.GetLen() > 0)
    {
        buf->Log("bases={");
        buf->IncLogLevel(1);
        m_BaseClasses.ToLua(buf);
        buf->IncLogLevel(-1);
        buf->Log("},");
    }

    if(m_VariableList.GetLen()>0)
    {
        buf->Log("variables={");
        buf->IncLogLevel(1);
        m_VariableList.ToLua(buf);
        buf->IncLogLevel(-1);
        buf->Log("},");
    }

    if(m_FunctionList.GetLen() > 0)
    {
        buf->Log("functions={");
        buf->IncLogLevel(1);
        m_FunctionList.ToLua(buf);
        buf->IncLogLevel(-1);
        buf->Log("},");
    }
    
    return OK;
}

CMem* CIdlClass::GetRawSource()
{
    return &m_RawSource;
}

const char* CIdlClass::GetRawSourceStr()
{
    return m_RawSource.CStr();
}

status_t CIdlClass::SetRawSource(CMem *_rawsource)
{
    ASSERT(_rawsource);
    return this->m_RawSource.Copy(_rawsource);
}

status_t CIdlClass::SetRawSource(const char *_rawsource)
{
    CMem tmp(_rawsource);
    return this->SetRawSource(&tmp);
}

