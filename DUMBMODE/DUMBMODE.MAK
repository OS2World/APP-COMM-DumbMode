PROJ = DUMBMODE
PROJFILE = DUMBMODE.MAK
DEBUG = 0

PWBRMAKE  = pwbrmake
NMAKEBSC1  = set
NMAKEBSC2  = nmake
LINKER  = link
ILINK  = ilink
LRF  = echo > NUL
BIND  = bind
RC  = rc
IMPLIB  = implib
LFLAGS_G  =  /NOI  /BATCH
LFLAGS_D  =  /CO /NOF /NOP  /PMTYPE:VIO
LFLAGS_R  =  /E /NOF /NOP  /PMTYPE:VIO
MAPFILE_D  = NUL
MAPFILE_R  = NUL
CC  = cl
CFLAGS_G  = /AL /W3 /G2 /Zp /BATCH
CFLAGS_D  = /qc /Od /Zi /Gs
CFLAGS_R  = /Ot /Ol /Og /Oe /Oi /Gs
LLIBS_R  =  /NOD:LLIBCE LLIBCEP
LLIBS_D  =  /NOD:LLIBCE LLIBCEP
ASM  = masm
AFLAGS_G  = /Mx /T
AFLAGS_D  = /Zi

OBJS  = dumbmode.obj
SBRS  = dumbmode.sbr

all: $(PROJ).exe

.SUFFIXES: .c .sbr .obj

dumbmode.obj : dumbmode.c

dumbmode.sbr : dumbmode.c


$(PROJ).bsc : $(SBRS)
        $(PWBRMAKE) @<<
$(BRFLAGS) $(SBRS)
<<

$(PROJ).exe : $(OBJS)
!IF $(DEBUG)
        $(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_D)
$(LLIBS_G: = +^
) +
$(LLIBS_D: = +^
) +
$(LIBS: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_D);
<<
!ELSE
        $(LRF) @<<$(PROJ).lrf
$(RT_OBJS: = +^
) $(OBJS: = +^
)
$@
$(MAPFILE_R)
$(LLIBS_G: = +^
) +
$(LLIBS_R: = +^
) +
$(LIBS: = +^
)
$(DEF_FILE) $(LFLAGS_G) $(LFLAGS_R);
<<
!ENDIF
!IF $(DEBUG)
        $(LINKER) @$(PROJ).lrf
!ELSE
        $(LINKER) @$(PROJ).lrf
!ENDIF


.c.sbr :
!IF $(DEBUG)
        $(CC) /Zs $(CFLAGS_G) $(CFLAGS_D) /FR$@ $<
!ELSE
        $(CC) /Zs $(CFLAGS_G) $(CFLAGS_R) /FR$@ $<
!ENDIF

.c.obj :
!IF $(DEBUG)
        $(CC) /c $(CFLAGS_G) $(CFLAGS_D) /Fo$@ $<
!ELSE
        $(CC) /c $(CFLAGS_G) $(CFLAGS_R) /Fo$@ $<
!ENDIF


run: $(PROJ).exe
        $(PROJ).exe $(RUNFLAGS)

debug: $(PROJ).exe
        CVP $(CVFLAGS) $(PROJ).exe $(RUNFLAGS)
