#include "wndpagehost.h"
#include "winmisc.h"
#include "syslog.h"
#include "mem_tool.h"

CWndPageHost::CWndPageHost()
{
	this->InitBasic();
}
CWndPageHost::~CWndPageHost()
{
	this->Destroy();
}
int CWndPageHost::InitBasic()
{
	CWnd::InitBasic();
	this->m_HScrollBar = NULL;
	this->m_VScrollBar = NULL;	
	this->i_Page = NULL;
	m_ViewW = 0;
	m_ViewH = 0;
	return OK;
}
int CWndPageHost::Init()
{
	this->InitBasic();
	CWnd::Init();
	//add your code
	return OK;
}
int CWndPageHost::Destroy()
{
	DEL(this->m_HScrollBar);
	DEL(this->m_VScrollBar);
	CWnd::Destroy();
	this->InitBasic();
	return OK;
}
int CWndPageHost::OnCreate(WPARAM wparam, LPARAM lparam)
{
	NEW(this->m_HScrollBar,CScrollBar);
	this->m_HScrollBar->Init();
	this->m_HScrollBar->SetParent(hwnd);
	this->m_HScrollBar->SetDir(0);
	this->m_HScrollBar->SetRange(0,100);
	this->m_HScrollBar->Create();
	this->m_HScrollBar->SetLineStep(1);
	this->m_HScrollBar->SetPageSize(10);

	NEW(this->m_VScrollBar,CScrollBar);
	this->m_VScrollBar->Init();
	this->m_VScrollBar->SetParent(hwnd);
	this->m_VScrollBar->SetDir(1);
	this->m_VScrollBar->SetRange(0,100);
	this->m_VScrollBar->Create();
	this->m_VScrollBar->SetLineStep(1);
	this->m_VScrollBar->SetPageSize(10);

	this->m_HScrollBar->Hide();
	this->m_VScrollBar->Hide();
	this->OnSize(0,0);
	return OK;
}
int CWndPageHost::OnClose(WPARAM wparam, LPARAM lparam)
{
	return OK;
}
int CWndPageHost::OnSize(WPARAM wparam, LPARAM lparam)
{
	RECT r,rt;
	int sb_width = 18;

	::GetClientRect(hwnd,&r);

	if(i_Page == NULL)
		return OK;

	int view_w = r.right-r.left;
	int view_h = r.bottom -r.top;

	if(view_w <= 0)return OK;
	if(view_h <= 0)return OK;

	if(i_Page->GetVirtualWidth() > view_w)
	{
		rt = r;
		if(i_Page->GetVirtualHeight() > view_h)
			rt.right = r.right - sb_width;
		view_h -= sb_width;			
		rt.top = r.bottom - sb_width;
		this->m_HScrollBar->Show();
		this->m_HScrollBar->SetRange(0,i_Page->GetVirtualWidth());
		this->m_HScrollBar->SetPageSize(view_w);
		this->m_HScrollBar->SetPos(0);
		this->m_HScrollBar->MoveWindow(&rt);
	}
	else
	{
		this->m_HScrollBar->Hide();
	}

	if(i_Page->GetVirtualHeight() > r.bottom-r.top)
	{
		rt = r;
		if(i_Page->GetVirtualWidth() > view_w)
			rt.bottom = r.bottom - sb_width;
		view_w -= sb_width;
		rt.left = r.right - sb_width;
		this->m_VScrollBar->Show();
		this->m_VScrollBar->SetRange(0,i_Page->GetVirtualHeight());
		this->m_VScrollBar->SetPageSize(view_h);
		this->m_VScrollBar->SetPos(0);
		this->m_VScrollBar->MoveWindow(&rt);
	}
	else
	{
		this->m_VScrollBar->Hide();
	}
	m_ViewW = view_w;
	m_ViewH = view_h;
	this->i_Page->MoveWindow(0,0,view_w,view_h);
	return OK;
}
int CWndPageHost::OnHScroll(WPARAM wparam, LPARAM lparam)
{
	if(i_Page == NULL)return ERROR;

	if(this->m_HScrollBar->OnScroll(wparam,lparam))
	{
		//ScrollWindowEx(i_Page->hwnd,-m_HScrollBar->inc,0,NULL,NULL,NULL,NULL,SW_SCROLLCHILDREN);		
		int x = m_HScrollBar->GetPos();
		int y = m_VScrollBar->GetPos();
		i_Page->MoveWindow(-x,-y,x+m_ViewW,y+m_ViewH);
		i_Page->SetCurHorzPos(this->m_HScrollBar->GetPos());
		::InvalidateRect(i_Page->hwnd,NULL,1);
	}
	return OK;
}
int CWndPageHost::OnVScroll(WPARAM wparam, LPARAM lparam)
{
	if(i_Page == NULL)return ERROR;
	if(this->m_VScrollBar->OnScroll(wparam,lparam))
	{
		//ScrollWindowEx(i_Page->hwnd,0,-m_VScrollBar->inc,NULL,NULL,NULL,NULL,SW_SCROLLCHILDREN);
		int x = m_HScrollBar->GetPos();
		int y = m_VScrollBar->GetPos();
		i_Page->MoveWindow(-x,-y,x+m_ViewW,y+m_ViewH);
		i_Page->SetCurHorzPos(this->m_VScrollBar->GetPos());
		::InvalidateRect(i_Page->hwnd,NULL,1);
	}
	return OK;
}

int CWndPageHost::OnCommand(WPARAM wparam, LPARAM lparam)
{
	return OK;
}
int CWndPageHost::PreTransMsg(MSG *msg)
{
	ASSERT(hwnd);
	HWND hlist[100];
	int i = 0;

	return CWinMisc::TabFocus(hwnd,hlist,i,msg);
}

status_t CWndPageHost::SetCurPage(CPage *page)
{
	ASSERT(page);
	if(this->i_Page == page)
		return ERROR;

	if(this->i_Page)
	{
		this->i_Page->Hide();
		this->i_Page->OnExit();
	}
	this->i_Page = page;
	this->i_Page->Show();
	this->i_Page->OnEnter();
	this->OnSize(0,0);
	return OK;
}
