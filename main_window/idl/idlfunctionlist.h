#ifndef __IDLFUNCTIONLIST_H
#define __IDLFUNCTIONLIST_H

#include "idlfunction.h"
#include "filebase.h"

class CIdlFunctionList{
private:
    CIdlFunction **m_Index;
    int m_Top;
    int m_Size;
public:		
    status_t ToLua(CFileBase *buf);
    int CompNode(CIdlFunction *idlfunction1, CIdlFunction *idlfunction2);
    status_t CopyNode(CIdlFunction *dst, CIdlFunction *src);
    status_t DelNode(CIdlFunction *idlfunction);
    CIdlFunction* CloneNode(CIdlFunction *idlfunction);
    status_t Copy(CIdlFunctionList *stk);
    CIdlFunction* RemoveElem(int index);
    status_t InsElemPtr(int i, CIdlFunction *idlfunction);
    CIdlFunction* PopPtr();
    status_t AutoResize();
    status_t PushPtr(CIdlFunction *idlfunction);
    status_t InitBasic();  
    int BSearchPos(CIdlFunction *idlfunction,int order,int *find_flag);
    status_t InsOrderedPtr(CIdlFunction *idlfunction,int order,int unique);
    status_t InsOrdered(CIdlFunction *idlfunction,int order,int unique);
    status_t DelElem(int i);
    status_t InsElem(int i,CIdlFunction *idlfunction);
    int BSearch(CIdlFunction *idlfunction,int order);
    CIdlFunction* BSearchNode(CIdlFunction *idlfunction,int order);
    status_t Sort(int order);
    CIdlFunction* GetElem(int index);
    CIdlFunction* GetTopPtr();
    CIdlFunction* Search(CIdlFunction *idlfunction);
    int SearchPos(CIdlFunction *idlfunction);
    CIdlFunctionList();
    status_t Clear();
    status_t DelTop();
    status_t Destroy();
    status_t Init(int init_size);
    status_t Init();
    bool IsEmpty();
    bool IsFull();
    status_t Pop(CIdlFunction *idlfunction);
    status_t Print(CFileBase *_buf);
    status_t Push(CIdlFunction *idlfunction);
    int GetLen();
    ~CIdlFunctionList();
};

#endif

