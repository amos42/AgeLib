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


/*******************
  수직선을 그린다.
********************/
void DLINE :: DrawVertXOR( INT StartX, INT StartY, INT Length )
{
    int t;
    COLOR *p;


    if( StartX < _Clip.StartX || StartX > _Clip.EndX ) return;

    if( StartY > _Clip.EndY ) return;
    if( StartY < _Clip.StartY ){
      Length -= _Clip.StartY - StartY;
      StartY= _Clip.StartY;
    }
    t = StartY + Length - 1;
    if( t < _Clip.StartY ) return;
    if( t > _Clip.EndY ){
      Length -= t - _Clip.EndY;
    }

    p = CALC_ADDR( StartX, StartY);

    for( int i = 0; i < Length; i ++ ){
      *p ^= 0xFF;
      p += VMEM_WIDTH;
    }
}



