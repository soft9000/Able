# Microsoft Developer Studio Generated NMAKE File, Based on EzLog.dsp
!IF "$(CFG)" == ""
CFG=EzLog - Win32 Debug
!MESSAGE No configuration specified. Defaulting to EzLog - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "EzLog - Win32 Release" && "$(CFG)" != "EzLog - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EzLog.mak" CFG="EzLog - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EzLog - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "EzLog - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "EzLog - Win32 Release"

OUTDIR=.\EzLog___Win32_Release
INTDIR=.\EzLog___Win32_Release
# Begin Custom Macros
OutDir=.\EzLog___Win32_Release
# End Custom Macros

ALL : "$(OUTDIR)\EzLog.exe"


CLEAN :
	-@erase "$(INTDIR)\EzLog.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\StdLog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WordWrap.obj"
	-@erase "$(OUTDIR)\EzLog.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EzLog.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\EzLog.pdb" /machine:I386 /out:"$(OUTDIR)\EzLog.exe" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\EzLog.obj" \
	"$(INTDIR)\StdLog.obj" \
	"$(INTDIR)\WordWrap.obj" \
	"..\..\..\lib\vc6\fjsl.lib"

"$(OUTDIR)\EzLog.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "EzLog - Win32 Debug"

OUTDIR=.\EzLog___Win32_Debug
INTDIR=.\EzLog___Win32_Debug
# Begin Custom Macros
OutDir=.\EzLog___Win32_Debug
# End Custom Macros

ALL : "$(OUTDIR)\EzLog.exe" "$(OUTDIR)\EzLog.bsc"


CLEAN :
	-@erase "$(INTDIR)\EzLog.obj"
	-@erase "$(INTDIR)\EzLog.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\StdLog.obj"
	-@erase "$(INTDIR)\StdLog.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WordWrap.obj"
	-@erase "$(INTDIR)\WordWrap.sbr"
	-@erase "$(OUTDIR)\EzLog.bsc"
	-@erase "$(OUTDIR)\EzLog.exe"
	-@erase "$(OUTDIR)\EzLog.ilk"
	-@erase "$(OUTDIR)\EzLog.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\EzLog.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\EzLog.sbr" \
	"$(INTDIR)\StdLog.sbr" \
	"$(INTDIR)\WordWrap.sbr"

"$(OUTDIR)\EzLog.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\EzLog.pdb" /debug /machine:I386 /out:"$(OUTDIR)\EzLog.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\EzLog.obj" \
	"$(INTDIR)\StdLog.obj" \
	"$(INTDIR)\WordWrap.obj" \
	"..\..\..\lib\vc6\fjsl.lib"

"$(OUTDIR)\EzLog.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("EzLog.dep")
!INCLUDE "EzLog.dep"
!ELSE 
!MESSAGE Warning: cannot find "EzLog.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "EzLog - Win32 Release" || "$(CFG)" == "EzLog - Win32 Debug"
SOURCE=..\..\..\a1extra\StdLog\EzLog.cpp

!IF  "$(CFG)" == "EzLog - Win32 Release"


"$(INTDIR)\EzLog.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "EzLog - Win32 Debug"


"$(INTDIR)\EzLog.obj"	"$(INTDIR)\EzLog.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\main.cpp

!IF  "$(CFG)" == "EzLog - Win32 Release"


"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "EzLog - Win32 Debug"


"$(INTDIR)\main.obj"	"$(INTDIR)\main.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=..\..\..\a1extra\StdLog\StdLog.cpp

!IF  "$(CFG)" == "EzLog - Win32 Release"


"$(INTDIR)\StdLog.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "EzLog - Win32 Debug"


"$(INTDIR)\StdLog.obj"	"$(INTDIR)\StdLog.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\a1extra\Formatting\WordWrap.cpp

!IF  "$(CFG)" == "EzLog - Win32 Release"


"$(INTDIR)\WordWrap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "EzLog - Win32 Debug"


"$(INTDIR)\WordWrap.obj"	"$(INTDIR)\WordWrap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

