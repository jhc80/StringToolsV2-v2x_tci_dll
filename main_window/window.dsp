# Microsoft Developer Studio Project File - Name="window" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=window - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "window.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "window.mak" CFG="window - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "window - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "window - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "window - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "release"
# PROP Intermediate_Dir "release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "common" /I "platform" /I "dshowInclude" /I "ximage" /I "lua" /I "lualib" /I "idl" /I "messagepeer" /I "share" /I "lexer" /I "websocket" /I "win32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "window - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "release"
# PROP Intermediate_Dir "release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "common" /I "platform" /I "dshowInclude" /I "ximage" /I "lua" /I "lualib" /I "idl" /I "messagepeer" /I "share" /I "lexer" /I "websocket" /I "win32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "window - Win32 Release"
# Name "window - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;h"
# Begin Source File

SOURCE=.\common\basicarray.h
# End Source File
# Begin Source File

SOURCE=.\websocket\bigendian.cpp
# End Source File
# Begin Source File

SOURCE=.\websocket\bigendian.h
# End Source File
# Begin Source File

SOURCE=.\common\callback.cpp
# End Source File
# Begin Source File

SOURCE=.\common\callback.h
# End Source File
# Begin Source File

SOURCE=.\common\callbackmap.cpp
# End Source File
# Begin Source File

SOURCE=.\common\callbackmap.h
# End Source File
# Begin Source File

SOURCE=.\common\closure.cpp
# End Source File
# Begin Source File

SOURCE=.\common\closure.h
# End Source File
# Begin Source File

SOURCE=.\common\closurelist.cpp
# End Source File
# Begin Source File

SOURCE=.\common\closurelist.h
# End Source File
# Begin Source File

SOURCE=.\common\cmdexe.cpp
# End Source File
# Begin Source File

SOURCE=.\common\cmdexe.h
# End Source File
# Begin Source File

SOURCE=.\common\combfile.cpp
# End Source File
# Begin Source File

SOURCE=.\common\combfile.h
# End Source File
# Begin Source File

SOURCE=.\common\commonarray.h
# End Source File
# Begin Source File

SOURCE=.\common\comnctls.cpp
# End Source File
# Begin Source File

SOURCE=.\common\comnctls.h
# End Source File
# Begin Source File

SOURCE=.\config.h
# End Source File
# Begin Source File

SOURCE=.\common\cruntime.c
# End Source File
# Begin Source File

SOURCE=.\common\cruntime.h
# End Source File
# Begin Source File

SOURCE=.\common\dirmgr.cpp
# End Source File
# Begin Source File

SOURCE=.\common\dirmgr.h
# End Source File
# Begin Source File

SOURCE=.\common\encoder.cpp
# End Source File
# Begin Source File

SOURCE=.\common\encoder.h
# End Source File
# Begin Source File

SOURCE=.\common\file.cpp
# End Source File
# Begin Source File

SOURCE=.\common\file.h
# End Source File
# Begin Source File

SOURCE=.\common\filebase.cpp
# End Source File
# Begin Source File

SOURCE=.\common\filebase.h
# End Source File
# Begin Source File

SOURCE=.\fileutils.cpp
# End Source File
# Begin Source File

SOURCE=.\fileutils.h
# End Source File
# Begin Source File

SOURCE=.\ximage\gif_encoder.cpp
# End Source File
# Begin Source File

SOURCE=.\ximage\gif_encoder.h
# End Source File
# Begin Source File

SOURCE=.\globals.cpp
# End Source File
# Begin Source File

SOURCE=.\globals.h
# End Source File
# Begin Source File

SOURCE=.\websocket\httpheader.cpp
# End Source File
# Begin Source File

SOURCE=.\websocket\httpheader.h
# End Source File
# Begin Source File

SOURCE=.\websocket\httppair.cpp
# End Source File
# Begin Source File

SOURCE=.\websocket\httppair.h
# End Source File
# Begin Source File

SOURCE=.\idl\idlclass.cpp
# End Source File
# Begin Source File

SOURCE=.\idl\idlclass.h
# End Source File
# Begin Source File

SOURCE=.\idl\idlclasslist.cpp
# End Source File
# Begin Source File

SOURCE=.\idl\idlclasslist.h
# End Source File
# Begin Source File

SOURCE=.\idl\idlfunction.cpp
# End Source File
# Begin Source File

SOURCE=.\idl\idlfunction.h
# End Source File
# Begin Source File

SOURCE=.\idl\idlfunctionlist.cpp
# End Source File
# Begin Source File

SOURCE=.\idl\idlfunctionlist.h
# End Source File
# Begin Source File

SOURCE=.\idl\idlhint.cpp
# End Source File
# Begin Source File

SOURCE=.\idl\idlhint.h
# End Source File
# Begin Source File

SOURCE=.\idl\idllexer.cpp
# End Source File
# Begin Source File

SOURCE=.\idl\idllexer.h
# End Source File
# Begin Source File

SOURCE=.\idl\idlmodule.cpp
# End Source File
# Begin Source File

SOURCE=.\idl\idlmodule.h
# End Source File
# Begin Source File

SOURCE=.\idl\idlparam.cpp
# End Source File
# Begin Source File

SOURCE=.\idl\idlparam.h
# End Source File
# Begin Source File

SOURCE=.\idl\idlparamlist.cpp
# End Source File
# Begin Source File

SOURCE=.\idl\idlparamlist.h
# End Source File
# Begin Source File

SOURCE=.\idl\idlparser.cpp
# End Source File
# Begin Source File

SOURCE=.\idl\idlparser.h
# End Source File
# Begin Source File

SOURCE=.\idl\idlsentence.cpp
# End Source File
# Begin Source File

SOURCE=.\idl\idlsentence.h
# End Source File
# Begin Source File

SOURCE=.\idl\idlsentencelist.cpp
# End Source File
# Begin Source File

SOURCE=.\idl\idlsentencelist.h
# End Source File
# Begin Source File

SOURCE=.\idl\idltype.cpp
# End Source File
# Begin Source File

SOURCE=.\idl\idltype.h
# End Source File
# Begin Source File

SOURCE=.\idl\idltypelist.cpp
# End Source File
# Begin Source File

SOURCE=.\idl\idltypelist.h
# End Source File
# Begin Source File

SOURCE=.\idl\idlvariable.cpp
# End Source File
# Begin Source File

SOURCE=.\idl\idlvariable.h
# End Source File
# Begin Source File

SOURCE=.\idl\idlvariablelist.cpp
# End Source File
# Begin Source File

SOURCE=.\idl\idlvariablelist.h
# End Source File
# Begin Source File

SOURCE=.\idl\idlword.cpp
# End Source File
# Begin Source File

SOURCE=.\idl\idlword.h
# End Source File
# Begin Source File

SOURCE=.\indextree.cpp
# End Source File
# Begin Source File

SOURCE=.\indextree.h
# End Source File
# Begin Source File

SOURCE=.\indextreenode.cpp
# End Source File
# Begin Source File

SOURCE=.\indextreenode.h
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_capimin.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_capistd.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_ccoefct.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_ccolor.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_cdctmgr.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_chuff.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_chuff.h
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_cinit.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_cmainct.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_cmarker.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_cmaster.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_comapi.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_config.h
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_cparam.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_cphuff.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_cprepct.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_csample.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_ctrans.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_dapimin.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_dapistd.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_datadst.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_datasrc.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_dcoefct.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_dcolor.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_dct.h
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_ddctmgr.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_dhuff.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_dhuff.h
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_dinput.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_dmainct.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_dmarker.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_dmaster.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_dmerge.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_dphuff.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_dpostct.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_dsample.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_dtrans.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_error.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_error.h
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_fdctflt.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_fdctfst.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_fdctint.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_idctflt.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_idctfst.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_idctint.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_idctred.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_include.h
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_int.h
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_lib.h
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_memmgr.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_memnobs.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_memsys.h
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_morecfg.h
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_quant1.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_quant2.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_utils.c
# End Source File
# Begin Source File

SOURCE=.\ximage\jpeg_version.h
# End Source File
# Begin Source File

SOURCE=.\lua\lapi.c
# End Source File
# Begin Source File

SOURCE=.\lua\lapi.h
# End Source File
# Begin Source File

SOURCE=.\lua\lauxlib.c
# End Source File
# Begin Source File

SOURCE=.\lua\lauxlib.h
# End Source File
# Begin Source File

SOURCE=.\lua\lbaselib.c
# End Source File
# Begin Source File

SOURCE=.\lua\lbitlib.c
# End Source File
# Begin Source File

SOURCE=.\lua\lcode.c
# End Source File
# Begin Source File

SOURCE=.\lua\lcode.h
# End Source File
# Begin Source File

SOURCE=.\lua\lcorolib.c
# End Source File
# Begin Source File

SOURCE=.\lua\lctype.c
# End Source File
# Begin Source File

SOURCE=.\lua\lctype.h
# End Source File
# Begin Source File

SOURCE=.\lua\ldblib.c
# End Source File
# Begin Source File

SOURCE=.\lua\ldebug.c
# End Source File
# Begin Source File

SOURCE=.\lua\ldebug.h
# End Source File
# Begin Source File

SOURCE=.\lua\ldo.c
# End Source File
# Begin Source File

SOURCE=.\lua\ldo.h
# End Source File
# Begin Source File

SOURCE=.\lua\ldump.c
# End Source File
# Begin Source File

SOURCE=.\lexer\lexer.cpp
# End Source File
# Begin Source File

SOURCE=.\lexer\lexer.h
# End Source File
# Begin Source File

SOURCE=.\lexer\lexercpp.cpp
# End Source File
# Begin Source File

SOURCE=.\lexer\lexercpp.h
# End Source File
# Begin Source File

SOURCE=.\lexer\lexerjs.cpp
# End Source File
# Begin Source File

SOURCE=.\lexer\lexerjs.h
# End Source File
# Begin Source File

SOURCE=.\lexer\lexerlua.cpp
# End Source File
# Begin Source File

SOURCE=.\lexer\lexerlua.h
# End Source File
# Begin Source File

SOURCE=.\lua\lfunc.c
# End Source File
# Begin Source File

SOURCE=.\lua\lfunc.h
# End Source File
# Begin Source File

SOURCE=.\lua\lgc.c
# End Source File
# Begin Source File

SOURCE=.\lua\lgc.h
# End Source File
# Begin Source File

SOURCE=.\lua\linit.c
# End Source File
# Begin Source File

SOURCE=.\messagepeer\linkrpccommon.h
# End Source File
# Begin Source File

SOURCE=.\lua\liolib.c
# End Source File
# Begin Source File

SOURCE=.\lua\llex.c
# End Source File
# Begin Source File

SOURCE=.\lua\llex.h
# End Source File
# Begin Source File

SOURCE=.\lua\llimits.h
# End Source File
# Begin Source File

SOURCE=.\lua\lmathlib.c
# End Source File
# Begin Source File

SOURCE=.\lua\lmem.c
# End Source File
# Begin Source File

SOURCE=.\lua\lmem.h
# End Source File
# Begin Source File

SOURCE=.\share\load_dll.h
# End Source File
# Begin Source File

SOURCE=.\lua\loadlib.c
# End Source File
# Begin Source File

SOURCE=.\lua\lobject.c
# End Source File
# Begin Source File

SOURCE=.\lua\lobject.h
# End Source File
# Begin Source File

SOURCE=.\lua\lopcodes.c
# End Source File
# Begin Source File

SOURCE=.\lua\lopcodes.h
# End Source File
# Begin Source File

SOURCE=.\lua\loslib.c
# End Source File
# Begin Source File

SOURCE=.\lua\lparser.c
# End Source File
# Begin Source File

SOURCE=.\lua\lparser.h
# End Source File
# Begin Source File

SOURCE=.\lua\lprefix.h
# End Source File
# Begin Source File

SOURCE=.\lua\lstate.c
# End Source File
# Begin Source File

SOURCE=.\lua\lstate.h
# End Source File
# Begin Source File

SOURCE=.\lua\lstring.c
# End Source File
# Begin Source File

SOURCE=.\lua\lstring.h
# End Source File
# Begin Source File

SOURCE=.\lua\lstrlib.c
# End Source File
# Begin Source File

SOURCE=.\lua\ltable.c
# End Source File
# Begin Source File

SOURCE=.\lua\ltable.h
# End Source File
# Begin Source File

SOURCE=.\lua\ltablib.c
# End Source File
# Begin Source File

SOURCE=.\lua\ltm.c
# End Source File
# Begin Source File

SOURCE=.\lua\ltm.h
# End Source File
# Begin Source File

SOURCE=.\lua\lua.c
# End Source File
# Begin Source File

SOURCE=.\lua\lua.h
# End Source File
# Begin Source File

SOURCE=.\win32\lua_button.cpp
# End Source File
# Begin Source File

SOURCE=.\win32\lua_button.h
# End Source File
# Begin Source File

SOURCE=.\win32\lua_edit_box.cpp
# End Source File
# Begin Source File

SOURCE=.\win32\lua_edit_box.h
# End Source File
# Begin Source File

SOURCE=.\win32\lua_hdc.cpp
# End Source File
# Begin Source File

SOURCE=.\win32\lua_hdc.h
# End Source File
# Begin Source File

SOURCE=.\lua_helper.cpp
# End Source File
# Begin Source File

SOURCE=.\lua_helper.h
# End Source File
# Begin Source File

SOURCE=.\lua_print.cpp
# End Source File
# Begin Source File

SOURCE=.\lua_print.h
# End Source File
# Begin Source File

SOURCE=.\win32\lua_window_base.cpp
# End Source File
# Begin Source File

SOURCE=.\win32\lua_window_base.h
# End Source File
# Begin Source File

SOURCE=.\lua\luac.c
# End Source File
# Begin Source File

SOURCE=.\lua\luaconf.h
# End Source File
# Begin Source File

SOURCE=.\lua\lualib.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_app.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_app.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_cfunc.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_cfunc.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_file.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_file.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_filebase.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_filebase.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_filemanager.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_filemanager.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_gifencoder.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_gifencoder.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_idlparser.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_idlparser.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_lexer.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_lexer.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_lexercpp.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_lexercpp.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_lexerlua.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_lexerlua.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_luabutton.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_luabutton.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_luaeditbox.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_luaeditbox.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_luahdc.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_luahdc.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_luawindowbase.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_luawindowbase.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_mem.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_mem.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_memdc.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_memdc.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_memfile.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_memfile.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_messagepeer.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_messagepeer.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_minibson.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_minibson.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_mmapfile.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_mmapfile.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_screen.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_screen.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_serversidepeer.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_serversidepeer.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_stream.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_stream.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_tasktimer.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_tasktimer.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_tcpsocket.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_tcpsocket.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_udpsocket.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_udpsocket.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_websocketmessage.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_websocketmessage.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_websocketserver.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_websocketserver.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_win32.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_win32.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_ximage.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_ximage.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_ximagegif.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_ximagegif.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_ximagehelper.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_ximagehelper.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_xml.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_xml.h
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_xmlnode.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib\lualib_xmlnode.h
# End Source File
# Begin Source File

SOURCE=.\luathread.cpp
# End Source File
# Begin Source File

SOURCE=.\luathread.h
# End Source File
# Begin Source File

SOURCE=.\common\luavm.cpp
# End Source File
# Begin Source File

SOURCE=.\common\luavm.h
# End Source File
# Begin Source File

SOURCE=.\lua\lundump.c
# End Source File
# Begin Source File

SOURCE=.\lua\lundump.h
# End Source File
# Begin Source File

SOURCE=.\lua\lutf8lib.c
# End Source File
# Begin Source File

SOURCE=.\lua\lvm.c
# End Source File
# Begin Source File

SOURCE=.\lua\lvm.h
# End Source File
# Begin Source File

SOURCE=.\lua\lzio.c
# End Source File
# Begin Source File

SOURCE=.\lua\lzio.h
# End Source File
# Begin Source File

SOURCE=.\mainform.cpp
# End Source File
# Begin Source File

SOURCE=.\mainform.h
# End Source File
# Begin Source File

SOURCE=.\common\mem.cpp
# End Source File
# Begin Source File

SOURCE=.\common\mem.h
# End Source File
# Begin Source File

SOURCE=.\common\mem_tool.c
# End Source File
# Begin Source File

SOURCE=.\common\mem_tool.h
# End Source File
# Begin Source File

SOURCE=.\common\memdc.cpp
# End Source File
# Begin Source File

SOURCE=.\common\memdc.h
# End Source File
# Begin Source File

SOURCE=.\common\memfile.cpp
# End Source File
# Begin Source File

SOURCE=.\common\memfile.h
# End Source File
# Begin Source File

SOURCE=.\common\memstk.cpp
# End Source File
# Begin Source File

SOURCE=.\common\memstk.h
# End Source File
# Begin Source File

SOURCE=.\messagepeer\messagepeer.cpp
# End Source File
# Begin Source File

SOURCE=.\messagepeer\messagepeer.h
# End Source File
# Begin Source File

SOURCE=.\common\minibson.cpp
# End Source File
# Begin Source File

SOURCE=.\common\minibson.h
# End Source File
# Begin Source File

SOURCE=.\common\minitask.cpp
# End Source File
# Begin Source File

SOURCE=.\common\minitask.h
# End Source File
# Begin Source File

SOURCE=.\common\misc.c
# End Source File
# Begin Source File

SOURCE=.\common\misc.h
# End Source File
# Begin Source File

SOURCE=.\common\mmapfile.cpp
# End Source File
# Begin Source File

SOURCE=.\common\mmapfile.h
# End Source File
# Begin Source File

SOURCE=.\common\mutex.cpp
# End Source File
# Begin Source File

SOURCE=.\common\mutex.h
# End Source File
# Begin Source File

SOURCE=.\common\notapad.cpp
# End Source File
# Begin Source File

SOURCE=.\common\notepad.h
# End Source File
# Begin Source File

SOURCE=.\common\page.cpp
# End Source File
# Begin Source File

SOURCE=.\common\page.h
# End Source File
# Begin Source File

SOURCE=.\pageimage.cpp
# End Source File
# Begin Source File

SOURCE=.\pageimage.h
# End Source File
# Begin Source File

SOURCE=.\common\pagemanager.cpp
# End Source File
# Begin Source File

SOURCE=.\common\pagemanager.h
# End Source File
# Begin Source File

SOURCE=.\pagetext.cpp
# End Source File
# Begin Source File

SOURCE=.\pagetext.h
# End Source File
# Begin Source File

SOURCE=.\common\partfile.cpp
# End Source File
# Begin Source File

SOURCE=.\common\partfile.h
# End Source File
# Begin Source File

SOURCE=.\messagepeer\peercommon.h
# End Source File
# Begin Source File

SOURCE=.\messagepeer\peerglobals.cpp
# End Source File
# Begin Source File

SOURCE=.\messagepeer\peerglobals.h
# End Source File
# Begin Source File

SOURCE=.\messagepeer\peermessage.cpp
# End Source File
# Begin Source File

SOURCE=.\messagepeer\peermessage.h
# End Source File
# Begin Source File

SOURCE=.\messagepeer\peermessagestk.cpp
# End Source File
# Begin Source File

SOURCE=.\messagepeer\peermessagestk.h
# End Source File
# Begin Source File

SOURCE=.\messagepeer\peerproxy.cpp
# End Source File
# Begin Source File

SOURCE=.\messagepeer\peerproxy.h
# End Source File
# Begin Source File

SOURCE=.\messagepeer\peerproxymanager.cpp
# End Source File
# Begin Source File

SOURCE=.\messagepeer\peerproxymanager.h
# End Source File
# Begin Source File

SOURCE=.\messagepeer\peerproxystk.cpp
# End Source File
# Begin Source File

SOURCE=.\messagepeer\peerproxystk.h
# End Source File
# Begin Source File

SOURCE=.\messagepeer\peerservicebase.cpp
# End Source File
# Begin Source File

SOURCE=.\messagepeer\peerservicebase.h
# End Source File
# Begin Source File

SOURCE=.\ximage\png_conf.h
# End Source File
# Begin Source File

SOURCE=.\ximage\png_error.c
# End Source File
# Begin Source File

SOURCE=.\ximage\png_gccrd.c
# End Source File
# Begin Source File

SOURCE=.\ximage\png_get.c
# End Source File
# Begin Source File

SOURCE=.\ximage\png_lib.c
# End Source File
# Begin Source File

SOURCE=.\ximage\png_lib.h
# End Source File
# Begin Source File

SOURCE=.\ximage\png_mem.c
# End Source File
# Begin Source File

SOURCE=.\ximage\png_pread.c
# End Source File
# Begin Source File

SOURCE=.\ximage\png_read.c
# End Source File
# Begin Source File

SOURCE=.\ximage\png_rio.c
# End Source File
# Begin Source File

SOURCE=.\ximage\png_rtran.c
# End Source File
# Begin Source File

SOURCE=.\ximage\png_rutil.c
# End Source File
# Begin Source File

SOURCE=.\ximage\png_set.c
# End Source File
# Begin Source File

SOURCE=.\ximage\png_trans.c
# End Source File
# Begin Source File

SOURCE=.\ximage\png_vcrd.c
# End Source File
# Begin Source File

SOURCE=.\ximage\png_wio.c
# End Source File
# Begin Source File

SOURCE=.\ximage\png_write.c
# End Source File
# Begin Source File

SOURCE=.\ximage\png_wtran.c
# End Source File
# Begin Source File

SOURCE=.\ximage\png_wutil.c
# End Source File
# Begin Source File

SOURCE=.\printbuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\printbuffer.h
# End Source File
# Begin Source File

SOURCE=.\messagepeer\ptrhashtable.cpp
# End Source File
# Begin Source File

SOURCE=.\messagepeer\ptrhashtable.h
# End Source File
# Begin Source File

SOURCE=.\common\rect.cpp
# End Source File
# Begin Source File

SOURCE=.\common\rect.h
# End Source File
# Begin Source File

SOURCE=.\common\refcnt.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\resource.rc
# End Source File
# Begin Source File

SOURCE=.\screenbuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\screenbuffer.h
# End Source File
# Begin Source File

SOURCE=.\messagepeer\serversidepeer.cpp
# End Source File
# Begin Source File

SOURCE=.\messagepeer\serversidepeer.h
# End Source File
# Begin Source File

SOURCE=.\websocket\sha1.c
# End Source File
# Begin Source File

SOURCE=.\websocket\sha1.h
# End Source File
# Begin Source File

SOURCE=.\websocket\sha1calculator.cpp
# End Source File
# Begin Source File

SOURCE=.\websocket\sha1calculator.h
# End Source File
# Begin Source File

SOURCE=.\messagepeer\socketreaderwriter.cpp
# End Source File
# Begin Source File

SOURCE=.\messagepeer\socketreaderwriter.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\common\stream.cpp
# End Source File
# Begin Source File

SOURCE=.\common\stream.h
# End Source File
# Begin Source File

SOURCE=.\common\syslog.c
# End Source File
# Begin Source File

SOURCE=.\common\syslog.h
# End Source File
# Begin Source File

SOURCE=.\messagepeer\tasklinkrpc.cpp
# End Source File
# Begin Source File

SOURCE=.\messagepeer\tasklinkrpc.h
# End Source File
# Begin Source File

SOURCE=.\messagepeer\tasklinkrpcreader.cpp
# End Source File
# Begin Source File

SOURCE=.\messagepeer\tasklinkrpcreader.h
# End Source File
# Begin Source File

SOURCE=.\messagepeer\tasklinkrpcwriter.cpp
# End Source File
# Begin Source File

SOURCE=.\messagepeer\tasklinkrpcwriter.h
# End Source File
# Begin Source File

SOURCE=.\common\taskmgr.cpp
# End Source File
# Begin Source File

SOURCE=.\common\taskmgr.h
# End Source File
# Begin Source File

SOURCE=.\messagepeer\taskpeerclient.cpp
# End Source File
# Begin Source File

SOURCE=.\messagepeer\taskpeerclient.h
# End Source File
# Begin Source File

SOURCE=.\messagepeer\taskpeerserver.cpp
# End Source File
# Begin Source File

SOURCE=.\messagepeer\taskpeerserver.h
# End Source File
# Begin Source File

SOURCE=.\common\taskrunner.cpp
# End Source File
# Begin Source File

SOURCE=.\common\taskrunner.h
# End Source File
# Begin Source File

SOURCE=.\messagepeer\tasktcpacceptor.cpp
# End Source File
# Begin Source File

SOURCE=.\messagepeer\tasktcpacceptor.h
# End Source File
# Begin Source File

SOURCE=.\messagepeer\tasktcpconnector.cpp
# End Source File
# Begin Source File

SOURCE=.\messagepeer\tasktcpconnector.h
# End Source File
# Begin Source File

SOURCE=.\common\tasktimer.cpp
# End Source File
# Begin Source File

SOURCE=.\common\tasktimer.h
# End Source File
# Begin Source File

SOURCE=.\websocket\taskwebsocketserver.cpp
# End Source File
# Begin Source File

SOURCE=.\websocket\taskwebsocketserver.h
# End Source File
# Begin Source File

SOURCE=.\common\tcp.cpp
# End Source File
# Begin Source File

SOURCE=.\common\tcp.h
# End Source File
# Begin Source File

SOURCE=.\common\thread.cpp
# End Source File
# Begin Source File

SOURCE=.\common\thread.h
# End Source File
# Begin Source File

SOURCE=.\common\udpsocket.cpp
# End Source File
# Begin Source File

SOURCE=.\common\udpsocket.h
# End Source File
# Begin Source File

SOURCE=.\common\userfunc.cpp
# End Source File
# Begin Source File

SOURCE=.\common\userfunc.h
# End Source File
# Begin Source File

SOURCE=.\common\weakptr.h
# End Source File
# Begin Source File

SOURCE=.\websocket\web_socket_call_context.cpp
# End Source File
# Begin Source File

SOURCE=.\websocket\web_socket_call_context.h
# End Source File
# Begin Source File

SOURCE=.\websocket\web_socket_param_base.cpp
# End Source File
# Begin Source File

SOURCE=.\websocket\web_socket_param_base.h
# End Source File
# Begin Source File

SOURCE=.\websocket\websocketframeheader.cpp
# End Source File
# Begin Source File

SOURCE=.\websocket\websocketframeheader.h
# End Source File
# Begin Source File

SOURCE=.\websocket\websocketmessage.cpp
# End Source File
# Begin Source File

SOURCE=.\websocket\websocketmessage.h
# End Source File
# Begin Source File

SOURCE=.\websocket\websocketmessagequeue.cpp
# End Source File
# Begin Source File

SOURCE=.\websocket\websocketmessagequeue.h
# End Source File
# Begin Source File

SOURCE=.\websocket\websocketserver.cpp
# End Source File
# Begin Source File

SOURCE=.\websocket\websocketserver.h
# End Source File
# Begin Source File

SOURCE=.\websocket\websocketservicebase.cpp
# End Source File
# Begin Source File

SOURCE=.\websocket\websocketservicebase.h
# End Source File
# Begin Source File

SOURCE=.\window.cpp
# End Source File
# Begin Source File

SOURCE=.\window.h
# End Source File
# Begin Source File

SOURCE=.\common\winmisc.cpp
# End Source File
# Begin Source File

SOURCE=.\common\winmisc.h
# End Source File
# Begin Source File

SOURCE=.\ximage\wintypes.h
# End Source File
# Begin Source File

SOURCE=.\common\wnd.cpp
# End Source File
# Begin Source File

SOURCE=.\common\wnd.h
# End Source File
# Begin Source File

SOURCE=.\wndembeddedui.cpp
# End Source File
# Begin Source File

SOURCE=.\wndembeddedui.h
# End Source File
# Begin Source File

SOURCE=.\common\wndpagehost.cpp
# End Source File
# Begin Source File

SOURCE=.\common\wndpagehost.h
# End Source File
# Begin Source File

SOURCE=.\wndproperty.cpp
# End Source File
# Begin Source File

SOURCE=.\wndproperty.h
# End Source File
# Begin Source File

SOURCE=.\wndsearch.cpp
# End Source File
# Begin Source File

SOURCE=.\wndsearch.h
# End Source File
# Begin Source File

SOURCE=.\common\wndsplit.cpp
# End Source File
# Begin Source File

SOURCE=.\common\wndsplit.h
# End Source File
# Begin Source File

SOURCE=.\ximage\ximage.cpp
# End Source File
# Begin Source File

SOURCE=.\ximage\ximage.h
# End Source File
# Begin Source File

SOURCE=.\ximage\ximagebmp.cpp
# End Source File
# Begin Source File

SOURCE=.\ximage\ximagebmp.h
# End Source File
# Begin Source File

SOURCE=.\ximage\ximagegif.cpp
# End Source File
# Begin Source File

SOURCE=.\ximage\ximagegif.h
# End Source File
# Begin Source File

SOURCE=.\ximage\ximagehelper.cpp
# End Source File
# Begin Source File

SOURCE=.\ximage\ximagehelper.h
# End Source File
# Begin Source File

SOURCE=.\ximage\ximageico.cpp
# End Source File
# Begin Source File

SOURCE=.\ximage\ximageico.h
# End Source File
# Begin Source File

SOURCE=.\ximage\ximagejpg.cpp
# End Source File
# Begin Source File

SOURCE=.\ximage\ximagejpg.h
# End Source File
# Begin Source File

SOURCE=.\ximage\ximagepng.cpp
# End Source File
# Begin Source File

SOURCE=.\ximage\ximagepng.h
# End Source File
# Begin Source File

SOURCE=.\common\xml.cpp
# End Source File
# Begin Source File

SOURCE=.\common\xml.h
# End Source File
# Begin Source File

SOURCE=.\common\xmlreader.cpp
# End Source File
# Begin Source File

SOURCE=.\common\xmlreader.h
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_adler32.c
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_compress.c
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_crc32.c
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_crc32.h
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_deflate.c
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_deflate.h
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_gzio.c
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_infback.c
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_inffast.c
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_inffast.h
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_inffixed.h
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_inflate.c
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_inflate.h
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_inftrees.c
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_inftrees.h
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_trees.c
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_trees.h
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_uncompr.c
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_zconf.h
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_zconf.in.h
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_zlib.h
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_zutil.c
# End Source File
# Begin Source File

SOURCE=.\ximage\zlib_zutil.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Toolbar_Property.bmp
# End Source File
# Begin Source File

SOURCE=.\res\window.ICO
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\XPStyle.manifest
# End Source File
# End Target
# End Project
