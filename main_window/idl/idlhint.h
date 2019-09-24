#ifndef __IDL_HINT_H
#define __IDL_HINT_H

#include "mem.h"
#include "memfile.h"
#include "memstk.h"

class CIdlHint{
public:
    uint32_t m_Flags;
    CMemStk m_Hints;

public:
	status_t ToLua(CFileBase *buf);
	status_t AddHint(CMem *hint);
	int GetHintsLen();
    CIdlHint();
    virtual ~CIdlHint();

    status_t InitBasic();
    status_t Init();
    status_t Destroy();

    status_t Copy(CIdlHint *_p);
    int Comp(CIdlHint *_p);
    status_t Print(CFileBase *_buf);

    uint32_t GetFlags();
    CMemStk* GetHints();
    status_t SetFlags(uint32_t _flags);
    status_t SetHints(CMemStk *_hints);
};

#endif
