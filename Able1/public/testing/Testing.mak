# Microsoft Developer Studio Generated NMAKE File, Based on Testing.dsp
!IF "$(CFG)" == ""
CFG=Testing - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Testing - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Testing - Win32 Release" && "$(CFG)" != "Testing - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Testing.mak" CFG="Testing - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Testing - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Testing - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "Testing - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Testing.exe"

!ELSE 

ALL : "fjsl - Win32 Release" "$(OUTDIR)\Testing.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"fjsl - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\DosMatch.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\TestCases.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Testing.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\Testing.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Testing.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\Testing.pdb" /machine:I386 /out:"$(OUTDIR)\Testing.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DosMatch.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\TestCases.obj" \
	"..\lib\vc6\fjsl.lib"

"$(OUTDIR)\Testing.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Testing - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Testing.exe" "$(OUTDIR)\Testing.bsc"

!ELSE 

ALL : "fjsl - Win32 Debug" "$(OUTDIR)\Testing.exe" "$(OUTDIR)\Testing.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"fjsl - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\DosMatch.obj"
	-@erase "$(INTDIR)\DosMatch.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\TestCases.obj"
	-@erase "$(INTDIR)\TestCases.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Testing.bsc"
	-@erase "$(OUTDIR)\Testing.exe"
	-@erase "$(OUTDIR)\Testing.ilk"
	-@erase "$(OUTDIR)\Testing.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Testing.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Testing.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\DosMatch.sbr" \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\TestCases.sbr"

"$(OUTDIR)\Testing.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\Testing.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Testing.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\DosMatch.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\TestCases.obj" \
	"..\lib\vc6\fjsl.lib"

"$(OUTDIR)\Testing.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("Testing.dep")
!INCLUDE "Testing.dep"
!ELSE 
!MESSAGE Warning: cannot find "Testing.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Testing - Win32 Release" || "$(CFG)" == "Testing - Win32 Debug"
SOURCE=..\Extra\Searching\DosMatch.Cpp

!IF  "$(CFG)" == "Testing - Win32 Release"


"$(INTDIR)\DosMatch.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Testing - Win32 Debug"


"$(INTDIR)\DosMatch.obj"	"$(INTDIR)\DosMatch.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\main.cpp

!IF  "$(CFG)" == "Testing - Win32 Release"


"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Testing - Win32 Debug"


"$(INTDIR)\main.obj"	"$(INTDIR)\main.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\TestCases.cpp

!IF  "$(CFG)" == "Testing - Win32 Release"


"$(INTDIR)\TestCases.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Testing - Win32 Debug"


"$(INTDIR)\TestCases.obj"	"$(INTDIR)\TestCases.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

!IF  "$(CFG)" == "Testing - Win32 Release"

"fjsl - Win32 Release" : 
   cd "\USR\code\Able1\public\lib\vc6\fjsl"
   $(MAKE) /$(MAKEFLAGS) /F .\fjsl.mak CFG="fjsl - Win32 Release" 
   cd "..\..\..\testing"

"fjsl - Win32 ReleaseCLEAN" : 
   cd "\USR\code\Able1\public\lib\vc6\fjsl"
   $(MAKE) /$(MAKEFLAGS) /F .\fjsl.mak CFG="fjsl - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\testing"

!ELSEIF  "$(CFG)" == "Testing - Win32 Debug"

"fjsl - Win32 Debug" : 
   cd "\USR\code\Able1\public\lib\vc6\fjsl"
   $(MAKE) /$(MAKEFLAGS) /F .\fjsl.mak CFG="fjsl - Win32 Debug" 
   cd "..\..\..\testing"

"fjsl - Win32 DebugCLEAN" : 
   cd "\USR\code\Able1\public\lib\vc6\fjsl"
   $(MAKE) /$(MAKEFLAGS) /F .\fjsl.mak CFG="fjsl - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\testing"

!ENDIF 


!ENDIF 

