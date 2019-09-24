#include "idlfunctionlist.h"
#include "mem_tool.h"
#include "syslog.h"

CIdlFunctionList::CIdlFunctionList()
{
	this->InitBasic();  
}
CIdlFunctionList::~CIdlFunctionList()
{
	this->Destroy();
}
status_t CIdlFunctionList::InitBasic()
{
	this->m_Index = NULL;
	this->m_Top = 0;
	this->m_Size = 0;	
	return OK;
}
status_t CIdlFunctionList::Init(int init_size)
{
	int i;
	this->InitBasic();  
	this->m_Size = init_size;
	MALLOC(this->m_Index,CIdlFunction* ,this->m_Size);
	for(i = 0; i < this->m_Size; i++)
		this->m_Index[i] = NULL;
	return OK;
}
status_t CIdlFunctionList::Init()
{
    return this->Init(64);
}
status_t CIdlFunctionList::Destroy()
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
bool CIdlFunctionList::IsEmpty()
{
	return this->m_Top <= 0;
}
bool CIdlFunctionList::IsFull()
{
	return this->m_Top >= this->m_Size;
}

status_t CIdlFunctionList::AutoResize()
{
	int i;

	if(this->IsFull())
	{
		REALLOC(this->m_Index,CIdlFunction*,this->m_Size,this->m_Size*2);
		this->m_Size *= 2;
		for(i = this->m_Top; i < this->m_Size; i++)
		{
			this->m_Index[i] = NULL;
		}
	}
	return OK;
}

status_t CIdlFunctionList::Push(CIdlFunction *idlfunction)
{
	CIdlFunction *tmp;
	ASSERT(idlfunction);
	tmp = this->CloneNode(idlfunction);
	if(!this->PushPtr(tmp))
	{
		this->DelNode(tmp);
		return ERROR;
	}
	
	return OK;
}

status_t CIdlFunctionList::PushPtr(CIdlFunction *idlfunction)
{
	ASSERT(idlfunction);	
	this->AutoResize();
	ASSERT(!this->IsFull());
	this->m_Index[this->m_Top] = idlfunction;
	this->m_Top++;
	return OK;
}

CIdlFunction * CIdlFunctionList::PopPtr()
{
	if(this->IsEmpty())
		return NULL;
	this->m_Top--;
	return this->m_Index[this->m_Top];
}

status_t CIdlFunctionList::Pop(CIdlFunction *idlfunction)
{
	ASSERT(!this->IsEmpty());	
	this->m_Top--;
	this->CopyNode(idlfunction,this->m_Index[this->m_Top]);
	this->DelNode(this->m_Index[this->m_Top]);
	return OK;
}
int CIdlFunctionList::GetLen()
{
	return this->m_Top;
}

int CIdlFunctionList::SearchPos(CIdlFunction *idlfunction)
{
	int i;
	for(i=0;i<this->m_Top;i++)
	{
		if(this->CompNode(this->m_Index[i],idlfunction) == 0)
			return i;
	}
	return -1;
}

CIdlFunction* CIdlFunctionList::Search(CIdlFunction *idlfunction)
{
	int pos = this->SearchPos(idlfunction);
	if(pos >= 0 && pos < this->m_Top)
		return this->m_Index[pos];;
	return NULL;
}
CIdlFunction* CIdlFunctionList::GetTopPtr()
{
	if(this->IsEmpty())
		return NULL;
	return this->m_Index[this->m_Top - 1];
}
status_t CIdlFunctionList::DelTop()
{
	if(this->IsEmpty())
		return ERROR;
	this->m_Top--;
	this->DelNode(this->m_Index[this->m_Top]);
	return OK;
}
status_t CIdlFunctionList::Clear()
{
	while(this->DelTop());
	return OK;
}

CIdlFunction* CIdlFunctionList::GetElem(int index)
{
	if(index < 0 || index >= this->m_Top)
		return NULL;
	return this->m_Index[index];
}

CIdlFunction* CIdlFunctionList::BSearchNode(CIdlFunction *idlfunction,int order)
{
	return this->GetElem(this->BSearch(idlfunction,order));
}
int CIdlFunctionList::BSearch(CIdlFunction *idlfunction,int order)
{
	int find,pos;
	pos = this->BSearchPos(idlfunction,order,&find);
	if(find) return pos;
	return -1;
}

status_t CIdlFunctionList::InsElemPtr(int i, CIdlFunction *idlfunction)
{
	int k;

	ASSERT(idlfunction);
	ASSERT(i >= 0 && i <= this->m_Top);

	this->AutoResize();
	ASSERT(!this->IsFull());
	for(k = this->m_Top; k > i; k--)
	{
		this->m_Index[k] = this->m_Index[k - 1];
	}
	this->m_Index[i] = idlfunction;
	this->m_Top++;
	return OK;
}

status_t CIdlFunctionList::InsElem(int i, CIdlFunction *idlfunction)
{
	CIdlFunction *tmp;
	ASSERT(idlfunction);
	tmp = this->CloneNode(idlfunction);
	if(!this->InsElemPtr(i,tmp))
	{
		this->DelNode(tmp);
		return ERROR;
	}
	return OK;
}

CIdlFunction* CIdlFunctionList::RemoveElem(int index)
{
	CIdlFunction *p;
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

status_t CIdlFunctionList::DelElem(int i)
{
	CIdlFunction *p = this->RemoveElem(i);
	if(p != NULL)
	{
		this->DelNode(p);
		return OK;
	}
	return ERROR;
}

status_t CIdlFunctionList::InsOrderedPtr(CIdlFunction *idlfunction, int order,int unique)
{
	int pos,find;
	pos = this->BSearchPos(idlfunction,order,&find);
	if(find && unique)
		return ERROR;
	return this->InsElemPtr(pos,idlfunction);
}

status_t CIdlFunctionList::InsOrdered(CIdlFunction *idlfunction, int order,int unique)
{
	int pos,find;
	ASSERT(idlfunction);
	pos = this->BSearchPos(idlfunction,order,&find);
	if(find && unique)
		return ERROR;
	return this->InsElem(pos,idlfunction);
}

int CIdlFunctionList::BSearchPos(CIdlFunction *idlfunction, int order, int *find_flag)
{
	int low,high,mid,comp;
	
	low = 0; 
	high = this->GetLen() - 1;

	while(low<=high)
	{
		mid = (low+high) >> 1;

		comp = this->CompNode(this->m_Index[mid],idlfunction);
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

status_t CIdlFunctionList::Sort(int order)
{
	int i,len;
	CIdlFunctionList tmp;

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
status_t CIdlFunctionList::Copy(CIdlFunctionList *stk)
{
	int i;

	ASSERT(stk);
	this->Destroy();
	this->Init(stk->GetLen());
	for(i = 0; i < stk->GetLen(); i++)
	{
		CIdlFunction *p = stk->GetElem(i);
		ASSERT(p);
		this->Push(p);
	}
	return OK;
}
status_t CIdlFunctionList::Print(CFileBase *_buf)
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
status_t CIdlFunctionList::CopyNode(CIdlFunction *dst, CIdlFunction *src)
{
	return dst->Copy(src);
}

CIdlFunction* CIdlFunctionList::CloneNode(CIdlFunction *idlfunction)
{
	CIdlFunction *tmp;
	NEW(tmp,CIdlFunction);
	tmp->Init();
	this->CopyNode(tmp,idlfunction);
	return tmp;
}

status_t CIdlFunctionList::DelNode(CIdlFunction *idlfunction)
{
	DEL(idlfunction);
	return OK;
}

int CIdlFunctionList::CompNode(CIdlFunction *idlfunction1, CIdlFunction *idlfunction2)
{
	ASSERT(idlfunction1 && idlfunction2);
	return idlfunction1->Comp(idlfunction2);
}

status_t CIdlFunctionList::ToLua(CFileBase *buf)
{
    ASSERT(buf);
    
    for(int i = 0; i < GetLen(); i++)
    {
        CIdlFunction *p = GetElem(i);
        ASSERT(p);
        buf->Log("{");
        buf->IncLogLevel(1);
        p->ToLua(buf);
        buf->IncLogLevel(-1);
        buf->Log("},");
    }
    return OK;
}
