#include "idlsentencelist.h"
#include "mem_tool.h"
#include "syslog.h"

CIdlSentenceList::CIdlSentenceList()
{
	this->InitBasic();  
}
CIdlSentenceList::~CIdlSentenceList()
{
	this->Destroy();
}
status_t CIdlSentenceList::InitBasic()
{
	this->m_Index = NULL;
	this->m_Top = 0;
	this->m_Size = 0;	
	return OK;
}
status_t CIdlSentenceList::Init(int init_size)
{
	int i;
	this->InitBasic();  
	this->m_Size = init_size;
	MALLOC(this->m_Index,CIdlSentence* ,this->m_Size);
	for(i = 0; i < this->m_Size; i++)
		this->m_Index[i] = NULL;
	return OK;
}
status_t CIdlSentenceList::Init()
{
    return this->Init(64);
}

status_t CIdlSentenceList::Destroy()
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
bool CIdlSentenceList::IsEmpty()
{
	return this->m_Top <= 0;
}
bool CIdlSentenceList::IsFull()
{
	return this->m_Top >= this->m_Size;
}

status_t CIdlSentenceList::AutoResize()
{
	int i;

	if(this->IsFull())
	{
		REALLOC(this->m_Index,CIdlSentence*,this->m_Size,this->m_Size*2);
		this->m_Size *= 2;
		for(i = this->m_Top; i < this->m_Size; i++)
		{
			this->m_Index[i] = NULL;
		}
	}
	return OK;
}

status_t CIdlSentenceList::Push(CIdlSentence *idlsentence)
{
	CIdlSentence *tmp;
	ASSERT(idlsentence);
	tmp = this->CloneNode(idlsentence);
	if(!this->PushPtr(tmp))
	{
		this->DelNode(tmp);
		return ERROR;
	}
	
	return OK;
}

status_t CIdlSentenceList::PushPtr(CIdlSentence *idlsentence)
{
	ASSERT(idlsentence);	
	this->AutoResize();
	ASSERT(!this->IsFull());
	this->m_Index[this->m_Top] = idlsentence;
	this->m_Top++;
	return OK;
}

CIdlSentence * CIdlSentenceList::PopPtr()
{
	if(this->IsEmpty())
		return NULL;
	this->m_Top--;
	return this->m_Index[this->m_Top];
}

status_t CIdlSentenceList::Pop(CIdlSentence *idlsentence)
{
	ASSERT(!this->IsEmpty());	
	this->m_Top--;
	this->CopyNode(idlsentence,this->m_Index[this->m_Top]);
	this->DelNode(this->m_Index[this->m_Top]);
	return OK;
}
int CIdlSentenceList::GetLen()
{
	return this->m_Top;
}

int CIdlSentenceList::SearchPos(CIdlSentence *idlsentence)
{
	int i;
	for(i=0;i<this->m_Top;i++)
	{
		if(this->CompNode(this->m_Index[i],idlsentence) == 0)
			return i;
	}
	return -1;
}

CIdlSentence* CIdlSentenceList::Search(CIdlSentence *idlsentence)
{
	int pos = this->SearchPos(idlsentence);
	if(pos >= 0 && pos < this->m_Top)
		return this->m_Index[pos];;
	return NULL;
}
CIdlSentence* CIdlSentenceList::GetTopPtr()
{
	if(this->IsEmpty())
		return NULL;
	return this->m_Index[this->m_Top - 1];
}
status_t CIdlSentenceList::DelTop()
{
	if(this->IsEmpty())
		return ERROR;
	this->m_Top--;
	this->DelNode(this->m_Index[this->m_Top]);
	return OK;
}
status_t CIdlSentenceList::Clear()
{
	while(this->DelTop());
	return OK;
}

CIdlSentence* CIdlSentenceList::GetElem(int index)
{
	if(index < 0 || index >= this->m_Top)
		return NULL;
	return this->m_Index[index];
}

CIdlSentence* CIdlSentenceList::BSearchNode(CIdlSentence *idlsentence,int order)
{
	return this->GetElem(this->BSearch(idlsentence,order));
}
int CIdlSentenceList::BSearch(CIdlSentence *idlsentence,int order)
{
	int find,pos;
	pos = this->BSearchPos(idlsentence,order,&find);
	if(find) return pos;
	return -1;
}

status_t CIdlSentenceList::InsElemPtr(int i, CIdlSentence *idlsentence)
{
	int k;

	ASSERT(idlsentence);
	ASSERT(i >= 0 && i <= this->m_Top);

	this->AutoResize();
	ASSERT(!this->IsFull());
	for(k = this->m_Top; k > i; k--)
	{
		this->m_Index[k] = this->m_Index[k - 1];
	}
	this->m_Index[i] = idlsentence;
	this->m_Top++;
	return OK;
}

status_t CIdlSentenceList::InsElem(int i, CIdlSentence *idlsentence)
{
	CIdlSentence *tmp;
	ASSERT(idlsentence);
	tmp = this->CloneNode(idlsentence);
	if(!this->InsElemPtr(i,tmp))
	{
		this->DelNode(tmp);
		return ERROR;
	}
	return OK;
}

CIdlSentence* CIdlSentenceList::RemoveElem(int index)
{
	CIdlSentence *p;
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

status_t CIdlSentenceList::DelElem(int i)
{
	CIdlSentence *p = this->RemoveElem(i);
	if(p != NULL)
	{
		this->DelNode(p);
		return OK;
	}
	return ERROR;
}

status_t CIdlSentenceList::InsOrderedPtr(CIdlSentence *idlsentence, int order,int unique)
{
	int pos,find;
	pos = this->BSearchPos(idlsentence,order,&find);
	if(find && unique)
		return ERROR;
	return this->InsElemPtr(pos,idlsentence);
}

status_t CIdlSentenceList::InsOrdered(CIdlSentence *idlsentence, int order,int unique)
{
	int pos,find;
	ASSERT(idlsentence);
	pos = this->BSearchPos(idlsentence,order,&find);
	if(find && unique)
		return ERROR;
	return this->InsElem(pos,idlsentence);
}

int CIdlSentenceList::BSearchPos(CIdlSentence *idlsentence, int order, int *find_flag)
{
	int low,high,mid,comp;
	
	low = 0; 
	high = this->GetLen() - 1;

	while(low<=high)
	{
		mid = (low+high) >> 1;

		comp = this->CompNode(this->m_Index[mid],idlsentence);
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

status_t CIdlSentenceList::Sort(int order)
{
	int i,len;
	CIdlSentenceList tmp;

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
status_t CIdlSentenceList::Copy(CIdlSentenceList *stk)
{
	int i;

	ASSERT(stk);
	this->Destroy();
	this->Init(stk->GetLen());
	for(i = 0; i < stk->GetLen(); i++)
	{
		CIdlSentence *p = stk->GetElem(i);
		ASSERT(p);
		this->Push(p);
	}
	return OK;
}
status_t CIdlSentenceList::Print(CFileBase *_buf)
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
status_t CIdlSentenceList::CopyNode(CIdlSentence *dst, CIdlSentence *src)
{
	return dst->Copy(src);
}

CIdlSentence* CIdlSentenceList::CloneNode(CIdlSentence *idlsentence)
{
	CIdlSentence *tmp;
	NEW(tmp,CIdlSentence);
	tmp->Init(idlsentence->GetLen());
	this->CopyNode(tmp,idlsentence);
	return tmp;
}

status_t CIdlSentenceList::DelNode(CIdlSentence *idlsentence)
{
	DEL(idlsentence);
	return OK;
}

int CIdlSentenceList::CompNode(CIdlSentence *idlsentence1, CIdlSentence *idlsentence2)
{
    ASSERT(0);
    return 0;
}
status_t CIdlSentenceList::Combine(CIdlSentenceList *stk)
{
    int i;    
    ASSERT(stk);
    for(i = 0; i < stk->GetLen(); i++)
    {
        CIdlSentence *p = stk->GetElem(i);
        ASSERT(p);
        this->Push(p);
    }
    return OK;
}

status_t CIdlSentenceList::ToLua(CFileBase *buf)
{
    ASSERT(buf);
    
    for(int i = 0; i < GetLen(); i++)
    {
        CIdlSentence *s = GetElem(i);
        ASSERT(s);
        buf->Log("{");
        buf->IncLogLevel(1);
        s->ToLua(buf);
        buf->IncLogLevel(-1);
        buf->Log("},");
    }

    return OK;
}
