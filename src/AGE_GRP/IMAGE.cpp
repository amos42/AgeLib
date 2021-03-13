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
#include <stdlib.h>
#include <string.h>
#include "age_grp.h"


struct IMG_HEADER {
    CHAR    Header[20];
    S32     Width, Height;
    S32     LogX, LogY;
};


/************************
  이미지 개체의 생성자
*************************/
IMAGE :: IMAGE( void )
{
    Bitmap = NULL;

    Reset();
}


/************************
  이미지 개체의 생성자
*************************/
IMAGE :: IMAGE( INT Width, INT Height )
{
    Bitmap = NULL;

    SetSize( Width, Height );
}


/************************
  이미지 개체의 생성자
*************************/
IMAGE :: IMAGE( INT Width, INT Height, COLOR *Bitmap )
{
    Bitmap = NULL;

    SetSize( Width, Height );

    SetBitmap( Bitmap );
}


/************************
  이미지 개체의 생성자
*************************/
IMAGE :: IMAGE( STRING FileName )
{
    Bitmap = NULL;

    Load( FileName );
}


/************************
  이미지 개체의 소멸자
*************************/
IMAGE :: ~IMAGE()
{
    Reset();
}


/************************
  비트맵을 리셋한다.
*************************/
void IMAGE :: Reset( void )
{
    if( Bitmap ){
      free( Bitmap );
      Bitmap = (COLOR *)NULL;
    }

    Width = Height = 0;
    LogX = LogY = 0;
}


/************************
  이미지  = 연산자 정의
*************************/
IMAGE &IMAGE :: operator = ( const IMAGE &Image )
{
    Reset();

    if( &Image != (IMAGE *)NULL ){
      SetSize( Image.Width, Image.Height );

      memcpy( Bitmap, Image.Bitmap, Width * Height );

      SetLogPosition( Image.LogX, Image.LogY );
    }

    return( *this );
}


/********************************
  디스크에서 이미지를 로드한다.
*********************************/
BOOL IMAGE :: Load( STRING FileName )
{
    Reset();

    char *res;
    if( !_Resource.Load( FileName, &res ) ) return( FALSE );

    IMG_HEADER *ih = (IMG_HEADER *)res;

    if( strcmp( ih->Header, "Amos Image File;" ) ) return( FALSE );

    SetSize( ih->Width, ih->Height );
    SetLogPosition( ih->LogX, ih->LogY );
    SetBitmap( (COLOR *)(res + sizeof(IMG_HEADER)) );

    free( res );

    return( TRUE );
}


/********************************
  디스크에서 이미지를 로드한다.
*********************************/
void IMAGE :: Write( STRING FileName )
{
    if( !Bitmap ) return;

    IMG_HEADER ih;

    memcpy( ih.Header, "Amos Image File;", 20 );
    ih.Width     = Width;
    ih.Height    = Height;
    ih.LogX      = LogX;
    ih.LogY      = LogY;

    int ImgSize  = Width * Height;

    // Word Alignment
    ImgSize = (ImgSize + 0x3) & ~0x3;

    FILE *fp = fopen( FileName, "wb" );
    fwrite( &ih, sizeof(IMG_HEADER), 1, fp );
    fwrite( Bitmap, ImgSize, 1, fp );
    fclose( fp );
}


/***************************
  이미지 크기를 재설정한다.
****************************/
void IMAGE :: SetSize( INT Width, INT Height )
{
    Reset();

    this->Width  = Width;
    this->Height = Height;

    int ImgSize = Width * Height;
    ImgSize = (ImgSize + 0x3) & ~0x3;

    if( ImgSize > 0 ){
      Bitmap = (COLOR *)malloc( ImgSize );
      memset( Bitmap, _TransColor, ImgSize );
    } else {
      Bitmap = (COLOR *)NULL;
    }
}


/***************************
  이미지 크기를 재설정한다.
****************************/
void IMAGE :: SetBitmap( COLOR *Bitmap )
{
    memcpy( this->Bitmap, Bitmap, Width * Height );
}


/*************************
  논리적 위치를 지정한다.
**************************/
void IMAGE :: SetLogPosition( INT LogX, INT LogY )
{
    this->LogX = LogX;
    this->LogY = LogY;
}


/******************************
  이미지가 유효한지를 살핀다.
*******************************/
BOOL IMAGE :: IsValidate( void )
{
    return( Bitmap != NULL );
}


/*****************************
  주어진 좌표의 점을 얻는다.
******************************/
COLOR IMAGE :: GetPixel( INT X, INT Y )
{
    return( *(Bitmap + Y * Width + X) );
}


/************************************
  이미지의 상하좌우 경계를 얻는다.
*************************************/
INT IMAGE :: FindTopBound( void )
{
    COLOR tc = _TransColor;

    for( int i = 0; i < Height; i ++ )
      for( int j = 0; j < Width; j ++ )
        if( GetPixel( j, i ) != tc ) return( i );

    return( -1 );
}

INT IMAGE :: FindBottomBound( void )
{
    COLOR tc = _TransColor;

    for( int i = Height-1; i >= 0; i -- )
      for( int j = 0; j < Width; j ++ )
        if( GetPixel( j, i ) != tc ) return( i );

    return( -1 );
}

INT IMAGE :: FindLeftBound( void )
{
    COLOR tc = _TransColor;

    for( int i = 0; i < Width; i ++ )
      for( int j = 0; j < Height; j ++ )
        if( GetPixel( i, j ) != tc ) return( i );

    return( -1 );
}

INT IMAGE :: FindRightBound( void )
{
    COLOR tc = _TransColor;

    for( int i = Width-1; i >= 0; i -- )
      for( int j = 0; j < Height; j ++ )
        if( GetPixel( i, j ) != tc ) return( i );

    return( -1 );
}


/************************************
  이미지의 바깥쪽 투명색을 제거하여
  컴팩트하게 만든다.
*************************************/
void IMAGE :: Compact( void )
{
    int sy = FindTopBound();
    int ey = FindBottomBound();
    int sx = FindLeftBound();
    int ex = FindRightBound();

    if( sx < 0 || sy < 0 || ex < 0 || ey < 0 ){
      Reset();
      return;
    }

    IMAGE tb;
    tb = *this;

    int w = ex - sx + 1;
    int h = ey - sy + 1;
    SetSize( w, h );

    COLOR *sb = tb.Bitmap + sx + sy * tb.Width;
    COLOR *db = Bitmap;

    for( int i = 0; i < h; i ++ ){
      memcpy( db, sb, w );
      db += w;
      sb += tb.Width;
    }

    SetLogPosition( tb.LogX + sx, tb.LogY + sy );
}



