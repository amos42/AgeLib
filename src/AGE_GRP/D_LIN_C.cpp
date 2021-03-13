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

#include "age_grp.h"


/***********************
  이미지를 생성한다.
************************/
void DLINE :: DrawCross( INT StartX, INT StartY, INT Length, COLOR Color )
{
    int t;
    COLOR *p;


    if( StartX > _Clip.EndX || StartY > _Clip.EndY ) return;

    if( StartX < _Clip.StartX ){
      Length -= _Clip.StartX - StartX;
      StartY += _Clip.StartX - StartX;
      StartX = _Clip.StartX;
    }
    if( StartY < _Clip.StartY ){
      Length -= _Clip.StartY - StartY;
      StartX += _Clip.StartY - StartY;
      StartY = _Clip.StartY;
    }

    t = StartX + Length - 1;
    if( t < _Clip.StartX ) return;
    if( t > _Clip.EndX ){
      Length -= t - _Clip.EndX;
    }
    t = StartY + Length - 1;
    if( t < _Clip.StartY ) return;
    if( t > _Clip.EndY ){
      Length -= t - _Clip.EndY;
    }

    p = CALC_ADDR( StartX, StartY );

    while( Length -- ){
      *p = Color;
      p += VMEM_WIDTH + 1;
    }
}



