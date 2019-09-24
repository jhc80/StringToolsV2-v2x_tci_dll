#ifndef __WNDSEARCH_H
#define __WNDSEARCH_H

#include "wnd.h"
#include "comnctls.h"
#include "mem.h"

class CWndSearch:public CWnd{
public:	
    static RECT saved_rect;

	CStatic *st_1;
	CEditBox *eb_text;
	CButton *pb_next;
	CCheckBox *ckb_case_sensitive;
	CGroupBox *gp_1;
	CRadioBox *rb_up;
	CRadioBox *rb_down;
	CButton *pb_cancel;

	CMem m_TmpText;
public:
	status_t Find();
	CWndSearch();
	virtual ~CWndSearch();
	int Init();
	int Destroy();
	int InitBasic();
	int OnCreate(WPARAM wparam, LPARAM lparam);
	int OnClose(WPARAM wparam, LPARAM lparam);
	int OnSize(WPARAM wparam, LPARAM lparam);
	int OnCommand(WPARAM wparam, LPARAM lparam);
	int PreTransMsg(MSG *msg);
};

#endif
