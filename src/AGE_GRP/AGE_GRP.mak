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


LIB_FILE = age_grp.lib
H_FILE   = age_grp.h

OBJS =  screen.obj pixel.obj scroll.obj &
        d_line.obj d_lin_h.obj d_lin_v.obj d_lin_c.obj &
        d_lin_ht.obj d_lin_vt.obj &
        d_lin_hx.obj d_lin_vx.obj &
        d_rt.obj d_rt_f.obj d_rt_t.obj d_rt_x.obj &
        d_cir.obj d_cir_f.obj d_cir_t.obj &
        d_tri.obj d_tri_f.obj d_tri_t.obj &
        image.obj img_get.obj img_put.obj &
        img_c.obj img_s.obj img_st.obj img_t.obj img_trt.obj &
        palatte.obj palmap.obj findcol.obj dp_pal.obj &
        text.obj font.obj &
        sprite.obj &
        tile.obj map.obj

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


#LIBS = age_voc\age_voc.lib age_mus\age_mus.lib


#===========================
# Modules
#===========================

.c.obj:
  @$(CC_EXE) $(CC_OPTION) $[.
.cpp.obj:
  @$(CPP_EXE) $(CPP_OPTION) $[.
.asm.obj:
  @$(ASM_EXE) $(ASM_OPTION) $[.


screen.obj   :   screen.cpp      age_grp.h
pixel.obj    :   pixel.cpp       age_grp.h
scroll.obj   :   scroll.cpp      age_grp.h

# Draw Line
d_line.obj   :   d_line.cpp      age_grp.h
d_lin_h.obj  :   d_lin_h.cpp     age_grp.h
d_lin_v.obj  :   d_lin_v.cpp     age_grp.h
d_lin_c.obj  :   d_lin_c.cpp     age_grp.h
d_lin_ht.obj :   d_lin_ht.cpp    age_grp.h
d_lin_vt.obj :   d_lin_vt.cpp    age_grp.h
d_lin_hx.obj :   d_lin_hx.cpp    age_grp.h
d_lin_vx.obj :   d_lin_vx.cpp    age_grp.h

# Draw Rectangle
d_rt.obj     :   d_rt.cpp        age_grp.h
d_rt_f.obj   :   d_rt_f.cpp      age_grp.h
d_rt_t.obj   :   d_rt_t.cpp      age_grp.h
d_rt_x.obj   :   d_rt_x.cpp      age_grp.h

# Draw Circle
d_cir.obj    :   d_cir.cpp       age_grp.h
d_cir_f.obj  :   d_cir_f.cpp     age_grp.h
d_cir_t.obj  :   d_cir_t.cpp     age_grp.h

# Draw Trangle
d_tri.obj    :   d_tri.cpp       age_grp.h
d_tri_f.obj  :   d_tri_f.cpp     age_grp.h
d_tri_t.obj  :   d_tri_t.cpp     age_grp.h

# Image
image.obj    :   image.cpp       age_grp.h
img_get.obj  :   img_get.cpp     age_grp.h
img_put.obj  :   img_put.cpp     age_grp.h
img_c.obj    :   img_c.cpp       age_grp.h
img_s.obj    :   img_s.cpp       age_grp.h
img_st.obj   :   img_st.cpp      age_grp.h
img_t.obj    :   img_t.cpp       age_grp.h
img_trt.obj  :   img_trt.cpp     age_grp.h

# Palette
pal_low.obj  :   pal_low.cpp     age_grp.h
palette.obj  :   palette.cpp     age_grp.h
findcol.obj  :   findcol.cpp     age_grp.h
dp_pal.obj   :   dp_pal.cpp      age_grp.h

# Text
text.obj     :   text.cpp        age_grp.h
font.obj     :   font.cpp

# Sprite
sprite.obj   :   sprite.cpp      age_grp.h

# Tile & Map
tile.obj     :   tile.cpp        age_grp.h
map.obj      :   map.cpp         age_grp.h

#===========< END >=============#

