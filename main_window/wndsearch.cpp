#include "wndsearch.h"
#include "winmisc.h"
#include "syslog.h"
#include "mem_tool.h"
#include "globals.h"

RECT CWndSearch::saved_rect = {0,0,0,0};

CWndSearch::CWndSearch()
{
	this->InitBasic();
}
CWndSearch::~CWndSearch()
{
	this->Destroy();
}
int CWndSearch::InitBasic()
{
	CWnd::InitBasic();
	this->st_1 = NULL;
	this->eb_text = NULL;
	this->pb_next = NULL;
	this->ckb_case_sensitive = NULL;
	this->gp_1 = NULL;
	this->rb_up = NULL;
	this->rb_down = NULL;
	this->pb_cancel = NULL;
	m_TmpText.InitBasic();
	return OK;
}
int CWndSearch::Init()
{
	this->InitBasic();
	CWnd::Init();
	//add your code
	m_TmpText.Init();
	return OK;
}
int CWndSearch::Destroy()
{
	if(hwnd)
    {
        GetWindowRect(hwnd,&saved_rect);    
    }

	DEL(this->st_1);
	DEL(this->eb_text);
	DEL(this->pb_next);
	DEL(this->ckb_case_sensitive);
	DEL(this->gp_1);
	DEL(this->rb_up);
	DEL(this->rb_down);
	DEL(this->pb_cancel);

	m_TmpText.Destroy();
	CWnd::Destroy();
	this->InitBasic();
	return OK;
}
int CWndSearch::OnCreate(WPARAM wparam, LPARAM lparam)
{
	
	NEW(this->st_1,CStatic);
	this->st_1->Init();
	this->st_1->SetParent(hwnd);
	this->st_1->SetText(L"查找内容:");
	this->st_1->Create();
	this->st_1->SetStockFont(DEFAULT_GUI_FONT);
	NEW(this->eb_text,CEditBox);
	this->eb_text->Init();
	this->eb_text->SetParent(hwnd);
	this->eb_text->AddStyle(ES_AUTOHSCROLL);
	this->eb_text->AddExStyle(WS_EX_CLIENTEDGE);
	this->eb_text->Create();
	this->eb_text->SetStockFont(DEFAULT_GUI_FONT);
	NEW(this->pb_next,CButton);
	this->pb_next->Init();
	this->pb_next->SetParent(hwnd);
	this->pb_next->SetText(L"查找下一个");
	this->pb_next->Create();
	this->pb_next->SetStockFont(DEFAULT_GUI_FONT);
	NEW(this->ckb_case_sensitive,CCheckBox);
	this->ckb_case_sensitive->Init();
	this->ckb_case_sensitive->SetParent(hwnd);
	this->ckb_case_sensitive->SetText(L"区分大小写");
	this->ckb_case_sensitive->Create();
	this->ckb_case_sensitive->SetStockFont(DEFAULT_GUI_FONT);
	NEW(this->gp_1,CGroupBox);
	this->gp_1->Init();
	this->gp_1->SetParent(hwnd);
	this->gp_1->SetText(L"方向");
	this->gp_1->Create();
	this->gp_1->SetStockFont(DEFAULT_GUI_FONT);
	NEW(this->rb_up,CRadioBox);
	this->rb_up->Init();
	this->rb_up->SetParent(hwnd);
	this->rb_up->SetText(L"向上");
	this->rb_up->AddStyle(WS_GROUP);
	this->rb_up->Create();
	this->rb_up->SetStockFont(DEFAULT_GUI_FONT);
	NEW(this->rb_down,CRadioBox);
	this->rb_down->Init();
	this->rb_down->SetParent(hwnd);
	this->rb_down->SetText(L"向下");	
	this->rb_down->Create();
	this->rb_down->SetStockFont(DEFAULT_GUI_FONT);
	NEW(this->pb_cancel,CButton);
	this->pb_cancel->Init();
	this->pb_cancel->SetParent(hwnd);
	this->pb_cancel->SetText(L"取消");
	this->pb_cancel->Create();
	this->pb_cancel->SetStockFont(DEFAULT_GUI_FONT);
	
	rb_down->SetCheck(TRUE);
	
	this->SetVirtualSize(537,165);
	this->OnSize(0,0);

    if(saved_rect.left == 0 && saved_rect.right == 0)
    {
        RECT r;
        HWND hp = GetParent();
        GetWindowRect(hp,&r);
        int ww = r.right-r.left;
        int hh = r.bottom-r.top;
		
        int w = 560, h = 200;
        this->MoveWindow(r.left + (ww-w)/2, r.top +(hh-h)/2,w,h);
    }
    else
    {
        this->MoveWindow(&saved_rect);
    }
	
	::SetFocus(eb_text->hwnd);

	return OK;
}
int CWndSearch::OnClose(WPARAM wparam, LPARAM lparam)
{
	this->Destroy();
	return OK;
}
int CWndSearch::OnSize(WPARAM wparam, LPARAM lparam)
{
	int x = 0,y = 0;
	this->st_1->MoveWindow(x+20,y+20,97,29);
	this->eb_text->MoveWindow(x+124,y+20,269,29);
	this->pb_next->MoveWindow(x+416,y+20,109,29);
	this->ckb_case_sensitive->MoveWindow(x+16,y+112,129,33);
	this->gp_1->MoveWindow(x+168,y+76,237,69);
	this->rb_up->MoveWindow(x+184,y+100,93,29);
	this->rb_down->MoveWindow(x+296,y+100,97,29);
	this->pb_cancel->MoveWindow(x+416,y+68,109,29);
	return OK;
}
int CWndSearch::OnCommand(WPARAM wparam, LPARAM lparam)
{
	if(pb_cancel->IsMyCommand(wparam))
	{
		this->Close();
	}
	else if(pb_next->IsMyCommand(wparam))
	{
		this->Find();
	}
	return OK;
}
int CWndSearch::PreTransMsg(MSG *msg)
{
	ASSERT(hwnd);
	
	if(msg->message == WM_KEYDOWN)
	{
		if(msg->wParam == VK_RETURN)
		{
			return this->Find();
		}
	}
	

	HWND hlist[100];
	int i = 0;
	
	hlist[i++] = eb_text->hwnd;
	hlist[i++] = pb_next->hwnd;
	hlist[i++] = ckb_case_sensitive->hwnd;
	hlist[i++] = rb_up->hwnd;
	hlist[i++] = rb_down->hwnd;
	hlist[i++] = pb_cancel->hwnd;
	
	return CWinMisc::TabFocus(hwnd,hlist,i,msg);
}

status_t CWndSearch::Find()
{
	LOCAL_MEM(find_text);
	eb_text->GetText_File(&find_text);

	if(find_text.GetSize() == 0)
		return ERROR;

	GLOBAL_PAGE_TEXT(page_text);
	CEditBox *pedit = page_text->eb_log;

	if(m_TmpText.GetSize() == 0)
	{		
		pedit->GetText_File(&m_TmpText);
		pedit->SetSel(0,0);
	}

	int s_pos = 0,e_pos = 0;
	pedit->GetSel(&s_pos,&e_pos);
	m_TmpText.Seek(e_pos*sizeof(wchar_t));
	
	int pos = (int)m_TmpText.SearchStrW(
		find_text.CStrW(),
		ckb_case_sensitive->GetCheck(),
		FALSE
	);

	if(pos < 0) 
	{
		m_TmpText.Seek(0);		
		pos = (int)m_TmpText.SearchStrW(
			find_text.CStrW(),
			ckb_case_sensitive->GetCheck(),
			FALSE
		);
	}

	if(pos < 0)
		return ERROR;
		
	pedit->SetSel(pos,pos+find_text.StrLenW());
	::SendMessage(pedit->hwnd,EM_SCROLLCARET ,0,0);
	return OK;
}
