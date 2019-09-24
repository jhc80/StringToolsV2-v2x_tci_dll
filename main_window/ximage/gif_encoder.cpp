#include "gif_encoder.h"
#include "syslog.h"
#include "mem_tool.h"
#include "ximagegif.h"

CGifEncoder::CGifEncoder()
{
    this->InitBasic();
}

CGifEncoder::~CGifEncoder()
{
    this->Destroy();
}

status_t CGifEncoder::InitBasic()
{
    WEAK_REF_ID_CLEAR();
    this->m_Loops = 0;
    this->m_LocalDispMeth = 0;
    this->m_LocalColorMap = 0;
    this->m_IsFirstFrame = 0;
    this->m_File = NULL;
    this->m_TmpFile.InitBasic();
    memset(m_comment,0,sizeof(m_comment));
    m_disposal_method = 0;
    return OK;
}

status_t CGifEncoder::Init()
{
    this->InitBasic();
    WEAK_REF_ID_INIT();
    this->m_TmpFile.Init();
    return OK;
}

status_t CGifEncoder::Destroy()
{
    this->m_TmpFile.Destroy();
    this->InitBasic();
    return OK;
}

int CGifEncoder::GetLoops()
{
    return m_Loops;
}

bool CGifEncoder::GetLocalDispMeth()
{
    return m_LocalDispMeth;
}

bool CGifEncoder::GetLocalColorMap()
{
    return m_LocalColorMap;
}

bool CGifEncoder::GetIsFirstFrame()
{
    return m_IsFirstFrame;
}

CFileBase* CGifEncoder::GetFile()
{
    return m_File;
}

CFile* CGifEncoder::GetTmpFile()
{
    return &m_TmpFile;
}

status_t CGifEncoder::SetLoops(int _loops)
{
    this->m_Loops = _loops;
    return OK;
}

status_t CGifEncoder::SetLocalDispMeth(bool _localdispmeth)
{
    this->m_LocalDispMeth = _localdispmeth;
    return OK;
}

status_t CGifEncoder::SetLocalColorMap(bool _localcolormap)
{
    this->m_LocalColorMap = _localcolormap;
    return OK;
}

status_t CGifEncoder::SetIsFirstFrame(bool _isfirstframe)
{
    this->m_IsFirstFrame = _isfirstframe;
    return OK;
}

status_t CGifEncoder::SetFile(CFileBase *_file)
{
    this->m_File = _file;
    return OK;
}

status_t CGifEncoder::SetComment(const char *comment)
{
    ASSERT(comment);
    crt_strncpy(m_comment,comment,sizeof(m_comment)-1);
    m_comment[sizeof(m_comment)-1] = 0;
    return OK;
}
status_t CGifEncoder::SetDisposalMethod(BYTE dm)
{
    m_disposal_method = dm;
    return OK;
}

status_t CGifEncoder::Begin(CFileBase *file)
{
    ASSERT(file);
    m_IsFirstFrame = true;
    return this->SetFile(file);
}

status_t CGifEncoder::Begin(const char *filename)
{
    ASSERT(filename);

    m_TmpFile.Destroy();
    m_TmpFile.Init();
    if(!m_TmpFile.OpenFile(filename,"wb+"))
    {
        XLOG(LOG_MODULE_USER,LOG_LEVEL_ERROR,
            "open file %s fail.",filename
        );
        return ERROR;
    }

    m_IsFirstFrame = true;
    this->SetFile(&m_TmpFile);
    return OK;
}

status_t CGifEncoder::End()
{
    ASSERT(m_File);
    m_File->Putc(';');
    m_TmpFile.CloseFile();
    return OK;
}
void CGifEncoder::EncodeComment()
{
    unsigned long n = (unsigned long) strlen(m_comment);
    
    if (n>255) n=255;
  
    if (n) {
        m_File->Putc('!');  //extension code:
        m_File->Putc((char)254);    //comment extension
        m_File->Putc((BYTE)n);  //size of comment
        m_File->Write(m_comment,n);
        m_File->Putc(0);    //block terminator
    }
}

status_t CGifEncoder::AddFrame(CxImage *img)
{
    ASSERT(img);
    ASSERT(m_File);
    ASSERT(img->IsValid());
    ASSERT(img->GetNumColors() != 0);

    if(m_IsFirstFrame)
    {
        CxImageGIF ghost;        
        ghost.Ghost(img);
        ghost.EncodeHeader(m_File);
        
        if (m_Loops!=1)
        {
            ghost.SetLoops(max(0,m_Loops-1));
            ghost.EncodeLoopExtension(m_File);
        }
        
        if (m_LocalDispMeth) 
        {
            ghost.EncodeExtension(m_File);
        } 
        else 
        {
            BYTE dm = ghost.GetDisposalMethod();
            ghost.SetDisposalMethod(m_disposal_method);
            ghost.EncodeExtension(m_File);
            ghost.SetDisposalMethod(dm);
        }
        
        this->EncodeComment();
        
        ghost.EncodeBody(m_File,FALSE);

        m_IsFirstFrame = false;
    }
    else
    {
        CxImageGIF ghost;   
        ghost.Ghost(img);        
        if (m_LocalDispMeth) 
        {
            ghost.EncodeExtension(m_File);
        }
        else 
        {
            BYTE dm = ghost.GetDisposalMethod();
            ghost.SetDisposalMethod(m_disposal_method);
            ghost.EncodeExtension(m_File);
            ghost.SetDisposalMethod(dm);
        }       
        
        ghost.EncodeBody(m_File,m_LocalColorMap);   
    }
    return OK;
}
