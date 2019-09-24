#include "idlvariablelist.h"
#include "mem_tool.h"
#include "syslog.h"

CIdlVariableList::CIdlVariableList()
{
	this->InitBasic();  
}
CIdlVariableList::~CIdlVariableList()
{
	this->Destroy();
}
status_t CIdlVariableList::InitBasic()
{
	this->m_Index = NULL;
	this->m_Top = 0;
	this->m_Size = 0;	
	return OK;
}
status_t CIdlVariableList::Init(int init_size)
{
	int i;
	this->InitBasic();  
	this->m_Size = init_size;
	MALLOC(this->m_Index,CIdlVariable* ,this->m_Size);
	for(i = 0; i < this->m_Size; i++)
		this->m_Index[i] = NULL;
	return OK;
}

status_t CIdlVariableList::Init()
{
    return this->Init(64);
}

status_t CIdlVariableList::Destroy()
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
bool CIdlVariableList::IsEmpty()
{
	return this->m_Top <= 0;
}
bool CIdlVariableList::IsFull()
{
	return this->m_Top >= this->m_Size;
}

status_t CIdlVariableList::AutoResize()
{
	int i;

	if(this->IsFull())
	{
		REALLOC(this->m_Index,CIdlVariable*,this->m_Size,this->m_Size*2);
		this->m_Size *= 2;
		for(i = this->m_Top; i < this->m_Size; i++)
		{
			this->m_Index[i] = NULL;
		}
	}
	return OK;
}

status_t CIdlVariableList::Push(CIdlVariable *idlvariable)
{
	CIdlVariable *tmp;
	ASSERT(idlvariable);
	tmp = this->CloneNode(idlvariable);
	if(!this->PushPtr(tmp))
	{
		this->DelNode(tmp);
		return ERROR;
	}
	
	return OK;
}

status_t CIdlVariableList::PushPtr(CIdlVariable *idlvariable)
{
	ASSERT(idlvariable);	
	this->AutoResize();
	ASSERT(!this->IsFull());
	this->m_Index[this->m_Top] = idlvariable;
	this->m_Top++;
	return OK;
}

CIdlVariable * CIdlVariableList::PopPtr()
{
	if(this->IsEmpty())
		return NULL;
	this->m_Top--;
	return this->m_Index[this->m_Top];
}

status_t CIdlVariableList::Pop(CIdlVariable *idlvariable)
{
	ASSERT(!this->IsEmpty());	
	this->m_Top--;
	this->CopyNode(idlvariable,this->m_Index[this->m_Top]);
	this->DelNode(this->m_Index[this->m_Top]);
	return OK;
}
int CIdlVariableList::GetLen()
{
	return this->m_Top;
}

int CIdlVariableList::SearchPos(CIdlVariable *idlvariable)
{
	int i;
	for(i=0;i<this->m_Top;i++)
	{
		if(this->CompNode(this->m_Index[i],idlvariable) == 0)
			return i;
	}
	return -1;
}

CIdlVariable* CIdlVariableList::Search(CIdlVariable *idlvariable)
{
	int pos = this->SearchPos(idlvariable);
	if(pos >= 0 && pos < this->m_Top)
		return this->m_Index[pos];;
	return NULL;
}
CIdlVariable* CIdlVariableList::GetTopPtr()
{
	if(this->IsEmpty())
		return NULL;
	return this->m_Index[this->m_Top - 1];
}
status_t CIdlVariableList::DelTop()
{
	if(this->IsEmpty())
		return ERROR;
	this->m_Top--;
	this->DelNode(this->m_Index[this->m_Top]);
	return OK;
}
status_t CIdlVariableList::Clear()
{
	while(this->DelTop());
	return OK;
}

CIdlVariable* CIdlVariableList::GetElem(int index)
{
	if(index < 0 || index >= this->m_Top)
		return NULL;
	return this->m_Index[index];
}

CIdlVariable* CIdlVariableList::BSearchNode(CIdlVariable *idlvariable,int order)
{
	return this->GetElem(this->BSearch(idlvariable,order));
}
int CIdlVariableList::BSearch(CIdlVariable *idlvariable,int order)
{
	int find,pos;
	pos = this->BSearchPos(idlvariable,order,&find);
	if(find) return pos;
	return -1;
}

status_t CIdlVariableList::InsElemPtr(int i, CIdlVariable *idlvariable)
{
	int k;

	ASSERT(idlvariable);
	ASSERT(i >= 0 && i <= this->m_Top);

	this->AutoResize();
	ASSERT(!this->IsFull());
	for(k = this->m_Top; k > i; k--)
	{
		this->m_Index[k] = this->m_Index[k - 1];
	}
	this->m_Index[i] = idlvariable;
	this->m_Top++;
	return OK;
}

status_t CIdlVariableList::InsElem(int i, CIdlVariable *idlvariable)
{
	CIdlVariable *tmp;
	ASSERT(idlvariable);
	tmp = this->CloneNode(idlvariable);
	if(!this->InsElemPtr(i,tmp))
	{
		this->DelNode(tmp);
		return ERROR;
	}
	return OK;
}

CIdlVariable* CIdlVariableList::RemoveElem(int index)
{
	CIdlVariable *p;
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

status_t CIdlVariableList::DelElem(int i)
{
	CIdlVariable *p = this->RemoveElem(i);
	if(p != NULL)
	{
		this->DelNode(p);
		return OK;
	}
	return ERROR;
}

status_t CIdlVariableList::InsOrderedPtr(CIdlVariable *idlvariable, int order,int unique)
{
	int pos,find;
	pos = this->BSearchPos(idlvariable,order,&find);
	if(find && unique)
		return ERROR;
	return this->InsElemPtr(pos,idlvariable);
}

status_t CIdlVariableList::InsOrdered(CIdlVariable *idlvariable, int order,int unique)
{
	int pos,find;
	ASSERT(idlvariable);
	pos = this->BSearchPos(idlvariable,order,&find);
	if(find && unique)
		return ERROR;
	return this->InsElem(pos,idlvariable);
}

int CIdlVariableList::BSearchPos(CIdlVariable *idlvariable, int order, int *find_flag)
{
	int low,high,mid,comp;
	
	low = 0; 
	high = this->GetLen() - 1;

	while(low<=high)
	{
		mid = (low+high) >> 1;

		comp = this->CompNode(this->m_Index[mid],idlvariable);
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

status_t CIdlVariableList::Sort(int order)
{
	int i,len;
	CIdlVariableList tmp;

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
status_t CIdlVariableList::Copy(CIdlVariableList *stk)
{
	int i;

	ASSERT(stk);
	this->Destroy();
	this->Init(stk->GetLen());
	for(i = 0; i < stk->GetLen(); i++)
	{
		CIdlVariable *p = stk->GetElem(i);
		ASSERT(p);
		this->Push(p);
	}
	return OK;
}
status_t CIdlVariableList::Print(CFileBase *_buf)
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
status_t CIdlVariableList::CopyNode(CIdlVariable *dst, CIdlVariable *src)
{
	return dst->Copy(src);
}

CIdlVariable* CIdlVariableList::CloneNode(CIdlVariable *idlvariable)
{
	CIdlVariable *tmp;
	NEW(tmp,CIdlVariable);
	tmp->Init();
	this->CopyNode(tmp,idlvariable);
	return tmp;
}

status_t CIdlVariableList::DelNode(CIdlVariable *idlvariable)
{
	DEL(idlvariable);
	return OK;
}

int CIdlVariableList::CompNode(CIdlVariable *idlvariable1, CIdlVariable *idlvariable2)
{
	ASSERT(idlvariable1 && idlvariable2);
	return idlvariable1->Comp(idlvariable2);
}

status_t CIdlVariableList::SetHint(CIdlHint *hint)
{
    for(int i = 0; i < GetLen(); i++)
    {
        this->GetElem(i)->SetHint(hint);
    }
    return OK;
}

status_t CIdlVariableList::Combine(CIdlVariableList *list)
{
    int i;    
    ASSERT(list);
    for(i = 0; i < list->GetLen(); i++)
    {
        CIdlVariable *p = list->GetElem(i);
        ASSERT(p);
        this->Push(p);
    }
	return OK;
}
status_t CIdlVariableList::ToLua(CFileBase *buf)
{
    ASSERT(buf);
    
    for(int i = 0; i < GetLen(); i++)
    {
        CIdlVariable *t = GetElem(i);
        ASSERT(t);
        buf->Log("{");
        buf->IncLogLevel(1);
        t->ToLua(buf);
        buf->IncLogLevel(-1);
        buf->Log("},");
    }
    
    return OK;
}
