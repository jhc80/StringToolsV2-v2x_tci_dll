#ifndef __S2_IDLPARAM_H
#define __S2_IDLPARAM_H

#include "cruntime.h"
#include "filebase.h"
#include "idlhint.h"
#include "idltype.h"
#include "mem.h"

#define IDL_PARAM_FLAG_FUNC(func,bit) FLAG_FUNC(m_Flags,func,bit)

class CIdlParam{
public:
	CMem m_Name;
	CIdlHint m_Hint;
	CIdlType m_Type;
	CMem m_DefaultValue;
    uint32_t m_Flags;
public:
    status_t AddHint(CMem *hint);
	status_t ToLua(CFileBase *buf);
	status_t ClearType();
	CIdlParam();
	virtual ~CIdlParam();
	status_t InitBasic();
	status_t Init();
	status_t Destroy();
	status_t Copy(CIdlParam *_p);
	int Comp(CIdlParam *_p);
	status_t Print(CFileBase *_buf);
	CMem* GetName();
	CIdlHint* GetHint();
	CIdlType* GetType();
	CMem* GetDefaultValue();
	status_t SetName(CMem* _name);
	status_t SetHint(CIdlHint* _hint);
	status_t SetType(CIdlType* _type);
	status_t SetDefaultValue(CMem* _defaultvalue);
	const char* GetNameStr();
	const char* GetDefaultValueStr();
	status_t SetName(const char *_name);
	status_t SetDefaultValue(const char *_defaultvalue);

    IDL_PARAM_FLAG_FUNC(HasDefaultValue,0x00000001);
};

#endif
