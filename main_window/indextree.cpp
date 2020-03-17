#include "indextree.h"
#include "syslog.h"
#include "mem_tool.h"
#include "dirmgr.h"
#include "encoder.h"

CIndexTree::CIndexTree()
{
	this->InitBasic();
}
CIndexTree::~CIndexTree()
{
	this->Destroy();
}
status_t CIndexTree::InitBasic()
{
	this->m_Root = 0;
	return OK;
}
status_t CIndexTree::Init()
{
	this->InitBasic();
	return OK;
}
status_t CIndexTree::Destroy()
{
    if(m_Root)
    {
        CIndexTreeNode::Free(m_Root);
        m_Root = NULL;
    }
    
	this->InitBasic();
	return OK;
}
int CIndexTree::Comp(CIndexTree *_p)
{
	ASSERT(_p);
	if(this==_p)return 0;
	return 0;
}
status_t CIndexTree::Copy(CIndexTree *_p)
{
	ASSERT(_p);
	if(this == _p)return OK;
	this->m_Root = _p->m_Root;
	return OK;
}
status_t CIndexTree::Print(CFileBase *_buf)
{
	return OK;
}

CIndexTreeNode* CIndexTree::GetRoot()
{
	return this->m_Root;
}

status_t CIndexTree::SetRoot(CIndexTreeNode* _root)
{
	this->m_Root = _root;
	return OK;
}

status_t CIndexTree::LoadFromFolder(CIndexTreeNode *root,const char *fullpath)
{
    ASSERT(fullpath && root);

    BEGIN_CLOSURE(on_search_dir)
    {
        CLOSURE_PARAM_INT(e,0);
        if(e == CDirMgr::EVENT_BEGIN_DIR)
        {
            CLOSURE_PARAM_PTR(CIndexTreeNode*,root,10);
            CLOSURE_PARAM_PTR(const char*,fullpath,2);            
            CIndexTreeNode *new_node = CIndexTree::AddNode(root,fullpath);
            if(new_node)
            {
                CIndexTree::LoadFromFolder(new_node,fullpath);
            }
        }
        return OK;
    }
    END_CLOSURE(on_search_dir);

    on_search_dir.SetParamPointer(10,root);
    CDirMgr::SearchDir(fullpath,false,&on_search_dir);
    return OK;
}

status_t CIndexTree::LoadFromFolder(const char *folder)
{
    ASSERT(folder);
    LOCAL_MEM(fullpath);
    fullpath.Puts(folder);
    CDirMgr::ToAbsPath(&fullpath);

    ASSERT(m_Root == NULL);

    m_Root = CIndexTree::AddNode(NULL,fullpath.CStr());
    ASSERT(m_Root);
    
    return this->LoadFromFolder(m_Root,fullpath.CStr());
}

CIndexTreeNode *CIndexTree::AddNode(CIndexTreeNode *parent, const char *fullpath)
{
    ASSERT(fullpath);
 
    CIndexTreeNode *node;
    NEW(node,CIndexTreeNode);
    node->Init();    
    node->SetPath(fullpath);
    node->LoadConfig();
    
    if(!node->HasConfig())
    {
        DEL(node);
        return ERROR;
    }

    CMem *config = node->GetConfig();
    ASSERT(config);

    LOCAL_MEM(name);
    config->ReadKeyValue("name",&name);

    node->SetName(&name);

    if(parent)
    {
        parent->AddChild(node);
    }

    return node;
}

static add_to_tree_view(CTreeView *tree_view,HTREEITEM hparent,CIndexTreeNode *parent)
{
    CIndexTreeNode *p = parent->child;
    
    if(p)
        tree_view->SetItemImg(hparent,3);
    else
        tree_view->SetItemImg(hparent,2);  

    LOCAL_MEM(name); 
    while(p)
    {        
        CEncoder::Utf8ToUnicode(p->GetName(),&name);
        HTREEITEM h = tree_view->AddItem(hparent,(wchar_t*)name.CStrW());
        p->SetTreeItemHandle(h);
        add_to_tree_view(tree_view,h,p);
        p = p->next;
    }

    return OK;
}

status_t CIndexTree::SyncToTreeView(CTreeView *tree_view)
{
    ASSERT(tree_view);
    ASSERT(m_Root);

    LOCAL_MEM(name); 
    CEncoder::Utf8ToUnicode(m_Root->GetName(),&name);
    HTREEITEM root = tree_view->AddRoot((wchar_t*)name.CStrW());
    ASSERT(root);
    return add_to_tree_view(tree_view,root,m_Root);
}

static CIndexTreeNode *find_node(CIndexTreeNode *root, HTREEITEM item)
{
    if(root->GetTreeItemHandle() == item)
        return root;

    CIndexTreeNode *p = root->child;

    while(p)
    {
        CIndexTreeNode *n = find_node(p,item);
        if(n && n->GetTreeItemHandle() == item)
            return n;
        p = p->next;
    }
    return NULL;
}

CIndexTreeNode* CIndexTree::FindNode(HTREEITEM item)
{
   return find_node(m_Root,item);
}

status_t CIndexTree::SortTreeNode(CIndexTreeNode *node)
{
    ASSERT(node);

    CIndexTreeNode *p = node->child;
    if(!p)return OK;

    const int MAX_ARRAY_SIZE = 1024;
    CIndexTreeNode *array[MAX_ARRAY_SIZE];

    int len = 0;
    while(p)
    {
        ASSERT(len < MAX_ARRAY_SIZE-1);
        array[len++] = p;
        p = p->next;
    }

    ASSERT(len > 0);
    //Bubble sort       
    CIndexTreeNode *swap;
    for (int i = 0 ; i < len - 1; i++)
    {
        for (int j = 0 ; j < len - i - 1; j++)
        {
            const char *name1 = array[j]->GetNameStr();
            const char *name2 = array[j+1]->GetNameStr();
            ASSERT(name1 && name2);
            if (crt_stricmp(name1,name2) > 0)
            {
                swap       = array[j];
                array[j]   = array[j+1];
                array[j+1] = swap;
            }
        }
    }
    ///////////    
    for(int k = 0; k < len-1; k++)
    {
        array[k]->next = array[k+1];
    }
    array[len-1]->next = NULL;
    node->child = array[0];

    for(int l = 0; l < len; l++)
    {
        this->SortTreeNode(array[l]);
    }

    return OK;
}

status_t CIndexTree::SortTree()
{
    return this->SortTreeNode(m_Root);
}
