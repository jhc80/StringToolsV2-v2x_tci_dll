#include "pagemanager.h"
#include "mem_tool.h"
#include "syslog.h"

CPageManager::CPageManager()
{
	this->InitBasic();  
}
CPageManager::~CPageManager()
{
	this->Destroy();
}
status_t CPageManager::InitBasic()
{
	this->mIndex = NULL;
	this->mTop = 0;
	this->mSize = 0;	
	return OK;
}
status_t CPageManager::Init(int init_size)
{
	int i;
	this->InitBasic();  
	this->mSize = init_size;
	MALLOC(this->mIndex,CPage* ,this->mSize);
	for(i = 0; i < this->mSize; i++)
		this->mIndex[i] = NULL;
	return OK;
}
status_t CPageManager::Destroy()
{
	int i;
	if(this->mIndex == NULL)
		return ERROR;
	for(i = 0; i < this->mTop; i++)
	{
		this->DelNode(this->mIndex[i]);
	}
	FREE(this->mIndex);
	this->InitBasic();	
	return OK;
}
bool CPageManager::IsEmpty()
{
	return this->mTop <= 0;
}
bool CPageManager::IsFull()
{
	return this->mTop >= this->mSize;
}

status_t CPageManager::AutoResize()
{
	int i;

	if(this->IsFull())
	{
		REALLOC(this->mIndex,CPage*,this->mSize,this->mSize*2);
		this->mSize *= 2;
		for(i = this->mTop; i < this->mSize; i++)
		{
			this->mIndex[i] = NULL;
		}
	}
	return OK;
}

status_t CPageManager::Push(CPage *page)
{
	CPage *tmp;
	ASSERT(page);
	tmp = this->CloneNode(page);
	if(!this->PushPtr(tmp))
	{
		this->DelNode(tmp);
		return ERROR;
	}
	
	return OK;
}

status_t CPageManager::PushPtr(CPage *page)
{
	ASSERT(page);	
	this->AutoResize();
	ASSERT(!this->IsFull());
	this->mIndex[this->mTop] = page;
	this->mTop++;
	return OK;
}

CPage * CPageManager::PopPtr()
{
	if(this->IsEmpty())
		return NULL;
	this->mTop--;
	return this->mIndex[this->mTop];
}

status_t CPageManager::Pop(CPage *page)
{
	ASSERT(!this->IsEmpty());	
	this->mTop--;
	this->CopyNode(page,this->mIndex[this->mTop]);
	this->DelNode(this->mIndex[this->mTop]);
	return OK;
}
int CPageManager::GetLen()
{
	return this->mTop;
}

int CPageManager::SearchPos(CPage *page)
{
	int i;
	for(i=0;i<this->mTop;i++)
	{
		if(this->CompNode(this->mIndex[i],page) == 0)
			return i;
	}
	return -1;
}

CPage* CPageManager::Search(CPage *page)
{
	int pos = this->SearchPos(page);
	if(pos >= 0 && pos < this->mTop)
		return this->mIndex[pos];;
	return NULL;
}
CPage* CPageManager::GetTopPtr()
{
	if(this->IsEmpty())
		return NULL;
	return this->mIndex[this->mTop - 1];
}
status_t CPageManager::DelTop()
{
	if(this->IsEmpty())
		return ERROR;
	this->mTop--;
	this->DelNode(this->mIndex[this->mTop]);
	return OK;
}
status_t CPageManager::Clear()
{
	while(this->DelTop());
	return OK;
}

CPage* CPageManager::GetElem(int index)
{
	if(index < 0 || index >= this->mTop)
		return NULL;
	return this->mIndex[index];
}

CPage* CPageManager::BSearchNode(CPage *page,int order)
{
	return this->GetElem(this->BSearch(page,order));
}
int CPageManager::BSearch(CPage *page,int order)
{
	int find,pos;
	pos = this->BSearchPos(page,order,&find);
	if(find) return pos;
	return -1;
}

status_t CPageManager::InsElemPtr(int i, CPage *page)
{
	int k;

	ASSERT(page);
	ASSERT(i >= 0 && i <= this->mTop);

	this->AutoResize();
	ASSERT(!this->IsFull());
	for(k = this->mTop; k > i; k--)
	{
		this->mIndex[k] = this->mIndex[k - 1];
	}
	this->mIndex[i] = page;
	this->mTop++;
	return OK;
}

status_t CPageManager::InsElem(int i, CPage *page)
{
	CPage *tmp;
	ASSERT(page);
	tmp = this->CloneNode(page);
	if(!this->InsElemPtr(i,tmp))
	{
		this->DelNode(tmp);
		return ERROR;
	}
	return OK;
}

CPage* CPageManager::RemoveElem(int index)
{
	CPage *p;
	int k;
	
	ASSERT(index >= 0 && index < this->mTop);
	p = this->GetElem(index);

	for(k = index; k < this->mTop-1; k++)
	{
		this->mIndex[k] = this->mIndex[k + 1];
	}
	this->mTop --;
	this->mIndex[this->mTop] = NULL;
	return p;
}

status_t CPageManager::DelElem(int i)
{
	CPage *p = this->RemoveElem(i);
	if(p != NULL)
	{
		this->DelNode(p);
		return OK;
	}
	return ERROR;
}

status_t CPageManager::InsOrderedPtr(CPage *page, int order,int unique)
{
	int pos,find;
	pos = this->BSearchPos(page,order,&find);
	if(find && unique)
		return ERROR;
	return this->InsElemPtr(pos,page);
}

status_t CPageManager::InsOrdered(CPage *page, int order,int unique)
{
	int pos,find;
	ASSERT(page);
	pos = this->BSearchPos(page,order,&find);
	if(find && unique)
		return ERROR;
	return this->InsElem(pos,page);
}

int CPageManager::BSearchPos(CPage *page, int order, int *find_flag)
{
	int low,high,mid,comp;
	
	low = 0; 
	high = this->GetLen() - 1;

	while(low<=high)
	{
		mid = (low+high) >> 1;

		comp = this->CompNode(this->mIndex[mid],page);
		if(comp == 0)
		{
			*find_flag = TRUE;
			return mid;
		}
	
		if(order != 0) comp = -comp;
		if(comp>0)high=mid-1;else low=mid+1;
	}
	*find_flag = FALSE;
	return low;
}

status_t CPageManager::Sort(int order)
{
	int i,len;
	CPageManager tmp;

	len = this->GetLen();
	tmp.Init(len);

	for(i = 0; i < len; i++)
	{
		tmp.PushPtr(this->GetElem(i));
	}

	this->mTop = 0;
	for(i = 0; i < len; i++)
	{
		this->InsOrderedPtr(tmp.PopPtr(),order,0);
	}
	
	for(i = 0; i < len; i++)
	{
		tmp.mIndex[i] = NULL;
	}

	return OK;
}
status_t CPageManager::Copy(CPageManager *stk)
{
	int i;

	ASSERT(stk);
	this->Destroy();
	this->Init(stk->GetLen());
	for(i = 0; i < stk->GetLen(); i++)
	{
		CPage *p = stk->GetElem(i);
		ASSERT(p);
		this->Push(p);
	}
	return OK;
}
status_t CPageManager::Print(int _level,CFileBase *_buf)
{
	return OK;
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
status_t CPageManager::CopyNode(CPage *dst, CPage *src)
{
	ASSERT(0);
	return ERROR;
}

CPage* CPageManager::CloneNode(CPage *page)
{
	ASSERT(0);
	return NULL;
}

status_t CPageManager::DelNode(CPage *page)
{
	DEL(page);
	return OK;
}

int CPageManager::CompNode(CPage *page1, CPage *page2)
{
	ASSERT(page1 && page2);
	return crt_stricmp_w(page1->GetNameStr(),page2->GetNameStr());
}

CPage* CPageManager::GetPage(const wchar_t *name)
{
	CPage tmp;
	tmp.Init();
	tmp.SetName(name);
	return this->Search(&tmp);
}
