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


LIB_FILE = age_obj.lib
H_FILE   = age_obj.h

OBJS =  object.obj message.obj charact.obj regions.obj chrmodel.obj

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


# Object Module
object.obj     :   object.cpp         age_obj.h
message.obj    :   message.cpp        age_obj.h
charact.obj    :   charact.cpp        age_obj.h
regions.obj    :   regions.cpp        age_obj.h
chrmodel.obj   :   chrmodel.cpp       age_obj.h

#===========< END >=============#

