# Microsoft Developer Studio Generated NMAKE File, Based on NOJ_020_TSPAWN.dsp
!IF "$(CFG)" == ""
CFG=NOJ_020_TSPAWN - Win32 Debug
!MESSAGE No configuration specified. Defaulting to NOJ_020_TSPAWN - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "NOJ_020_TSPAWN - Win32 Release" && "$(CFG)" != "NOJ_020_TSPAWN - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NOJ_020_TSPAWN.mak" CFG="NOJ_020_TSPAWN - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NOJ_020_TSPAWN - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "NOJ_020_TSPAWN - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "NOJ_020_TSPAWN - Win32 Release"

OUTDIR=d:\bin
INTDIR=.\Release

ALL : ".\tspawn.exe"


CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\SpawnT.obj"
	-@erase "$(INTDIR)\SpawnTask.obj"
	-@erase "$(INTDIR)\StdLog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase ".\tspawn.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\NOJ_020_TSPAWN.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NOJ_020_TSPAWN.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\tspawn.pdb" /machine:I386 /out:"tspawn.exe" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\SpawnT.obj" \
	"$(INTDIR)\SpawnTask.obj" \
	"$(INTDIR)\StdLog.obj" \
	"..\..\lib\vc6\fjsl.lib"

".\tspawn.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "NOJ_020_TSPAWN - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\tspawn.exe" "$(OUTDIR)\NOJ_020_TSPAWN.bsc"


CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\SpawnT.obj"
	-@erase "$(INTDIR)\SpawnT.sbr"
	-@erase "$(INTDIR)\SpawnTask.obj"
	-@erase "$(INTDIR)\SpawnTask.sbr"
	-@erase "$(INTDIR)\StdLog.obj"
	-@erase "$(INTDIR)\StdLog.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\NOJ_020_TSPAWN.bsc"
	-@erase "$(OUTDIR)\tspawn.pdb"
	-@erase ".\tspawn.exe"
	-@erase ".\tspawn.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\NOJ_020_TSPAWN.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NOJ_020_TSPAWN.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\SpawnT.sbr" \
	"$(INTDIR)\SpawnTask.sbr" \
	"$(INTDIR)\StdLog.sbr"

"$(OUTDIR)\NOJ_020_TSPAWN.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\tspawn.pdb" /debug /machine:I386 /out:"tspawn.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\SpawnT.obj" \
	"$(INTDIR)\SpawnTask.obj" \
	"$(INTDIR)\StdLog.obj" \
	"..\..\lib\vc6\fjsl.lib"

".\tspawn.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("NOJ_020_TSPAWN.dep")
!INCLUDE "NOJ_020_TSPAWN.dep"
!ELSE 
!MESSAGE Warning: cannot find "NOJ_020_TSPAWN.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "NOJ_020_TSPAWN - Win32 Release" || "$(CFG)" == "NOJ_020_TSPAWN - Win32 Debug"
SOURCE=.\main.cpp

!IF  "$(CFG)" == "NOJ_020_TSPAWN - Win32 Release"


"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NOJ_020_TSPAWN - Win32 Debug"


"$(INTDIR)\main.obj"	"$(INTDIR)\main.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SpawnT.cpp

!IF  "$(CFG)" == "NOJ_020_TSPAWN - Win32 Release"


"$(INTDIR)\SpawnT.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NOJ_020_TSPAWN - Win32 Debug"


"$(INTDIR)\SpawnT.obj"	"$(INTDIR)\SpawnT.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SpawnTask.cpp

!IF  "$(CFG)" == "NOJ_020_TSPAWN - Win32 Release"


"$(INTDIR)\SpawnTask.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NOJ_020_TSPAWN - Win32 Debug"


"$(INTDIR)\SpawnTask.obj"	"$(INTDIR)\SpawnTask.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=..\..\Extra\StdLog\StdLog.cpp

!IF  "$(CFG)" == "NOJ_020_TSPAWN - Win32 Release"


"$(INTDIR)\StdLog.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NOJ_020_TSPAWN - Win32 Debug"


"$(INTDIR)\StdLog.obj"	"$(INTDIR)\StdLog.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

