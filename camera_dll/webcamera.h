#ifndef __WEBCAMERA_H
#define __WEBCAMERA_H

#include "cruntime.h"

#include <atlbase.h>
typedef unsigned long* DWORD_PTR;
typedef long* LONG_PTR;
#include <dshow.h>
#include <Qedit.h>

#include "mem.h"
#include "memfile.h"
#include "closure.h"

class CSampleGrabberCB;
class CWndVideoCommand;

class CWebCamera{
public:
    WEAK_REF_ID_DEFINE();

public:
	enum{
		EVENT_ON_LBUTTON_DOWN = 1
	};
	
	CClosure *mCallback;
	VIDEOINFOHEADER *mVideoInfo;
    IGraphBuilder *mGraphBuilder;
    ICaptureGraphBuilder2* mCaptureGraphBuilder;
    IBaseFilter* mBaseFilter;
    IMediaControl* mMediaControl;
    IVideoWindow* mVideoWindow;
    ISampleGrabber* mSampleGrabber;	
	CSampleGrabberCB *mSampleGrabberCB;
	CMem *mFrameBuffer;
	CWndVideoCommand *mWndVideoCmd;
public:
	bool IsValid();
	CClosure* Callback();
	status_t GetDeviceName(int index, CMem *name);
	int GetDeviceNum();
	status_t SetVideoWindowVisible(bool v);
	status_t Stop();
	int GetPixelHeight();
	int GetPixelWidth();
	status_t TakePictureBmp();
	CMem* GetFrameData();
	status_t TakePictureRaw(int offset);
	status_t SetMessageDrainWindow(HWND hwnd);
	status_t MoveVideoWindow(RECT r);
	status_t Start();
	status_t FreeMediaType(AM_MEDIA_TYPE *mt);
	status_t MoveVideoWindow(int l, int t, int w, int h);
	status_t SetHostWindow(HWND hostWnd);
	status_t SetActiveDevice(int index);
	status_t GetAllDeviceNames(CFileBase *list);
	status_t EnumDevices(CClosure *closure);
	CWebCamera();
	virtual ~CWebCamera();
	status_t InitBasic();
	status_t Init();
	status_t Destroy();
};

#endif
