

#include "idlclasslist.h"
#include "mem_tool.h"
#include "syslog.h"

CIdlClassList::CIdlClassList()
{
	this->InitBasic();  
}
CIdlClassList::~CIdlClassList()
{
	this->Destroy();
}
status_t CIdlClassList::InitBasic()
{
	this->m_Index = NULL;
	this->m_Top = 0;
	this->m_Size = 0;	
	return OK;
}
status_t CIdlClassList::Init(int init_size)
{
	int i;
	this->InitBasic();  
	this->m_Size = init_size;
	MALLOC(this->m_Index,CIdlClass* ,this->m_Size);
	for(i = 0; i < this->m_Size; i++)
		this->m_Index[i] = NULL;
	return OK;
}
status_t CIdlClassList::Destroy()
{
	int i;
	if(this->m_Index == NULL)
		return ERROR;
	for(i = 0; i < this->m_Top; i++)
	{
		this->DelNode(this->m_Index[i]);
	}
	FREE(this->m_Index);
	this->InitBasic();	
	return OK;
}
bool CIdlClassList::IsEmpty()
{
	return this->m_Top <= 0;
}
bool CIdlClassList::IsFull()
{
	return this->m_Top >= this->m_Size;
}

status_t CIdlClassList::AutoResize()
{
	int i;

	if(this->IsFull())
	{
		REALLOC(this->m_Index,CIdlClass*,this->m_Size,this->m_Size*2);
		this->m_Size *= 2;
		for(i = this->m_Top; i < this->m_Size; i++)
		{
			this->m_Index[i] = NULL;
		}
	}
	return OK;
}

status_t CIdlClassList::Push(CIdlClass *idlclass)
{
	CIdlClass *tmp;
	ASSERT(idlclass);
	tmp = this->CloneNode(idlclass);
	if(!this->PushPtr(tmp))
	{
		this->DelNode(tmp);
		return ERROR;
	}
	
	return OK;
}

status_t CIdlClassList::PushPtr(CIdlClass *idlclass)
{
	ASSERT(idlclass);	
	this->AutoResize();
	ASSERT(!this->IsFull());
	this->m_Index[this->m_Top] = idlclass;
	this->m_Top++;
	return OK;
}

CIdlClass * CIdlClassList::PopPtr()
{
	if(this->IsEmpty())
		return NULL;
	this->m_Top--;
	return this->m_Index[this->m_Top];
}

status_t CIdlClassList::Pop(CIdlClass *idlclass)
{
	ASSERT(!this->IsEmpty());	
	this->m_Top--;
	this->CopyNode(idlclass,this->m_Index[this->m_Top]);
	this->DelNode(this->m_Index[this->m_Top]);
	return OK;
}
int CIdlClassList::GetLen()
{
	return this->m_Top;
}

int CIdlClassList::SearchPos(CIdlClass *idlclass)
{
	int i;
	for(i=0;i<this->m_Top;i++)
	{
		if(this->CompNode(this->m_Index[i],idlclass) == 0)
			return i;
	}
	return -1;
}

CIdlClass* CIdlClassList::Search(CIdlClass *idlclass)
{
	int pos = this->SearchPos(idlclass);
	if(pos >= 0 && pos < this->m_Top)
		return this->m_Index[pos];;
	return NULL;
}
CIdlClass* CIdlClassList::GetTopPtr()
{
	if(this->IsEmpty())
		return NULL;
	return this->m_Index[this->m_Top - 1];
}
status_t CIdlClassList::DelTop()
{
	if(this->IsEmpty())
		return ERROR;
	this->m_Top--;
	this->DelNode(this->m_Index[this->m_Top]);
	return OK;
}
status_t CIdlClassList::Clear()
{
	while(this->DelTop());
	return OK;
}

CIdlClass* CIdlClassList::GetElem(int index)
{
	if(index < 0 || index >= this->m_Top)
		return NULL;
	return this->m_Index[index];
}

CIdlClass* CIdlClassList::BSearchNode(CIdlClass *idlclass,int order)
{
	return this->GetElem(this->BSearch(idlclass,order));
}
int CIdlClassList::BSearch(CIdlClass *idlclass,int order)
{
	int find,pos;
	pos = this->BSearchPos(idlclass,order,&find);
	if(find) return pos;
	return -1;
}

status_t CIdlClassList::InsElemPtr(int i, CIdlClass *idlclass)
{
	int k;

	ASSERT(idlclass);
	ASSERT(i >= 0 && i <= this->m_Top);

	this->AutoResize();
	ASSERT(!this->IsFull());
	for(k = this->m_Top; k > i; k--)
	{
		this->m_Index[k] = this->m_Index[k - 1];
	}
	this->m_Index[i] = idlclass;
	this->m_Top++;
	return OK;
}

status_t CIdlClassList::InsElem(int i, CIdlClass *idlclass)
{
	CIdlClass *tmp;
	ASSERT(idlclass);
	tmp = this->CloneNode(idlclass);
	if(!this->InsElemPtr(i,tmp))
	{
		this->DelNode(tmp);
		return ERROR;
	}
	return OK;
}

CIdlClass* CIdlClassList::RemoveElem(int index)
{
	CIdlClass *p;
	int k;
	
	ASSERT(index >= 0 && index < this->m_Top);
	p = this->GetElem(index);

	for(k = index; k < this->m_Top-1; k++)
	{
		this->m_Index[k] = this->m_Index[k + 1];
	}
	this->m_Top --;
	this->m_Index[this->m_Top] = NULL;
	return p;
}

status_t CIdlClassList::DelElem(int i)
{
	CIdlClass *p = this->RemoveElem(i);
	if(p != NULL)
	{
		this->DelNode(p);
		return OK;
	}
	return ERROR;
}

status_t CIdlClassList::InsOrderedPtr(CIdlClass *idlclass, int order,int unique)
{
	int pos,find;
	pos = this->BSearchPos(idlclass,order,&find);
	if(find && unique)
		return ERROR;
	return this->InsElemPtr(pos,idlclass);
}

status_t CIdlClassList::InsOrdered(CIdlClass *idlclass, int order,int unique)
{
	int pos,find;
	ASSERT(idlclass);
	pos = this->BSearchPos(idlclass,order,&find);
	if(find && unique)
		return ERROR;
	return this->InsElem(pos,idlclass);
}

int CIdlClassList::BSearchPos(CIdlClass *idlclass, int order, int *find_flag)
{
	int low,high,mid,comp;
	
	low = 0; 
	high = this->GetLen() - 1;

	while(low<=high)
	{
		mid = (low+high) >> 1;

		comp = this->CompNode(this->m_Index[mid],idlclass);
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

status_t CIdlClassList::Sort(int order)
{
	int i,len;
	CIdlClassList tmp;

	len = this->GetLen();
	tmp.Init(len);

	for(i = 0; i < len; i++)
	{
		tmp.PushPtr(this->GetElem(i));
	}

	this->m_Top = 0;
	for(i = 0; i < len; i++)
	{
		this->InsOrderedPtr(tmp.PopPtr(),order,0);
	}
	
	for(i = 0; i < len; i++)
	{
		tmp.m_Index[i] = NULL;
	}

	return OK;
}
status_t CIdlClassList::Copy(CIdlClassList *stk)
{
	int i;

	ASSERT(stk);
	this->Destroy();
	this->Init(stk->GetLen());
	for(i = 0; i < stk->GetLen(); i++)
	{
		CIdlClass *p = stk->GetElem(i);
		ASSERT(p);
		this->Push(p);
	}
	return OK;
}
status_t CIdlClassList::Print(CFileBase *_buf)
{
	for(int i = 0; i < this->m_Top; i++)
	{
		if(this->m_Index[i])
		{
			_buf->Log("[%d]={",i);
			_buf->IncLogLevel(1);
			this->m_Index[i]->Print(_buf);
			_buf->IncLogLevel(-1);
			_buf->Log("}");
		}
	}
	_buf->Log("top = %d",this->m_Top);
	_buf->Log("size = %d",this->m_Size);
	return OK;
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
status_t CIdlClassList::CopyNode(CIdlClass *dst, CIdlClass *src)
{
	return dst->Copy(src);
}

CIdlClass* CIdlClassList::CloneNode(CIdlClass *idlclass)
{
	CIdlClass *tmp;
	NEW(tmp,CIdlClass);
	tmp->Init();
	this->CopyNode(tmp,idlclass);
	return tmp;
}

status_t CIdlClassList::DelNode(CIdlClass *idlclass)
{
	DEL(idlclass);
	return OK;
}

int CIdlClassList::CompNode(CIdlClass *idlclass1, CIdlClass *idlclass2)
{
	ASSERT(idlclass1 && idlclass2);
	return idlclass1->Comp(idlclass2);
}

status_t CIdlClassList::ToLua(CFileBase *buf)
{
    ASSERT(buf);
    
	int len = this->GetLen();
    for(int i = 0; i < GetLen(); i++)
    {
        CIdlClass *t = GetElem(i);
        ASSERT(t);
        buf->Log("{");
        buf->IncLogLevel(1);
        t->ToLua(buf);
        buf->IncLogLevel(-1);
        buf->Log("}");

		if(i < len-1)
			buf->Log(",");
    }
    
    return OK;
}
