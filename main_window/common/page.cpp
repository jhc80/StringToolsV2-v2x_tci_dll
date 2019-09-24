#include "page.h"
#include "syslog.h"
#include "mem_tool.h"
#include "syslog.h"

CPage::CPage()
{
	this->InitBasic();
}
CPage::~CPage()
{
	this->Destroy();
}
status_t CPage::InitBasic()
{
	WEAK_REF_ID_CLEAR();
	CWnd::InitBasic();
	this->m_Name.InitBasic();
	this->m_VirtualWidth = 0;
	this->m_VirtualHeight = 0;
	this->m_CurHorzPos = 0;
	this->m_CurVertPos = 0;
	return OK;
}
status_t CPage::Init()
{
	this->InitBasic();
	WEAK_REF_ID_INIT();
	CWnd::Init();	
	this->m_Name.Init();
	return OK;
}
status_t CPage::Destroy()
{
	this->m_Name.Destroy();
	CWnd::Destroy();
	this->InitBasic();
	return OK;
}
CMem* CPage::GetName()
{
	return &this->m_Name;
}
int CPage::GetVirtualWidth()
{
	return this->m_VirtualWidth;
}
int CPage::GetVirtualHeight()
{
	return this->m_VirtualHeight;
}
const wchar_t* CPage::GetNameStr()
{
	return this->m_Name.CStrW();
}
status_t CPage::SetName(CMem* _name)
{
	this->m_Name.Copy(_name);
	return OK;
}
status_t CPage::SetName(const wchar_t *_name)
{
	CMem _mem(_name);
	return this->SetName(&_mem);
}
int CPage::GetCurHorzPos()
{
	return this->m_CurHorzPos;
}
int CPage::GetCurVertPos()
{
	return this->m_CurVertPos;
}
status_t CPage::SetCurHorzPos(int _curhorzpos)
{
	this->m_CurHorzPos = _curhorzpos;
	return OK;
}
status_t CPage::SetCurVertPos(int _curvertpos)
{
	this->m_CurVertPos = _curvertpos;
	return OK;
}

status_t CPage::SetPageSize(int w, int h)
{
	this->m_VirtualWidth = w;
	this->m_VirtualHeight = h;
	return OK;
}
status_t CPage::AddTabWnd(HWND *hlist, int *i)
{
	ASSERT(0);
	return OK;
}
status_t CPage::OnEnter()
{
	return OK;
}
status_t CPage::OnExit()
{
	return OK;
}