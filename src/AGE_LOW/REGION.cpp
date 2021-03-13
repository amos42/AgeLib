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

#include "age_low.h"


/**********************************
  점이 영역 안에 있는가를 살핀다.
***********************************/
BOOL REGION :: IsInnerPoint( INT X, INT Y )
{
    return( X >= StartX && X < StartX + Width &&
            Y >= StartY && Y < StartY + Height );
}


/***********************************
  점이 영역 안에 있는가를 살핀다.
************************************/
BOOL REGION :: IsInnerPoint( POINT &Point )
{
    return( Point.X >= StartX && Point.X < StartX + Width &&
            Point.Y >= StartY && Point.Y < StartY + Height );
}


/**********************************
  두 영역이 중복되었는가를 살핀다.
***********************************/
BOOL REGION :: IsIntersect( REGION &Reg )
{
    if( StartX < Reg.StartX ){
      if( Reg.StartX >= StartX + Width ) return( FALSE );
    } else {
      if( StartX >= Reg.StartX + Reg.Width ) return( FALSE );
    }

    if( StartY < Reg.StartY ){
      if( Reg.StartY >= StartY + Height ) return( FALSE );
    } else {
      if( StartY >= Reg.StartY + Reg.Height ) return( FALSE );
    }

    return( TRUE );
}


/*******************************
  두 영역이 중복된 부분을 세트
********************************/
void REGION :: Intersect( REGION *DesReg, REGION &Reg )
{
    int temp;

    if( StartX < Reg.StartX ){
      DesReg->StartX = Reg.StartX;
      temp = StartX + Width - Reg.StartX + 1;
      DesReg->Width  = (temp <= Reg.Width)? temp : Reg.Width;
    } else {
      DesReg->StartX = StartX;
      temp = Reg.StartX + Reg.Width - StartX + 1;
      DesReg->Width  = (temp <= Width)? temp : Width;
    }

    if( StartY < Reg.StartY ){
      DesReg->StartY = Reg.StartY;
      temp = StartY + Height - Reg.StartY + 1;
      DesReg->Height = (temp <= Reg.Height)? temp : Reg.Height;
    } else {
      DesReg->StartY = StartY;
      temp = Reg.StartY + Reg.Height - StartY + 1;
      DesReg->Height = (temp <= Height)? temp : Height;
    }
}


