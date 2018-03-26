# Microsoft Developer Studio Generated NMAKE File, Based on HotSwap.dsp
!IF "$(CFG)" == ""
CFG=HotSwap - Win32 Debug
!MESSAGE No configuration specified. Defaulting to HotSwap - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "HotSwap - Win32 Release" && "$(CFG)" != "HotSwap - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HotSwap.mak" CFG="HotSwap - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HotSwap - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "HotSwap - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "HotSwap - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\HotSwap.exe"

!ELSE 

ALL : "fjsl - Win32 Release" "$(OUTDIR)\HotSwap.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"fjsl - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\HotSwap.obj"
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\HotSwap.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\HotSwap.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HotSwap.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\HotSwap.pdb" /machine:I386 /out:"$(OUTDIR)\HotSwap.exe" /out:"/bin/HotSwap.exe" 
LINK32_OBJS= \
	"$(INTDIR)\HotSwap.obj" \
	"$(INTDIR)\Main.obj" \
	"..\..\lib\vc6\fjsl.lib"

"$(OUTDIR)\HotSwap.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "HotSwap - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\HotSwap.exe" "$(OUTDIR)\HotSwap.bsc"

!ELSE 

ALL : "fjsl - Win32 Debug" "$(OUTDIR)\HotSwap.exe" "$(OUTDIR)\HotSwap.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"fjsl - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\HotSwap.obj"
	-@erase "$(INTDIR)\HotSwap.sbr"
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\Main.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\HotSwap.bsc"
	-@erase "$(OUTDIR)\HotSwap.exe"
	-@erase "$(OUTDIR)\HotSwap.ilk"
	-@erase "$(OUTDIR)\HotSwap.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\HotSwap.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\HotSwap.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\HotSwap.sbr" \
	"$(INTDIR)\Main.sbr"

"$(OUTDIR)\HotSwap.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\HotSwap.pdb" /debug /machine:I386 /out:"$(OUTDIR)\HotSwap.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\HotSwap.obj" \
	"$(INTDIR)\Main.obj" \
	"..\..\lib\vc6\fjsl.lib"

"$(OUTDIR)\HotSwap.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("HotSwap.dep")
!INCLUDE "HotSwap.dep"
!ELSE 
!MESSAGE Warning: cannot find "HotSwap.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "HotSwap - Win32 Release" || "$(CFG)" == "HotSwap - Win32 Debug"

!IF  "$(CFG)" == "HotSwap - Win32 Release"

"fjsl - Win32 Release" : 
   cd "\USR\code\mynoj\FastJob\lib\vc6\fjsl"
   $(MAKE) /$(MAKEFLAGS) /F .\fjsl.mak CFG="fjsl - Win32 Release" 
   cd "..\..\..\Projects\noj_019_hotswap"

"fjsl - Win32 ReleaseCLEAN" : 
   cd "\USR\code\mynoj\FastJob\lib\vc6\fjsl"
   $(MAKE) /$(MAKEFLAGS) /F .\fjsl.mak CFG="fjsl - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\Projects\noj_019_hotswap"

!ELSEIF  "$(CFG)" == "HotSwap - Win32 Debug"

"fjsl - Win32 Debug" : 
   cd "\USR\code\mynoj\FastJob\lib\vc6\fjsl"
   $(MAKE) /$(MAKEFLAGS) /F .\fjsl.mak CFG="fjsl - Win32 Debug" 
   cd "..\..\..\Projects\noj_019_hotswap"

"fjsl - Win32 DebugCLEAN" : 
   cd "\USR\code\mynoj\FastJob\lib\vc6\fjsl"
   $(MAKE) /$(MAKEFLAGS) /F .\fjsl.mak CFG="fjsl - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\Projects\noj_019_hotswap"

!ENDIF 

SOURCE=.\HotSwap.Cpp

!IF  "$(CFG)" == "HotSwap - Win32 Release"


"$(INTDIR)\HotSwap.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HotSwap - Win32 Debug"


"$(INTDIR)\HotSwap.obj"	"$(INTDIR)\HotSwap.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Main.cpp

!IF  "$(CFG)" == "HotSwap - Win32 Release"


"$(INTDIR)\Main.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "HotSwap - Win32 Debug"


"$(INTDIR)\Main.obj"	"$(INTDIR)\Main.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 


!ENDIF 

