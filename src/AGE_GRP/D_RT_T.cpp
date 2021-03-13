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


/***************************************
  테이블에 의해 변환된 사각형을 찍는다.
****************************************/
void DRECT :: DrawTrans( INT StartX, INT StartY, INT EndX, INT EndY, COLOR *TransTable )
{
    int i, j;
    int width, height, skip;
    COLOR *p;


    if( TransTable == NULL ) return;

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

    skip = VMEM_WIDTH - width;

    for( i = 0; i < height; i ++ ){
      for( j = 0; j < width; j ++ ){
        *p = TransTable[ *p ];
        p ++;
      }

      p += skip;
    }
}


/***************************************
  테이블에 의해 변환된 사각형을 찍는다.
****************************************/
void DRECT :: DrawTrans( void )
{
    DrawTrans( StartX, StartY, EndX, EndY, _ShadeTransTable.Get() );
}


/***************************************
  테이블에 의해 변환된 사각형을 찍는다.
****************************************/
void DREGION :: DrawTrans( INT StartX, INT StartY, INT Width, INT Height, COLOR *TransTable )
{
    DRECT::DrawTrans( StartX, StartY, StartX + Width - 1, StartY + Height - 1, TransTable );
}


/***************************************
  테이블에 의해 변환된 사각형을 찍는다.
****************************************/
void DREGION :: DrawTrans( void )
{
    DrawTrans( StartX, StartY, Width, Height, _ShadeTransTable.Get() );
}



