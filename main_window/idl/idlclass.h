#ifndef __S2_IDLCLASS_H
#define __S2_IDLCLASS_H

#include "cruntime.h"
#include "filebase.h"
#include "idlfunctionlist.h"
#include "idlhint.h"
#include "idlsentencelist.h"
#include "idlvariablelist.h"
#include "mem.h"

class CIdlClass{
public:
    CMem m_RawSource;
	CMem m_ClassName;
	CIdlHint m_Hint;
	CIdlSentenceList m_BaseClasses;
	CIdlVariableList m_VariableList;
	CIdlFunctionList m_FunctionList;
public:
	status_t ToLua(CFileBase *buf);
	status_t AddFunction(CIdlFunction *func);
	status_t AddVariableList(CIdlVariableList *list);
	status_t AddHint(CMem *hint);
	CIdlClass();
	virtual ~CIdlClass();
	status_t InitBasic();
	status_t Init();
	status_t Destroy();
	status_t Copy(CIdlClass *_p);
	int Comp(CIdlClass *_p);
	status_t Print(CFileBase *_buf);
	CMem* GetClassName();
	CIdlHint* GetHint();
	CIdlSentenceList* GetBaseClasses();
	CIdlVariableList* GetVariableList();
	CIdlFunctionList* GetFunctionList();
	status_t SetClassName(CMem* _classname);
	status_t SetHint(CIdlHint* _hint);
	status_t SetBaseClasses(CIdlSentenceList* _baseclasses);
	status_t SetVariableList(CIdlVariableList* _variablelist);
	status_t SetFunctionList(CIdlFunctionList* _functionlist);
	const char* GetClassNameStr();
	status_t SetClassName(const char *_classname);    
    CMem* GetRawSource();
    const char* GetRawSourceStr();
    status_t SetRawSource(CMem *_rawsource);
    status_t SetRawSource(const char *_rawsource);
};

#endif
