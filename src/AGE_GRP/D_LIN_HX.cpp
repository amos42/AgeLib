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
  수평선을 그린다.
************************/
void DLINE :: DrawHorizXOR( INT StartX, INT StartY, INT Length )
{
    int i, t;
    COLOR *p;


    if( StartX > _Clip.EndX ) return;
    if( StartX < _Clip.StartX ){
      Length -= _Clip.StartX - StartX;
      StartX = _Clip.StartX;
    }
    t = StartX + Length - 1;
    if( t < _Clip.StartX ) return;
    if( t > _Clip.EndX ){
      Length -= t - _Clip.EndX;
    }

    p = CALC_ADDR( StartX, StartY );

    for( i = 0; i < Length; i ++ ){
      *p ^= 0xFF;
      p ++;
    }
}



