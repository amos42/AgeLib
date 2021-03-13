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

#include <stdio.h>
#include <string.h>
#include "age_grp.h"


struct PIC_HEADER {
    CHAR     Header[20];
    INT      Ver;
    INT      Width, Height;
};


SCREEN      _Screen( (COLOR *)0xA0000 );


/*************************
  스크린 개체의 생성자
**************************/
SCREEN :: SCREEN( void ) : PALETTEMAP()
{
    Video = new COLOR[ VMEM_SIZE ];

    IsVirtual = TRUE;

    Clear( 0 );
}


/*************************
  스크린 개체의 생성자
**************************/
SCREEN :: SCREEN( COLOR *Video ) : PALETTEMAP()
{
    this->Video = Video;

    IsVirtual = FALSE;
}


/*************************
  스크린 개체의 생성자
**************************/
SCREEN :: SCREEN( STRING FileName ) : PALETTEMAP()
{
    Video = new COLOR[ VMEM_SIZE ];

    Load( FileName );

    IsVirtual = TRUE;
}


/*************************
  스크린 개체의 소멸자
**************************/
SCREEN :: ~SCREEN()
{
    if( IsVirtual ) delete Video;
}


/******************************
  페이지 간에 내용을 복사한다.
*******************************/
SCREEN &SCREEN :: operator = ( const SCREEN &Screen )
{
    memcpy( Video, Screen.Video, VMEM_SIZE );
    memcpy( Palette, Screen.Palette, 256*sizeof(PALETTE) );

    return( *this );
}


/******************************
  페이지 간에 내용을 복사한다.
*******************************/
SCREEN &SCREEN :: operator << ( const SCREEN &Screen )
{
    *this = Screen;

    return( *this );
}


/******************************
  페이지 간에 내용을 복사한다.
*******************************/
SCREEN &SCREEN :: operator >> ( SCREEN &Screen )
{
    Screen = *this;

    return( Screen );
}


/****************************************
  화면의 내용을 지정된 색으로 지운다.
*****************************************/
void SCREEN :: Clear( COLOR Color )
{
    memset( Video, Color, VMEM_SIZE );
}


/****************************************
  화면의 내용을 지정된 색으로 지운다.
*****************************************/
void SCREEN :: Reset( void  )
{
    extern U8 dp_pal[ 256 ][ 3 ];

    Clear( 0 );

    PALETTEMAP::Set( (PALETTE *)dp_pal );
}


/****************************************
  화면의 내용을 가상 페이지로 저장한다.
*****************************************/
BOOL SCREEN :: Load( STRING FileName )
{
    char *res;
    if( !_Resource.Load( FileName, &res ) ) return( FALSE );
    char *temp = res;

    PIC_HEADER *ph = (PIC_HEADER *)res;
    res += sizeof(PIC_HEADER);

    if( strcmp( ph->Header, "Amos Picture File;" ) ) return( FALSE );
    if( ph->Ver != 2 ) return( FALSE );

    PALETTEMAP::Set( (PALETTE *)res );
    res += sizeof( PALETTE[256] );

    memcpy( Video, res, VMEM_SIZE );

    free( temp );

    return( TRUE );
}


/****************************************
  화면의 내용을 가상 페이지로 저장한다.
*****************************************/
void SCREEN :: Write( STRING FileName )
{
    PIC_HEADER ph;

    FILE *fp = fopen( FileName, "wb" );

    memcpy( ph.Header, "Amos Picture File;", 20 );
    ph.Ver    = 2;
    ph.Width  = SCREEN_WIDTH;
    ph.Height = SCREEN_HEIGHT;
    fwrite( &ph, sizeof(PIC_HEADER), 1, fp );

    fwrite( Palette, sizeof( PALETTE[256] ), 1, fp );
    fwrite( Video, VMEM_SIZE, 1, fp );

    fclose( fp );
}


/*******************************
  가상 페이지 영역을 복사한다.
********************************/
void SCREEN :: Save( SCREEN &Screen, INT StartX, INT StartY, INT EndX, INT EndY )
{
    int i;
    COLOR *SrcPtr, *DesPtr;
    int width, height;


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

    SrcPtr = Screen.Video + CALC_OFFS( StartX, StartY );
    DesPtr = Video + CALC_OFFS( StartX, StartY );

    width  = EndX - StartX + 1;
    height = EndY - StartY + 1;

    for( i = 0; i < height; i ++ ){
      memcpy( DesPtr, SrcPtr, width );
      DesPtr += VMEM_WIDTH;
      SrcPtr += VMEM_WIDTH;
    }
}


/**************************************
  가상페이지로부터 이미지를 복사한다.
***************************************/
void SCREEN :: Restore( SCREEN &Screen, INT StartX, INT StartY, INT EndX, INT EndY )
{
    int i;
    COLOR *SrcPtr, *DesPtr;
    int width, height;


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

    SrcPtr = Video + CALC_OFFS( StartX, StartY );
    DesPtr = Screen.Video + CALC_OFFS( StartX, StartY );

    width  = EndX - StartX + 1;
    height = EndY - StartY + 1;

    for( i = 0; i < height; i ++ ){
      memcpy( DesPtr, SrcPtr, width );
      DesPtr += VMEM_WIDTH;
      SrcPtr += VMEM_WIDTH;
    }
}


/*********************************
  화면에 현 페이지를 표시한다.
**********************************/
void SCREEN :: Display( void )
{
    CRTC::WaitVert();

    _Screen = *this;
}



