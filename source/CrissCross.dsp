# Microsoft Developer Studio Project File - Name="CrissCross" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=CrissCross - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CrissCross.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CrissCross.mak" CFG="CrissCross - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CrissCross - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "CrissCross - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "CrissCross - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../bin/crisscross/release"
# PROP Intermediate_Dir "../obj/crisscross/release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zi /O2 /I "." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"crisscross/universal_include.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "CrissCross - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../bin/crisscross/debug"
# PROP Intermediate_Dir "../obj/crisscross/debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "." /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /FR /Yu"crisscross/universal_include.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "CrissCross - Win32 Release"
# Name "CrissCross - Win32 Debug"
# Begin Group "Includes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\crisscross\core_compare.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_console.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_cpuid.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_databuffer.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_debug.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_deprecate.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_error.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_filesystem.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_io.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_io_reader.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_io_writer.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_mutex.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_network.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_socket.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_system.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_thread.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\darray.cpp

!IF  "$(CFG)" == "CrissCross - Win32 Release"

!ELSEIF  "$(CFG)" == "CrissCross - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\crisscross\darray.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\dstack.cpp

!IF  "$(CFG)" == "CrissCross - Win32 Release"

!ELSEIF  "$(CFG)" == "CrissCross - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\crisscross\dstack.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\llist.cpp

!IF  "$(CFG)" == "CrissCross - Win32 Release"

!ELSEIF  "$(CFG)" == "CrissCross - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\crisscross\llist.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\rbtree.cpp

!IF  "$(CFG)" == "CrissCross - Win32 Release"

!ELSEIF  "$(CFG)" == "CrissCross - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\crisscross\rbtree.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\sortclass.cpp

!IF  "$(CFG)" == "CrissCross - Win32 Release"

!ELSEIF  "$(CFG)" == "CrissCross - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\crisscross\sortclass.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\splay.cpp

!IF  "$(CFG)" == "CrissCross - Win32 Release"

!ELSEIF  "$(CFG)" == "CrissCross - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\crisscross\splay.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\stopwatch.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\tcpsocket.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\textreader.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\textwriter.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\tree.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\udpsocket.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\universal_include.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\win32_pthread_emulate.h
# End Source File
# End Group
# Begin Group "Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\core_console.cpp
# End Source File
# Begin Source File

SOURCE=.\core_cpuid.cpp
# End Source File
# Begin Source File

SOURCE=.\core_databuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\core_debug.cpp
# End Source File
# Begin Source File

SOURCE=.\core_error.cpp
# End Source File
# Begin Source File

SOURCE=.\core_filesystem.cpp
# End Source File
# Begin Source File

SOURCE=.\core_io_reader.cpp
# End Source File
# Begin Source File

SOURCE=.\core_io_writer.cpp
# End Source File
# Begin Source File

SOURCE=.\core_mutex.cpp
# End Source File
# Begin Source File

SOURCE=.\core_network.cpp
# End Source File
# Begin Source File

SOURCE=.\core_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\core_system.cpp
# End Source File
# Begin Source File

SOURCE=.\core_thread.cpp
# End Source File
# Begin Source File

SOURCE=.\stopwatch.cpp
# End Source File
# Begin Source File

SOURCE=.\tcpsocket.cpp
# End Source File
# Begin Source File

SOURCE=.\textreader.cpp
# End Source File
# Begin Source File

SOURCE=.\textwriter.cpp
# End Source File
# Begin Source File

SOURCE=.\udpsocket.cpp
# End Source File
# Begin Source File

SOURCE=.\universal_include.cpp

!IF  "$(CFG)" == "CrissCross - Win32 Release"

!ELSEIF  "$(CFG)" == "CrissCross - Win32 Debug"

# ADD CPP /Yc"crisscross/universal_include.h"

!ENDIF 

# End Source File
# End Group
# End Target
# End Project
