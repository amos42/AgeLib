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



/*************************
  사각형을 정규화시킨다.
**************************/
void RECT :: Normal( void )
{
    int temp;

    if( StartX > EndX ){
      temp   = StartX;
      StartX = EndX;
      EndX   = temp;
    }

    if( StartY > EndY ){
      temp   = StartY;
      StartY = EndY;
      EndY   = temp;
    }
}


/***********************************
  점이 사각형 안에 있는가를 살핀다.
************************************/
BOOL RECT :: IsInnerPoint( INT X, INT Y )
{
    return( X >= StartX && X <= EndX &&
            Y >= StartY && Y <= EndY );
}


/***********************************
  점이 사각형 안에 있는가를 살핀다.
************************************/
BOOL RECT :: IsInnerPoint( POINT &Point )
{
    return( Point.X >= StartX && Point.X <= EndX &&
            Point.Y >= StartY && Point.Y <= EndY );
}


/*************************************
  두 사각형이 중복되었는가를 살핀다.
**************************************/
BOOL RECT :: IsIntersect( RECT &Rect )
{
    if( StartX < Rect.StartX )
      if( Rect.StartX > EndX ) return( FALSE );
    else
      if( StartX > Rect.EndX ) return( FALSE );

    if( StartY < Rect.StartY )
      if( Rect.StartY > EndY ) return( FALSE );
    else
      if( StartY > Rect.EndY ) return( FALSE );

    return( TRUE );
}


/*************************************
  두 사각형의 중복된 영역을 세트한다.
  만약 사각형이 정규화되지 않았고,
  또 서로 겹치지 않았다면 정상적인
  결과가 나오지 않는다.
**************************************/
void RECT :: Intersect( RECT *DesRect, RECT &Rect )
{
    DesRect->StartX = ( StartX > Rect.StartX )? StartX : Rect.StartX;
    DesRect->StartY = ( StartY > Rect.StartY )? StartY : Rect.StartY;

    DesRect->EndX   = ( EndX < Rect.EndX )? EndX : Rect.EndX;
    DesRect->EndY   = ( EndY < Rect.EndY )? EndY : Rect.EndY;
}


