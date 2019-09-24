#ifndef __WNDEMBEDDEDUI_H
#define __WNDEMBEDDEDUI_H

#include "wnd.h"
#include "comnctls.h"

class CWndEmbeddedUI:public CWnd{
public:
public:
	CWndEmbeddedUI();
	virtual ~CWndEmbeddedUI();
	int Init();
	int Destroy();
	int InitBasic();
	int OnCreate(WPARAM wparam, LPARAM lparam);
	int OnClose(WPARAM wparam, LPARAM lparam);
	int OnSize(WPARAM wparam, LPARAM lparam);
	int OnCommand(WPARAM wparam, LPARAM lparam);
	int PreTransMsg(MSG *msg);
    virtual LRESULT ProcessAllMsg(UINT message,WPARAM wparam,LPARAM lparam);
};

#endif
