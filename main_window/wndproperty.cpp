#include "cruntime.h"
#include "resource.h"
#include "wndproperty.h"
#include "winmisc.h"
#include "encoder.h"
#include "mem_tool.h"
#include "syslog.h"
#include "file.h"
#include "resource.h"
#include "memfile.h"
#include "globals.h"
#include "dirmgr.h"

RECT CWndProperty::saved_rect={0,0,0,0};

CWndProperty::CWndProperty()
{
    this->InitBasic();
}
CWndProperty::~CWndProperty()
{
    this->Destroy();
}
int CWndProperty::InitBasic()
{
	this->pb_cancel = NULL;
	this->pb_ok = NULL;
	this->pb_default = NULL;
	this->eb_code = NULL;
	this->toolbar = NULL;
	this->tbb_file = NULL;
	this->tbb_path = NULL;
	this->tbb_load = NULL;
	this->tbb_save = NULL;
	this->can_be_closed = TRUE;
    text_changed = false;
    cur_node = NULL;
    CWnd::InitBasic();
    return OK;
}
int CWndProperty::Init()
{
    this->InitBasic();
    CWnd::Init();
    //add your code
    return OK;
}
int  CWndProperty::Destroy()
{
	if(!this->can_be_closed)
		return ERROR;

	if(hwnd)
    {
        GetWindowRect(hwnd,&saved_rect);
        SetForegroundWindow(GetParent());
    }

	DEL(this->tbb_load);
	DEL(this->tbb_save);
	DEL(this->pb_cancel);
	DEL(this->pb_ok);
	DEL(this->pb_default);
	DEL(this->eb_code);
	DEL(this->toolbar);
	DEL(this->tbb_file);
	DEL(this->tbb_path);
    DEL(this->tbb_1);
    DEL(this->tbb_2);
    DEL(this->tbb_3);
    DEL(this->tbb_4);
    DEL(this->tbb_5);
    DEL(this->tbb_help);
    DEL(this->tbb_open_folder);
    CWnd::Destroy();
    this->InitBasic();
    return OK;
}
int CWndProperty::OnCreate(WPARAM wparam, LPARAM lparam)
{
	NEW(this->pb_cancel,CButton);
	this->pb_cancel->Init();
	this->pb_cancel->SetParent(hwnd);
	this->pb_cancel->SetText(L"Cancel");
	this->pb_cancel->Create();
	this->pb_cancel->SetStockFont(DEFAULT_GUI_FONT);
	NEW(this->pb_ok,CButton);
	this->pb_ok->Init();
	this->pb_ok->SetParent(hwnd);
	this->pb_ok->SetText(L"Ok");
	this->pb_ok->Create();
	this->pb_ok->SetStockFont(DEFAULT_GUI_FONT);
	NEW(this->pb_default,CButton);
	this->pb_default->Init();
	this->pb_default->SetParent(hwnd);
	this->pb_default->SetText(L"Default");
	this->pb_default->Create();
	this->pb_default->SetStockFont(DEFAULT_GUI_FONT);
	NEW(this->eb_code,CEditBox);
	this->eb_code->Init();
	this->eb_code->SetParent(hwnd);
	this->eb_code->AddStyle(ES_MULTILINE|ES_NOHIDESEL);
	this->eb_code->AddStyle(WS_HSCROLL);
	this->eb_code->AddStyle(WS_VSCROLL);
	this->eb_code->AddStyle(ES_AUTOHSCROLL);
	this->eb_code->AddStyle(ES_AUTOVSCROLL);
	this->eb_code->AddExStyle(WS_EX_CLIENTEDGE);
	this->eb_code->Create();
	this->eb_code->SetStockFont(SYSTEM_FIXED_FONT);
	this->eb_code->SetMaxText(10485760);
	NEW(this->toolbar,CToolBar);
	this->toolbar->Init();
	this->toolbar->SetParent(hwnd);
	this->toolbar->Create();
	this->toolbar->CreateImageList(
        IDB_BITMAP_TOOLBAR_PROPERTY,
        16,16,16,RGB(192,192,192)
    );
	this->toolbar->SetAutoSize();
	
    NEW(this->tbb_load,CTBButton);
	this->tbb_load->Init();
	this->tbb_load->SetImgIndex(0);
	this->tbb_load->SetToolTip(L"Load code from file");

	NEW(this->tbb_save,CTBButton);
	this->tbb_save->Init();
	this->tbb_save->SetImgIndex(1);
	this->tbb_save->SetToolTip(L"Save as");

	NEW(this->tbb_file,CTBButton);
	this->tbb_file->Init();
	this->tbb_file->SetImgIndex(2);
	this->tbb_file->SetToolTip(L"Insert file code");

    NEW(this->tbb_path,CTBButton);
	this->tbb_path->Init();
	this->tbb_path->SetImgIndex(3);
	this->tbb_path->SetToolTip(L"Insert path code");
    

    NEW(this->tbb_1,CTBButton);
    this->tbb_1->Init();
    this->tbb_1->SetImgIndex(5);
    this->tbb_1->SetToolTip(L"user config 1");
    
    NEW(this->tbb_2,CTBButton);
    this->tbb_2->Init();
    this->tbb_2->SetImgIndex(6);
    this->tbb_2->SetToolTip(L"user config 2");
    
    NEW(this->tbb_3,CTBButton);
    this->tbb_3->Init();
    this->tbb_3->SetImgIndex(7);
    this->tbb_3->SetToolTip(L"user config 3");
    
    NEW(this->tbb_4,CTBButton);
    this->tbb_4->Init();
    this->tbb_4->SetImgIndex(8);
    this->tbb_4->SetToolTip(L"user config 4");
    
    NEW(this->tbb_5,CTBButton);
    this->tbb_5->Init();
    this->tbb_5->SetImgIndex(9);
    this->tbb_5->SetToolTip(L"user config 5");

    NEW(this->tbb_open_folder,CTBButton);
    this->tbb_open_folder->Init();
    this->tbb_open_folder->SetImgIndex(10);
    this->tbb_open_folder->SetToolTip(L"open this folder");

    NEW(this->tbb_help,CTBButton);
    this->tbb_help->Init();
    this->tbb_help->SetImgIndex(11);
    this->tbb_help->SetToolTip(L"help");

	this->toolbar->AddButton(tbb_load);
	this->toolbar->AddButton(tbb_save);
	this->toolbar->AddButton(tbb_file);
	this->toolbar->AddButton(tbb_path);
    this->toolbar->AddButton(tbb_open_folder);
    this->toolbar->AddSeparator();
    this->toolbar->AddButton(tbb_1);
    this->toolbar->AddButton(tbb_2);
    this->toolbar->AddButton(tbb_3);
    this->toolbar->AddButton(tbb_4);
    this->toolbar->AddButton(tbb_5);
    this->toolbar->AddSeparator();
  	this->toolbar->AddButton(tbb_help);

	this->eb_code->SetTabStops(4*4);
	this->SetVirtualSize(381,361);
	
    if(saved_rect.left == 0 && saved_rect.right == 0)
    {
        RECT r;
        HWND hp = GetParent();
        GetWindowRect(hp,&r);
        int ww = r.right-r.left;
        int hh = r.bottom-r.top;

        int w = 640, h = 480;
        this->MoveWindow(r.left + (ww-w)/2, r.top +(hh-h)/2,w,h);
    }
    else
    {
        this->MoveWindow(&saved_rect);
    }
	return OK;
}
int CWndProperty::OnClose(WPARAM wparam, LPARAM lparam)
{
    return this->Destroy();
}
int CWndProperty::OnSize(WPARAM wparam, LPARAM lparam)
{
	RECT r,rt;

    int button_width=75,button_height=25,button_interval=10;
	int from_bottom = 5;

	this->toolbar->OnSize();

	GetClientRect(hwnd,&r);
	GetWindowRect(this->toolbar->hwnd,&rt);
	
	r.top += (rt.bottom - rt.top);

	if(r.right / 4 < (75+10))
	{
		button_width = (r.right / 4) * 8/10;
		button_interval = (r.right / 4) * 2/10;
	}

	this->eb_code->MoveWindow(r.left,r.top,r.right-r.left,r.bottom -r.top - 35);

	this->pb_default->MoveWindow(r.right - button_width * 3 - button_interval *3,
							   r.bottom - from_bottom - button_height,
							   button_width,button_height);

	this->pb_ok->MoveWindow(r.right - button_width * 2 - button_interval *2,
							r.bottom - from_bottom - button_height,
							button_width,button_height);

	this->pb_cancel->MoveWindow(r.right - button_width * 1 - button_interval *1,
								r.bottom - from_bottom - button_height,
								button_width,button_height);

    return OK;
}
int CWndProperty::OnCommand(WPARAM wparam, LPARAM lparam)
{
	if(this->pb_default->IsMyCommand(wparam))
	{
		this->RestoreDefault();
	}
	
	else if(this->tbb_load->IsMyCommand(wparam))
    {
        this->OnLoad();
    }
	
	else if(this->tbb_save->IsMyCommand(wparam))
    {
        this->OnSave();
    }

    else if(this->eb_code->IsMyCommand(wparam))
    {
        if(eb_code->GetCommandCode(wparam) == EN_CHANGE)
        {
            text_changed = true;
        }
    }

    else if(tbb_file->IsMyCommand(wparam))
    {
        this->OnInsertFileName();
    }

    else if(tbb_path->IsMyCommand(wparam))
    {
        this->OnInsertPathName();
    }

    else if(this->pb_cancel->IsMyCommand(wparam))
    {
        this->Close();
    }
    
    else if(this->pb_ok->IsMyCommand(wparam))
    {
        this->OnOK();
	}

    else if(tbb_1->IsMyCommand(wparam))
    {
        this->ChangeCurrentUser(0);
    }
    else if(tbb_2->IsMyCommand(wparam))
    {
        this->ChangeCurrentUser(1);
    }
    else if(tbb_3->IsMyCommand(wparam))
    {
        this->ChangeCurrentUser(2);
    }
    else if(tbb_4->IsMyCommand(wparam))
    {
        this->ChangeCurrentUser(3);
    }
    else if(tbb_5->IsMyCommand(wparam))
    {
        this->ChangeCurrentUser(4);
    }

    else if(tbb_open_folder->IsMyCommand(wparam))
    {
        this->OpenTheFolder();
    }

    else if(tbb_help->IsMyCommand(wparam))
    {
        g_globals.ShowHelp();
    }
    return OK;
}
int CWndProperty::PreTransMsg(MSG *msg)
{
	HWND hlist[100];
	int i = 0;
	
	if(this->hwnd)
	{
		if(msg->message == WM_KEYDOWN)
		{
			if(msg->wParam == VK_ESCAPE)
			{
				this->Close();
				return TRUE;
			}

			if(CWinMisc::IsKeyDown(VK_CONTROL)  && CWinMisc::IsKeyDown('D'))
			{
				return TRUE;
			}
		}
	}

	return CWinMisc::TabFocus(hwnd,hlist,i,msg);
}

int CWndProperty::OnNotify(WPARAM wparam, LPARAM lparam)
{
	return this->toolbar->OnNotify(wparam,lparam);
}

int CWndProperty::OnOK()
{   
    //will close this window
	g_globals.StartLuaThread();
	return OK;
}

int CWndProperty::OnLoad()
{
	if(this->can_be_closed == 0)
		return ERROR;
	this->can_be_closed = 0;

   	LOCAL_MEM(mem);
	int ret = CWinMisc::GetAFileName(hwnd,&mem,L"All files\0*.*\0\0");
	this->can_be_closed = 1;
	if(!ret)return ERROR;
	
	CEncoder::UnicodeToGb(&mem);
    
    CMem buf;
    buf.Init();
    
    if(!buf.LoadFile(mem.CStr()))
        return ERROR;

    CMemFile mf_uni;
    mf_uni.Init();

    CEncoder::Utf8ToUnicode(&buf,&mf_uni);

	eb_code->SetText_File(&mf_uni);
	return OK;
}

int CWndProperty::OnSave()
{
    LOCAL_MEM(filename);
    this->can_be_closed = 0;
    status_t ret = CWinMisc::GetSaveFileName(hwnd,&filename,L"All files\0*.*\0\0");
    this->can_be_closed = 1;
    if(!ret) return ERROR;
    
    CEncoder::EncodingConvert(ENCODING_UNICODE,LOCAL_ENCODING,&filename);

    LOCAL_MEM(mem);
    eb_code->GetText_File(&mem);

    CMemFile mf_tmp;
    mf_tmp.Init();
    CEncoder::UnicodeToUtf8(&mem,&mf_tmp);
    mf_tmp.WriteToFile(filename.CStr());
	return OK;
}

status_t CWndProperty::LoadNode(CIndexTreeNode *node)
{
    ASSERT(node);
    
    this->AutoSave();

    LOCAL_MEM(title);
    title.Puts(node->GetName());
    CEncoder::Utf8ToUnicode(&title);

    this->SetTextF(L"%s (%d)",title.CStrW(),node->GetCurrentUser()+1);

    CMemFile mf;
    mf.Init();
    if(!node->LoadUserCode(&mf))
    {
        node->LoadDefaultCode(&mf);
    }
    CEncoder::Utf8ToUnicode(&mf);
    eb_code->SetText_File(&mf);
    text_changed = false;
    cur_node = node;
    return OK;
}

status_t CWndProperty::AutoSave()
{
    if(!cur_node)
        return ERROR;

    if(!text_changed)
        return ERROR;

	LOCAL_MEM(mem);
    eb_code->GetText_File(&mem);
    cur_node->SaveUserCode_Unicode(&mem);
    text_changed = false;
    return OK;
}

status_t CWndProperty::RestoreDefault()
{
    if(!cur_node)return ERROR;
    CMemFile mf_def;
    mf_def.Init();
    if(!cur_node->LoadDefaultCode(&mf_def))
    {
        LOG("load fault code error");
        return ERROR;
    }
    CEncoder::Utf8ToUnicode(&mf_def);
    eb_code->SetText_File(&mf_def);
    return OK;
}

static escape_unicode_c_str(CFileBase *uni_in,CFileBase *uni_out)
{
    uni_in->Seek(0);
    for(int i = 0; i < uni_in->StrLen(); i++)
    {
        wchar_t ch = uni_in->GetcW();
        if(ch == L'\\')
            uni_out->PutsW(L"\\\\");
        else
            uni_out->PutcW(ch);
    }
    return OK;
}

status_t CWndProperty::OnInsertFileName()
{
    LOCAL_MEM(filename);
    this->can_be_closed = 0;
	status_t ret = CWinMisc::GetAFileName(hwnd,&filename,L"All files\0*.*\0\0");
    this->can_be_closed = 1;
    if(!ret) return ERROR;
    LOCAL_MEM(esc);
    escape_unicode_c_str(&filename,&esc);
    eb_code->ReplaceSel(esc.CStrW());
    return OK;
}

status_t CWndProperty::OnInsertPathName()
{
    LOCAL_MEM(filename);
    this->can_be_closed = 0;
    status_t ret = CWinMisc::FolderSelect(hwnd,&filename);
    this->can_be_closed = 1;
    if(!ret) return ERROR;
    LOCAL_MEM(esc);
    escape_unicode_c_str(&filename,&esc);
    eb_code->ReplaceSel(esc.CStrW());
    return OK;
}

status_t CWndProperty::ChangeCurrentUser(int index)
{
    if(!cur_node)return ERROR;
    this->AutoSave();
    if(cur_node->GetCurrentUser() == index)
        return OK;  
    cur_node->SetCurrentUser(index);
    this->LoadNode(cur_node);
    return OK;
}

status_t CWndProperty::OpenTheFolder()
{
    ASSERT(cur_node);
  
    LOCAL_MEM(cmd);
    cmd.Printf("explorer \"%s\"",cur_node->GetPathStr());
    WinExec(cmd.CStr(),SW_SHOW);
    return OK;
}
