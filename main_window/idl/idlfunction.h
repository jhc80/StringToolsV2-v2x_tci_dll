#ifndef __S2_IDLFUNCTION_H
#define __S2_IDLFUNCTION_H

#include "cruntime.h"
#include "filebase.h"
#include "idlhint.h"
#include "idlparamlist.h"
#include "idltypelist.h"
#include "mem.h"

class CIdlFunction{
public:
    CMem m_RawSource;
	CMem m_Name;
	CIdlParamList m_ParamList;
	CIdlTypeList m_RetTypeList;
	CIdlHint m_Hint;
public:
	status_t ToLua(CFileBase *buf);
	CIdlFunction();
	virtual ~CIdlFunction();
	status_t InitBasic();
	status_t Init();
	status_t Destroy();
	status_t Copy(CIdlFunction *_p);
	int Comp(CIdlFunction *_p);
	status_t Print(CFileBase *_buf);
	CMem* GetName();
	CIdlParamList* GetParamList();
	CIdlTypeList* GetRetTypeList();
	CIdlHint* GetHint();
	status_t SetName(CMem* _name);
	status_t SetParamList(CIdlParamList* _paramlist);
	status_t SetRetTypeList(CIdlTypeList* _rettypelist);
	status_t SetHint(CIdlHint* _hint);
	const char* GetNameStr();
	status_t SetName(const char *_name);
    
    CMem* GetRawSource();
    const char* GetRawSourceStr();
    status_t SetRawSource(CMem *_rawsource);
    status_t SetRawSource(const char *_rawsource);
};

#endif
