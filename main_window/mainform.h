// MainForm.h: interface for the CMainForm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFORM_H__52483360_52D1_4193_ADDF_F85BF4919F98__INCLUDED_)
#define AFX_MAINFORM_H__52483360_52D1_4193_ADDF_F85BF4919F98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wnd.h"
#include "comnctls.h"
#include "mem_tool.h"
#include "wndsplit.h"
#include "wndpagehost.h"
#include "pagemanager.h"
#include "wndembeddedui.h"

class CMainForm : public CWnd{
public:
	CWndSplit *m_WndSplit_H;
	CWndSplit *m_WndSplit_V;
	CStatusBar *m_StatusBar;
	CTreeView *m_TreeView;
    CWndPageHost *m_WndPageHost;
    CPageManager *m_PageManager;
	CWnd *m_WndRight;
	CWndEmbeddedUI *m_WndEmbeddedUI;
	int m_EmbeddedUIWindowHeight;
	//////////////////////////////////
    CMenu *menu_file;
    CMenu *mitem_open;
    CMenu *mitem_save_as;
    CMenu *mitem_property;
    CMenu *mitem_exit;
    CMenu *menu_bar;
    CMenu *menu_edit;
    CMenu *mitem_cut;
    CMenu *mitem_copy;
    CMenu *mitem_paste;
    CMenu *mitem_delete;
    CMenu *mitem_clear;
    CMenu *mitem_select_all;
    CMenu *menu_help;
    CMenu *mitem_help;
    CMenu *mitem_help_lua_doc;
    CMenu *mitem_help_lua_pattern;
    CMenu *mitem_about;
    CMenu *menu_vm;
    CMenu *mitem_start;
    CMenu *mitem_stop;
    CMenu *menu_view;
    CMenu *mitem_text_window;
    CMenu *mitem_image_window;
	CMenu *mitem_find;
    //////////////////////////////////
    CPopupMenu *menu_context;
    CMenu *mitem_r_run;
    CMenu *mitem_r_attrib;
    CMenu *mitem_r_open_folder;
    CMenu *mitem_r_help;

public:
	status_t OnShowContextMenu(MSG *msg);
	status_t HideEmbeddedUIWindow();
	status_t ShowEmbeddedUIWindow(int height);
	status_t OnWndSplitVEvent();
	status_t OnWndSplitHEvent();
	status_t SwitchPage_ThreadSafe(const wchar_t *name);
	status_t SwitchToPageImage();
	status_t SwitchToPageText();
	int OnLoad();
	int OnSaveAs();
	status_t SetStatusText(int part,const char *szFormat,...);
	status_t ShowPropertyWindow();
	CTreeView* GetTreeView();
    int CreateMenu();
	status_t SwitchPage(const wchar_t *name);
	int OnUnknown(WPARAM wparam,LPARAM lparam);
	int PreTransMsg(MSG *msg);
	LRESULT ProcessAllMsg(UINT message, WPARAM wparam, LPARAM lparam);
    CMainForm();
    virtual ~CMainForm();
    int Init();
    int Destroy();
    int Copy(CMainForm *p);
    int Comp(CMainForm *p);
    int Print();
	int InitBasic();
	int OnClose(WPARAM wparam,LPARAM lparam);
	int OnPaint(WPARAM wparam,LPARAM lparam);
	int OnCreate(WPARAM wparam,LPARAM lparam);
	int OnSize(WPARAM wparam,LPARAM lparam);
	int OnCommand(WPARAM wparam,LPARAM lparam);
	int OnNotify(WPARAM wparam,LPARAM lparam);
	int OnLButtonDown(WPARAM wparam,LPARAM lparam);
	int OnLButtonUp(WPARAM wparam,LPARAM lparam);
	int OnRButtonDown(WPARAM wparam,LPARAM lparam);
	int OnRButtonUp(WPARAM wparam,LPARAM lparam);
	int OnScroll(WPARAM wparam,LPARAM lparam);
	int OnMouseMove(WPARAM wparam,LPARAM lparam);
	int OnChar(WPARAM wparam,LPARAM lparam);
	int OnKeyDown(WPARAM wparam,LPARAM lparam);
	int OnPosChanged(WPARAM wparam,LPARAM lparam);
};

#endif // !defined(AFX_MAINFORM_H__52483360_52D1_4193_ADDF_F85BF4919F98__INCLUDED_)
