#ifndef __IDLPARAMLIST_H
#define __IDLPARAMLIST_H

#include "idlparam.h"
#include "filebase.h"

class CIdlParamList{
private:
	CIdlParam **m_Index;
	int m_Top;
	int m_Size;
public:		
    status_t ToLua(CFileBase *buf);
	int CompNode(CIdlParam *idlparam1, CIdlParam *idlparam2);
	status_t CopyNode(CIdlParam *dst, CIdlParam *src);
	status_t DelNode(CIdlParam *idlparam);
	CIdlParam* CloneNode(CIdlParam *idlparam);
	status_t Copy(CIdlParamList *stk);
	CIdlParam* RemoveElem(int index);
	status_t InsElemPtr(int i, CIdlParam *idlparam);
	CIdlParam* PopPtr();
	status_t AutoResize();
	status_t PushPtr(CIdlParam *idlparam);
	status_t InitBasic();  
	int BSearchPos(CIdlParam *idlparam,int order,int *find_flag);
	status_t InsOrderedPtr(CIdlParam *idlparam,int order,int unique);
	status_t InsOrdered(CIdlParam *idlparam,int order,int unique);
	status_t DelElem(int i);
	status_t InsElem(int i,CIdlParam *idlparam);
	int BSearch(CIdlParam *idlparam,int order);
	CIdlParam* BSearchNode(CIdlParam *idlparam,int order);
	status_t Sort(int order);
	CIdlParam* GetElem(int index);
	CIdlParam* GetTopPtr();
	CIdlParam* Search(CIdlParam *idlparam);
	int SearchPos(CIdlParam *idlparam);
	CIdlParamList();
	status_t Clear();
	status_t DelTop();
	status_t Destroy();
	status_t Init(int init_size);
    status_t Init();
	bool IsEmpty();
	bool IsFull();
	status_t Pop(CIdlParam *idlparam);
	status_t Print(CFileBase *_buf);
	status_t Push(CIdlParam *idlparam);
	int GetLen();
	~CIdlParamList();
};

#endif

