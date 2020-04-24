#include "screenbuffer.h"
#include "syslog.h"
#include "mem_tool.h"
#include "ximagehelper.h"

int32_t rgbquad_to_int32(RGBQUAD r);
RGBQUAD int32_to_rgbquad(int32_t r);

CScreenBuffer::CScreenBuffer()
{
    this->InitBasic();
}

CScreenBuffer::~CScreenBuffer()
{
    this->Destroy();
}

status_t CScreenBuffer::InitBasic()
{
    m_Lock.InitBasic();
    this->m_ImageBuffer.InitBasic();
    return OK;
}

status_t CScreenBuffer::Init()
{
    this->InitBasic();
    m_Lock.Init();
    this->m_ImageBuffer.Init();
    return OK;
}

status_t CScreenBuffer::Destroy()
{
    m_Lock.Destroy();
    this->m_ImageBuffer.Destroy();
    this->InitBasic();
    return OK;
}

status_t CScreenBuffer::Copy(CScreenBuffer *_p)
{
    ASSERT(_p);
    if(this == _p)return OK;

    this->m_ImageBuffer.Copy(&_p->m_ImageBuffer);
    return OK;
}

status_t CScreenBuffer::Comp(CScreenBuffer *_p)
{
    ASSERT(_p);
    if(this == _p)return 0;
    ASSERT(0);
    return 0;
}

status_t CScreenBuffer::Print(CFileBase *_buf)
{
    return OK;
}

CxImage* CScreenBuffer::GetImageBuffer()
{
    return &m_ImageBuffer;
}

status_t CScreenBuffer::Create(int width, int height)
{
    ASSERT((width*height*4) < 512*1024*1024);
    m_ImageBuffer.DestroyAll();
    m_ImageBuffer.Init();
    m_ImageBuffer.Create(width,height,32,0);
    m_ImageBuffer.AlphaCreate();
    return OK;
}

status_t CScreenBuffer::Lock()
{
    return m_Lock.Lock();
}

status_t CScreenBuffer::Unlock()
{
    return m_Lock.Unlock();
}

status_t CScreenBuffer::Resize(int width, int height)
{
    return this->Create(width,height);
}

int CScreenBuffer::GetWidth()
{
    return m_ImageBuffer.GetWidth();
}

int CScreenBuffer::GetHeight()
{
    return m_ImageBuffer.GetHeight();
}

status_t CScreenBuffer::DestroyImageBuffer()
{
    return this->Resize(0,0);
}

status_t CScreenBuffer::Clear(uint32_t color)
{
    RECT r;
    r.left = 0;
    r.top = 0;
    r.right = m_ImageBuffer.GetWidth();
    r.bottom= m_ImageBuffer.GetHeight();
    m_ImageBuffer.FillRect(r,int32_to_rgbquad(color),TRUE);
    return OK;
}

status_t CScreenBuffer::Resample(int neww, int newh)
{
    if(m_ImageBuffer.GetWidth() == neww && m_ImageBuffer.GetHeight() == newh)
    {
        return OK;
    }

    if(m_ImageBuffer.GetWidth() > neww && m_ImageBuffer.GetHeight() > newh)
    {
        m_ImageBuffer.QIShrink(neww,newh,&m_ImageBuffer,false);
    }
    else
    {
        m_ImageBuffer.Resample2(neww,newh,5,5,&m_ImageBuffer,FALSE);
    }
    return OK;
}

status_t CScreenBuffer::DrawImage(CxImage *img, int offx, int offy, int op, bool mix_alpha)
{
    ASSERT(img);
    offy = offy - m_ImageBuffer.GetHeight() + img->GetHeight();
    offx = -offx;
    m_ImageBuffer.Mix(*img,(ImageOpType)op,offx,offy,mix_alpha);
    return OK;
}

status_t CScreenBuffer::LoadFile(const char *fn)
{
	ASSERT(fn);
	return CxImageHelper::LoadImage(fn,&m_ImageBuffer);
}