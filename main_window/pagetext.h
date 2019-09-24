#ifndef __PAGETEXT_H
#define __PAGETEXT_H

#include "page.h"
#include "comnctls.h"

class CPageText:public CPage{
public:
	CEditBox *eb_log;
public:
	virtual status_t OnEnter();
	virtual status_t OnExit();

	CPageText();
	virtual ~CPageText();
	int Init();
	int Destroy();
	int InitBasic();
	int OnCreate(WPARAM wparam, LPARAM lparam);
	int OnClose(WPARAM wparam, LPARAM lparam);
	int OnSize(WPARAM wparam, LPARAM lparam);
	int OnCommand(WPARAM wparam, LPARAM lparam);
	virtual status_t AddTabWnd(HWND *hlist, int *i);
};

#endif
