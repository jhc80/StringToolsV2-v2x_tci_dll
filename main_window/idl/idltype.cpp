#include "idltype.h"
#include "syslog.h"
#include "mem_tool.h"

CIdlType::CIdlType()
{
	this->InitBasic();
}
CIdlType::~CIdlType()
{
	this->Destroy();
}
status_t CIdlType::InitBasic()
{
	this->m_Name.InitBasic();
	this->m_Flags = 0;
	this->m_ArraySize.InitBasic();
	m_VarName.InitBasic();	
    this->m_NameSpace.InitBasic();
	return OK;
}
status_t CIdlType::Init()
{
	this->InitBasic();
	this->m_Name.Init();
	this->m_ArraySize.Init();
	m_VarName.Init();
	this->m_NameSpace.Init();
	return OK;
}
status_t CIdlType::Destroy()
{
    this->m_NameSpace.Destroy();
	m_VarName.Destroy();
	this->m_Name.Destroy();
	this->m_ArraySize.Destroy();
	this->InitBasic();
	return OK;
}
int CIdlType::Comp(CIdlType *_p)
{
	ASSERT(_p);
	if(this==_p)return 0;
	return 0;
}
status_t CIdlType::Copy(CIdlType *_p)
{
	ASSERT(_p);
	if(this == _p)return OK;
	this->m_Name.Copy(&_p->m_Name);
	this->m_Flags = _p->m_Flags;
	this->m_ArraySize.Copy(&_p->m_ArraySize);
	m_VarName.Copy(&_p->m_VarName);	
    this->m_NameSpace.Copy(&_p->m_NameSpace);
	return OK;
}
status_t CIdlType::Print(CFileBase *_buf)
{
	const char* _str_name = "<null>";
	if(this->m_Name.StrLen() > 0)
		_str_name = m_Name.CStr();
	_buf->Log("Name = %s",_str_name);
	_buf->Log("Flags = %d",this->m_Flags);
	
	const char* _str_arraysize = "<null>";
	if(this->m_ArraySize.StrLen() > 0)
		_str_arraysize = m_ArraySize.CStr();
	_buf->Log("ArraySize = %s",_str_arraysize);

	const char* _str_var_name = "<null>";
	if(this->m_VarName.StrLen() > 0)
		_str_var_name = m_VarName.CStr();
	_buf->Log("VarName = %s",_str_var_name);

	_buf->Log("NameSpace = %s",
        m_NameSpace.StrLen()>0?m_NameSpace.CStr():"<null>"
    );

	return OK;
}
CMem* CIdlType::GetName()
{
	return &this->m_Name;
}
uint32_t CIdlType::GetFlags()
{
	return this->m_Flags;
}
CMem* CIdlType::GetArraySize()
{
	return &this->m_ArraySize;
}
const char* CIdlType::GetNameStr()
{
	return this->m_Name.CStr();
}
const char* CIdlType::GetArraySizeStr()
{
	return this->m_ArraySize.CStr();
}
status_t CIdlType::SetName(CMem* _name)
{
	this->m_Name.Copy(_name);
	return OK;
}
status_t CIdlType::SetFlags(uint32_t _flags)
{
	this->m_Flags = _flags;
	return OK;
}
status_t CIdlType::SetArraySize(CMem* _arraysize)
{
	this->m_ArraySize.Copy(_arraysize);
	return OK;
}
status_t CIdlType::SetName(const char *_name)
{
	CMem _mem(_name);
	return this->SetName(&_mem);
}
status_t CIdlType::SetArraySize(const char *_arraysize)
{
	CMem _mem(_arraysize);
	return this->SetArraySize(&_mem);
}

status_t CIdlType::ToLua(CFileBase *buf)
{
    ASSERT(buf);
    buf->Log("name=\"%s\",",GetNameStr());
    if(this->IsArray() && m_ArraySize.StrLen() > 0)
    {
        buf->Log("array_size=\"%s\",",GetArraySizeStr());
    }

	if(HasVarName() && m_VarName.StrLen() > 0)
	{
		buf->Log("var_name=\"%s\",",GetVarNameStr());
	}

    buf->Log("flags=0x%x,",m_Flags);

	if(m_NameSpace.StrLen() > 0)
	{
		buf->Log("namespace=\"%s\",",m_NameSpace.CStr());
	}

    return OK;
}

CMem* CIdlType::GetVarName()
{
    return &m_VarName;
}

const char* CIdlType::GetVarNameStr()
{
    return m_VarName.CStr();
}

status_t CIdlType::SetVarName(CMem *_varname)
{
    ASSERT(_varname);
    return this->m_VarName.Copy(_varname);
}

status_t CIdlType::SetVarName(const char *_varname)
{
    CMem tmp(_varname);
    return this->SetVarName(&tmp);
}

CMem* CIdlType::GetNameSpace()
{
    return &m_NameSpace;
}

const char* CIdlType::GetNameSpaceStr()
{
    return m_NameSpace.CStr();
}

status_t CIdlType::SetNameSpace(CMem *_namespace)
{
    ASSERT(_namespace);
    return this->m_NameSpace.Copy(_namespace);
}

status_t CIdlType::SetNameSpace(const char *_namespace)
{
    CMem tmp(_namespace);
    return this->SetNameSpace(&tmp);
}

