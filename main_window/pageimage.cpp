#include "pageimage.h"
#include "syslog.h"
#include "mem_tool.h"
#include "globals.h"
#include "ximagehelper.h"

#define SBW 18

CPageImage::CPageImage()
{
    this->InitBasic();
}

CPageImage::~CPageImage()
{
    this->Destroy();
}

status_t CPageImage::InitBasic()
{
    scroll_event_nest = 0;
    this->sb_v = NULL;
    this->sb_h = NULL;
    draw_pos_x = 0;
    draw_pos_y = 0;
    CPage::InitBasic();
    return OK;
}

status_t CPageImage::Init()
{
    this->InitBasic();
    CPage::Init();
    return OK;
}

status_t CPageImage::Destroy()
{
    DEL(this->sb_v);
    DEL(this->sb_h);
    CPage::Destroy();
    this->InitBasic();
    return OK;
}

status_t CPageImage::OnEnter()
{
    return OK;
}

status_t CPageImage::OnExit()
{
    return OK;
}

int CPageImage::OnCreate(WPARAM wparam, LPARAM lparam)
{
    NEW(this->sb_v,CScrollBar);
    this->sb_v->Init();
    this->sb_v->SetParent(hwnd);
    this->sb_v->SetDir(1);
    this->sb_v->SetRange(0,100);
    this->sb_v->Create();
    this->sb_v->SetLineStep(1);
    this->sb_v->SetPageSize(10);
    NEW(this->sb_h,CScrollBar);
    this->sb_h->Init();
    this->sb_h->SetParent(hwnd);
    this->sb_h->SetDir(0);
    this->sb_h->SetRange(0,100);
    this->sb_h->Create();
    this->sb_h->SetLineStep(1);
    this->sb_h->SetPageSize(10);
    return OK;
}

int CPageImage::OnClose(WPARAM wparam, LPARAM lparam)
{
    return OK;
}

int CPageImage::OnSize(WPARAM wparam, LPARAM lparam)
{
    this->RefreshUI();
    return OK;
}

int CPageImage::OnCommand(WPARAM wparam, LPARAM lparam)
{
    return OK;
}

status_t CPageImage::AddTabWnd(HWND *hlist, int *i)
{
    return OK;
}

status_t CPageImage::OnHScroll(WPARAM wparam,LPARAM lparam)
{
    if(scroll_event_nest)
        return ERROR;
    sb_h->OnScroll(wparam,lparam);
    draw_pos_x = -sb_h->GetPos();
    this->RefreshScreen();
    return OK;
}
 
status_t CPageImage::OnVScroll(WPARAM wparam,LPARAM lparam)
{
    if(scroll_event_nest)
        return ERROR;
    sb_v->OnScroll(wparam,lparam);
    draw_pos_y = -sb_v->GetPos();
    this->RefreshScreen();
    return OK;
}

status_t CPageImage::RefreshUI()
{
    RECT r;
    ::GetClientRect(hwnd,&r);
    
    this->ResetPosition();

    int win_width = r.right-r.left;
    int win_height = r.bottom - r.top;

    if(win_width <= 0 || win_height <= 0)
        return ERROR;

    GLOBAL_SCREEN_BUFFER(screen_buffer);
    if(!screen_buffer)
    {
        sb_h->Hide();
        sb_v->Hide();
        return ERROR;
    }

    CxImage *img = screen_buffer->GetImageBuffer();
    ASSERT(img);

    if(win_width < img->GetWidth())
    {
        sb_h->MoveWindow(0,r.bottom-SBW,r.right - r.left-SBW,SBW);        
        sb_h->SetRange(0,img->GetWidth()); 
        sb_h->SetPageSize(win_width-SBW);                      
        sb_h->Show();
    }
    else
    {     
        sb_h->Hide();
    }

    if(win_height < img->GetHeight())
    {
        sb_v->MoveWindow(r.right-SBW,0,SBW,r.bottom-r.top-SBW);
        sb_v->SetRange(0,img->GetHeight());
        sb_v->SetPageSize(win_height-SBW);                
        sb_v->Show();
    }
    else
    {
        sb_v->Hide();
    }

    this->RefreshScreen();
    return OK;
}
status_t CPageImage::OnPaint(WPARAM wparam, LPARAM lparam)
{
    PAINTSTRUCT ps;
    HDC hdc = ::BeginPaint(hwnd,&ps);

    GLOBAL_SCREEN_BUFFER(screen_buffer);
    ASSERT(screen_buffer);
    screen_buffer->Lock();
    CxImage *img = screen_buffer->GetImageBuffer();
    ASSERT(img);
    img->Draw2(hdc,draw_pos_x,draw_pos_y,img->GetWidth(),img->GetHeight());
    screen_buffer->Unlock();
    ::EndPaint(hwnd,&ps);
    return OK;
}

status_t CPageImage::RefreshScreen(BOOL clear)
{
    RECT r;
    ::GetClientRect(hwnd,&r);
    
    if(CWnd::IsVisible(sb_v->hwnd))
        r.right -= SBW;
    if(CWnd::IsVisible(sb_h->hwnd))
        r.bottom -= SBW;
    
    int win_width = r.right-r.left;
    int win_height = r.bottom - r.top;

    GLOBAL_SCREEN_BUFFER(screen_buffer);
    ASSERT(screen_buffer);   
    CxImage *img = screen_buffer->GetImageBuffer();
    ASSERT(img);

    if(win_width > img->GetWidth() || win_height > img->GetHeight())
        ::InvalidateRect(hwnd,&r,clear);
    else
        ::InvalidateRect(hwnd,&r,clear);

    return OK;
}

status_t CPageImage::ResetPosition()
{
    draw_pos_x = 0;
    draw_pos_y = 0;
    scroll_event_nest ++;
    sb_h->SetPos(0);
    sb_v->SetPos(0);
    scroll_event_nest --;
    return OK;
}

status_t CPageImage::ResetPosition_ThreadSafe()
{
    if(g_globals.IsOnMainThread())
    {
        return this->ResetPosition();
    }
    else
    {
        BEGIN_NEW_CLOSURE(run_on_main_thread)
        {
            CLOSURE_PARAM_PTR(CPageImage *,self,10);
            self->ResetPosition();
            return OK;
        }
        END_NEW_CLOSURE(run_on_main_thread);
 
        run_on_main_thread->SetParamPointer(10,this);
        GLOBAL_MAIN_TASK_RUNNER(runner);
        runner->AddClosure(run_on_main_thread,0);
    }
    return OK;
}

