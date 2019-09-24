#include "webcamera.h"
#include "syslog.h"
#include "wnd.h"
#include "mem_tool.h"

#pragma comment(lib,"dshowLib\\quartz.lib")
#pragma comment(lib,"dshowLib\\ddraw.lib")
#pragma comment(lib,"dshowLib\\strmiids.lib")
#pragma comment(lib,"dshowLib\\strmbasd.lib")

#define MAX_FB_SIZE (1024*1024*4)

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

class CWndVideoCommand:public CWnd{
public:
	CWebCamera *iHost;
public:
	CWndVideoCommand();
	virtual ~CWndVideoCommand();
	int Init();
	int Destroy();
	int InitBasic();
	int OnCreate(WPARAM wparam, LPARAM lparam);
	int OnClose(WPARAM wparam, LPARAM lparam);
	int OnCommand(WPARAM wparam, LPARAM lparam);
	int OnLButtonDown(WPARAM wparam, LPARAM lparam);
	int OnLButtonUp(WPARAM wparam, LPARAM lparam);
	int OnRButtonDown(WPARAM wparam, LPARAM lparam);
	int OnRButtonUp(WPARAM wparam, LPARAM lparam);
	int OnKeyDown(WPARAM wparam, LPARAM lparam);
};

CWndVideoCommand::CWndVideoCommand()
{
	this->InitBasic();
}
CWndVideoCommand::~CWndVideoCommand()
{
	this->Destroy();
}
int CWndVideoCommand::InitBasic()
{    
	CWnd::InitBasic();
	this->iHost = NULL;
	return OK;
}
int CWndVideoCommand::Init()
{
	this->InitBasic();
	CWnd::Init();
	//add your code
	return OK;
}
int CWndVideoCommand::Destroy()
{
	//add your code
	CWnd::Destroy();
	this->InitBasic();
	return OK;
}
int CWndVideoCommand::OnCreate(WPARAM wparam, LPARAM lparam)
{
	return OK;
}
int CWndVideoCommand::OnClose(WPARAM wparam, LPARAM lparam)
{
	return OK;
}
int CWndVideoCommand::OnCommand(WPARAM wparam, LPARAM lparam)
{
	return OK;
}
int CWndVideoCommand::OnLButtonDown(WPARAM wparam, LPARAM lparam)
{
	ASSERT(this->iHost);
	iHost->Callback()->Run(CWebCamera::EVENT_ON_LBUTTON_DOWN);		
	return OK;
}
int CWndVideoCommand::OnLButtonUp(WPARAM wparam, LPARAM lparam)
{
	return OK;
}
int CWndVideoCommand::OnRButtonDown(WPARAM wparam, LPARAM lparam)
{
	return OK;
}
int CWndVideoCommand::OnRButtonUp(WPARAM wparam, LPARAM lparam)
{
	return OK;
}
int CWndVideoCommand::OnKeyDown(WPARAM wparam, LPARAM lparam)
{
	return OK;
}
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

class CSampleGrabberCB : public ISampleGrabberCB 
{
public:
	CWebCamera *iHost;
	void *mParams[32];

public:
	CSampleGrabberCB( )
	{
		this->iHost = NULL;
		memset(mParams,0,sizeof(mParams));
	} 
	
	STDMETHODIMP_(ULONG) AddRef() 
	{
		return 2; 
	}
	
	STDMETHODIMP_(ULONG) Release() 
	{
		return 1; 
	}

	STDMETHODIMP QueryInterface(REFIID riid, void ** ppv)
	{
		if( riid == IID_ISampleGrabberCB || riid == IID_IUnknown )
		{ 
			*ppv = (void *) static_cast<ISampleGrabberCB*> ( this );
			return NOERROR;
		} 
		return E_NOINTERFACE;
	}

	STDMETHODIMP SampleCB( double SampleTime, IMediaSample * pSample )
	{
		return 0;
	}
	
	STDMETHODIMP BufferCB( double dblSampleTime, BYTE * pBuffer, long lBufferSize )
	{
		if(mParams[0] == (void*)1)
		{
			char *fb = (char*)mParams[1];
			ASSERT(fb);
			memcpy(fb,pBuffer,lBufferSize);
			mParams[2] = (void*)lBufferSize; //size
			mParams[0] = (void*)2; //notify complete
		}
		return 0;
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
CWebCamera::CWebCamera()
{
	this->InitBasic();
}
CWebCamera::~CWebCamera()
{
	this->Destroy();
}
status_t CWebCamera::InitBasic()
{
    WEAK_REF_ID_CLEAR();
	this->mGraphBuilder = NULL;
	this->mCaptureGraphBuilder = NULL;
	this->mBaseFilter = NULL;
	this->mMediaControl = NULL;
	this->mVideoWindow = NULL;
	this->mSampleGrabber = NULL;
	this->mVideoInfo = NULL;
	this->mSampleGrabberCB = NULL;
	this->mFrameBuffer = NULL;
	this->mWndVideoCmd = NULL;
	this->mCallback = NULL;
	return OK;
}
status_t CWebCamera::Init()
{
	this->InitBasic();
    WEAK_REF_ID_INIT();

	HRESULT hr;
	
	NEW(mCallback,CClosure);
	mCallback->Init();

	NEW(mWndVideoCmd,CWndVideoCommand);
	mWndVideoCmd->Init();
	mWndVideoCmd->MoveWindow(0,0,100,100);
	mWndVideoCmd->SetText(L"cmd window");
	mWndVideoCmd->SetParent(0);
	mWndVideoCmd->SetStyle(0);
	mWndVideoCmd->Create();
	mWndVideoCmd->iHost = this;

	NEW(this->mSampleGrabberCB,CSampleGrabberCB);

	MALLOC(this->mVideoInfo,VIDEOINFOHEADER,1);
	memset(this->mVideoInfo,0,sizeof(VIDEOINFOHEADER));

	hr=CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&this->mGraphBuilder);
	ASSERT(SUCCEEDED(hr) && mGraphBuilder);
	
	hr = CoCreateInstance (CLSID_CaptureGraphBuilder2 , NULL, CLSCTX_INPROC,IID_ICaptureGraphBuilder2, (void **) &this->mCaptureGraphBuilder);
	ASSERT(SUCCEEDED(hr) && mCaptureGraphBuilder);
	
	hr = this->mCaptureGraphBuilder->SetFiltergraph(this->mGraphBuilder);
	ASSERT(SUCCEEDED(hr));

	hr = mGraphBuilder->QueryInterface(IID_IMediaControl, (void **)&this->mMediaControl);
	ASSERT(SUCCEEDED(hr) && mMediaControl);

	hr = mGraphBuilder->QueryInterface(IID_IVideoWindow, (void **) &this->mVideoWindow);
	ASSERT(SUCCEEDED(hr) && mVideoWindow);

	NEW(this->mFrameBuffer,CMem);
	this->mFrameBuffer->Init();
	this->mFrameBuffer->Malloc(MAX_FB_SIZE);

	return OK;
}

status_t CWebCamera::Destroy()
{
	if(this->mMediaControl)
	{
		this->mMediaControl->Stop();
		this->mMediaControl->Release();
		this->mMediaControl = NULL;
	}

	if(this->mVideoWindow)
	{
		this->mVideoWindow->put_Visible(OAFALSE);
		this->mVideoWindow->put_Owner(NULL);
		this->mVideoWindow->Release();
		this->mVideoWindow = NULL;
	}

	if(this->mBaseFilter)
	{
		this->mBaseFilter->Release();
		this->mBaseFilter = NULL;
	}

	if(this->mCaptureGraphBuilder)
	{
		this->mCaptureGraphBuilder->Release();
		this->mCaptureGraphBuilder = NULL;
	}

	if(this->mGraphBuilder)
	{
		this->mGraphBuilder->Release();
		this->mGraphBuilder = NULL;
	}

	if(this->mSampleGrabber)
	{
		this->mSampleGrabber->Release();
		this->mSampleGrabber = NULL;
	}

	DEL(this->mFrameBuffer);
	DEL(this->mSampleGrabberCB);
	FREE(this->mVideoInfo);
	DEL(this->mWndVideoCmd);
	DEL(mCallback);
	this->InitBasic();
	return OK;
}

status_t CWebCamera::EnumDevices(CClosure *closure)
{
	ASSERT(closure);

	ICreateDevEnum *pCreateDevEnum;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,IID_ICreateDevEnum, (void**)&pCreateDevEnum);
	ASSERT(SUCCEEDED(hr) && pCreateDevEnum);

	CComPtr<IEnumMoniker> pEm;
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&pEm, 0);
	ASSERT(SUCCEEDED(hr) && pEm);

	ULONG cFetched;
	IMoniker *pM;
	pEm->Reset();

	while(pEm->Next(1, &pM, &cFetched)==S_OK)
	{
		IPropertyBag *pBag;
		hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);		
		if(SUCCEEDED(hr)) 
		{
			VARIANT var;
			var.vt = VT_BSTR;
			hr = pBag->Read(L"FriendlyName", &var, NULL);
			if (SUCCEEDED(hr)) 
			{
				TCHAR str[2048]; 
				WideCharToMultiByte(CP_ACP,0,var.bstrVal, -1, str, 2048, NULL, NULL);

				closure->SetParamPointer(1,this);
				closure->SetParamPointer(2,str);
				closure->SetParamPointer(3,pM);
				closure->Run();
		
				SysFreeString(var.bstrVal);
			}
			pBag->Release();
		}
		pM->Release();
	}
	pCreateDevEnum->Release();
	return OK;
}

status_t CWebCamera::GetAllDeviceNames(CFileBase *list)
{
	ASSERT(list);

	BEGIN_CLOSURE(on_enum)
	{
		CLOSURE_PARAM_PTR(CFileBase*,list,10);
		CLOSURE_PARAM_PTR(char*,str,2);
		
		list->Puts(str);
		list->Puts("\r\n");
		return OK;
	}
	END_CLOSURE(on_enum);

	on_enum.SetParamPointer(10,list);
	this->EnumDevices(&on_enum);
	return OK;
}

status_t CWebCamera::SetActiveDevice(int index)
{
	BEGIN_CLOSURE(on_enum)
	{
		CLOSURE_PARAM_INT(index,10);
		CLOSURE_PARAM_INT(counter,11);

		CLOSURE_PARAM_PTR(CWebCamera*,self,1);
		CLOSURE_PARAM_PTR(IMoniker*,pM,3);

		if(counter == index)
		{
			HRESULT hr = pM->BindToObject(0,0,IID_IBaseFilter,(void**)(&self->mBaseFilter));
			ASSERT(SUCCEEDED(hr) && self->mBaseFilter);		
			closure->SetParamInt(12,OK);
		}

		closure->SetParamInt(12,counter+1);
		return OK;
	}
	END_CLOSURE(on_enum);


	on_enum.SetParamInt(10,index);
	on_enum.SetParamInt(11,0); //counter
	on_enum.SetParamInt(12,ERROR); //return value

	this->EnumDevices(&on_enum);

	status_t ret = on_enum.GetParamInt(12);
	ASSERT(ret == OK);

	HRESULT hr = this->mGraphBuilder->AddFilter(this->mBaseFilter, L"Capture Filter");
	ASSERT(SUCCEEDED(hr));

	ASSERT(this->mSampleGrabber == NULL);
	hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER,IID_ISampleGrabber, (void**)&this->mSampleGrabber);
	ASSERT(SUCCEEDED(hr) && mSampleGrabber);

	CComQIPtr< IBaseFilter, &IID_IBaseFilter > pGrabBase( mSampleGrabber );
	AM_MEDIA_TYPE mt; 
	ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
	mt.majortype = MEDIATYPE_Video;
	mt.subtype = MEDIASUBTYPE_RGB24;
	
	hr = mSampleGrabber->SetMediaType(&mt);
	ASSERT(SUCCEEDED(hr));
	
	hr = this->mGraphBuilder->AddFilter( pGrabBase, L"Grabber" );
	ASSERT(SUCCEEDED(hr));

	hr = this->mCaptureGraphBuilder->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,this->mBaseFilter,pGrabBase,NULL);
	if( FAILED( hr ) )
		hr = this->mCaptureGraphBuilder->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video,this->mBaseFilter,pGrabBase,NULL);
	ASSERT(SUCCEEDED(hr));

	hr = this->mSampleGrabber->GetConnectedMediaType( &mt );
	ASSERT(SUCCEEDED(hr));

	memcpy(this->mVideoInfo,mt.pbFormat,sizeof(VIDEOINFOHEADER));
	FreeMediaType(&mt);

	hr = this->mSampleGrabber->SetBufferSamples( FALSE );
	ASSERT(SUCCEEDED(hr));
	hr = this->mSampleGrabber->SetOneShot( FALSE );
	ASSERT(SUCCEEDED(hr));
	hr = this->mSampleGrabber->SetCallback( this->mSampleGrabberCB, 1 );
	ASSERT(SUCCEEDED(hr));

	return OK;
}

status_t CWebCamera::SetHostWindow(HWND hostWnd)
{
	ASSERT(this->mVideoWindow);
	HRESULT hr;

	hr = this->mVideoWindow->put_Owner((OAHWND)hostWnd);
	ASSERT(SUCCEEDED(hr));
	hr = this->mVideoWindow->put_WindowStyle(WS_CHILD);
	ASSERT(SUCCEEDED(hr));
	hr = this->mVideoWindow->put_MessageDrain((OAHWND)this->mWndVideoCmd->hwnd);
	ASSERT(SUCCEEDED(hr));

	RECT r;
	::GetClientRect(hostWnd,&r);
	this->MoveVideoWindow(0,0,r.right,r.bottom);
	hr = this->mVideoWindow->put_Visible(OATRUE);
	ASSERT(SUCCEEDED(hr));
	return OK;
}

status_t CWebCamera::MoveVideoWindow(int l, int t, int w, int h)
{
	ASSERT(this->mVideoWindow);
	HRESULT hr;
	if(w <= 0)return ERROR;
	if(h <= 0)return ERROR;
	hr = this->mVideoWindow->SetWindowPosition(l,t,w,h);
	ASSERT(SUCCEEDED(hr));
	return OK;
}

status_t CWebCamera::MoveVideoWindow(RECT r)
{
	return this->MoveVideoWindow(r.left,r.top,r.right-r.left,r.bottom-r.top);
}

status_t CWebCamera::FreeMediaType(AM_MEDIA_TYPE *mt)
{
	ASSERT(mt);

	if (mt->cbFormat != 0) 
	{
		CoTaskMemFree((PVOID)mt->pbFormat);
		// Strictly unnecessary but tidier
		mt->cbFormat = 0;
		mt->pbFormat = NULL;
	}
	if (mt->pUnk != NULL) 
	{
		mt->pUnk->Release();
		mt->pUnk = NULL;
	}

	return OK;
}

status_t CWebCamera::Start()
{
	ASSERT(this->mMediaControl);
	HRESULT hr = this->mMediaControl->Run();
	ASSERT(SUCCEEDED(hr));
	return OK;
}

status_t CWebCamera::Stop()
{
	ASSERT(this->mMediaControl);
	HRESULT hr = this->mMediaControl->Stop();
	ASSERT(SUCCEEDED(hr));
	return OK;	
}

status_t CWebCamera::SetMessageDrainWindow(HWND hwnd)
{
	ASSERT(this->mVideoWindow);
	HRESULT hr;
	hr = this->mVideoWindow->put_MessageDrain((OAHWND)hwnd);
	ASSERT(SUCCEEDED(hr));
	return OK;
}

status_t CWebCamera::TakePictureRaw(int offset)
{
	void **p =this->mSampleGrabberCB->mParams;
	ASSERT(p[0] == 0);
	p[1] = this->mFrameBuffer->GetRawBuf()+offset;
	p[0] = (void*)1; //start

	for(int i = 0; i < 100; i++)
	{
		if(p[0] == (void*)2)
		{			
			p[0] = 0; //can be started again
			return OK;
		}
		crt_msleep(20);
	}

	return ERROR;
}

CMem *CWebCamera::GetFrameData()
{
	return this->mFrameBuffer;
}

status_t CWebCamera::TakePictureBmp()
{
	int w = this->GetPixelWidth();
	int h = this->GetPixelHeight();

	CMem *mem = this->mFrameBuffer;
	mem->SetSize(0);
	mem->Putc('B');
	mem->Putc('M');

	DWORD t;
	int bits = 24,header_size = 54;
	int size = w*h*(bits >> 3);
	t = header_size+size;mem->Write(&t,4);	
	t = 0; mem->Write(&t,4);
	t = 0x36; mem->Write(&t,4);
	t = 0x28; mem->Write(&t,4);
	t = w; mem->Write(&t,4);
	t = h; mem->Write(&t,4);
	t = 1; mem->Write(&t,2);
	t = bits;mem->Write(&t,2);
	t = 0; mem->Write(&t,4);
	t = (bits >> 3)*w*h; mem->Write(&t,4);

	//BMP has 54 bytes header
	mem->FillBlock(header_size - mem->GetOffset(),0);
	status_t ret = this->TakePictureRaw(header_size);
	this->mFrameBuffer->SetSize(size + header_size);
	return ret;
}

int CWebCamera::GetPixelWidth()
{
	return this->mVideoInfo->bmiHeader.biWidth;
}

int CWebCamera::GetPixelHeight()
{
	return this->mVideoInfo->bmiHeader.biHeight;
}

status_t CWebCamera::SetVideoWindowVisible(bool v)
{
	ASSERT(this->mVideoWindow);
	this->mVideoWindow->put_Visible(v?OATRUE:OAFALSE);
	return OK;
}

int CWebCamera::GetDeviceNum()
{
	LOCAL_MEM(list);
	LOCAL_MEM(mem);

	this->GetAllDeviceNames(&list);

	int c = 0;
	list.Seek(0);
	while(list.ReadLine(&mem))
	{
		if(mem.C(0) == 0)continue;
		c++;
	}

	return c;
}

status_t CWebCamera::GetDeviceName(int index, CMem *name)
{
	LOCAL_MEM(list);
	LOCAL_MEM(mem);

	name->SetSize(0);

	this->GetAllDeviceNames(&list);

	int c = 0;
	list.Seek(0);
	while(list.ReadLine(&mem))
	{
		if(mem.C(0) == 0)continue;
		if(c == index)
		{
			name->StrCpy(&mem);
			break;
		}
		c++;
	}

	return OK;
}

CClosure* CWebCamera::Callback()
{
	return mCallback;
}

bool CWebCamera::IsValid()
{
	if(!mVideoInfo)
		return false;
	return mVideoInfo->bmiHeader.biWidth > 0 && mVideoInfo->bmiHeader.biHeight > 0;
}
