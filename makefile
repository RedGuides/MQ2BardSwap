!include "../global.mak"

ALL : "$(OUTDIR)\MQ2Bardswap.dll"

CLEAN :
	-@erase "$(INTDIR)\MQ2Bardswap.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\MQ2Bardswap.dll"
	-@erase "$(OUTDIR)\MQ2Bardswap.exp"
	-@erase "$(OUTDIR)\MQ2Bardswap.lib"
	-@erase "$(OUTDIR)\MQ2Bardswap.pdb"


LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(DETLIB) ..\Release\MQ2Main.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\MQ2Bardswap.pdb" /debug /machine:I386 /out:"$(OUTDIR)\MQ2Bardswap.dll" /implib:"$(OUTDIR)\MQ2Bardswap.lib" /OPT:NOICF /OPT:NOREF 
LINK32_OBJS= \
	"$(INTDIR)\MQ2Bardswap.obj" \
	"$(OUTDIR)\MQ2Main.lib"

"$(OUTDIR)\MQ2Bardswap.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) $(LINK32_FLAGS) $(LINK32_OBJS)


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("MQ2Bardswap.dep")
!INCLUDE "MQ2Bardswap.dep"
!ELSE 
!MESSAGE Warning: cannot find "MQ2Bardswap.dep"
!ENDIF 
!ENDIF 


SOURCE=.\MQ2Bardswap.cpp

"$(INTDIR)\MQ2Bardswap.obj" : $(SOURCE) "$(INTDIR)"

