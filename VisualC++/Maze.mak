# Microsoft Developer Studio Generated NMAKE File, Based on Maze.dsp
!IF "$(CFG)" == ""
CFG=Maze - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Maze - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Maze - Win32 Release" && "$(CFG)" != "Maze - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Maze.mak" CFG="Maze - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Maze - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Maze - Win32 Debug" (based on "Win32 (x86) Console Application")
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

!IF  "$(CFG)" == "Maze - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Maze.exe"


CLEAN :
	-@erase "$(INTDIR)\Bitmap.obj"
	-@erase "$(INTDIR)\Camera.obj"
	-@erase "$(INTDIR)\Cell.obj"
	-@erase "$(INTDIR)\Collision.obj"
	-@erase "$(INTDIR)\Colour.obj"
	-@erase "$(INTDIR)\Control.obj"
	-@erase "$(INTDIR)\Cylinder.obj"
	-@erase "$(INTDIR)\Disc.obj"
	-@erase "$(INTDIR)\Display.obj"
	-@erase "$(INTDIR)\Game.obj"
	-@erase "$(INTDIR)\Group.obj"
	-@erase "$(INTDIR)\Label.obj"
	-@erase "$(INTDIR)\Light.obj"
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\Material.obj"
	-@erase "$(INTDIR)\Maze.obj"
	-@erase "$(INTDIR)\Mesh.obj"
	-@erase "$(INTDIR)\Node.obj"
	-@erase "$(INTDIR)\Plane.obj"
	-@erase "$(INTDIR)\Polyhedron.obj"
	-@erase "$(INTDIR)\Reader.obj"
	-@erase "$(INTDIR)\Reference.obj"
	-@erase "$(INTDIR)\Scene.obj"
	-@erase "$(INTDIR)\Screen.obj"
	-@erase "$(INTDIR)\Shape.obj"
	-@erase "$(INTDIR)\Sound.obj"
	-@erase "$(INTDIR)\Sphere.obj"
	-@erase "$(INTDIR)\Texture.obj"
	-@erase "$(INTDIR)\Transform.obj"
	-@erase "$(INTDIR)\Triangle.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Vectors.obj"
	-@erase "$(OUTDIR)\Maze.exe"
	-@erase "$(OUTDIR)\Maze.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\Maze.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Maze.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS= kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\Maze.pdb" /machine:I386 /out:"$(OUTDIR)\Maze.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Bitmap.obj" \
	"$(INTDIR)\Camera.obj" \
	"$(INTDIR)\Cell.obj" \
	"$(INTDIR)\Collision.obj" \
	"$(INTDIR)\Colour.obj" \
	"$(INTDIR)\Control.obj" \
	"$(INTDIR)\Cylinder.obj" \
	"$(INTDIR)\Disc.obj" \
	"$(INTDIR)\Display.obj" \
	"$(INTDIR)\Game.obj" \
	"$(INTDIR)\Group.obj" \
	"$(INTDIR)\Label.obj" \
	"$(INTDIR)\Light.obj" \
	"$(INTDIR)\Main.obj" \
	"$(INTDIR)\Material.obj" \
	"$(INTDIR)\Maze.obj" \
	"$(INTDIR)\Mesh.obj" \
	"$(INTDIR)\Node.obj" \
	"$(INTDIR)\Plane.obj" \
	"$(INTDIR)\Polyhedron.obj" \
	"$(INTDIR)\Reader.obj" \
	"$(INTDIR)\Reference.obj" \
	"$(INTDIR)\Scene.obj" \
	"$(INTDIR)\Screen.obj" \
	"$(INTDIR)\Shape.obj" \
	"$(INTDIR)\Sound.obj" \
	"$(INTDIR)\Sphere.obj" \
	"$(INTDIR)\Texture.obj" \
	"$(INTDIR)\Transform.obj" \
	"$(INTDIR)\Triangle.obj" \
	"$(INTDIR)\Vectors.obj"

"$(OUTDIR)\Maze.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Maze - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Maze.exe"


CLEAN :
	-@erase "$(INTDIR)\Bitmap.obj"
	-@erase "$(INTDIR)\Camera.obj"
	-@erase "$(INTDIR)\Cell.obj"
	-@erase "$(INTDIR)\Collision.obj"
	-@erase "$(INTDIR)\Colour.obj"
	-@erase "$(INTDIR)\Control.obj"
	-@erase "$(INTDIR)\Cylinder.obj"
	-@erase "$(INTDIR)\Disc.obj"
	-@erase "$(INTDIR)\Display.obj"
	-@erase "$(INTDIR)\Game.obj"
	-@erase "$(INTDIR)\Group.obj"
	-@erase "$(INTDIR)\Label.obj"
	-@erase "$(INTDIR)\Light.obj"
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\Material.obj"
	-@erase "$(INTDIR)\Maze.obj"
	-@erase "$(INTDIR)\Mesh.obj"
	-@erase "$(INTDIR)\Node.obj"
	-@erase "$(INTDIR)\Plane.obj"
	-@erase "$(INTDIR)\Polyhedron.obj"
	-@erase "$(INTDIR)\Reader.obj"
	-@erase "$(INTDIR)\Reference.obj"
	-@erase "$(INTDIR)\Scene.obj"
	-@erase "$(INTDIR)\Screen.obj"
	-@erase "$(INTDIR)\Shape.obj"
	-@erase "$(INTDIR)\Sound.obj"
	-@erase "$(INTDIR)\Sphere.obj"
	-@erase "$(INTDIR)\Texture.obj"
	-@erase "$(INTDIR)\Transform.obj"
	-@erase "$(INTDIR)\Triangle.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Vectors.obj"
	-@erase "$(OUTDIR)\Maze.exe"
	-@erase "$(OUTDIR)\Maze.ilk"
	-@erase "$(OUTDIR)\Maze.map"
	-@erase "$(OUTDIR)\Maze.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_OPENAL" /Fp"$(INTDIR)\Maze.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Maze.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib alut.lib openal32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\Maze.pdb" /map:"$(INTDIR)\Maze.map" /debug /machine:I386 /out:"$(OUTDIR)\Maze.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Bitmap.obj" \
	"$(INTDIR)\Camera.obj" \
	"$(INTDIR)\Cell.obj" \
	"$(INTDIR)\Collision.obj" \
	"$(INTDIR)\Colour.obj" \
	"$(INTDIR)\Control.obj" \
	"$(INTDIR)\Cylinder.obj" \
	"$(INTDIR)\Disc.obj" \
	"$(INTDIR)\Display.obj" \
	"$(INTDIR)\Game.obj" \
	"$(INTDIR)\Group.obj" \
	"$(INTDIR)\Label.obj" \
	"$(INTDIR)\Light.obj" \
	"$(INTDIR)\Main.obj" \
	"$(INTDIR)\Material.obj" \
	"$(INTDIR)\Maze.obj" \
	"$(INTDIR)\Mesh.obj" \
	"$(INTDIR)\Node.obj" \
	"$(INTDIR)\Plane.obj" \
	"$(INTDIR)\Polyhedron.obj" \
	"$(INTDIR)\Reader.obj" \
	"$(INTDIR)\Reference.obj" \
	"$(INTDIR)\Scene.obj" \
	"$(INTDIR)\Screen.obj" \
	"$(INTDIR)\Shape.obj" \
	"$(INTDIR)\Sound.obj" \
	"$(INTDIR)\Sphere.obj" \
	"$(INTDIR)\Texture.obj" \
	"$(INTDIR)\Transform.obj" \
	"$(INTDIR)\Triangle.obj" \
	"$(INTDIR)\Vectors.obj"

"$(OUTDIR)\Maze.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("Maze.dep")
!INCLUDE "Maze.dep"
!ELSE 
!MESSAGE Warning: cannot find "Maze.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Maze - Win32 Release" || "$(CFG)" == "Maze - Win32 Debug"
SOURCE=..\Source\Bitmap.cpp

"$(INTDIR)\Bitmap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Camera.cpp

"$(INTDIR)\Camera.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Cell.cpp

"$(INTDIR)\Cell.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Collision.cpp

"$(INTDIR)\Collision.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Colour.cpp

"$(INTDIR)\Colour.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Control.cpp

"$(INTDIR)\Control.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Cylinder.cpp

"$(INTDIR)\Cylinder.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Disc.cpp

"$(INTDIR)\Disc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Display.cpp

"$(INTDIR)\Display.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Game.cpp

"$(INTDIR)\Game.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Group.cpp

"$(INTDIR)\Group.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Label.cpp

"$(INTDIR)\Label.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Light.cpp

"$(INTDIR)\Light.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Main.cpp

"$(INTDIR)\Main.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Material.cpp

"$(INTDIR)\Material.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Maze.cpp

"$(INTDIR)\Maze.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Mesh.cpp

"$(INTDIR)\Mesh.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Node.cpp

"$(INTDIR)\Node.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Plane.cpp

"$(INTDIR)\Plane.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Polyhedron.cpp

"$(INTDIR)\Polyhedron.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Reader.cpp

"$(INTDIR)\Reader.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Reference.cpp

"$(INTDIR)\Reference.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Scene.cpp

"$(INTDIR)\Scene.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Screen.cpp

"$(INTDIR)\Screen.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Shape.cpp

"$(INTDIR)\Shape.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Sound.cpp

"$(INTDIR)\Sound.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Sphere.cpp

"$(INTDIR)\Sphere.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Texture.cpp

"$(INTDIR)\Texture.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Transform.cpp

"$(INTDIR)\Transform.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Triangle.cpp

"$(INTDIR)\Triangle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Source\Vectors.cpp

"$(INTDIR)\Vectors.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

