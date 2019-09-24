#ifndef __S2_IDLMODULE_H
#define __S2_IDLMODULE_H

#include "cruntime.h"
#include "filebase.h"
#include "idlclasslist.h"

class CIdlModule{
public:
	CIdlClassList m_AllClasses;
public:
    status_t ToLua(CFileBase *buf);
	status_t AddIdlClass(CIdlClass *idl_class);
	CIdlModule();
	virtual ~CIdlModule();
	status_t InitBasic();
	status_t Init();
	status_t Destroy();
	status_t Copy(CIdlModule *_p);
	int Comp(CIdlModule *_p);
	status_t Print(CFileBase *_buf);
	CIdlClassList* GetAllClasses();
	status_t SetAllClasses(CIdlClassList* _allclasses);
};

#endif
