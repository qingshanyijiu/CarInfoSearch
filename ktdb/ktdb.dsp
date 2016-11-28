# Microsoft Developer Studio Project File - Name="ktdb" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ktdb - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ktdb.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ktdb.mak" CFG="ktdb - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ktdb - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ktdb - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/1.工作区/c.源代码/04.SP-V2.0/ktdb", PHZQAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ktdb - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "ktdb - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "SQLITE_CORE" /D "SQLITE_ENABLE_RTREE" /D "SQLITE_ENABLE_COLUMN_METADATA" /D "SQLITE_ENABLE_FTS3" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\ktdbD.lib"

!ENDIF 

# Begin Target

# Name "ktdb - Win32 Release"
# Name "ktdb - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\alter.c
# End Source File
# Begin Source File

SOURCE=.\analyze.c
# End Source File
# Begin Source File

SOURCE=.\attach.c
# End Source File
# Begin Source File

SOURCE=.\auth.c
# End Source File
# Begin Source File

SOURCE=.\backup.c
# End Source File
# Begin Source File

SOURCE=.\bitvec.c
# End Source File
# Begin Source File

SOURCE=.\btmutex.c
# End Source File
# Begin Source File

SOURCE=.\btree.c
# End Source File
# Begin Source File

SOURCE=.\build.c
# End Source File
# Begin Source File

SOURCE=.\callback.c
# End Source File
# Begin Source File

SOURCE=.\complete.c
# End Source File
# Begin Source File

SOURCE=.\ctime.c
# End Source File
# Begin Source File

SOURCE=.\date.c
# End Source File
# Begin Source File

SOURCE=.\delete.c
# End Source File
# Begin Source File

SOURCE=.\expr.c
# End Source File
# Begin Source File

SOURCE=.\fault.c
# End Source File
# Begin Source File

SOURCE=.\fkey.c
# End Source File
# Begin Source File

SOURCE=.\fts3.c
# End Source File
# Begin Source File

SOURCE=.\fts3_expr.c
# End Source File
# Begin Source File

SOURCE=.\fts3_hash.c
# End Source File
# Begin Source File

SOURCE=.\fts3_icu.c
# End Source File
# Begin Source File

SOURCE=.\fts3_porter.c
# End Source File
# Begin Source File

SOURCE=.\fts3_snippet.c
# End Source File
# Begin Source File

SOURCE=.\fts3_tokenizer.c
# End Source File
# Begin Source File

SOURCE=.\fts3_tokenizer1.c
# End Source File
# Begin Source File

SOURCE=.\fts3_write.c
# End Source File
# Begin Source File

SOURCE=.\func.c
# End Source File
# Begin Source File

SOURCE=.\global.c
# End Source File
# Begin Source File

SOURCE=.\hash.c
# End Source File
# Begin Source File

SOURCE=.\insert.c
# End Source File
# Begin Source File

SOURCE=.\journal.c
# End Source File
# Begin Source File

SOURCE=.\legacy.c
# End Source File
# Begin Source File

SOURCE=.\loadext.c
# End Source File
# Begin Source File

SOURCE=.\main.c
# End Source File
# Begin Source File

SOURCE=.\malloc.c
# End Source File
# Begin Source File

SOURCE=.\mem0.c
# End Source File
# Begin Source File

SOURCE=.\mem1.c
# End Source File
# Begin Source File

SOURCE=.\mem2.c
# End Source File
# Begin Source File

SOURCE=.\mem3.c
# End Source File
# Begin Source File

SOURCE=.\mem5.c
# End Source File
# Begin Source File

SOURCE=.\memjournal.c
# End Source File
# Begin Source File

SOURCE=.\mutex.c
# End Source File
# Begin Source File

SOURCE=.\mutex_noop.c
# End Source File
# Begin Source File

SOURCE=.\mutex_os2.c
# End Source File
# Begin Source File

SOURCE=.\mutex_unix.c
# End Source File
# Begin Source File

SOURCE=.\mutex_w32.c
# End Source File
# Begin Source File

SOURCE=.\notify.c
# End Source File
# Begin Source File

SOURCE=.\opcodes.c
# End Source File
# Begin Source File

SOURCE=.\os.c
# End Source File
# Begin Source File

SOURCE=.\os_os2.c
# End Source File
# Begin Source File

SOURCE=.\os_unix.c
# End Source File
# Begin Source File

SOURCE=.\os_win.c
# End Source File
# Begin Source File

SOURCE=.\pager.c
# End Source File
# Begin Source File

SOURCE=.\parse.c
# End Source File
# Begin Source File

SOURCE=.\pcache.c
# End Source File
# Begin Source File

SOURCE=.\pcache1.c
# End Source File
# Begin Source File

SOURCE=.\pragma.c
# End Source File
# Begin Source File

SOURCE=.\prepare.c
# End Source File
# Begin Source File

SOURCE=.\printf.c
# End Source File
# Begin Source File

SOURCE=.\random.c
# End Source File
# Begin Source File

SOURCE=.\resolve.c
# End Source File
# Begin Source File

SOURCE=.\rowset.c
# End Source File
# Begin Source File

SOURCE=.\rtree.c
# End Source File
# Begin Source File

SOURCE=.\select.c
# End Source File
# Begin Source File

SOURCE=.\status.c
# End Source File
# Begin Source File

SOURCE=.\table.c
# End Source File
# Begin Source File

SOURCE=.\tokenize.c
# End Source File
# Begin Source File

SOURCE=.\trigger.c
# End Source File
# Begin Source File

SOURCE=.\update.c
# End Source File
# Begin Source File

SOURCE=.\utf.c
# End Source File
# Begin Source File

SOURCE=.\util.c
# End Source File
# Begin Source File

SOURCE=.\vacuum.c
# End Source File
# Begin Source File

SOURCE=.\vdbe.c
# End Source File
# Begin Source File

SOURCE=.\vdbeapi.c
# End Source File
# Begin Source File

SOURCE=.\vdbeaux.c
# End Source File
# Begin Source File

SOURCE=.\vdbeblob.c
# End Source File
# Begin Source File

SOURCE=.\vdbemem.c
# End Source File
# Begin Source File

SOURCE=.\vdbetrace.c
# End Source File
# Begin Source File

SOURCE=.\vtab.c
# End Source File
# Begin Source File

SOURCE=.\wal.c
# End Source File
# Begin Source File

SOURCE=.\walker.c
# End Source File
# Begin Source File

SOURCE=.\where.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\btree.h
# End Source File
# Begin Source File

SOURCE=.\btreeInt.h
# End Source File
# Begin Source File

SOURCE=.\fts3.h
# End Source File
# Begin Source File

SOURCE=.\fts3_hash.h
# End Source File
# Begin Source File

SOURCE=.\fts3_tokenizer.h
# End Source File
# Begin Source File

SOURCE=.\fts3Int.h
# End Source File
# Begin Source File

SOURCE=.\hash.h
# End Source File
# Begin Source File

SOURCE=.\hwtime.h
# End Source File
# Begin Source File

SOURCE=.\keywordhash.h
# End Source File
# Begin Source File

SOURCE=.\mutex.h
# End Source File
# Begin Source File

SOURCE=.\opcodes.h
# End Source File
# Begin Source File

SOURCE=.\os.h
# End Source File
# Begin Source File

SOURCE=.\os_common.h
# End Source File
# Begin Source File

SOURCE=.\pager.h
# End Source File
# Begin Source File

SOURCE=.\parse.h
# End Source File
# Begin Source File

SOURCE=.\pcache.h
# End Source File
# Begin Source File

SOURCE=.\rtree.h
# End Source File
# Begin Source File

SOURCE=.\sqlite3.h
# End Source File
# Begin Source File

SOURCE=.\sqlite3ext.h
# End Source File
# Begin Source File

SOURCE=.\sqliteicu.h
# End Source File
# Begin Source File

SOURCE=.\sqliteInt.h
# End Source File
# Begin Source File

SOURCE=.\sqliteLimit.h
# End Source File
# Begin Source File

SOURCE=.\vdbe.h
# End Source File
# Begin Source File

SOURCE=.\vdbeInt.h
# End Source File
# Begin Source File

SOURCE=.\wal.h
# End Source File
# End Group
# End Target
# End Project
