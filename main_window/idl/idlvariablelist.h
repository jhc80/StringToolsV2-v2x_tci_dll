#ifndef __IDLVARIABLELIST_H
#define __IDLVARIABLELIST_H

#include "idlvariable.h"
#include "filebase.h"

class CIdlVariableList{
private:
    CIdlVariable **m_Index;
    int m_Top;
    int m_Size;
public:		
    status_t ToLua(CFileBase *buf);
	status_t Combine(CIdlVariableList *list);
	status_t SetHint(CIdlHint *hint);
    int CompNode(CIdlVariable *idlvariable1, CIdlVariable *idlvariable2);
    status_t CopyNode(CIdlVariable *dst, CIdlVariable *src);
    status_t DelNode(CIdlVariable *idlvariable);
    CIdlVariable* CloneNode(CIdlVariable *idlvariable);
    status_t Copy(CIdlVariableList *stk);
    CIdlVariable* RemoveElem(int index);
    status_t InsElemPtr(int i, CIdlVariable *idlvariable);
    CIdlVariable* PopPtr();
    status_t AutoResize();
    status_t PushPtr(CIdlVariable *idlvariable);
    status_t InitBasic();  
    int BSearchPos(CIdlVariable *idlvariable,int order,int *find_flag);
    status_t InsOrderedPtr(CIdlVariable *idlvariable,int order,int unique);
    status_t InsOrdered(CIdlVariable *idlvariable,int order,int unique);
    status_t DelElem(int i);
    status_t InsElem(int i,CIdlVariable *idlvariable);
    int BSearch(CIdlVariable *idlvariable,int order);
    CIdlVariable* BSearchNode(CIdlVariable *idlvariable,int order);
    status_t Sort(int order);
    CIdlVariable* GetElem(int index);
    CIdlVariable* GetTopPtr();
    CIdlVariable* Search(CIdlVariable *idlvariable);
    int SearchPos(CIdlVariable *idlvariable);
    CIdlVariableList();
    status_t Clear();
    status_t DelTop();
    status_t Destroy();
    status_t Init(int init_size);
    status_t Init();
    bool IsEmpty();
    bool IsFull();
    status_t Pop(CIdlVariable *idlvariable);
    status_t Print(CFileBase *_buf);
    status_t Push(CIdlVariable *idlvariable);
    int GetLen();
    ~CIdlVariableList();
};

#endif
