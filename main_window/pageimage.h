#ifndef __PAGEIMAGE_H
#define __PAGEIMAGE_H

#include "mem.h"
#include "memfile.h"
#include "page.h"
#include "comnctls.h"

class CPageImage:public CPage{
public:
    CScrollBar *sb_v;
    CScrollBar *sb_h;
    int draw_pos_x,draw_pos_y;
    int scroll_event_nest;
public:
    status_t ResetPosition_ThreadSafe();
	status_t ResetPosition();
	status_t RefreshScreen();
	status_t RefreshUI();
    CPageImage();
    ~CPageImage();

    status_t InitBasic();
    status_t Init();
    status_t Destroy();

    virtual status_t OnEnter();
    virtual status_t OnExit();
    
    int OnCreate(WPARAM wparam, LPARAM lparam);
    int OnClose(WPARAM wparam, LPARAM lparam);
    int OnSize(WPARAM wparam, LPARAM lparam);
    int OnCommand(WPARAM wparam, LPARAM lparam);
    status_t OnHScroll(WPARAM wparam,LPARAM lparam);
    status_t OnVScroll(WPARAM wparam,LPARAM lparam);
    status_t AddTabWnd(HWND *hlist, int *i);
    status_t OnPaint(WPARAM wparam, LPARAM lparam);    
};

#endif
