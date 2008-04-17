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
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CrissCross - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\bin\Release\CrissCross"
# PROP Intermediate_Dir "..\obj\Release\CrissCross"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /O2 /I "." /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Yu"crisscross/universal_include.h" /FD /c
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
# PROP Output_Dir "..\bin\Debug\CrissCross"
# PROP Intermediate_Dir "..\obj\Debug\CrissCross"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /ZI /Od /I "." /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Yu"crisscross/universal_include.h" /FD /EHsc /RTC1 /c
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
# Begin Group "Data"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\crisscross\avltree.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\crisscross\avltree.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\bubblesort.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\combsort.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\compare.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\darray.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\crisscross\darray.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\dstack.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\crisscross\dstack.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\hashtable.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\crisscross\hashtable.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\heapsort.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\insertionsort.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\internal_mem.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\llist.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\crisscross\llist.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\node.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\quicksort.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\rbtree.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\crisscross\rbtree.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\shellsort.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\sort.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\splaytree.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\crisscross\splaytree.h
# End Source File
# End Group
# Begin Group "Hash"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\md2.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\md2.h
# End Source File
# Begin Source File

SOURCE=.\md4.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\md4.h
# End Source File
# Begin Source File

SOURCE=.\md5.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\md5.h
# End Source File
# Begin Source File

SOURCE=.\sha1.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\sha1.h
# End Source File
# Begin Source File

SOURCE=.\sha256.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\sha256.h
# End Source File
# Begin Source File

SOURCE=.\sha512.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\sha512.h
# End Source File
# Begin Source File

SOURCE=.\tiger.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\tiger.h
# End Source File
# End Group
# Begin Group "Include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\crisscross\crisscross.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\datatypes.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\deprecate.h
# End Source File
# Begin Source File

SOURCE=.\error.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\error.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\platform_detect.h
# End Source File
# Begin Source File

SOURCE=.\universal_include.cpp
# ADD CPP /Yc"crisscross/universal_include.h"
# End Source File
# Begin Source File

SOURCE=.\crisscross\universal_include.h

!IF  "$(CFG)" == "CrissCross - Win32 Release"

# Begin Custom Build - Generating build number...
ProjDir=.
InputPath=.\crisscross\universal_include.h

"$(ProjDir)\crisscross\build_number.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ProjDir)\..\tools\GenerateBuildNumber.exe $(ProjDir)\crisscross

# End Custom Build

!ELSEIF  "$(CFG)" == "CrissCross - Win32 Debug"

# Begin Custom Build - Generating build number...
ProjDir=.
InputPath=.\crisscross\universal_include.h

"$(ProjDir)\crisscross\build_number.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(ProjDir)\..\tools\GenerateBuildNumber.exe $(ProjDir)\crisscross

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "IO"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\console.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\console.h
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_io.h
# End Source File
# Begin Source File

SOURCE=.\core_io_reader.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_io_reader.h
# End Source File
# Begin Source File

SOURCE=.\core_io_writer.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_io_writer.h
# End Source File
# Begin Source File

SOURCE=.\filereader.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\filereader.h
# End Source File
# Begin Source File

SOURCE=.\filewriter.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\filewriter.h
# End Source File
# End Group
# Begin Group "Net"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\core_network.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_network.h
# End Source File
# Begin Source File

SOURCE=.\core_socket.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\core_socket.h
# End Source File
# Begin Source File

SOURCE=.\tcpsocket.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\tcpsocket.h
# End Source File
# Begin Source File

SOURCE=.\udpsocket.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\udpsocket.h
# End Source File
# End Group
# Begin Group "System"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\cpuid.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\cpuid.h
# End Source File
# Begin Source File

SOURCE=.\debug.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\debug.h
# End Source File
# Begin Source File

SOURCE=.\mutex.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\mutex.h
# End Source File
# Begin Source File

SOURCE=.\stopwatch.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\stopwatch.h
# End Source File
# Begin Source File

SOURCE=.\system.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\system.h
# End Source File
# Begin Source File

SOURCE=.\version.cpp
# End Source File
# Begin Source File

SOURCE=.\crisscross\version.h
# End Source File
# End Group
# Begin Group "XCrashReports"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\XCrashReports\exception_handler.cpp
# End Source File
# Begin Source File

SOURCE=.\XCrashReports\exception_handler.h
# End Source File
# Begin Source File

SOURCE=.\XCrashReports\GetWinVer.cpp
# End Source File
# Begin Source File

SOURCE=.\XCrashReports\GetWinVer.h
# End Source File
# Begin Source File

SOURCE=.\XCrashReports\MiniVersion.cpp
# End Source File
# Begin Source File

SOURCE=.\XCrashReports\MiniVersion.h
# End Source File
# End Group
# End Target
# End Project
