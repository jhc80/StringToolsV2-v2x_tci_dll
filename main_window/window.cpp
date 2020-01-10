#include "cruntime.h"
#include "resource.h"
#include "wnd.h"
#include "notepad.h"
#include "comnctls.h"
#include "mem_tool.h"
#include "mainform.h"
#include "mem.h"
#include "encoder.h"
#include "winmisc.h"
#include "taskmgr.h"
#include "syslog.h"
#include "globals.h"
#include "mutex.h"

int sys_log_puts_with_nl(int module, int log_level, const char *str, int nl)
{	
	bool redirect = false;
	
	if(g_globals.m_MainLoopRunning)
	{		
		GLOBAL_PAGE_TEXT(page_text);
		
		if(page_text)
		{
			if(page_text->eb_log)
			{
				if(g_globals.IsOnMainThread())
				{
					LOCAL_MEM(mem);
					mem.Puts(str);
					CEncoder::GbToUnicode(&mem);
					page_text->eb_log->Puts((WORD*)mem.CStrW());
					if(nl)page_text->eb_log->Puts(L"\r\n");				
				}
				else
				{
					BEGIN_NEW_CLOSURE(log)
					{
						CLOSURE_PARAM_INT(module,0);
						CLOSURE_PARAM_INT(log_level,1);
						CLOSURE_PARAM_STRING(str,2);
						CLOSURE_PARAM_INT(nl,3);
						sys_log_puts_with_nl(module,log_level,str,nl);
						return OK;
					}
					END_NEW_CLOSURE(log);
					
					log->SetParamInt(0,module);
					log->SetParamInt(1,log_level);
					log->SetParamString(2,str);
					log->SetParamInt(3,nl);

					GLOBAL_MAIN_TASK_RUNNER(runner);
					runner->AddClosure(log,0);
					crt_msleep(10);
				}

				redirect = true;			
			}
		}
	}
	
	if(!redirect)
	{
		LOCAL_MEM(mem);
		mem.Puts(str);
		CEncoder::GbToUnicode(&mem);
		note_pad.Puts((WORD*)mem.CStrW());
		if(nl)note_pad.Puts(L"\r\n");
	}

	return OK;
}

static int _sys_log_puts(int module, int log_level, const char *str)
{
	return sys_log_puts_with_nl(module,log_level,str,false);
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR     lpCmdLine,
                     int       nCmdShow)
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(INITCOMMONCONTROLSEX);
	InitCtrls.dwICC = ICC_LISTVIEW_CLASSES | ICC_TREEVIEW_CLASSES | ICC_UPDOWN_CLASS | ICC_DATE_CLASSES;
    __hinstance = hInstance;
	InitCommonControlsEx(&InitCtrls);
	/////////////////////
	syslog_set_puts_handler(_sys_log_puts);	
	ASSERT(SUCCEEDED(CoInitialize(NULL)));
	CWnd::RegDefWnd();
	g_globals.Init();
	g_globals.MainLoop();
	g_globals.Destroy();
	/////////////////////
	::MessageBeep(MB_ICONEXCLAMATION);
	return 0;
}



