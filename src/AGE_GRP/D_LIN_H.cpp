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
void DLINE :: DrawHoriz( INT StartX, INT StartY, INT Length, COLOR Color )
{
    int i, t;
    int w2;
    COLOR *p;
    long c;


    if( StartY < _Clip.StartY || StartY > _Clip.EndY ) return;

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

    c = (unsigned long)Color;
    c |= c << 8;
    c |= c << 16;

    p = CALC_ADDR( StartX, StartY );

    w2 = Length & 0x03;
    Length >>= 2;

    for( i = 0; i < Length; i ++ ){
      *(long *)p = c;
      p += sizeof(long);
    }

    for( i = 0; i < w2; i ++ )
      *p++ = (COLOR)c;
}


/***********************
  수평선을 그린다 (2).
************************/
void DLINE :: DrawHoriz2( INT StartX, INT StartY, INT EndX, COLOR Color )
{
    if( StartX > EndX ){
      int temp = StartX; StartX = EndX; EndX = temp;
    }

    DLINE::DrawHoriz( StartX, StartY, EndX - StartX + 1, Color );
}



