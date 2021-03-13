#============================#
#                            #
#  AGE Library MAKE File     #
#           Chu, Kyong-min   #
#                            #
#============================#

#===========================
# Compiler & Option
#===========================
CC_EXE = c:\language\watcom\binw\wcc386.exe
CPP_EXE = c:\language\watcom\binw\wpp386.exe
ASM_EXE = c:\language\watcom\binw\wasm.exe
LIB_EXE = c:\language\watcom\binw\wlib.exe

DEBUG = no


!ifeq DEBUG yes
CC_OPTION  = -od -d2
CPP_OPTION = -od -d2
ASM_OPTION =
!else
CC_OPTION  = -ox
CPP_OPTION = -ox
ASM_OPTION =
!endif


LIB_FILE = age_low.lib
H_FILE   = age_low.h

OBJS =  age_low.obj crtc.obj timer.obj trans.obj f_skip.obj &
        sqrt.obj trifunc.obj &
        rect.obj region.obj

LIBS =

all : $(LIB_FILE)


#===========================
# Library
#===========================

$(LIB_FILE) : $(OBJS) $(LIBS) $(H_FILE)

  @%create age.mkl
  @for %i in ($(OBJS)) do @%append age.mkl +%i
  @for %i in ($(LIBS)) do @%append age.mkl +%i
  @$(LIB_EXE) -n -b $(LIB_FILE) @age.mkl
  @del age.mkl


#===========================
# Modules
#===========================

.c.obj:
  @$(CC_EXE) $(CC_OPTION) $[.
.cpp.obj:
  @$(CPP_EXE) $(CPP_OPTION) $[.
.asm.obj:
  @$(ASM_EXE) $(ASM_OPTION) $[.


# Common Module
age_low.obj  :   age_low.cpp     age_low.h
crtc.obj     :   crtc.cpp        age_low.h
timer.obj    :   timer.cpp       age_low.h
f_skip.obj   :   f_skip.cpp      age_low.h
sqrt.obj     :   sqrt.asm
trifunc.obj  :   trifunc.cpp     age_low.h

rect.obj     :   rect.cpp        age_low.h
region.obj   :   region.cpp      age_low.h


#===========< END >=============#

