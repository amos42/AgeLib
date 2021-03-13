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

#include <stdio.h>
#include <string.h>
#include "age_grp.h"


typedef struct {
    CHAR    Header[20];
    LONG    Ver;
    LONG    Count;
    LONG    Width, Height;
} TIL_HEADER;


/****************
  TILE의 생성자
*****************/
TILE :: TILE( void )
{
    Count = 0;
    Width = Height = 0;
    Bitmap = NULL;
}


/****************
  TILE의 생성자
*****************/
TILE :: TILE( STRING FileName )
{
    Count = 0;
    Width = Height = 0;
    Bitmap = NULL;

    Load( FileName );
}


/****************
  TILE의 소멸자
*****************/
TILE :: ~TILE()
{
    Clear();
}


/****************
  TILE을 지운다.
*****************/
void TILE :: Clear( void )
{
    Count = 0;
    Width = Height = 0;
    if( Bitmap ) delete Bitmap;
    Bitmap = 0;
}


BOOL TILE :: Load( STRING FileName )
{
    Clear();

    char *res;
    if( !_Resource.Load( FileName, &res ) ) return( FALSE );
    char *temp = res;

    TIL_HEADER *th = (TIL_HEADER *)res;
    res += sizeof(TIL_HEADER);
    if( strcmp( th->Header, "Amos Tile File;" ) ) return( 2 );

    Count  = th->Count;
    Width  = th->Width;
    Height = th->Height;

    int TileSize = Count * Width * Height;

    Bitmap = new CHAR[ TileSize ];
    memcpy( Bitmap, res, TileSize );

    free( temp );

    return( TRUE );
}


void TILE :: Put( INT X, INT Y, INT Index )
{
    if( Index >= Count ) return;

    int width  = Width;
    int height = Height;

    if( width == 0 || height == 0 ) return;

    char *ImgPtr = Bitmap + width * height * Index;

    if( Y > _Clip.EndY ) return;
    if( Y < _Clip.StartY ){
      height -= _Clip.StartY - Y;
      ImgPtr += (_Clip.StartY - Y) * width;
      Y = _Clip.StartY;
    }

    int t = Y + height - 1;
    if( t < _Clip.StartY ) return;
    if( t > _Clip.EndY ){
      height -= t - _Clip.EndY;
    }

    int iskip = 0;
    if( X > _Clip.EndX ) return;
    if( X < _Clip.StartX ){
      width -= _Clip.StartX - X;
      ImgPtr += _Clip.StartX - X;
      iskip += _Clip.StartX - X;
      X = _Clip.StartX;
    }
    t = X + width - 1;
    if( t < _Clip.StartX ) return;
    if( t > _Clip.EndX ){
      width -= t - _Clip.EndX;
      iskip += t - _Clip.EndX;
    }

    char *ScrPtr = CALC_ADDR( X, Y );

    int sskip = VMEM_WIDTH - width;

    int w2 = width & 0x03;
    width >>= 2;

    for( int i = 0; i < height; i ++ ){
      for( int j = 0; j < width; j ++ ){
        *((long *)ScrPtr) = *((long *)ImgPtr);
        ScrPtr += sizeof(long);
        ImgPtr += sizeof(long);
      }

      for( j = 0; j < w2; j ++ )
        *ScrPtr++ = *ImgPtr++;

      ScrPtr += sskip;
      ImgPtr += iskip;
    }
}



