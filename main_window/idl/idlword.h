#ifndef __S2_IDLWORD_H
#define __S2_IDLWORD_H

#include "cruntime.h"
#include "filebase.h"
#include "mem.h"

class CIdlWord{
public:
	CMem m_Name;
public:
	const char * CStr();
	CIdlWord();
	virtual ~CIdlWord();
	status_t InitBasic();
	status_t Init();
	status_t Destroy();
	status_t Copy(CIdlWord *_p);
	int Comp(CIdlWord *_p);
	status_t Print(CFileBase *_buf);
	CMem* GetName();
	status_t SetName(CMem* _name);
	const char* GetNameStr();
	status_t SetName(const char *_name);
};

#endif
