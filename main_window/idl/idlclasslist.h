#ifndef __IDLCLASSLIST_H
#define __IDLCLASSLIST_H

#include "idlclass.h"
#include "filebase.h"

class CIdlClassList{
private:
    CIdlClass **m_Index;
    int m_Top;
    int m_Size;
public:		
    status_t ToLua(CFileBase *buf);
    int CompNode(CIdlClass *idlclass1, CIdlClass *idlclass2);
    status_t CopyNode(CIdlClass *dst, CIdlClass *src);
    status_t DelNode(CIdlClass *idlclass);
    CIdlClass* CloneNode(CIdlClass *idlclass);
    status_t Copy(CIdlClassList *stk);
    CIdlClass* RemoveElem(int index);
    status_t InsElemPtr(int i, CIdlClass *idlclass);
    CIdlClass* PopPtr();
    status_t AutoResize();
    status_t PushPtr(CIdlClass *idlclass);
    status_t InitBasic();  
    int BSearchPos(CIdlClass *idlclass,int order,int *find_flag);
    status_t InsOrderedPtr(CIdlClass *idlclass,int order,int unique);
    status_t InsOrdered(CIdlClass *idlclass,int order,int unique);
    status_t DelElem(int i);
    status_t InsElem(int i,CIdlClass *idlclass);
    int BSearch(CIdlClass *idlclass,int order);
    CIdlClass* BSearchNode(CIdlClass *idlclass,int order);
    status_t Sort(int order);
    CIdlClass* GetElem(int index);
    CIdlClass* GetTopPtr();
    CIdlClass* Search(CIdlClass *idlclass);
    int SearchPos(CIdlClass *idlclass);
    CIdlClassList();
    status_t Clear();
    status_t DelTop();
    status_t Destroy();
    status_t Init(int init_size);
    bool IsEmpty();
    bool IsFull();
    status_t Pop(CIdlClass *idlclass);
    status_t Print(CFileBase *_buf);
    status_t Push(CIdlClass *idlclass);
    int GetLen();
    ~CIdlClassList();
};

#endif
