#ifndef __S2_INDEXTREE_H
#define __S2_INDEXTREE_H

#include "cruntime.h"
#include "filebase.h"
#include "indextreenode.h"
#include "comnctls.h"

class CIndexTree{
public:
	CIndexTreeNode *m_Root;
public:
	status_t SortTree();
	status_t SortTreeNode(CIndexTreeNode *node);
	CIndexTreeNode* FindNode(HTREEITEM item);
	status_t SyncToTreeView(CTreeView *tree_view);
	static CIndexTreeNode *AddNode(CIndexTreeNode *parent, const char *fullpath);
    static status_t LoadFromFolder(CIndexTreeNode *root,const char *fullpath);
	status_t LoadFromFolder(const char *folder);
	CIndexTree();
	virtual ~CIndexTree();
	status_t InitBasic();
	status_t Init();
	status_t Destroy();
	status_t Copy(CIndexTree *_p);
	int Comp(CIndexTree *_p);
	status_t Print(CFileBase *_buf);
	CIndexTreeNode* GetRoot();
	status_t SetRoot(CIndexTreeNode* _root);
};

#endif
