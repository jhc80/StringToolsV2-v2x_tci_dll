#ifndef __S2_PAGE_H
#define __S2_PAGE_H

#include "cruntime.h"
#include "filebase.h"
#include "wnd.h"
#include "mem.h"

class CPage:public CWnd{
public:
	CMem m_Name;
	int m_VirtualWidth;
	int m_VirtualHeight;
	int m_CurHorzPos;
	int m_CurVertPos;
public:
	virtual status_t OnEnter();
	virtual status_t OnExit();
	virtual status_t AddTabWnd(HWND *hlist, int *i);
	status_t SetPageSize(int w,int h);
	CPage();
	virtual ~CPage();
	status_t InitBasic();
	status_t Init();
	status_t Destroy();
	CMem* GetName();
	int GetVirtualWidth();
	int GetVirtualHeight();
	status_t SetName(CMem* _name);
	const wchar_t* GetNameStr();
	status_t SetName(const wchar_t *_name);
	int GetCurHorzPos();
	int GetCurVertPos();
	status_t SetCurHorzPos(int _curhorzpos);
	status_t SetCurVertPos(int _curvertpos);
};

#endif
