#ifndef __IDLTYPELIST_H
#define __IDLTYPELIST_H

#include "idltype.h"
#include "filebase.h"

class CIdlTypeList{
private:
	CIdlType **m_Index;
	int m_Top;
	int m_Size;
public:		
    status_t ToLua(CFileBase *buf);
	int CompNode(CIdlType *idltype1, CIdlType *idltype2);
	status_t CopyNode(CIdlType *dst, CIdlType *src);
	status_t DelNode(CIdlType *idltype);
	CIdlType* CloneNode(CIdlType *idltype);
	status_t Copy(CIdlTypeList *stk);
	CIdlType* RemoveElem(int index);
	status_t InsElemPtr(int i, CIdlType *idltype);
	CIdlType* PopPtr();
	status_t AutoResize();
	status_t PushPtr(CIdlType *idltype);
	status_t InitBasic();  
	int BSearchPos(CIdlType *idltype,int order,int *find_flag);
	status_t InsOrderedPtr(CIdlType *idltype,int order,int unique);
	status_t InsOrdered(CIdlType *idltype,int order,int unique);
	status_t DelElem(int i);
	status_t InsElem(int i,CIdlType *idltype);
	int BSearch(CIdlType *idltype,int order);
	CIdlType* BSearchNode(CIdlType *idltype,int order);
	status_t Sort(int order);
	CIdlType* GetElem(int index);
	CIdlType* GetTopPtr();
	CIdlType* Search(CIdlType *idltype);
	int SearchPos(CIdlType *idltype);
	CIdlTypeList();
	status_t Clear();
	status_t DelTop();
	status_t Destroy();
	status_t Init(int init_size);
    status_t Init();
	bool IsEmpty();
	bool IsFull();
	status_t Pop(CIdlType *idltype);
	status_t Print(CFileBase *_buf);
	status_t Push(CIdlType *idltype);
	int GetLen();
	~CIdlTypeList();
};

#endif
