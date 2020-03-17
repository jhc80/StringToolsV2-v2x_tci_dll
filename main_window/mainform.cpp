#include "MainForm.h"
#include "resource.h"
#include "syslog.h"
#include "winmisc.h"
#include "encoder.h"
#include "pagetext.h"
#include "pageimage.h"
#include "globals.h"

#define PAGE_NAME_TEXT L"text"
#define PAGE_NAME_IMAGE L"image"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMainForm::CMainForm()
{
    this->InitBasic();
}
CMainForm::~CMainForm()
{
    this->Destroy();
}
int CMainForm::InitBasic()
{
	CWnd::InitBasic();
	this->m_WndSplit_H = NULL;
	this->m_WndSplit_V = NULL;
	this->m_StatusBar = NULL;
	this->m_TreeView = NULL;
	this->m_WndPageHost = NULL;
	this->m_PageManager = NULL;
	this->m_WndRight = NULL;
	this->m_WndEmbeddedUI = NULL;
	this->m_EmbeddedUIWindowHeight = 0;
    ////////////////////
    this->menu_file = NULL;
    this->mitem_open = NULL;
    this->mitem_save_as = NULL;
    this->mitem_property = NULL;
    this->mitem_exit = NULL;
    this->menu_bar = NULL;
    this->menu_edit = NULL;
    this->mitem_cut = NULL;
    this->mitem_copy = NULL;
    this->mitem_paste = NULL;
    this->mitem_delete = NULL;
    this->mitem_clear = NULL;
    this->mitem_select_all = NULL;
    this->menu_help = NULL;
    this->mitem_help = NULL;
    this->mitem_about = NULL;
    this->menu_vm = NULL;
    this->mitem_start = NULL;
    this->mitem_stop = NULL;
    this->mitem_text_window = NULL;
    this->mitem_image_window = NULL;
	this->mitem_find = NULL;
    this->menu_context = NULL;
    this->mitem_r_run = NULL;
    this->mitem_r_attrib = NULL;
    this->mitem_r_open_folder = NULL;
    this->mitem_r_help = NULL;
    return OK;
}
int CMainForm::Init()
{
    this->InitBasic();
	CWnd::Init();
    return OK;
}

int CMainForm::OnClose(WPARAM wparam,LPARAM lparam)
{
    GLOBAL_LUA_THREAD(lua_thread);
    if(lua_thread->IsRunning())
    {
        MessageBoxW(hwnd,L"current Lua vm is running!!",L"can not close",MB_OK|MB_ICONSTOP);
        return ERROR;
    }
	this->Destroy();
	return OK;
}
int CMainForm::OnPaint(WPARAM wparam,LPARAM lparam)
{
	PAINTSTRUCT ps;
	HDC hdc = ::BeginPaint(hwnd,&ps);
	::EndPaint(hwnd,&ps);
	return OK;
}
int CMainForm::OnCreate(WPARAM wparam,LPARAM lparam)
{
    this->CreateMenu();

	NEW(this->m_WndSplit_H,CWndSplit);
	this->m_WndSplit_H->Init(true);
	this->m_WndSplit_H->Registe();
	this->m_WndSplit_H->SetParent(hwnd);
	this->m_WndSplit_H->Create();
	this->m_WndSplit_H->SetBarPos(this->GetWidth()/4);

	BEGIN_CLOSURE_FUNC(on_split_wnd_h_event)
	{
		CLOSURE_PARAM_PTR(CMainForm*,self,10);
		self->OnWndSplitHEvent();
		return OK;
	}
	END_CLOSURE_FUNC(on_split_wnd_h_event);

	m_WndSplit_H->Callback()->SetFunc(on_split_wnd_h_event);
	m_WndSplit_H->Callback()->SetParamPointer(10,this);

	NEW(this->m_StatusBar,CStatusBar);
	this->m_StatusBar->Init();
	this->m_StatusBar->SetParent(hwnd);
	this->m_StatusBar->Create();
	this->m_StatusBar->SetParts(3);

	NEW(this->m_TreeView,CTreeView);
	this->m_TreeView->Init();
	this->m_TreeView->SetParent(hwnd);
	this->m_TreeView->Create();
    
    this->m_TreeView->CreateImageList(
        IDB_BITMAP_TOOLBAR_PROPERTY,
        16,16,16,RGB(192,192,192)
    );

	NEW(this->m_PageManager,CPageManager);
	this->m_PageManager->Init(1024);

	NEW(m_WndRight,CWnd);
	m_WndRight->Init();
	m_WndRight->SetParent(hwnd);
	m_WndRight->SetStyle(WS_VISIBLE|WS_CHILD);
	m_WndRight->Create();

	NEW(m_WndPageHost,CWndPageHost);
	m_WndPageHost->Init();	
	m_WndPageHost->SetText(L"PageHost");
	m_WndPageHost->SetParent(m_WndRight->hwnd);
	m_WndPageHost->SetStyle(WS_VISIBLE|WS_CHILD);
	m_WndPageHost->Create();

	this->m_WndSplit_H->pane0 = this->m_TreeView->hwnd;
	this->m_WndSplit_H->pane1 = this->m_WndRight->hwnd;

    GLOBAL_INDEX_TREE(tree);
    tree->LoadFromFolder(g_globals.GetWorkFolder());
    tree->SortTree();
    tree->SyncToTreeView(m_TreeView);
    
	this->m_TreeView->Expand(m_TreeView->GetRoot(),TVE_EXPAND,FALSE);
    
	this->SetVirtualSize(280,280);
	this->OnSize(0,0);

    this->SwitchPage(PAGE_NAME_IMAGE);
    this->SwitchPage(PAGE_NAME_TEXT);

	return OK;
}
int CMainForm::CreateMenu()
{
    NEW(this->menu_file,CMenu);
    this->menu_file->Init();
    this->menu_file->SetName(L"F&ile");
    this->menu_file->Create();
    NEW(this->mitem_open,CMenu);
    this->mitem_open->Init();
    this->mitem_open->SetName(L"&Open");
    this->mitem_open->Create();
    NEW(this->mitem_save_as,CMenu);
    this->mitem_save_as->Init();
    this->mitem_save_as->SetName(L"Save &As");
    this->mitem_save_as->Create();
    NEW(this->mitem_property,CMenu);
    this->mitem_property->Init();
    this->mitem_property->SetName(L"&Property");
    this->mitem_property->Create();
    NEW(this->mitem_exit,CMenu);
    this->mitem_exit->Init();
    this->mitem_exit->SetName(L"E&xit");
    this->mitem_exit->Create();
    NEW(this->menu_bar,CMenu);
    this->menu_bar->Init();
    this->menu_bar->Create();
    NEW(this->menu_edit,CMenu);
    this->menu_edit->Init();
    this->menu_edit->SetName(L"E&dit");
    this->menu_edit->Create();
    NEW(this->mitem_cut,CMenu);
    this->mitem_cut->Init();
    this->mitem_cut->SetName(L"Cu&t");
    this->mitem_cut->Create();
    NEW(this->mitem_copy,CMenu);
    this->mitem_copy->Init();
    this->mitem_copy->SetName(L"&Copy");
    this->mitem_copy->Create();
    NEW(this->mitem_paste,CMenu);
    this->mitem_paste->Init();
    this->mitem_paste->SetName(L"&Paste");
    this->mitem_paste->Create();
    NEW(this->mitem_delete,CMenu);
    this->mitem_delete->Init();
    this->mitem_delete->SetName(L"&Delete");
    this->mitem_delete->Create();
    NEW(this->mitem_clear,CMenu);
    this->mitem_clear->Init();
    this->mitem_clear->SetName(L"Clea&r All");
    this->mitem_clear->Create();
    NEW(this->mitem_select_all,CMenu);
    this->mitem_select_all->Init();
    this->mitem_select_all->SetName(L"Select A&ll");
    this->mitem_select_all->Create();

    NEW(this->menu_help,CMenu);
    this->menu_help->Init();
    this->menu_help->SetName(L"Help");
    this->menu_help->Create();
    NEW(this->mitem_help,CMenu);
    this->mitem_help->Init();
    this->mitem_help->SetName(L"&Help");
    this->mitem_help->Create();
    NEW(this->mitem_about,CMenu);
    this->mitem_about->Init();
    this->mitem_about->SetName(L"&About");
    this->mitem_about->Create();
    NEW(this->menu_vm,CMenu);
    this->menu_vm->Init();
    this->menu_vm->SetName(L"V&M");
    this->menu_vm->Create();
    NEW(this->mitem_start,CMenu);
    this->mitem_start->Init();
    this->mitem_start->SetName(L"&Start\tCtrl+Enter");
    this->mitem_start->Create();
    NEW(this->mitem_stop,CMenu);
    this->mitem_stop->Init();
    this->mitem_stop->SetName(L"S&top\t Escape");
    this->mitem_stop->Create();

    NEW(this->menu_view,CMenu);
    this->menu_view->Init();
    this->menu_view->SetName(L"&View");
    this->menu_view->Create();
    NEW(this->mitem_text_window,CMenu);
    this->mitem_text_window->Init();
    this->mitem_text_window->SetName(L"Text Window");
    this->mitem_text_window->Create();
    NEW(this->mitem_image_window,CMenu);
    this->mitem_image_window->Init();
    this->mitem_image_window->SetName(L"Image Window");
    this->mitem_image_window->Create();

	NEW(this->mitem_find,CMenu);
	this->mitem_find->Init();
	this->mitem_find->SetName(L"Find\tCtrl+F");
	this->mitem_find->Create();

    this->menu_bar->AddMenu(menu_file);
    this->menu_bar->AddMenu(menu_vm);
    this->menu_file->AddItem(mitem_open);
    this->menu_file->AddItem(mitem_save_as);
    this->menu_file->AddItem(mitem_property);
    this->menu_file->AddItem(mitem_exit);
    this->menu_bar->AddMenu(menu_edit);
    this->menu_edit->AddItem(mitem_cut);
    this->menu_edit->AddItem(mitem_copy);
    this->menu_edit->AddItem(mitem_paste);
    this->menu_edit->AddItem(mitem_delete);   
	this->menu_edit->AddSeparator();
	this->menu_edit->AddItem(mitem_find);
    this->menu_edit->AddSeparator();
    this->menu_edit->AddItem(mitem_clear);
    this->menu_edit->AddItem(mitem_select_all);
    this->menu_bar->AddMenu(menu_view);
    this->menu_view->AddItem(mitem_text_window);
    this->menu_view->AddItem(mitem_image_window);
    this->menu_bar->AddMenu(menu_help);
    this->menu_help->AddItem(mitem_help);
    this->menu_help->AddItem(mitem_about);    
    this->menu_vm->AddItem(mitem_start);
    this->menu_vm->AddItem(mitem_stop);

    this->menu_bar->SetToWnd(hwnd);

    NEW(this->menu_context,CPopupMenu);
    this->menu_context->Init();
    this->menu_context->SetParent(hwnd);
    this->menu_context->SetName(L"RightClick");
    this->menu_context->Create();
    NEW(this->mitem_r_run,CMenu);
    this->mitem_r_run->Init();
    this->mitem_r_run->SetName(L"运行");
    this->mitem_r_run->Create();
    NEW(this->mitem_r_attrib,CMenu);
    this->mitem_r_attrib->Init();
    this->mitem_r_attrib->SetName(L"属性");
    this->mitem_r_attrib->Create();
    NEW(this->mitem_r_open_folder,CMenu);
    this->mitem_r_open_folder->Init();
    this->mitem_r_open_folder->SetName(L"打开文件夹");
    this->mitem_r_open_folder->Create();
    NEW(this->mitem_r_help,CMenu);
    this->mitem_r_help->Init();
    this->mitem_r_help->SetName(L"显示帮助");
    this->mitem_r_help->Create();
    this->menu_context->AddItem(mitem_r_run);
    this->menu_context->AddItem(mitem_r_attrib);
    this->menu_context->AddItem(mitem_r_open_folder);
    this->menu_context->AddItem(mitem_r_help);
    return OK;
}
int CMainForm::Destroy()
{
	DEL(this->m_PageManager);
	DEL(this->m_WndPageHost);
	DEL(this->m_TreeView);
	DEL(this->m_StatusBar);
	DEL(this->m_WndSplit_H);
	DEL(this->m_WndRight);
	DEL(this->m_WndEmbeddedUI);
    //////////////////////
    DEL(this->menu_file);
    DEL(this->mitem_open);
    DEL(this->mitem_save_as);
    DEL(this->mitem_property);
    DEL(this->mitem_exit);
    DEL(this->menu_bar);
    DEL(this->menu_edit);
    DEL(this->mitem_cut);
    DEL(this->mitem_copy);
    DEL(this->mitem_paste);
    DEL(this->mitem_delete);
    DEL(this->mitem_clear);
    DEL(this->mitem_select_all);
    DEL(this->menu_help);
    DEL(this->mitem_help);
    DEL(this->mitem_about);
    DEL(this->menu_vm);
    DEL(this->mitem_start);
    DEL(this->mitem_stop);
	DEL(mitem_find);
    //////////////////////
    DEL(this->menu_context);
    DEL(this->mitem_r_run);
    DEL(this->mitem_r_attrib);
    DEL(this->mitem_r_help);
    DEL(this->mitem_r_open_folder);
    //////////////////////
    DEL(mitem_text_window);
    DEL(mitem_image_window);
    DEL(menu_view);
    //////////////////////
	CWnd::Destroy();
    this->InitBasic();
	PostQuitMessage(0);
    return OK;
}
int CMainForm::OnSize(WPARAM wparam,LPARAM lparam)
{
	RECT r;
	GetClientRect(hwnd,&r);

	this->m_StatusBar->OnSize();
	this->m_StatusBar->SetAveragePos();
	this->m_StatusBar->RefreshUI();

	r.bottom -= this->m_StatusBar->GetHeight();
	m_WndSplit_H->RecalcLayout(r);

	if(m_WndSplit_V)
	{
		::GetClientRect(m_WndRight->hwnd,&r);
		m_WndSplit_V->SetBarPos(r.bottom - m_EmbeddedUIWindowHeight);
		m_WndSplit_V->RecalcLayout(r);
	}
	else
	{
		::GetClientRect(m_WndRight->hwnd,&r);
		m_WndPageHost->MoveWindow(&r);
	}
	return OK;
}
int CMainForm::OnCommand(WPARAM wparam,LPARAM lparam)
{
	if(mitem_exit->IsMyCommand(wparam))
	{
		this->Close();
	}
	else if(mitem_about->IsMyCommand(wparam))
	{
		MessageBoxW(hwnd,L"Moon String Tools by\nChen XiangPeng",L"About",MB_OK);		
	}
    else if(mitem_start->IsMyCommand(wparam))
    {		
        g_globals.StartLuaThread();
    }

    else if(mitem_stop->IsMyCommand(wparam))
    {
        g_globals.StopLuaThread();
    }

	else if(mitem_property->IsMyCommand(wparam))
	{
		this->ShowPropertyWindow();
	}

	else if(mitem_save_as->IsMyCommand(wparam))
	{
		this->OnSaveAs();
	}

	else if(mitem_open->IsMyCommand(wparam))
	{
		this->OnLoad();
	}

    else if(mitem_select_all->IsMyCommand(wparam))
    {
        CEditBox *eb = g_globals.GetTheEditBox();
        ASSERT(eb);
        eb->SetSel(0,-1);
    }

    else if(mitem_clear->IsMyCommand(wparam))
    {
        g_globals.ClearScreen();
    }

    else if(mitem_copy->IsMyCommand(wparam))
    {
        CEditBox *eb = g_globals.GetTheEditBox();
        ASSERT(eb);
        SendMessage(eb->hwnd,WM_COPY,0,0);
    }

    else if(mitem_paste->IsMyCommand(wparam))
    {
        CEditBox *eb = g_globals.GetTheEditBox();
        ASSERT(eb);
        SendMessage(eb->hwnd,WM_PASTE,0,0);
    }

    else if(mitem_delete->IsMyCommand(wparam))
    {
        CEditBox *eb = g_globals.GetTheEditBox();
        ASSERT(eb);
        eb->ReplaceSel(L"");
    }

    else if(mitem_cut->IsMyCommand(wparam))
    {
        CEditBox *eb = g_globals.GetTheEditBox();
        ASSERT(eb);
        SendMessage(eb->hwnd,WM_CUT,0,0);
    }

    else if(mitem_image_window->IsMyCommand(wparam))
    {
        this->SwitchPage(PAGE_NAME_IMAGE);
    }

    else if(mitem_text_window->IsMyCommand(wparam))
    {
        this->SwitchPage(PAGE_NAME_TEXT);
    }
	else if(mitem_find->IsMyCommand(wparam))
	{
		g_globals.ShowSearchWindow();
	}
    else if(mitem_help->IsMyCommand(wparam))
    {
        g_globals.ShowHelp();
    }

    else if(mitem_r_help->IsMyCommand(wparam))
    {
        g_globals.ShowHelp();
    }

    else if(mitem_r_open_folder->IsMyCommand(wparam))
    {
        g_globals.OpenTheFolder();
    }

    else if(mitem_r_run->IsMyCommand(wparam))
    {
        g_globals.StartLuaThread();
    }

    else if(mitem_r_attrib->IsMyCommand(wparam))
    {
        this->ShowPropertyWindow();
    }
	return OK;
}

int CMainForm::OnNotify(WPARAM wparam,LPARAM lparam)
{	
	if(this->m_TreeView->IsMyNotify(lparam))
	{
		if(this->m_TreeView->GetNotifyCode(lparam) == (int)TVN_SELCHANGEDW)
		{
			HTREEITEM item = this->m_TreeView->GetSelectItem();
                      
			if(!this->m_TreeView->IsLeaf(item))
            {
                g_globals.SetCurIndexTreeNode(NULL);
                return ERROR;
            }
            else
            {
                GLOBAL_INDEX_TREE(tree);
                CIndexTreeNode*n = tree->FindNode(item);
                ASSERT(n);
                g_globals.SetCurIndexTreeNode(n);

                GLOBAL_WND_PROPERTY(win);
                if(win && win->hwnd)
                {
                    g_globals.ShowPropertyWindow(n);
                }
            }
		}
	}
	return OK;
}
int CMainForm::OnLButtonDown(WPARAM wparam,LPARAM lparam)
{
	return OK;
}
int CMainForm::OnLButtonUp(WPARAM wparam,LPARAM lparam)
{
	return OK;
}
int CMainForm::OnRButtonDown(WPARAM wparam,LPARAM lparam)
{
	return OK;
}
int CMainForm::OnRButtonUp(WPARAM wparam,LPARAM lparam)
{
	return OK;
}
int CMainForm::OnScroll(WPARAM wparam,LPARAM lparam)
{
	return OK;
}
int CMainForm::OnMouseMove(WPARAM wparam,LPARAM lparam)
{
	return OK;
}
int CMainForm::OnChar(WPARAM wparam,LPARAM lparam)
{
	return OK;
}
int CMainForm::OnKeyDown(WPARAM wparam,LPARAM lparam)
{
	return OK;
}
int CMainForm::OnPosChanged(WPARAM wparam,LPARAM lparam)
{
	return OK;
}
int CMainForm::OnUnknown(WPARAM wparam, LPARAM lparam)
{
	return OK;
}
LRESULT CMainForm::ProcessAllMsg(UINT message, WPARAM wparam, LPARAM lparam)
{
	return CWnd::ProcessAllMsg(message,wparam,lparam);
}

//////////////////////////////
static int all_keys[256] = {0};

static int simple_keymanager_on_msg(MSG *msg)
{
	if(msg->message == WM_KEYDOWN)
	{
		uint32_t vk = msg->wParam & 0x000000ff;
		all_keys[vk] = 1;
	}

	if(msg->message == WM_KEYUP)
	{
		uint32_t vk = msg->wParam & 0x000000ff;
		all_keys[vk] = 0;
	}
	
	return OK;
}

static bool simple_keymanager_is_keydown(int vk)
{
	ASSERT(vk >= 0  && vk <= 256);
	return all_keys[vk] !=0 ;
}

status_t simple_keymanager_clear_all()
{
    memset(all_keys,0,sizeof(all_keys));
    return OK;
}

//////////////////////////////

static bool is_ctrl_key_down()
{
    return simple_keymanager_is_keydown(VK_CONTROL) ||
        simple_keymanager_is_keydown(VK_LCONTROL) ||
        simple_keymanager_is_keydown(VK_RCONTROL);
}


int CMainForm::PreTransMsg(MSG *msg)
{
	HWND hlist[100];
	int i = 0;

	hlist[i++] = this->m_TreeView->hwnd;
	if(this->m_WndPageHost)
	{
		CPage *cur_page = this->m_WndPageHost->i_Page;
		if(cur_page)cur_page->AddTabWnd(hlist,&i);
	}
	
    if(m_TreeView)
    {
        if(msg->hwnd == m_TreeView->hwnd && msg->message == WM_LBUTTONDBLCLK)
        {
            this->ShowPropertyWindow();
        }

        if(msg->hwnd == m_TreeView->hwnd && msg->message == WM_RBUTTONDOWN)
        {
            this->OnShowContextMenu(msg);
        }
	}
	
	simple_keymanager_on_msg(msg);

	static int is_ctrl_enter_down = 0;
	if(is_ctrl_key_down() && simple_keymanager_is_keydown(VK_RETURN))
	{
		if(!is_ctrl_enter_down)
		{
			mitem_start->EmuPush(hwnd);
			is_ctrl_enter_down = 1;
			return OK;
		}		
	}
	else
	{
		is_ctrl_enter_down = 0;
	}
	
	static int is_return_down = 0;
	if(msg->hwnd == m_TreeView->hwnd && !is_ctrl_key_down()  && simple_keymanager_is_keydown(VK_RETURN))
	{
		if(!is_return_down)
		{
			is_return_down = 1;
			this->ShowPropertyWindow();
			return OK;
		}			
	}
	else
	{
		is_return_down = 0;
	}
	
    static int is_ctrl_a_down = 0;
	if(is_ctrl_key_down() && simple_keymanager_is_keydown('A'))
	{		
        if(is_ctrl_a_down == 0)
        {
			HWND hwnd  = ::GetFocus();
			SendMessageW(hwnd,EM_SETSEL,(WPARAM)0,(LPARAM)-1);
            is_ctrl_a_down = 1;
			return OK;
        }
	}
    else
    {
        is_ctrl_a_down = 0;
    }

	static int is_ctrl_f_down = 0;
	if(is_ctrl_key_down() && simple_keymanager_is_keydown('F'))
	{		
        if(is_ctrl_f_down == 0)
        {
			g_globals.ShowSearchWindow();		
            is_ctrl_f_down = 1;
			return OK;
        }
	}
    else
    {
        is_ctrl_f_down = 0;
    }

    if(simple_keymanager_is_keydown(VK_ESCAPE))
    {
		g_globals.CloseSearchWindow();
        g_globals.TryStopLuaThread();
        simple_keymanager_clear_all();
    }

	GLOBAL_WND_SEARCH(wnd_search);
	if(wnd_search->hwnd)
	{
		return wnd_search->PreTransMsg(msg);
	}

	return CWinMisc::TabFocus(hwnd,hlist,i,msg);
}
status_t CMainForm::SwitchPage(const wchar_t *name)
{
	ASSERT(name);

	CPage *page = this->m_PageManager->GetPage(name);

	if(crt_stricmp_w(name,PAGE_NAME_TEXT) == 0)
	{
        if(!page)
        {
    	    CPageText *pt;
		    NEW(pt,CPageText);
		    pt->Init();
		    pt->SetParent(m_WndPageHost->hwnd);
		    pt->SetName(name);
		    pt->SetStyle(WS_CHILD|WS_VISIBLE);
		    pt->Create();
		    pt->SetPageSize(1,1);		
		    this->m_PageManager->PushPtr(pt);
		    page = pt;

		    g_globals.i_PageText.WeakRef(pt);
        }
        mitem_text_window->CheckItem(TRUE);
        mitem_image_window->CheckItem(FALSE);
	}

    if(crt_stricmp_w(name,PAGE_NAME_IMAGE) == 0)
    {
        if(!page)
        {
            CPageImage *pt;
            NEW(pt,CPageImage);
            pt->Init();
            pt->SetParent(m_WndPageHost->hwnd);
            pt->SetName(name);
            pt->SetStyle(WS_CHILD|WS_VISIBLE);
            pt->Create();
            pt->SetPageSize(1,1);		
            this->m_PageManager->PushPtr(pt);
            page = pt;       

            g_globals.i_PageImage.WeakRef(pt);
        }
        mitem_text_window->CheckItem(FALSE);
        mitem_image_window->CheckItem(TRUE);
    }

    ASSERT(page);
	this->m_WndPageHost->SetCurPage(page);	

	return OK;
}

CTreeView* CMainForm::GetTreeView()
{
    return m_TreeView;
}

status_t CMainForm::ShowPropertyWindow()
{
    GLOBAL_WND_PROPERTY(win);
    if(win && win->hwnd)return OK;
    HTREEITEM sel_item = m_TreeView->GetSelectItem();
    if(!sel_item)return ERROR;
    GLOBAL_INDEX_TREE(index_tree);
    if(!m_TreeView->IsLeaf(sel_item))return ERROR;
    CIndexTreeNode *node = index_tree->FindNode(sel_item);
    ASSERT(node);
    g_globals.ShowPropertyWindow(node);
    return OK;
}

status_t CMainForm::SetStatusText(int part,const char *szFormat, ...)
{
    MAKE_VARGS_BUFFER(szFormat);

    if(g_globals.IsOnMainThread())
    {
        LOCAL_MEM(tmp);
        tmp.Puts(szBuffer);
        CEncoder::EncodingConvert(ENCODING_UTF8,ENCODING_UNICODE,&tmp);
        m_StatusBar->SetPartText(0,tmp.CStrW());
    }
    else
    {
        BEGIN_NEW_CLOSURE(run)
        {
            CLOSURE_PARAM_PTR(char *,szBuffer,10);
            CLOSURE_PARAM_PTR(CStatusBar*,status_bar,11);
            CLOSURE_PARAM_INT(part,12);
            LOCAL_MEM(tmp);
            tmp.Puts(szBuffer);
            CEncoder::EncodingConvert(ENCODING_UTF8,ENCODING_UNICODE,&tmp);
            status_bar->SetPartText(part,tmp.CStrW());
            return OK;
        }
        END_NEW_CLOSURE(run);      
        run->Malloc(10,szBuffer,strlen(szBuffer)+1);
        run->SetParamPointer(11,m_StatusBar);
        run->SetParamInt(12,part);

        GLOBAL_MAIN_TASK_RUNNER(task_runner);
        task_runner->AddClosure(run,0);
    }
    return OK;
}


int CMainForm::OnSaveAs()
{

	CEditBox *eb = g_globals.GetTheEditBox();
	ASSERT(eb);

	int len = eb->GetTextLen();
	if(len <= 0)return ERROR;

	LOCAL_MEM(mem);

	if(CWinMisc::GetSaveFileName(hwnd,&mem,L"All type file\0*.*\0\0"))
	{
	
		CEncoder::EncodingConvert(ENCODING_UNICODE,LOCAL_ENCODING,&mem);
		
		LOCAL_MEM(unicode);
		eb->GetText_File(&unicode);
		
		CMemFile utf8;
		utf8.Init();
		CEncoder::UnicodeToUtf8(&unicode,&utf8);		
		utf8.WriteToFile(mem.CStr());
	}
	
	return OK;
}

int CMainForm::OnLoad()
{
	LOCAL_MEM(mem);
	
	if(!CWinMisc::GetAFileName(hwnd,&mem,L"All files\0*.*\0\0"))
		return ERROR;
	
	CEncoder::EncodingConvert(ENCODING_UNICODE,LOCAL_ENCODING,&mem);
	
	CEditBox *eb = g_globals.GetTheEditBox();
	ASSERT(eb);

	CMemFile mf_utf8;
	mf_utf8.Init();
	mf_utf8.LoadFile(mem.CStr());

	CMem mem_unicode;
	mem_unicode.Init();
	mem_unicode.Malloc((int)mf_utf8.GetSize()*2);
	
	CEncoder::Utf8ToUnicode(&mf_utf8,&mem_unicode);

	eb->SetText(mem_unicode.CStrW());
	return OK;
}

status_t CMainForm::SwitchToPageText()
{
    return this->SwitchPage_ThreadSafe(PAGE_NAME_TEXT);
}

status_t CMainForm::SwitchToPageImage()
{
    return this->SwitchPage_ThreadSafe(PAGE_NAME_IMAGE);
}

status_t CMainForm::SwitchPage_ThreadSafe(const wchar_t *name)
{
    ASSERT(name);

    if(g_globals.IsOnMainThread())
    {
        return this->SwitchPage(name);
    }
    else
    {
        BEGIN_NEW_CLOSURE(run)
        {
            CLOSURE_PARAM_PTR(CMainForm*,self,10);
            CLOSURE_PARAM_PTR(wchar_t*,name,11);
            return self->SwitchPage(name);
        }
        END_NEW_CLOSURE(run);      
        run->SetParamPointer(10,this);
        run->SetParamPointer(11,(void*)name);
                
        GLOBAL_MAIN_TASK_RUNNER(task_runner);
        task_runner->AddClosure(run,0);
    }

    return OK;
}

status_t CMainForm::OnWndSplitHEvent()
{
	RECT r;
	::GetClientRect(m_WndRight->hwnd,&r);
	m_WndPageHost->MoveWindow(&r);

	if(!m_WndSplit_V)return ERROR;	
	::GetClientRect(m_WndRight->hwnd,&r);
	m_WndSplit_V->RecalcLayout(r);
	return OK;
}

status_t CMainForm::ShowEmbeddedUIWindow(int height)
{
	ASSERT(m_WndEmbeddedUI == NULL);
	ASSERT(m_WndSplit_V == NULL);

	RECT r;
	::GetClientRect(m_WndRight->hwnd,&r);

	int pos = r.bottom-height;
	ASSERT(pos > 0);


	NEW(this->m_WndSplit_V,CWndSplit);
	this->m_WndSplit_V->Init(false);
	this->m_WndSplit_V->Registe();
	this->m_WndSplit_V->SetParent(m_WndRight->hwnd);
	this->m_WndSplit_V->Create();
	
	NEW(m_WndEmbeddedUI,CWndEmbeddedUI);
	m_WndEmbeddedUI->Init();
	m_WndEmbeddedUI->SetParent(m_WndRight->hwnd);
	m_WndEmbeddedUI->SetStyle(WS_CHILD|WS_VISIBLE);
	m_WndEmbeddedUI->Create();

	this->m_WndSplit_V->pane0 = m_WndPageHost->hwnd;
	this->m_WndSplit_V->pane1 = m_WndEmbeddedUI->hwnd;
	
	m_EmbeddedUIWindowHeight = height;
	this->m_WndSplit_V->SetBarPos(pos);

	return OK;
}

status_t CMainForm::HideEmbeddedUIWindow()
{
	DEL(m_WndSplit_V);
	DEL(m_WndEmbeddedUI);
	return OK;
}

status_t CMainForm::OnShowContextMenu(MSG *msg)
{
    ASSERT(msg);
    ::SetFocus(m_TreeView->hwnd);
    int xPos = LOWORD(msg->lParam);
    int yPos = HIWORD(msg->lParam);  
    
    TVHITTESTINFO info;
    memset(&info,0,sizeof(info));
    info.pt.x = xPos;
    info.pt.y = yPos;
    
    TreeView_HitTest(m_TreeView->hwnd,&info);
    
    if(!m_TreeView->IsLeaf(info.hItem))
        return ERROR;

    if(info.hItem)
    {
        ::ClientToScreen(m_TreeView->hwnd,&info.pt);
        m_TreeView->SetSelect(info.hItem);
        menu_context->Show(info.pt.x,info.pt.y);
    }

    return OK;
}
