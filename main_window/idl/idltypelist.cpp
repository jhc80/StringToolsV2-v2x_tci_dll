#include "idltypelist.h"
#include "mem_tool.h"
#include "syslog.h"

CIdlTypeList::CIdlTypeList()
{
	this->InitBasic();  
}
CIdlTypeList::~CIdlTypeList()
{
	this->Destroy();
}
status_t CIdlTypeList::InitBasic()
{
	this->m_Index = NULL;
	this->m_Top = 0;
	this->m_Size = 0;	
	return OK;
}
status_t CIdlTypeList::Init()
{
    return this->Init(64);
}
status_t CIdlTypeList::Init(int init_size)
{
	int i;
	this->InitBasic();  
	this->m_Size = init_size;
	MALLOC(this->m_Index,CIdlType* ,this->m_Size);
	for(i = 0; i < this->m_Size; i++)
		this->m_Index[i] = NULL;
	return OK;
}
status_t CIdlTypeList::Destroy()
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
bool CIdlTypeList::IsEmpty()
{
	return this->m_Top <= 0;
}
bool CIdlTypeList::IsFull()
{
	return this->m_Top >= this->m_Size;
}

status_t CIdlTypeList::AutoResize()
{
	int i;

	if(this->IsFull())
	{
		REALLOC(this->m_Index,CIdlType*,this->m_Size,this->m_Size*2);
		this->m_Size *= 2;
		for(i = this->m_Top; i < this->m_Size; i++)
		{
			this->m_Index[i] = NULL;
		}
	}
	return OK;
}

status_t CIdlTypeList::Push(CIdlType *idltype)
{
	CIdlType *tmp;
	ASSERT(idltype);
	tmp = this->CloneNode(idltype);
	if(!this->PushPtr(tmp))
	{
		this->DelNode(tmp);
		return ERROR;
	}
	
	return OK;
}

status_t CIdlTypeList::PushPtr(CIdlType *idltype)
{
	ASSERT(idltype);	
	this->AutoResize();
	ASSERT(!this->IsFull());
	this->m_Index[this->m_Top] = idltype;
	this->m_Top++;
	return OK;
}

CIdlType * CIdlTypeList::PopPtr()
{
	if(this->IsEmpty())
		return NULL;
	this->m_Top--;
	return this->m_Index[this->m_Top];
}

status_t CIdlTypeList::Pop(CIdlType *idltype)
{
	ASSERT(!this->IsEmpty());	
	this->m_Top--;
	this->CopyNode(idltype,this->m_Index[this->m_Top]);
	this->DelNode(this->m_Index[this->m_Top]);
	return OK;
}
int CIdlTypeList::GetLen()
{
	return this->m_Top;
}

int CIdlTypeList::SearchPos(CIdlType *idltype)
{
	int i;
	for(i=0;i<this->m_Top;i++)
	{
		if(this->CompNode(this->m_Index[i],idltype) == 0)
			return i;
	}
	return -1;
}

CIdlType* CIdlTypeList::Search(CIdlType *idltype)
{
	int pos = this->SearchPos(idltype);
	if(pos >= 0 && pos < this->m_Top)
		return this->m_Index[pos];;
	return NULL;
}
CIdlType* CIdlTypeList::GetTopPtr()
{
	if(this->IsEmpty())
		return NULL;
	return this->m_Index[this->m_Top - 1];
}
status_t CIdlTypeList::DelTop()
{
	if(this->IsEmpty())
		return ERROR;
	this->m_Top--;
	this->DelNode(this->m_Index[this->m_Top]);
	return OK;
}
status_t CIdlTypeList::Clear()
{
	while(this->DelTop());
	return OK;
}

CIdlType* CIdlTypeList::GetElem(int index)
{
	if(index < 0 || index >= this->m_Top)
		return NULL;
	return this->m_Index[index];
}

CIdlType* CIdlTypeList::BSearchNode(CIdlType *idltype,int order)
{
	return this->GetElem(this->BSearch(idltype,order));
}
int CIdlTypeList::BSearch(CIdlType *idltype,int order)
{
	int find,pos;
	pos = this->BSearchPos(idltype,order,&find);
	if(find) return pos;
	return -1;
}

status_t CIdlTypeList::InsElemPtr(int i, CIdlType *idltype)
{
	int k;

	ASSERT(idltype);
	ASSERT(i >= 0 && i <= this->m_Top);

	this->AutoResize();
	ASSERT(!this->IsFull());
	for(k = this->m_Top; k > i; k--)
	{
		this->m_Index[k] = this->m_Index[k - 1];
	}
	this->m_Index[i] = idltype;
	this->m_Top++;
	return OK;
}

status_t CIdlTypeList::InsElem(int i, CIdlType *idltype)
{
	CIdlType *tmp;
	ASSERT(idltype);
	tmp = this->CloneNode(idltype);
	if(!this->InsElemPtr(i,tmp))
	{
		this->DelNode(tmp);
		return ERROR;
	}
	return OK;
}

CIdlType* CIdlTypeList::RemoveElem(int index)
{
	CIdlType *p;
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

status_t CIdlTypeList::DelElem(int i)
{
	CIdlType *p = this->RemoveElem(i);
	if(p != NULL)
	{
		this->DelNode(p);
		return OK;
	}
	return ERROR;
}

status_t CIdlTypeList::InsOrderedPtr(CIdlType *idltype, int order,int unique)
{
	int pos,find;
	pos = this->BSearchPos(idltype,order,&find);
	if(find && unique)
		return ERROR;
	return this->InsElemPtr(pos,idltype);
}

status_t CIdlTypeList::InsOrdered(CIdlType *idltype, int order,int unique)
{
	int pos,find;
	ASSERT(idltype);
	pos = this->BSearchPos(idltype,order,&find);
	if(find && unique)
		return ERROR;
	return this->InsElem(pos,idltype);
}

int CIdlTypeList::BSearchPos(CIdlType *idltype, int order, int *find_flag)
{
	int low,high,mid,comp;
	
	low = 0; 
	high = this->GetLen() - 1;

	while(low<=high)
	{
		mid = (low+high) >> 1;

		comp = this->CompNode(this->m_Index[mid],idltype);
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

status_t CIdlTypeList::Sort(int order)
{
	int i,len;
	CIdlTypeList tmp;

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
status_t CIdlTypeList::Copy(CIdlTypeList *stk)
{
	int i;

	ASSERT(stk);
	this->Destroy();
	this->Init(stk->GetLen());
	for(i = 0; i < stk->GetLen(); i++)
	{
		CIdlType *p = stk->GetElem(i);
		ASSERT(p);
		this->Push(p);
	}
	return OK;
}
status_t CIdlTypeList::Print(CFileBase *_buf)
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
status_t CIdlTypeList::CopyNode(CIdlType *dst, CIdlType *src)
{
	return dst->Copy(src);
}

CIdlType* CIdlTypeList::CloneNode(CIdlType *idltype)
{
	CIdlType *tmp;
	NEW(tmp,CIdlType);
	tmp->Init();
	this->CopyNode(tmp,idltype);
	return tmp;
}

status_t CIdlTypeList::DelNode(CIdlType *idltype)
{
	DEL(idltype);
	return OK;
}

int CIdlTypeList::CompNode(CIdlType *idltype1, CIdlType *idltype2)
{
	ASSERT(idltype1 && idltype2);
	return idltype1->Comp(idltype2);
}

status_t CIdlTypeList::ToLua(CFileBase *buf)
{
    ASSERT(buf);
    
    for(int i = 0; i < GetLen(); i++)
    {
        CIdlType *t = GetElem(i);
        ASSERT(t);
        buf->Log("{");
        buf->IncLogLevel(1);
        t->ToLua(buf);
        buf->IncLogLevel(-1);
        buf->Log("},");
    }
    
    return OK;
}
