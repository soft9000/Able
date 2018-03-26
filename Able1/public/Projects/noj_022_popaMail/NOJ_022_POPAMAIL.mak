# Microsoft Developer Studio Generated NMAKE File, Based on NOJ_022_POPAMAIL.dsp
!IF "$(CFG)" == ""
CFG=NOJ_022_POPAMAIL - Win32 Debug
!MESSAGE No configuration specified. Defaulting to NOJ_022_POPAMAIL - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "NOJ_022_POPAMAIL - Win32 Release" && "$(CFG)" != "NOJ_022_POPAMAIL - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "NOJ_022_POPAMAIL.mak" CFG="NOJ_022_POPAMAIL - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "NOJ_022_POPAMAIL - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "NOJ_022_POPAMAIL - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Release"

OUTDIR=C:\POPAMAIL
INTDIR=.\Release
# Begin Custom Macros
OutDir=C:\POPAMAIL
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\POPAMAIL.exe"

!ELSE 

ALL : "stdnet - Win32 Release" "fjsl - Win32 Release" "BetterMail - Win32 Release" "$(OUTDIR)\POPAMAIL.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"BetterMail - Win32 ReleaseCLEAN" "fjsl - Win32 ReleaseCLEAN" "stdnet - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\IniData.obj"
	-@erase "$(INTDIR)\IniFile.obj"
	-@erase "$(INTDIR)\IniSection.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\StdLog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\POPAMAIL.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\NOJ_022_POPAMAIL.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NOJ_022_POPAMAIL.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\POPAMAIL.pdb" /machine:I386 /out:"$(OUTDIR)\POPAMAIL.exe" 
LINK32_OBJS= \
	"$(INTDIR)\IniData.obj" \
	"$(INTDIR)\IniFile.obj" \
	"$(INTDIR)\IniSection.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\StdLog.obj" \
	"..\..\lib\vc6\fjsl.lib" \
	"..\..\lib\vc6\BetterMail.lib" \
	"..\..\lib\vc6\stdnet.lib" \
	"..\..\..\..\lib\WSock32.Lib"

"$(OUTDIR)\POPAMAIL.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Debug"

OUTDIR=C:\POPAMAIL
INTDIR=.\Debug
# Begin Custom Macros
OutDir=C:\POPAMAIL
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\POPAMAIL.exe" "$(OUTDIR)\NOJ_022_POPAMAIL.bsc"

!ELSE 

ALL : "stdnet - Win32 Debug" "fjsl - Win32 Debug" "BetterMail - Win32 Debug" "$(OUTDIR)\POPAMAIL.exe" "$(OUTDIR)\NOJ_022_POPAMAIL.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"BetterMail - Win32 DebugCLEAN" "fjsl - Win32 DebugCLEAN" "stdnet - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\IniData.obj"
	-@erase "$(INTDIR)\IniData.sbr"
	-@erase "$(INTDIR)\IniFile.obj"
	-@erase "$(INTDIR)\IniFile.sbr"
	-@erase "$(INTDIR)\IniSection.obj"
	-@erase "$(INTDIR)\IniSection.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\StdLog.obj"
	-@erase "$(INTDIR)\StdLog.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\NOJ_022_POPAMAIL.bsc"
	-@erase "$(OUTDIR)\POPAMAIL.exe"
	-@erase "$(OUTDIR)\POPAMAIL.ilk"
	-@erase "$(OUTDIR)\POPAMAIL.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\NOJ_022_POPAMAIL.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\NOJ_022_POPAMAIL.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\IniData.sbr" \
	"$(INTDIR)\IniFile.sbr" \
	"$(INTDIR)\IniSection.sbr" \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\StdLog.sbr"

"$(OUTDIR)\NOJ_022_POPAMAIL.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\POPAMAIL.pdb" /debug /machine:I386 /out:"$(OUTDIR)\POPAMAIL.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\IniData.obj" \
	"$(INTDIR)\IniFile.obj" \
	"$(INTDIR)\IniSection.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\StdLog.obj" \
	"..\..\lib\vc6\fjsl.lib" \
	"..\..\lib\vc6\BetterMail.lib" \
	"..\..\lib\vc6\stdnet.lib" \
	"..\..\..\..\lib\WSock32.Lib"

"$(OUTDIR)\POPAMAIL.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("NOJ_022_POPAMAIL.dep")
!INCLUDE "NOJ_022_POPAMAIL.dep"
!ELSE 
!MESSAGE Warning: cannot find "NOJ_022_POPAMAIL.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Release" || "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Debug"
SOURCE=..\..\Extra\ini\IniData.cpp

!IF  "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Release"


"$(INTDIR)\IniData.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Debug"


"$(INTDIR)\IniData.obj"	"$(INTDIR)\IniData.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\Extra\ini\IniFile.cpp

!IF  "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Release"


"$(INTDIR)\IniFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Debug"


"$(INTDIR)\IniFile.obj"	"$(INTDIR)\IniFile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\Extra\ini\IniSection.cpp

!IF  "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Release"


"$(INTDIR)\IniSection.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Debug"


"$(INTDIR)\IniSection.obj"	"$(INTDIR)\IniSection.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\main.cpp

!IF  "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Release"


"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Debug"


"$(INTDIR)\main.obj"	"$(INTDIR)\main.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=..\..\Extra\StdLog\StdLog.cpp

!IF  "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Release"


"$(INTDIR)\StdLog.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Debug"


"$(INTDIR)\StdLog.obj"	"$(INTDIR)\StdLog.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

!IF  "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Release"

"BetterMail - Win32 Release" : 
   cd "\USR\CODE\MYNOJ\FASTJOB\LIB\VC6\BetterMail"
   $(MAKE) /$(MAKEFLAGS) /F .\BetterMail.mak CFG="BetterMail - Win32 Release" 
   cd "..\..\..\PROJECTS\NOJ_022_POPAMAIL"

"BetterMail - Win32 ReleaseCLEAN" : 
   cd "\USR\CODE\MYNOJ\FASTJOB\LIB\VC6\BetterMail"
   $(MAKE) /$(MAKEFLAGS) /F .\BetterMail.mak CFG="BetterMail - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\PROJECTS\NOJ_022_POPAMAIL"

!ELSEIF  "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Debug"

"BetterMail - Win32 Debug" : 
   cd "\USR\CODE\MYNOJ\FASTJOB\LIB\VC6\BetterMail"
   $(MAKE) /$(MAKEFLAGS) /F .\BetterMail.mak CFG="BetterMail - Win32 Debug" 
   cd "..\..\..\PROJECTS\NOJ_022_POPAMAIL"

"BetterMail - Win32 DebugCLEAN" : 
   cd "\USR\CODE\MYNOJ\FASTJOB\LIB\VC6\BetterMail"
   $(MAKE) /$(MAKEFLAGS) /F .\BetterMail.mak CFG="BetterMail - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\PROJECTS\NOJ_022_POPAMAIL"

!ENDIF 

!IF  "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Release"

"fjsl - Win32 Release" : 
   cd "\USR\CODE\MYNOJ\FASTJOB\lib\vc6\fjsl"
   $(MAKE) /$(MAKEFLAGS) /F .\fjsl.mak CFG="fjsl - Win32 Release" 
   cd "..\..\..\PROJECTS\NOJ_022_POPAMAIL"

"fjsl - Win32 ReleaseCLEAN" : 
   cd "\USR\CODE\MYNOJ\FASTJOB\lib\vc6\fjsl"
   $(MAKE) /$(MAKEFLAGS) /F .\fjsl.mak CFG="fjsl - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\PROJECTS\NOJ_022_POPAMAIL"

!ELSEIF  "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Debug"

"fjsl - Win32 Debug" : 
   cd "\USR\CODE\MYNOJ\FASTJOB\lib\vc6\fjsl"
   $(MAKE) /$(MAKEFLAGS) /F .\fjsl.mak CFG="fjsl - Win32 Debug" 
   cd "..\..\..\PROJECTS\NOJ_022_POPAMAIL"

"fjsl - Win32 DebugCLEAN" : 
   cd "\USR\CODE\MYNOJ\FASTJOB\lib\vc6\fjsl"
   $(MAKE) /$(MAKEFLAGS) /F .\fjsl.mak CFG="fjsl - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\PROJECTS\NOJ_022_POPAMAIL"

!ENDIF 

!IF  "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Release"

"stdnet - Win32 Release" : 
   cd "\USR\CODE\MYNOJ\FASTJOB\LIB\VC6\stdnet"
   $(MAKE) /$(MAKEFLAGS) /F .\stdnet.mak CFG="stdnet - Win32 Release" 
   cd "..\..\..\PROJECTS\NOJ_022_POPAMAIL"

"stdnet - Win32 ReleaseCLEAN" : 
   cd "\USR\CODE\MYNOJ\FASTJOB\LIB\VC6\stdnet"
   $(MAKE) /$(MAKEFLAGS) /F .\stdnet.mak CFG="stdnet - Win32 Release" RECURSE=1 CLEAN 
   cd "..\..\..\PROJECTS\NOJ_022_POPAMAIL"

!ELSEIF  "$(CFG)" == "NOJ_022_POPAMAIL - Win32 Debug"

"stdnet - Win32 Debug" : 
   cd "\USR\CODE\MYNOJ\FASTJOB\LIB\VC6\stdnet"
   $(MAKE) /$(MAKEFLAGS) /F .\stdnet.mak CFG="stdnet - Win32 Debug" 
   cd "..\..\..\PROJECTS\NOJ_022_POPAMAIL"

"stdnet - Win32 DebugCLEAN" : 
   cd "\USR\CODE\MYNOJ\FASTJOB\LIB\VC6\stdnet"
   $(MAKE) /$(MAKEFLAGS) /F .\stdnet.mak CFG="stdnet - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\..\..\PROJECTS\NOJ_022_POPAMAIL"

!ENDIF 


!ENDIF 

