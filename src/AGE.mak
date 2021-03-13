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


LIB_FILE = age.lib
H_FILE   = age.h

LIBS = age_low\age_low.lib &
       age_in\age_in.lib   &
       age_grp\age_grp.lib &
       age_res\age_res.lib &
       age_obj\age_obj.lib
#       age_voc\age_voc.lib &
#       age_mus\age_mus.lib

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


#===========< END >=============#

