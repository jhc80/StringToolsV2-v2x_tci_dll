# Microsoft Developer Studio Project File - Name="dll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=dll - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dll.mak" CFG="dll - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dll - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DLL_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\main_window\common" /I "..\main_window\platform" /I "..\main_window\lua" /I "..\main_window\share" /I "dshowInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DLL_EXPORTS" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "dll - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DLL_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "common" /I "platform" /I "lua" /I "share" /I "dshowInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "DLL_EXPORTS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "dll - Win32 Release"
# Name "dll - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;h"
# Begin Source File

SOURCE=..\main_window\common\basicarray.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\closure.cpp
# End Source File
# Begin Source File

SOURCE=..\main_window\common\closure.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\closurelist.cpp
# End Source File
# Begin Source File

SOURCE=..\main_window\common\closurelist.h
# End Source File
# Begin Source File

SOURCE=.\config.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\cruntime.c
# End Source File
# Begin Source File

SOURCE=..\main_window\common\cruntime.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\dirmgr.cpp
# End Source File
# Begin Source File

SOURCE=..\main_window\common\dirmgr.h
# End Source File
# Begin Source File

SOURCE=.\dll.cpp
# End Source File
# Begin Source File

SOURCE=.\dll.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\encoder.cpp
# End Source File
# Begin Source File

SOURCE=..\main_window\common\encoder.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\file.cpp
# End Source File
# Begin Source File

SOURCE=..\main_window\common\file.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\filebase.cpp
# End Source File
# Begin Source File

SOURCE=..\main_window\common\filebase.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lapi.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lapi.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lauxlib.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lauxlib.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lbaselib.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lbitlib.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lcode.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lcode.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lcorolib.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lctype.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lctype.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\ldblib.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\ldebug.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\ldebug.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\ldo.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\ldo.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\ldump.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lfunc.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lfunc.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lgc.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lgc.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\linit.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\liolib.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\llex.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\llex.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\llimits.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lmathlib.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lmem.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lmem.h
# End Source File
# Begin Source File

SOURCE=.\share\load_dll.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\loadlib.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lobject.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lobject.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lopcodes.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lopcodes.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\loslib.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lparser.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lparser.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lprefix.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lstate.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lstate.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lstring.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lstring.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lstrlib.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\ltable.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\ltable.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\ltablib.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\ltm.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\ltm.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lua.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lua.h
# End Source File
# Begin Source File

SOURCE=..\main_window\share\lua_helper.cpp
# End Source File
# Begin Source File

SOURCE=..\main_window\share\lua_helper.h
# End Source File
# Begin Source File

SOURCE=.\lua_print.cpp
# End Source File
# Begin Source File

SOURCE=.\lua_print.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\luac.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\luaconf.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lualib.h
# End Source File
# Begin Source File

SOURCE=.\lualib_webcamera.cpp
# End Source File
# Begin Source File

SOURCE=.\lualib_webcamera.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\luavm.cpp
# End Source File
# Begin Source File

SOURCE=..\main_window\common\luavm.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lundump.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lundump.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lutf8lib.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lvm.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lvm.h
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lzio.c
# End Source File
# Begin Source File

SOURCE=..\main_window\lua\lzio.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\mem.cpp
# End Source File
# Begin Source File

SOURCE=..\main_window\common\mem.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\mem_tool.c
# End Source File
# Begin Source File

SOURCE=..\main_window\common\mem_tool.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\memfile.cpp
# End Source File
# Begin Source File

SOURCE=..\main_window\common\memfile.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\memstk.cpp
# End Source File
# Begin Source File

SOURCE=..\main_window\common\memstk.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\minibson.cpp
# End Source File
# Begin Source File

SOURCE=..\main_window\common\minibson.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\misc.c
# End Source File
# Begin Source File

SOURCE=..\main_window\common\misc.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\raw_weak_pointer.cpp
# End Source File
# Begin Source File

SOURCE=..\main_window\common\raw_weak_pointer.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\syslog.c
# End Source File
# Begin Source File

SOURCE=..\main_window\common\syslog.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\taskmgr.cpp
# End Source File
# Begin Source File

SOURCE=..\main_window\common\taskmgr.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\tcp.cpp
# End Source File
# Begin Source File

SOURCE=..\main_window\common\tcp.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\userfunc.cpp
# End Source File
# Begin Source File

SOURCE=..\main_window\common\userfunc.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\weak_pointer.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\weak_ref.h
# End Source File
# Begin Source File

SOURCE=.\webcamera.cpp
# End Source File
# Begin Source File

SOURCE=.\webcamera.h
# End Source File
# Begin Source File

SOURCE=..\main_window\common\wnd.cpp
# End Source File
# Begin Source File

SOURCE=..\main_window\common\wnd.h
# End Source File
# End Group
# End Target
# End Project
