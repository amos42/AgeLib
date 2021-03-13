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
void DRECT :: Draw( INT StartX, INT StartY, INT EndX, INT EndY, COLOR Color )
{
    int i;


    if( StartX > EndX ){
      i = StartX; StartX = EndX; EndX = i;
    }
    if( StartY > EndY ){
      i = StartY; StartY = EndY; EndY = i;
    }

    DLINE::DrawHoriz( StartX, StartY,     EndX - StartX + 1, Color );
    DLINE::DrawVert(  StartX, StartY + 1, EndY - StartY - 1, Color );
    DLINE::DrawVert(  EndX,   StartY + 1, EndY - StartY - 1, Color );
    DLINE::DrawHoriz( StartX, EndY,       EndX - StartX + 1, Color );
}


/*********************************
  지정된 좌 의 점을 읽어온다.
**********************************/
void DRECT :: Draw( void )
{
    Draw( StartX, StartY, EndX, EndY, Color );
}


/*********************************
  지정된 좌 의 점을 읽어온다.
**********************************/
void DREGION :: Draw( INT StartX, INT StartY, INT Width, INT Height, COLOR Color )
{
    DLINE::DrawHoriz( StartX,   StartY++, Width, Color );
    Height --;
    DLINE::DrawVert(  StartX++, StartY,   Height,  Color );
    Width --;
    DLINE::DrawHoriz( StartX,   StartY + --Height,   Width, Color );
    DLINE::DrawVert(  StartX + --Width, StartY, Height, Color );
}


/*********************************
  지정된 좌 의 점을 읽어온다.
**********************************/
void DREGION :: Draw( void )
{
    Draw( StartX, StartY, Width, Height, Color );
}



