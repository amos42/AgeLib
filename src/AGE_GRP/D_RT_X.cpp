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


/*********************************
  지정된 좌 의 점을 읽어온다.
**********************************/
void DRECT :: DrawXOR( INT StartX, INT StartY, INT EndX, INT EndY )
{
    if( StartX > EndX ){
      int i = StartX; StartX = EndX; EndX = i;
    }
    if( StartY > EndY ){
      int i = StartY; StartY = EndY; EndY = i;
    }

    DLINE::DrawHorizXOR( StartX, StartY,     EndX - StartX + 1 );
    DLINE::DrawVertXOR(  StartX, StartY + 1, EndY - StartY - 1 );
    DLINE::DrawVertXOR(  EndX,   StartY + 1, EndY - StartY - 1 );
    DLINE::DrawHorizXOR( StartX, EndY,       EndX - StartX + 1 );
}


/*********************************
  지정된 좌 의 점을 읽어온다.
**********************************/
void DRECT :: DrawXOR( void )
{
     DrawXOR( StartX, StartY, EndX, EndY );
}


/*********************************
  지정된 좌 의 점을 읽어온다.
**********************************/
void DREGION :: DrawXOR( INT StartX, INT StartY, INT Width, INT Height )
{
    DRECT::DrawXOR( StartX, StartY, StartX + Width - 1, StartY + Height - 1 );
}


/*********************************
  지정된 좌 의 점을 읽어온다.
**********************************/
void DREGION :: DrawXOR( void )
{
    DrawXOR( StartX, StartY, Width, Height );
}



