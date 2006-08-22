# Microsoft Developer Studio Project File - Name="Technetium" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Technetium - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Technetium.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Technetium.mak" CFG="Technetium - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Technetium - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Technetium - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Technetium - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Technetium___Win32_Release"
# PROP BASE Intermediate_Dir "Technetium___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../bin/Release"
# PROP Intermediate_Dir "../obj/Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"universal_include.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Technetium - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Technetium___Win32_Debug"
# PROP BASE Intermediate_Dir "Technetium___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../bin/Debug"
# PROP Intermediate_Dir "../obj/Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I "datastructures" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /Yu"universal_include.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 dbghelp.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Technetium - Win32 Release"
# Name "Technetium - Win32 Debug"
# Begin Group "IO"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\core_console.cpp
# End Source File
# Begin Source File

SOURCE=.\core_console.h
# End Source File
# Begin Source File

SOURCE=.\core_io.cpp
# End Source File
# Begin Source File

SOURCE=.\core_io.h
# End Source File
# Begin Source File

SOURCE=.\textreader.cpp
# End Source File
# Begin Source File

SOURCE=.\textreader.h
# End Source File
# Begin Source File

SOURCE=.\textwriter.cpp
# End Source File
# Begin Source File

SOURCE=.\textwriter.h
# End Source File
# End Group
# Begin Group "System"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\core_cpuid.cpp
# End Source File
# Begin Source File

SOURCE=.\core_cpuid.h
# End Source File
# Begin Source File

SOURCE=.\core_debug.cpp
# End Source File
# Begin Source File

SOURCE=.\core_debug.h
# End Source File
# Begin Source File

SOURCE=.\core_exception.h
# End Source File
# Begin Source File

SOURCE=.\core_mutex.cpp
# End Source File
# Begin Source File

SOURCE=.\core_mutex.h
# End Source File
# Begin Source File

SOURCE=.\core_system.cpp
# End Source File
# Begin Source File

SOURCE=.\core_system.h
# End Source File
# Begin Source File

SOURCE=.\core_thread.cpp
# End Source File
# Begin Source File

SOURCE=.\core_thread.h
# End Source File
# End Group
# Begin Group "Include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\core_deprecate.h
# End Source File
# Begin Source File

SOURCE=.\universal_include.cpp
# ADD CPP /Yc"universal_include.h"
# End Source File
# Begin Source File

SOURCE=.\universal_include.h
# End Source File
# Begin Source File

SOURCE=.\win32_pthread_emulate.h
# End Source File
# End Group
# Begin Group "Data Structures"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\datastructures\darray.cpp
# End Source File
# Begin Source File

SOURCE=.\datastructures\darray.h
# End Source File
# Begin Source File

SOURCE=.\datastructures\dstack.cpp
# End Source File
# Begin Source File

SOURCE=.\datastructures\dstack.h
# End Source File
# Begin Source File

SOURCE=.\datastructures\llist.cpp
# End Source File
# Begin Source File

SOURCE=.\datastructures\llist.h
# End Source File
# Begin Source File

SOURCE=.\datastructures\rbtree.cpp
# End Source File
# Begin Source File

SOURCE=.\datastructures\rbtree.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# End Target
# End Project
