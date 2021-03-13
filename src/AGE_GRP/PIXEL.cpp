/*#################################################################
-------------------------------------------------------------------

                             AGE (Ver 1.0)
                       (* =================== *)
                           Amos Game Engine

 Author         : Chu, Kyong-min( Amos )

 Date           : 1997/02/08
 C Compiler     : WATCOM 11.0
 Assembler      : WASM 11.0

-------------------------------------------------------------------
###################################################################*/

#include "age_grp.h"


#if 0
/******************
  PIXEL의 생성자
*******************/
PIXEL :: PIXEL( void )
{
    X = Y = 0;
    Color = 255;
}


/******************
  PIXEL의 생성자
*******************/
PIXEL :: PIXEL( INT X, INT Y, COLOR Color )
{
    Set( X, Y, Color );
}


/******************
  PIXEL의 소멸자
*******************/
PIXEL :: ~PIXEL()
{
}


/***********************
  PIXEL 값을 세트한다.
************************/
void PIXEL :: Set( INT X, INT Y, COLOR Color )
{
    this->X = X;
    this->Y = Y;
    this->Color = Color;
}
#endif


/*********************************
  지정된 좌표의 점을 읽어온다.
**********************************/
COLOR PIXEL :: Get( void )
{
    if( X < _Clip.StartX || X > _Clip.EndX ||
        Y < _Clip.StartY || Y > _Clip.EndY ) return( _TransColor );

    return( (Color = *CALC_ADDR( X, Y )) );
}


/*********************************
  지정된 좌표의 점을 읽어온다.
**********************************/
COLOR PIXEL :: Get( INT X, INT Y )
{
    if( X < _Clip.StartX || X > _Clip.EndX ||
        Y < _Clip.StartY || Y > _Clip.EndY ) return( _TransColor );

    return( *CALC_ADDR( X, Y ) );
}


/*********************************
  지정된 좌표의 점을 읽어온다.
**********************************/
void PIXEL :: Put( void )
{
    if( X < _Clip.StartX || X > _Clip.EndX ||
        Y < _Clip.StartY || Y > _Clip.EndY ) return;

    *CALC_ADDR( X, Y ) = Color;
}

/*********************************
  지정된 좌표의 점을 읽어온다.
**********************************/
void PIXEL :: Put( INT X, INT Y, COLOR Color )
{
    if( X < _Clip.StartX || X > _Clip.EndX ||
        Y < _Clip.StartY || Y > _Clip.EndY ) return;

    *CALC_ADDR( X, Y ) = Color;
}



