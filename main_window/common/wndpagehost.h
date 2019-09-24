#ifndef __WNDPAGEHOST_H
#define __WNDPAGEHOST_H

#include "wnd.h"
#include "comnctls.h"
#include "page.h"

class CWndPageHost:public CWnd{
public:
	CScrollBar *m_HScrollBar;
	CScrollBar *m_VScrollBar;
	CPage *i_Page;
	int m_ViewW, m_ViewH;
public:
	status_t SetCurPage(CPage *page);
	CWndPageHost();
	virtual ~CWndPageHost();
	int Init();
	int Destroy();
	int InitBasic();
	int OnCreate(WPARAM wparam, LPARAM lparam);
	int OnClose(WPARAM wparam, LPARAM lparam);
	int OnSize(WPARAM wparam, LPARAM lparam);
	int OnCommand(WPARAM wparam, LPARAM lparam);
	int PreTransMsg(MSG *msg);
	int OnHScroll(WPARAM wparam, LPARAM lparam);
	int OnVScroll(WPARAM wparam, LPARAM lparam);
};

#endif
