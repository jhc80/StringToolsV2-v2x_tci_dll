#ifndef __S2_IDLVARIABLE_H
#define __S2_IDLVARIABLE_H

#include "cruntime.h"
#include "filebase.h"
#include "idlhint.h"
#include "idltype.h"
#include "mem.h"

#define IDL_VAR_FLAG_FUNC(func,bit) FLAG_FUNC(m_Flags,func,bit)

class CIdlVariable{
public:
	CMem m_Name;
	uint32_t m_Flags;
	CIdlHint m_Hint;
	CIdlType m_Type;
	CMem m_InitValue;
public:
	CIdlVariable();
	virtual ~CIdlVariable();
	status_t InitBasic();
	status_t Init();
	status_t Destroy();
	status_t Copy(CIdlVariable *_p);
	int Comp(CIdlVariable *_p);
	status_t Print(CFileBase *_buf);
	CMem* GetName();
	uint32_t GetFlags();
	CIdlHint* GetHint();
	CIdlType* GetType();
	CMem* GetInitValue();
	status_t SetName(CMem* _name);
	status_t SetFlags(uint32_t _flags);
	status_t SetHint(CIdlHint* _hint);
	status_t SetType(CIdlType* _type);
	status_t SetInitValue(CMem* _initvalue);
	const char* GetNameStr();
	const char* GetInitValueStr();
	status_t SetName(const char *_name);
	status_t SetInitValue(const char *_initvalue);
    status_t ToLua(CFileBase *buf);

    IDL_VAR_FLAG_FUNC(HasInitValue,0x00000001);
};

#endif
