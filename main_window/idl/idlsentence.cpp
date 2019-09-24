#include "idlsentence.h"
#include "mem_tool.h"
#include "syslog.h"

CIdlSentence::CIdlSentence()
{
	this->InitBasic();  
}
CIdlSentence::~CIdlSentence()
{
	this->Destroy();
}
status_t CIdlSentence::InitBasic()
{
	this->m_Index = NULL;
	this->m_Top = 0;
	this->m_Size = 0;	
	return OK;
}
status_t CIdlSentence::Init(int init_size)
{
	int i;
	this->InitBasic();  
	this->m_Size = init_size;
	MALLOC(this->m_Index,CIdlWord* ,this->m_Size);
	for(i = 0; i < this->m_Size; i++)
		this->m_Index[i] = NULL;
	return OK;
}
status_t CIdlSentence::Init()
{
    return this->Init(64);
}
status_t CIdlSentence::Destroy()
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
bool CIdlSentence::IsEmpty()
{
	return this->m_Top <= 0;
}
bool CIdlSentence::IsFull()
{
	return this->m_Top >= this->m_Size;
}

status_t CIdlSentence::AutoResize()
{
	int i;

	if(this->IsFull())
	{
		REALLOC(this->m_Index,CIdlWord*,this->m_Size,this->m_Size*2);
		this->m_Size *= 2;
		for(i = this->m_Top; i < this->m_Size; i++)
		{
			this->m_Index[i] = NULL;
		}
	}
	return OK;
}

status_t CIdlSentence::Push(CIdlWord *idlword)
{
	CIdlWord *tmp;
	ASSERT(idlword);
	tmp = this->CloneNode(idlword);
	if(!this->PushPtr(tmp))
	{
		this->DelNode(tmp);
		return ERROR;
	}
	
	return OK;
}

status_t CIdlSentence::PushPtr(CIdlWord *idlword)
{
	ASSERT(idlword);	
	this->AutoResize();
	ASSERT(!this->IsFull());
	this->m_Index[this->m_Top] = idlword;
	this->m_Top++;
	return OK;
}

CIdlWord * CIdlSentence::PopPtr()
{
	if(this->IsEmpty())
		return NULL;
	this->m_Top--;
	return this->m_Index[this->m_Top];
}

status_t CIdlSentence::Pop(CIdlWord *idlword)
{
	ASSERT(!this->IsEmpty());	
	this->m_Top--;
	this->CopyNode(idlword,this->m_Index[this->m_Top]);
	this->DelNode(this->m_Index[this->m_Top]);
	return OK;
}
int CIdlSentence::GetLen()
{
	return this->m_Top;
}

int CIdlSentence::SearchPos(CIdlWord *idlword)
{
	int i;
	for(i=0;i<this->m_Top;i++)
	{
		if(this->CompNode(this->m_Index[i],idlword) == 0)
			return i;
	}
	return -1;
}

CIdlWord* CIdlSentence::Search(CIdlWord *idlword)
{
	int pos = this->SearchPos(idlword);
	if(pos >= 0 && pos < this->m_Top)
		return this->m_Index[pos];;
	return NULL;
}
CIdlWord* CIdlSentence::GetTopPtr()
{
	if(this->IsEmpty())
		return NULL;
	return this->m_Index[this->m_Top - 1];
}
status_t CIdlSentence::DelTop()
{
	if(this->IsEmpty())
		return ERROR;
	this->m_Top--;
	this->DelNode(this->m_Index[this->m_Top]);
	return OK;
}
status_t CIdlSentence::Clear()
{
	while(this->DelTop());
	return OK;
}

CIdlWord* CIdlSentence::GetElem(int index)
{
	if(index < 0 || index >= this->m_Top)
		return NULL;
	return this->m_Index[index];
}

CIdlWord* CIdlSentence::BSearchNode(CIdlWord *idlword,int order)
{
	return this->GetElem(this->BSearch(idlword,order));
}
int CIdlSentence::BSearch(CIdlWord *idlword,int order)
{
	int find,pos;
	pos = this->BSearchPos(idlword,order,&find);
	if(find) return pos;
	return -1;
}

status_t CIdlSentence::InsElemPtr(int i, CIdlWord *idlword)
{
	int k;

	ASSERT(idlword);
	ASSERT(i >= 0 && i <= this->m_Top);

	this->AutoResize();
	ASSERT(!this->IsFull());
	for(k = this->m_Top; k > i; k--)
	{
		this->m_Index[k] = this->m_Index[k - 1];
	}
	this->m_Index[i] = idlword;
	this->m_Top++;
	return OK;
}

status_t CIdlSentence::InsElem(int i, CIdlWord *idlword)
{
	CIdlWord *tmp;
	ASSERT(idlword);
	tmp = this->CloneNode(idlword);
	if(!this->InsElemPtr(i,tmp))
	{
		this->DelNode(tmp);
		return ERROR;
	}
	return OK;
}

CIdlWord* CIdlSentence::RemoveElem(int index)
{
	CIdlWord *p;
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

status_t CIdlSentence::DelElem(int i)
{
	CIdlWord *p = this->RemoveElem(i);
	if(p != NULL)
	{
		this->DelNode(p);
		return OK;
	}
	return ERROR;
}

status_t CIdlSentence::InsOrderedPtr(CIdlWord *idlword, int order,int unique)
{
	int pos,find;
	pos = this->BSearchPos(idlword,order,&find);
	if(find && unique)
		return ERROR;
	return this->InsElemPtr(pos,idlword);
}

status_t CIdlSentence::InsOrdered(CIdlWord *idlword, int order,int unique)
{
	int pos,find;
	ASSERT(idlword);
	pos = this->BSearchPos(idlword,order,&find);
	if(find && unique)
		return ERROR;
	return this->InsElem(pos,idlword);
}

int CIdlSentence::BSearchPos(CIdlWord *idlword, int order, int *find_flag)
{
	int low,high,mid,comp;
	
	low = 0; 
	high = this->GetLen() - 1;

	while(low<=high)
	{
		mid = (low+high) >> 1;

		comp = this->CompNode(this->m_Index[mid],idlword);
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

status_t CIdlSentence::Sort(int order)
{
	int i,len;
	CIdlSentence tmp;

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
status_t CIdlSentence::Copy(CIdlSentence *stk)
{
	int i;

	ASSERT(stk);
	this->Destroy();
	this->Init(stk->GetLen());
	for(i = 0; i < stk->GetLen(); i++)
	{
		CIdlWord *p = stk->GetElem(i);
		ASSERT(p);
		this->Push(p);
	}
	return OK;
}
status_t CIdlSentence::Print(CFileBase *_buf)
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
status_t CIdlSentence::CopyNode(CIdlWord *dst, CIdlWord *src)
{
	return dst->Copy(src);
}

CIdlWord* CIdlSentence::CloneNode(CIdlWord *idlword)
{
	CIdlWord *tmp;
	NEW(tmp,CIdlWord);
	tmp->Init();
	this->CopyNode(tmp,idlword);
	return tmp;
}

status_t CIdlSentence::DelNode(CIdlWord *idlword)
{
	DEL(idlword);
	return OK;
}

int CIdlSentence::CompNode(CIdlWord *idlword1, CIdlWord *idlword2)
{
	ASSERT(idlword1 && idlword2);
	return idlword1->Comp(idlword2);
}

const char * CIdlSentence::CStr()
{
    ASSERT(GetLen() == 1);
    return GetElem(0)->CStr();
}

status_t CIdlSentence::ToLua(CFileBase *buf)
{
    ASSERT(buf);
    for(int i = 0; i < this->m_Top; i++)
    {
        CIdlWord *word = GetElem(i);
        ASSERT(word);
        buf->Log("\"%s\",",word->CStr());
	}
    return OK;
}
