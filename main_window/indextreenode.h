#ifndef __S2_INDEXTREENODE_H
#define __S2_INDEXTREENODE_H

#include "cruntime.h"
#include "filebase.h"
#include "mem.h"

class CIndexTreeNode{
public:
	CMem m_Name;
	HTREEITEM m_TreeItemHandle;
	CMem m_Path;
    CMem m_Config;
    int m_CurrentUser;
public:
    CIndexTreeNode *parent,*child,*next;
public:
	status_t GetHelpFile(CMem *path);
	status_t SetCurrentUser(int cur);
	int GetCurrentUser();
	bool HasConfig();
	CMem* GetConfig();
	status_t LoadConfig();
	status_t SaveUserCode_Unicode(CFileBase *file);
    status_t GetUserCodePath(CFileBase *path);
    status_t LoadUserCode(CFileBase *code);
    status_t GetDefaultCodePath(CFileBase *path);
    status_t LoadDefaultCode(CFileBase *code);
    status_t GetMainCodePath(CFileBase *path);
    status_t LoadMainCode(CFileBase *code);
    status_t AddChild(CIndexTreeNode *node);
	CIndexTreeNode();
	virtual ~CIndexTreeNode();
	status_t InitBasic();
	status_t Init();
	status_t Destroy();
	status_t Copy(CIndexTreeNode *_p);
	int Comp(CIndexTreeNode *_p);
	status_t Print(CFileBase *_buf);
	CMem* GetName();
	HTREEITEM GetTreeItemHandle();
	CMem* GetPath();
	status_t SetName(CMem* _name);
	status_t SetTreeItemHandle(HTREEITEM _treeitemhandle);
	status_t SetPath(CMem* _path);
	const char* GetNameStr();
	const char* GetPathStr();
	status_t SetName(const char *_name);
	status_t SetPath(const char *_path);
};

#endif
