#ifndef __IDLSENTENCELIST_H
#define __IDLSENTENCELIST_H

#include "idlsentence.h"
#include "filebase.h"

class CIdlSentenceList{
private:
    CIdlSentence **m_Index;
    int m_Top;
    int m_Size;
public:		
	status_t ToLua(CFileBase *buf);
    status_t Combine(CIdlSentenceList *stk);
    int CompNode(CIdlSentence *idlsentence1, CIdlSentence *idlsentence2);
    status_t CopyNode(CIdlSentence *dst, CIdlSentence *src);
    status_t DelNode(CIdlSentence *idlsentence);
    CIdlSentence* CloneNode(CIdlSentence *idlsentence);
    status_t Copy(CIdlSentenceList *stk);
    CIdlSentence* RemoveElem(int index);
    status_t InsElemPtr(int i, CIdlSentence *idlsentence);
    CIdlSentence* PopPtr();
    status_t AutoResize();
    status_t PushPtr(CIdlSentence *idlsentence);
    status_t InitBasic();  
    int BSearchPos(CIdlSentence *idlsentence,int order,int *find_flag);
    status_t InsOrderedPtr(CIdlSentence *idlsentence,int order,int unique);
    status_t InsOrdered(CIdlSentence *idlsentence,int order,int unique);
    status_t DelElem(int i);
    status_t InsElem(int i,CIdlSentence *idlsentence);
    int BSearch(CIdlSentence *idlsentence,int order);
    CIdlSentence* BSearchNode(CIdlSentence *idlsentence,int order);
    status_t Sort(int order);
    CIdlSentence* GetElem(int index);
    CIdlSentence* GetTopPtr();
    CIdlSentence* Search(CIdlSentence *idlsentence);
    int SearchPos(CIdlSentence *idlsentence);
    CIdlSentenceList();
    status_t Clear();
    status_t DelTop();
    status_t Destroy();
    status_t Init(int init_size);
    status_t Init();
    bool IsEmpty();
    bool IsFull();
    status_t Pop(CIdlSentence *idlsentence);
    status_t Print(CFileBase *_buf);
    status_t Push(CIdlSentence *idlsentence);
    int GetLen();
    ~CIdlSentenceList();
};

#endif
