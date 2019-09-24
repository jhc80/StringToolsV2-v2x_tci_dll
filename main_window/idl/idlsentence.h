#ifndef __IDLSENTENCE_H
#define __IDLSENTENCE_H

#include "idlword.h"
#include "filebase.h"

class CIdlSentence{
private:
    CIdlWord **m_Index;
    int m_Top;
    int m_Size;
public:		
	status_t ToLua(CFileBase *buf);
	const char * CStr();
    int CompNode(CIdlWord *idlword1, CIdlWord *idlword2);
    status_t CopyNode(CIdlWord *dst, CIdlWord *src);
    status_t DelNode(CIdlWord *idlword);
    CIdlWord* CloneNode(CIdlWord *idlword);
    status_t Copy(CIdlSentence *stk);
    CIdlWord* RemoveElem(int index);
    status_t InsElemPtr(int i, CIdlWord *idlword);
    CIdlWord* PopPtr();
    status_t AutoResize();
    status_t PushPtr(CIdlWord *idlword);
    status_t InitBasic();  
    int BSearchPos(CIdlWord *idlword,int order,int *find_flag);
    status_t InsOrderedPtr(CIdlWord *idlword,int order,int unique);
    status_t InsOrdered(CIdlWord *idlword,int order,int unique);
    status_t DelElem(int i);
    status_t InsElem(int i,CIdlWord *idlword);
    int BSearch(CIdlWord *idlword,int order);
    CIdlWord* BSearchNode(CIdlWord *idlword,int order);
    status_t Sort(int order);
    CIdlWord* GetElem(int index);
    CIdlWord* GetTopPtr();
    CIdlWord* Search(CIdlWord *idlword);
    int SearchPos(CIdlWord *idlword);
    CIdlSentence();
    status_t Clear();
    status_t DelTop();
    status_t Destroy();
    status_t Init(int init_size);
    status_t Init();
    bool IsEmpty();
    bool IsFull();
    status_t Pop(CIdlWord *idlword);
    status_t Print(CFileBase *_buf);
    status_t Push(CIdlWord *idlword);
    int GetLen();
    ~CIdlSentence();
};

#endif
