# Microsoft Developer Studio Project File - Name="tmcdbgW" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=tmcdbgW - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tmcdbgW.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tmcdbgW.mak" CFG="tmcdbgW - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tmcdbgW - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "tmcdbgW - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "tmcdbgW - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "tmcdbgW - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "tmcdbgW___Win32_Debug"
# PROP BASE Intermediate_Dir "tmcdbgW___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "tmcdbgW___Win32_Debug"
# PROP Intermediate_Dir "tmcdbgW___Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "tmcdbgW - Win32 Release"
# Name "tmcdbgW - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "TMC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\tmc\clapack.h
# End Source File
# Begin Source File

SOURCE=.\tmc\clapack_types.h
# End Source File
# Begin Source File

SOURCE=.\tmc\cmatrix.c
# End Source File
# Begin Source File

SOURCE=.\tmc\cmatrix.h
# End Source File
# Begin Source File

SOURCE=.\tmc\tmc.h
# End Source File
# Begin Source File

SOURCE=.\tmc\tmc_lib.h
# End Source File
# Begin Source File

SOURCE=.\tmc\tmccell.c
# End Source File
# Begin Source File

SOURCE=.\tmc\tmcexcpt.c
# End Source File
# Begin Source File

SOURCE=.\tmc\tmcio.c
# End Source File
# Begin Source File

SOURCE=.\tmc\tmclib.c
# End Source File
# Begin Source File

SOURCE=.\tmc\tmcmstruct.c
# End Source File
# Begin Source File

SOURCE=.\tmc\tmcstringhash.c
# End Source File
# Begin Source File

SOURCE=.\tmc\tmcstringhash.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\__init_hash_data.c
# End Source File
# Begin Source File

SOURCE=.\SplitWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\splitwnd.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\tmcdbg_w.c
# End Source File
# Begin Source File

SOURCE=.\tmcdbgW.cpp
# End Source File
# Begin Source File

SOURCE=.\tmcdbgW.rc
# End Source File
# Begin Source File

SOURCE=.\tmcdbgWDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\tmcdbgW.h
# End Source File
# Begin Source File

SOURCE=.\tmcdbgWDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\tmcdbgW.ico
# End Source File
# Begin Source File

SOURCE=.\res\tmcdbgW.rc2
# End Source File
# End Group
# Begin Group "plot"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cplot.h
# End Source File
# Begin Source File

SOURCE=.\Plot.lib
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
