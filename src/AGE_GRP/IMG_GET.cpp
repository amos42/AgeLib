/*#################################################################
-------------------------------------------------------------------

                             AGE (Ver 1.0)
                       (* =================== *)
                           Amos Game Engine

 Author         : Chu, Kyong-min( Amos )

 Date           : 1997/02/08
 C Compiler     : WATCOM 10.5
 Assembler      : WASM 10.5

-------------------------------------------------------------------
###################################################################*/

#include <string.h>
#include "age_grp.h"


/***********************
  이미지를 생성한다.
************************/
void IMAGE :: Get( INT X, INT Y )
{
    int i;
    COLOR *ScrPtr, *ImgPtr;
    int width, height;


    width = Width;
    height = Height;

    if( width == 0 || height == 0 ) return;

    ScrPtr = CALC_ADDR( X + LogX, Y + LogY );
    ImgPtr = Bitmap;

    for( i = 0; i < height; i ++ ){
      memcpy( ImgPtr, ScrPtr, width );
      ImgPtr += width;
      ScrPtr += VMEM_WIDTH;
    }
}



