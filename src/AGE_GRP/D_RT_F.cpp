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


/*********************************
  지정된 좌 의 점을 읽어온다.
**********************************/
void DRECT :: DrawFill( INT StartX, INT StartY, INT EndX, INT EndY, COLOR Color )
{
    int i;
    int width, height;
    COLOR *p;


    if( StartX > EndX ){
      i = StartX; StartX = EndX; EndX = i;
    }
    if( StartY > EndY ){
      i = StartY; StartY = EndY; EndY = i;
    }

    if( (StartX > _Clip.EndX) || (EndX < _Clip.StartX) ||
        (StartY > _Clip.EndY) || (EndY < _Clip.StartY) )
      return;

    if( StartX < _Clip.StartX ) StartX = _Clip.StartX;
    if( EndX   > _Clip.EndX   ) EndX   = _Clip.EndX;
    if( StartY < _Clip.StartY ) StartY = _Clip.StartY;
    if( EndY   > _Clip.EndY   ) EndY   = _Clip.EndY;

    width  = EndX - StartX + 1;
    height = EndY - StartY + 1;

    p = CALC_ADDR( StartX, StartY );

    for( i = 0; i < height; i ++ ){
      memset( p, Color, width );
      p += VMEM_WIDTH;
    }
}


/*********************************
  지정된 좌 의 점을 읽어온다.
**********************************/
void DRECT :: DrawFill( void )
{
    DrawFill( StartX, StartY, EndX, EndY, Color );
}


/*********************************
  지정된 좌 의 점을 읽어온다.
**********************************/
void DREGION :: DrawFill( INT StartX, INT StartY, INT Width, INT Height, COLOR Color )
{
    DRECT::DrawFill( StartX, StartY, StartX + Width - 1, StartY + Height - 1, Color );
}



/*********************************
  지정된 좌 의 점을 읽어온다.
**********************************/
void DREGION :: DrawFill( void )
{
    DrawFill( StartX, StartY, Width, Height, Color );
}



