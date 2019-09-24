#ifndef __PAGEMANAGER_H
#define __PAGEMANAGER_H

#include "page.h"
#include "filebase.h"

class CPageManager{
public:
	CPage **mIndex;
	int mTop;
	int mSize;
public:		
	CPage* GetPage(const wchar_t *name);
	int CompNode(CPage *page1, CPage *page2);
	status_t CopyNode(CPage *dst, CPage *src);
	status_t DelNode(CPage *page);
	CPage* CloneNode(CPage *page);
	status_t Copy(CPageManager *stk);
	CPage* RemoveElem(int index);
	status_t InsElemPtr(int i, CPage *page);
	CPage* PopPtr();
	status_t AutoResize();
	status_t PushPtr(CPage *page);
	status_t InitBasic();  
	int BSearchPos(CPage *page,int order,int *find_flag);
	status_t InsOrderedPtr(CPage *page,int order,int unique);
	status_t InsOrdered(CPage *page,int order,int unique);
	status_t DelElem(int i);
	status_t InsElem(int i,CPage *page);
	int BSearch(CPage *page,int order);
	CPage* BSearchNode(CPage *page,int order);
	status_t Sort(int order);
	CPage* GetElem(int index);
	CPage* GetTopPtr();
	CPage* Search(CPage *page);
	int SearchPos(CPage *page);
	CPageManager();
	status_t Clear();
	status_t DelTop();
	status_t Destroy();
	status_t Init(int init_size);
	bool IsEmpty();
	bool IsFull();
	status_t Pop(CPage *page);
	status_t Print(int _level,CFileBase *_buf);
	status_t Push(CPage *page);
	int GetLen();
	~CPageManager();
};

#endif
