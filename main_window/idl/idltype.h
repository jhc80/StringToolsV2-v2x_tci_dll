#ifndef __S2_IDLTYPE_H
#define __S2_IDLTYPE_H

#include "cruntime.h"
#include "filebase.h"
#include "mem.h"

#define IDL_TYPE_FLAG_FUNC(func,bit) FLAG_FUNC(m_Flags,func,bit)

class CIdlType{
public:
	CMem m_Name;
	uint32_t m_Flags;
	CMem m_ArraySize;
	CMem m_VarName;
	CMem m_NameSpace;
public:
	status_t ToLua(CFileBase *buf);
	CIdlType();
	virtual ~CIdlType();
	status_t InitBasic();
	status_t Init();
	status_t Destroy();
	status_t Copy(CIdlType *_p);
	int Comp(CIdlType *_p);
	status_t Print(CFileBase *_buf);
	CMem* GetName();
	uint32_t GetFlags();
	CMem* GetArraySize();
	status_t SetName(CMem* _name);
	status_t SetFlags(uint32_t _flags);
	status_t SetArraySize(CMem* _arraysize);
	const char* GetNameStr();
	const char* GetArraySizeStr();
	status_t SetName(const char *_name);
    status_t SetArraySize(const char *_arraysize);
	CMem *GetVarName();
	const char *GetVarNameStr();
	status_t SetVarName(CMem *_varname);
	status_t SetVarName(const char *varname);
	
	CMem* GetNameSpace();
    const char* GetNameSpaceStr();
    status_t SetNameSpace(CMem *_namespace);
    status_t SetNameSpace(const char *_namespace);

    IDL_TYPE_FLAG_FUNC(IsArray,0x00000001);
    IDL_TYPE_FLAG_FUNC(IsPointer,0x00000002);
	IDL_TYPE_FLAG_FUNC(HasVarName,0x00000004);
};

#endif
