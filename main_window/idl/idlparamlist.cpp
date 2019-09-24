#include "idlparamlist.h"
#include "mem_tool.h"
#include "syslog.h"

CIdlParamList::CIdlParamList()
{
	this->InitBasic();  
}
CIdlParamList::~CIdlParamList()
{
	this->Destroy();
}
status_t CIdlParamList::InitBasic()
{
	this->m_Index = NULL;
	this->m_Top = 0;
	this->m_Size = 0;	
	return OK;
}
status_t CIdlParamList::Init(int init_size)
{
	int i;
	this->InitBasic();  
	this->m_Size = init_size;
	MALLOC(this->m_Index,CIdlParam* ,this->m_Size);
	for(i = 0; i < this->m_Size; i++)
		this->m_Index[i] = NULL;
	return OK;
}
status_t CIdlParamList::Init()
{
    return this->Init(64);
}
status_t CIdlParamList::Destroy()
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
bool CIdlParamList::IsEmpty()
{
	return this->m_Top <= 0;
}
bool CIdlParamList::IsFull()
{
	return this->m_Top >= this->m_Size;
}

status_t CIdlParamList::AutoResize()
{
	int i;

	if(this->IsFull())
	{
		REALLOC(this->m_Index,CIdlParam*,this->m_Size,this->m_Size*2);
		this->m_Size *= 2;
		for(i = this->m_Top; i < this->m_Size; i++)
		{
			this->m_Index[i] = NULL;
		}
	}
	return OK;
}

status_t CIdlParamList::Push(CIdlParam *idlparam)
{
	CIdlParam *tmp;
	ASSERT(idlparam);
	tmp = this->CloneNode(idlparam);
	if(!this->PushPtr(tmp))
	{
		this->DelNode(tmp);
		return ERROR;
	}
	
	return OK;
}

status_t CIdlParamList::PushPtr(CIdlParam *idlparam)
{
	ASSERT(idlparam);	
	this->AutoResize();
	ASSERT(!this->IsFull());
	this->m_Index[this->m_Top] = idlparam;
	this->m_Top++;
	return OK;
}

CIdlParam * CIdlParamList::PopPtr()
{
	if(this->IsEmpty())
		return NULL;
	this->m_Top--;
	return this->m_Index[this->m_Top];
}

status_t CIdlParamList::Pop(CIdlParam *idlparam)
{
	ASSERT(!this->IsEmpty());	
	this->m_Top--;
	this->CopyNode(idlparam,this->m_Index[this->m_Top]);
	this->DelNode(this->m_Index[this->m_Top]);
	return OK;
}
int CIdlParamList::GetLen()
{
	return this->m_Top;
}

int CIdlParamList::SearchPos(CIdlParam *idlparam)
{
	int i;
	for(i=0;i<this->m_Top;i++)
	{
		if(this->CompNode(this->m_Index[i],idlparam) == 0)
			return i;
	}
	return -1;
}

CIdlParam* CIdlParamList::Search(CIdlParam *idlparam)
{
	int pos = this->SearchPos(idlparam);
	if(pos >= 0 && pos < this->m_Top)
		return this->m_Index[pos];;
	return NULL;
}
CIdlParam* CIdlParamList::GetTopPtr()
{
	if(this->IsEmpty())
		return NULL;
	return this->m_Index[this->m_Top - 1];
}
status_t CIdlParamList::DelTop()
{
	if(this->IsEmpty())
		return ERROR;
	this->m_Top--;
	this->DelNode(this->m_Index[this->m_Top]);
	return OK;
}
status_t CIdlParamList::Clear()
{
	while(this->DelTop());
	return OK;
}

CIdlParam* CIdlParamList::GetElem(int index)
{
	if(index < 0 || index >= this->m_Top)
		return NULL;
	return this->m_Index[index];
}

CIdlParam* CIdlParamList::BSearchNode(CIdlParam *idlparam,int order)
{
	return this->GetElem(this->BSearch(idlparam,order));
}
int CIdlParamList::BSearch(CIdlParam *idlparam,int order)
{
	int find,pos;
	pos = this->BSearchPos(idlparam,order,&find);
	if(find) return pos;
	return -1;
}

status_t CIdlParamList::InsElemPtr(int i, CIdlParam *idlparam)
{
	int k;

	ASSERT(idlparam);
	ASSERT(i >= 0 && i <= this->m_Top);

	this->AutoResize();
	ASSERT(!this->IsFull());
	for(k = this->m_Top; k > i; k--)
	{
		this->m_Index[k] = this->m_Index[k - 1];
	}
	this->m_Index[i] = idlparam;
	this->m_Top++;
	return OK;
}

status_t CIdlParamList::InsElem(int i, CIdlParam *idlparam)
{
	CIdlParam *tmp;
	ASSERT(idlparam);
	tmp = this->CloneNode(idlparam);
	if(!this->InsElemPtr(i,tmp))
	{
		this->DelNode(tmp);
		return ERROR;
	}
	return OK;
}

CIdlParam* CIdlParamList::RemoveElem(int index)
{
	CIdlParam *p;
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

status_t CIdlParamList::DelElem(int i)
{
	CIdlParam *p = this->RemoveElem(i);
	if(p != NULL)
	{
		this->DelNode(p);
		return OK;
	}
	return ERROR;
}

status_t CIdlParamList::InsOrderedPtr(CIdlParam *idlparam, int order,int unique)
{
	int pos,find;
	pos = this->BSearchPos(idlparam,order,&find);
	if(find && unique)
		return ERROR;
	return this->InsElemPtr(pos,idlparam);
}

status_t CIdlParamList::InsOrdered(CIdlParam *idlparam, int order,int unique)
{
	int pos,find;
	ASSERT(idlparam);
	pos = this->BSearchPos(idlparam,order,&find);
	if(find && unique)
		return ERROR;
	return this->InsElem(pos,idlparam);
}

int CIdlParamList::BSearchPos(CIdlParam *idlparam, int order, int *find_flag)
{
	int low,high,mid,comp;
	
	low = 0; 
	high = this->GetLen() - 1;

	while(low<=high)
	{
		mid = (low+high) >> 1;

		comp = this->CompNode(this->m_Index[mid],idlparam);
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

status_t CIdlParamList::Sort(int order)
{
	int i,len;
	CIdlParamList tmp;

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
status_t CIdlParamList::Copy(CIdlParamList *stk)
{
	int i;

	ASSERT(stk);
	this->Destroy();
	this->Init(stk->GetLen());
	for(i = 0; i < stk->GetLen(); i++)
	{
		CIdlParam *p = stk->GetElem(i);
		ASSERT(p);
		this->Push(p);
	}
	return OK;
}
status_t CIdlParamList::Print(CFileBase *_buf)
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
status_t CIdlParamList::CopyNode(CIdlParam *dst, CIdlParam *src)
{
	return dst->Copy(src);
}

CIdlParam* CIdlParamList::CloneNode(CIdlParam *idlparam)
{
	CIdlParam *tmp;
	NEW(tmp,CIdlParam);
	tmp->Init();
	this->CopyNode(tmp,idlparam);
	return tmp;
}

status_t CIdlParamList::DelNode(CIdlParam *idlparam)
{
	DEL(idlparam);
	return OK;
}

int CIdlParamList::CompNode(CIdlParam *idlparam1, CIdlParam *idlparam2)
{
	ASSERT(idlparam1 && idlparam2);
	return idlparam1->Comp(idlparam2);
}

status_t CIdlParamList::ToLua(CFileBase *buf)
{
    ASSERT(buf);
    
    for(int i = 0; i < GetLen(); i++)
    {
        CIdlParam *p = GetElem(i);
        ASSERT(p);
        buf->Log("{");
        buf->IncLogLevel(1);
        p->ToLua(buf);
        buf->IncLogLevel(-1);
        buf->Log("},");
    }
    return OK;
}

