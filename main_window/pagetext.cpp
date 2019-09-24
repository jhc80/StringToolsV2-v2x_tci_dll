#include "pagetext.h"
#include "winmisc.h"
#include "syslog.h"
#include "mem_tool.h"

CPageText::CPageText()
{
	this->InitBasic();
}
CPageText::~CPageText()
{
	this->Destroy();
}
int CPageText::InitBasic()
{
	CPage::InitBasic();
	this->eb_log = NULL;
	return OK;
}
int CPageText::Init()
{
	this->InitBasic();
	CPage::Init();
	return OK;
}
int CPageText::Destroy()
{
	CPage::Destroy(); //destroy first
	DEL(this->eb_log);	
	this->InitBasic();
	return OK;
}
int CPageText::OnCreate(WPARAM wparam, LPARAM lparam)
{
	NEW(this->eb_log,CEditBox);
	this->eb_log->Init();
	this->eb_log->SetParent(hwnd);
	this->eb_log->AddStyle(ES_MULTILINE|ES_NOHIDESEL);
	this->eb_log->AddStyle(WS_VSCROLL|WS_HSCROLL);
	this->eb_log->AddStyle(ES_AUTOVSCROLL|ES_AUTOHSCROLL);
	//this->eb_log->AddExStyle(WS_EX_CLIENTEDGE);
	this->eb_log->Create();
	this->eb_log->SetStockFont(SYSTEM_FIXED_FONT);
	this->eb_log->SetMaxText(32*1024*1024);
	this->SetVirtualSize(553,373);
	this->OnSize(0,0);
    this->eb_log->SetTabStops(4*4);
	return OK;
}
int CPageText::OnClose(WPARAM wparam, LPARAM lparam)
{
	this->Destroy();
	return OK;
}
int CPageText::OnSize(WPARAM wparam, LPARAM lparam)
{
	this->SetRealClientRect(NULL);
	RECT r;
	::GetClientRect(hwnd,&r);
	int x = 0,y =0;
	int left = 0;
	this->eb_log->MoveWindow(left,0,r.right-left,r.bottom);
	return OK;
}
int CPageText::OnCommand(WPARAM wparam, LPARAM lparam)
{
	return OK;
}
int CPageText::AddTabWnd(HWND *hlist, int *i)
{
	ASSERT(hlist);
	//hlist[(*i)++] = eb_log->hwnd;
	return OK;
}
status_t CPageText::OnEnter()
{
	return OK;
}
status_t CPageText::OnExit()
{
	return OK;
}
