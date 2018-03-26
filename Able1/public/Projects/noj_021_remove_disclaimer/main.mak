# Microsoft Developer Studio Generated NMAKE File, Based on main.dsp
!IF "$(CFG)" == ""
CFG=main - Win32 Debug
!MESSAGE No configuration specified. Defaulting to main - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "main - Win32 Release" && "$(CFG)" != "main - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "main.mak" CFG="main - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "main - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "main - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "main - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\main.exe"

!ELSE 

ALL : "fjsl - Win32 Release" "$(OUTDIR)\main.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"fjsl - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\main.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\main.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\main.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\main.pdb" /machine:I386 /out:"$(OUTDIR)\main.exe" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"..\..\lib\vc6\fjsl.lib"

"$(OUTDIR)\main.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "main - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\main.exe"

!ELSE 

ALL : "fjsl - Win32 Debug" "$(OUTDIR)\main.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"fjsl - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\main.exe"
	-@erase "$(OUTDIR)\main.ilk"
	-@erase "$(OUTDIR)\main.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\main.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\main.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\main.pdb" /debug /machine:I386 /out:"$(OUTDIR)\main.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"..\..\lib\vc6\fjsl.lib"

"$(OUTDIR)\main.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("main.dep")
!INCLUDE "main.dep"
!ELSE 
!MESSAGE Warning: cannot find "main.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "main - Win32 Release" || "$(CFG)" == "main - Win32 Debug"

!IF  "$(CFG)" == "main - Win32 Release"

"fjsl - Win32 Release" : 
   cd "\USR\code\mynoj\FastJob\lib\vc6\fjsl"
   $(MAKE) /$(MAKEFLAGS) /F .\fjsl.mak CFG="fjsl - Win32 Release" 
   cd "..\..\..\Projects\noj_021_remove_disclaimer"

"fjsl - Win32 ReleaseCLEAN" : 
   cd "\USR\code\mynoj\FastJob\lib\vc6\fjsl"
   $(MAKE) /$(MAKEFLAGS) /F .\fjsl.mak CFG="fjsl - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\Projects\noj_021_remove_disclaimer"

!ELSEIF  "$(CFG)" == "main - Win32 Debug"

"fjsl - Win32 Debug" : 
   cd "\USR\code\mynoj\FastJob\lib\vc6\fjsl"
   $(MAKE) /$(MAKEFLAGS) /F .\fjsl.mak CFG="fjsl - Win32 Debug" 
   cd "..\..\..\Projects\noj_021_remove_disclaimer"

"fjsl - Win32 DebugCLEAN" : 
   cd "\USR\code\mynoj\FastJob\lib\vc6\fjsl"
   $(MAKE) /$(MAKEFLAGS) /F .\fjsl.mak CFG="fjsl - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\Projects\noj_021_remove_disclaimer"

!ENDIF 

SOURCE=.\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

