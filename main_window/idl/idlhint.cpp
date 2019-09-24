#include "idlhint.h"
#include "syslog.h"
#include "mem_tool.h"

CIdlHint::CIdlHint()
{
    this->InitBasic();
}

CIdlHint::~CIdlHint()
{
    this->Destroy();
}

status_t CIdlHint::InitBasic()
{
    this->m_Flags = 0;
    this->m_Hints.InitBasic();
    return OK;
}

status_t CIdlHint::Init()
{
    this->InitBasic();
    this->m_Hints.Init(1024);
    return OK;
}

status_t CIdlHint::Destroy()
{
    this->m_Hints.Destroy();
    this->InitBasic();
    return OK;
}

status_t CIdlHint::Copy(CIdlHint *_p)
{
    ASSERT(_p);
    if(this == _p)return OK;

    this->m_Flags = _p->m_Flags;
    this->m_Hints.Copy(&_p->m_Hints);
    return OK;
}

status_t CIdlHint::Comp(CIdlHint *_p)
{
    ASSERT(_p);
    if(this == _p)return 0;
    ASSERT(0);
    return 0;
}

status_t CIdlHint::Print(CFileBase *_buf)
{
    ASSERT(_buf);
    _buf->Log("Flags = %u",m_Flags);
    _buf->Log("Hints = {");
    _buf->IncLogLevel(1);
    this->m_Hints.Print(_buf);
    _buf->IncLogLevel(-1);
    _buf->Log("");
    _buf->Log("},");
    return OK;
}

uint32_t CIdlHint::GetFlags()
{
    return m_Flags;
}

CMemStk* CIdlHint::GetHints()
{
    return &m_Hints;
}

status_t CIdlHint::SetFlags(uint32_t _flags)
{
    this->m_Flags = _flags;
    return OK;
}

status_t CIdlHint::SetHints(CMemStk *_hints)
{
    ASSERT(_hints);
    return this->m_Hints.Copy(_hints);
}

int CIdlHint::GetHintsLen()
{
    return m_Hints.GetLen();
}

status_t CIdlHint::AddHint(CMem *hint)
{
    ASSERT(hint);
    return m_Hints.Push(hint);
}

status_t CIdlHint::ToLua(CFileBase *buf)
{
    ASSERT(buf);
    for(int i = 0; i < m_Hints.GetLen(); i++)
    {
        CMem *mem = m_Hints.GetElem(i);
        ASSERT(mem);
        buf->Log(NULL);
        buf->Puts("[[");
        buf->Puts(mem);
        buf->Puts("]],");        
    }
    return OK;
}
