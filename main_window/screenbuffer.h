#ifndef __SCREENBUFFER_H
#define __SCREENBUFFER_H

#include "mem.h"
#include "memfile.h"
#include "ximage.h"
#include "mutex.h"

class CScreenBuffer{
public:
    CxImage m_ImageBuffer;
    CMutex m_Lock;
public:
	status_t DrawImage(CxImage *img, int offx, int offy, int op, bool mix_alpha);
	status_t Resample(int neww, int newh);
	status_t Clear(uint32_t color);
	status_t DestroyImageBuffer();
	int GetHeight();
	int GetWidth();
	status_t Resize(int width, int height);
	status_t Unlock();
	status_t Lock();
	status_t Create(int width, int height);
    CScreenBuffer();
    ~CScreenBuffer();

    status_t InitBasic();
    status_t Init();
    status_t Destroy();

    status_t Copy(CScreenBuffer *_p);
    int Comp(CScreenBuffer *_p);
    status_t Print(CFileBase *_buf);

    CxImage* GetImageBuffer();
};

#endif
