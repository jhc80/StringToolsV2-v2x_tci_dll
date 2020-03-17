#include "indextreenode.h"
#include "syslog.h"
#include "mem_tool.h"
#include "memfile.h"
#include "encoder.h"

CIndexTreeNode::CIndexTreeNode()
{
	this->InitBasic();
}
CIndexTreeNode::~CIndexTreeNode()
{
	this->Destroy();
}
status_t CIndexTreeNode::InitBasic()
{
	this->m_Name.InitBasic();
	this->m_TreeItemHandle = 0;
	this->m_Path.InitBasic();
    m_Config.InitBasic();
    m_CurrentUser = 0;
    parent = NULL;
    child = NULL;
    next = NULL;
	return OK;
}
status_t CIndexTreeNode::Init()
{
	this->InitBasic();
	this->m_Name.Init();
	this->m_Path.Init();
    m_Config.Init();
	return OK;
}

status_t CIndexTreeNode::Destroy()
{
    m_Config.Destroy();
	this->m_Name.Destroy();
	this->m_Path.Destroy();
	this->InitBasic();
	return OK;
}
int CIndexTreeNode::Comp(CIndexTreeNode *_p)
{
	ASSERT(_p);
	if(this==_p)return 0;
	return 0;
}
status_t CIndexTreeNode::Copy(CIndexTreeNode *_p)
{
	ASSERT(_p);
	if(this == _p)return OK;
	this->m_Name.Copy(&_p->m_Name);
	this->m_TreeItemHandle = _p->m_TreeItemHandle;
	this->m_Path.Copy(&_p->m_Path);
    m_Config.Copy(&_p->m_Config);
    m_CurrentUser = _p->m_CurrentUser;
	return OK;
}
status_t CIndexTreeNode::Print(CFileBase *_buf)
{
	const char* _str_name = "<null>";
	if(this->m_Name.StrLen() > 0)
		_str_name = m_Name.CStr();
	_buf->Log("Name = %s",_str_name);
	_buf->Log("TreeItemHandle = %x",this->m_TreeItemHandle);
	const char* _str_path = "<null>";
	if(this->m_Path.StrLen() > 0)
		_str_path = m_Path.CStr();
	_buf->Log("Path = %s",_str_path);
	return OK;
}
CMem* CIndexTreeNode::GetName()
{
	return &this->m_Name;
}
HTREEITEM CIndexTreeNode::GetTreeItemHandle()
{
	return this->m_TreeItemHandle;
}
CMem* CIndexTreeNode::GetPath()
{
	return &this->m_Path;
}
const char* CIndexTreeNode::GetNameStr()
{
	return this->m_Name.CStr();
}
const char* CIndexTreeNode::GetPathStr()
{
	return this->m_Path.CStr();
}
status_t CIndexTreeNode::SetName(CMem* _name)
{
	this->m_Name.Copy(_name);
	return OK;
}
status_t CIndexTreeNode::SetTreeItemHandle(HTREEITEM _treeitemhandle)
{
	this->m_TreeItemHandle = _treeitemhandle;
	return OK;
}
status_t CIndexTreeNode::SetPath(CMem* _path)
{
	this->m_Path.Copy(_path);
	return OK;
}
status_t CIndexTreeNode::SetName(const char *_name)
{
	CMem _mem(_name);
	return this->SetName(&_mem);
}

status_t CIndexTreeNode::SetPath(const char *_path)
{
	CMem _mem(_path);
	return this->SetPath(&_mem);
}

status_t CIndexTreeNode::AddChild(CIndexTreeNode *node)
{
    ASSERT(node);

    if(this->child == NULL)
    {
        this->child = node;
        node->next = NULL;
    }
    else
    {
        node->next = this->child;
        this->child = node;
    }
    node->parent = this;
    return OK;
}

status_t CIndexTreeNode::GetUserCodePath(CFileBase *path)
{
    ASSERT(path);
    path->Puts(this->GetPath());
    path->Putc(crt_get_path_splitor());
    path->Printf("user-%d.lua",m_CurrentUser);
    return OK;
}

status_t CIndexTreeNode::LoadUserCode(CFileBase *code)
{
    ASSERT(code);
    LOCAL_MEM(path);
    code->SetSize(0);
    this->GetUserCodePath(&path);
    return code->LoadFile(path.CStr());
}

status_t CIndexTreeNode::GetDefaultCodePath(CFileBase *path)
{
    ASSERT(path);
    path->Puts(this->GetPath());
    path->Putc(crt_get_path_splitor());
    path->Puts("default.lua");
    return OK;
}

status_t CIndexTreeNode::LoadDefaultCode(CFileBase *code)
{
    ASSERT(code);
    LOCAL_MEM(path);
    code->SetSize(0);
    this->GetDefaultCodePath(&path);
    return code->LoadFile(path.CStr());
}

status_t CIndexTreeNode::GetMainCodePath(CFileBase *path)
{
    ASSERT(path);
    path->Puts(this->GetPath());
    path->Putc(crt_get_path_splitor());
    path->Puts("main.lua");
    return OK;
}

status_t CIndexTreeNode::LoadMainCode(CFileBase *code)
{
    ASSERT(code);
    code->SetSize(0);
    LOCAL_MEM(path);
    this->GetMainCodePath(&path);
    return code->LoadFile(path.CStr());
}

status_t CIndexTreeNode::SaveUserCode_Unicode(CFileBase *file)
{
    ASSERT(file);

    CMemFile tmp;
    tmp.Init();
    CEncoder::UnicodeToUtf8(file,&tmp);

    LOCAL_MEM(path);
    this->GetUserCodePath(&path);

    if(tmp.WriteToFile(path.CStr()) < 0)
    {
        LOG("save user code fail.");
        return ERROR;
    }
    
    return OK;
}

status_t CIndexTreeNode::LoadConfig()
{
    ASSERT(m_Config.GetSize() == 0);

    LOCAL_MEM(config_path);
    config_path.Puts(this->GetPath());
    config_path.Putc(crt_get_path_splitor());
    config_path.Puts("config.txt");
    return m_Config.LoadFile(config_path.CStr());
}

CMem* CIndexTreeNode::GetConfig()
{
    return &m_Config;
}

bool CIndexTreeNode::HasConfig()
{
    return m_Config.GetSize() > 0;
}

int CIndexTreeNode::GetCurrentUser()
{
    return m_CurrentUser;
}

status_t CIndexTreeNode::SetCurrentUser(int cur)
{
    m_CurrentUser = cur;
    return OK;
}

status_t CIndexTreeNode::GetHelpFile(CMem *path)
{
    ASSERT(path);
    path->SetSize(0);
    path->Puts(this->GetPath());
    path->Putc(crt_get_path_splitor());
    path->Puts("readme.txt");
    return OK;
}
status_t CIndexTreeNode::Free(CIndexTreeNode *node)
{
    CIndexTreeNode *p , *q;
    
    if(node == NULL)
        return OK;
    
    p = node->child;
    if( p ) q = p->next;
    while(p)
    {
        CIndexTreeNode::Free(p);
        p = q;
        if(q != NULL)
            q = q->next;
    }
    node->Destroy();
    DEL( node );
    return OK;
}