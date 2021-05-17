#ifndef __WNDPROPERTY_H
#define __WNDPROPERTY_H

#include "wnd.h"
#include "comnctls.h"
#include "indextreenode.h"

class CWndProperty:public CWnd{
public:
    static RECT saved_rect;

	CButton *pb_cancel;
	CButton *pb_ok;
	CButton *pb_default;
	CEditBox *eb_code;
	CToolBar *toolbar;
	CTBButton *tbb_load;
	CTBButton *tbb_save;
	CTBButton *tbb_file;
	CTBButton *tbb_path;
    
    CTBButton *tbb_1;
    CTBButton *tbb_2;
    CTBButton *tbb_3;
    CTBButton *tbb_4;
    CTBButton *tbb_5;
    CTBButton *tbb_6;
    CTBButton *tbb_7;
    CTBButton *tbb_8;
    CTBButton *tbb_9;
    CTBButton *tbb_10;

    CTBButton *tbb_help;
    CTBButton *tbb_open_folder;

    CIndexTreeNode *cur_node;
    bool text_changed;
	int can_be_closed;
public:
	status_t OpenTheFolder();
	status_t ChangeCurrentUser(int index);
	status_t OnInsertPathName();
	status_t OnInsertFileName();
	status_t RestoreDefault();
	status_t AutoSave();
	status_t LoadNode(CIndexTreeNode *node);
	int OnSave();
	int OnLoad();
	int OnOK();
	int OnNotify(WPARAM wparam,LPARAM lparam);
    CWndProperty();
    virtual ~CWndProperty();
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