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


extern U8 dp_pal[ 256 ][ 3 ];


/**************************
  팔레트 = 연산자르 정의
***************************/
PALETTEMAP :: PALETTEMAP( void )
{
    Palette = new PALETTE[ 256 ];

    memcpy( Palette, dp_pal, 256*sizeof(PALETTE) );
}


/**************************
  팔레트 = 연산자르 정의
***************************/
PALETTEMAP &PALETTEMAP :: operator = ( const PALETTEMAP &Palette )
{
    memcpy( this->Palette, Palette.Palette, 256*sizeof(PALETTE) );

    return( *this );
}


/**************************
  팔레트 = 연산자를 정의
***************************/
void PALETTEMAP :: Set( PALETTE *Palette )
{
    memcpy( this->Palette, Palette, 256*sizeof(PALETTE) );
}


/**********************************
  팔레트를 디스크에서 읽어 들인다.
***********************************/
BOOL PALETTEMAP :: Load( STRING FileName )
{
    char *res;
    if( !_Resource.Load( FileName, &res ) ) return( FALSE );

    Set( (PALETTE *)res );

    free( res );

    return( TRUE );
}


/*****************************
  팔레트를 디스크에 저장한다.
******************************/
void PALETTEMAP :: Write( STRING FileName )
{
    FILE *fp = fopen( FileName, "wb" );

    fwrite( Palette, 256*sizeof(PALETTE), 1, fp );

    fclose( fp );
}


/****************************
  팔레트를 실제로 적용한다.
*****************************/
void PALETTEMAP :: RealizePalette( void )
{
    PALETTE *pal = Palette;


    for( int i = 0; i < 256; i ++ ){
      PALETTE::Put( (COLOR)i, pal->Red >> 2,
                              pal->Green >> 2,
                              pal->Blue >> 2 );

      pal ++;
    }
}


/**************************
  fade in을 스텝으로 진행
***************************/
void PALETTEMAP :: FadePalette( DACVALUE Red, DACVALUE Green, DACVALUE Blue, INT Step )
{
    if( Step < 0  ) Step = 0;
    if( Step > 63 ) Step = 63;

    PALETTE *pal = Palette;

    for( int i = 0; i < 256; i ++ ){
      char r = Red   + ((pal->Red   - Red)   * Step >> 6);
      char g = Green + ((pal->Green - Green) * Step >> 6);
      char b = Blue  + ((pal->Blue  - Blue)  * Step >> 6);

      PALETTE::Put( i, r, g, b );

      pal ++;
    }
}



/**************************
  fade in을 스텝으로 진행
***************************/
void PALETTEMAP :: FadePalette( DACVALUE Red, DACVALUE Green, DACVALUE Blue, INT Step, INT StartColor, INT EndColor )
{
    if( Step < 0  ) Step = 0;
    if( Step > 63 ) Step = 63;

    PALETTE *pal = Palette;

    for( int i = StartColor; i <= EndColor; i ++ ){
      char r = Red   + ((pal->Red   - Red)   * Step >> 6);
      char g = Green + ((pal->Green - Green) * Step >> 6);
      char b = Blue  + ((pal->Blue  - Blue)  * Step >> 6);

      PALETTE::Put( i, r, g, b );

      pal ++;
    }
}


/**************************
  팔레트를 순환시킨다.
***************************/
void PALETTEMAP :: AnimatePalette( INT StartPal, INT EndPal )
{
    PALETTE *src, *des;


    if( StartPal == EndPal ) return;

    PALETTE temp = Palette[ EndPal ];

    if( StartPal < EndPal ){
      des = &Palette[ EndPal ];
      src = des - 1;

      for( int i = EndPal; i > StartPal; i -- )
        *des-- = *src--;
    } else {
      des = &Palette[ EndPal ];
      src = des + 1;

      for( int i = EndPal; i < StartPal; i ++ )
        *des++ = *src++;
    }

    Palette[ StartPal ]  = temp;
}


/*********************************
  팔레트를 모두 흑백으로 바꾼다.
**********************************/
void PALETTEMAP :: GrayPalette( void )
{
    PALETTE *pal = Palette;

    for( int i = 0; i < 255; i ++ ){
      char r = pal->Red   * 30;
      char g = pal->Green * 59;
      char b = pal->Blue  * 11;

      DACVALUE avr = (DACVALUE)( (r + g + b) / 100 );

      pal->Red   = avr;
      pal->Green = avr;
      pal->Blue  = avr;

      pal ++;
    }
}


/*********************************
  팔레트를 모두 흑백으로 바꾼다.
**********************************/
void PALETTEMAP :: GrayPalette( COLOR StartPal, COLOR EndPal )
{
    PALETTE *pal = Palette;

    for( int i = StartPal; i <= EndPal; i ++ ){
      char r = pal->Red   * 30;
      char g = pal->Green * 59;
      char b = pal->Blue  * 11;

      DACVALUE avr = (DACVALUE)( (r + g + b) / 100 );

      pal->Red   = avr;
      pal->Green = avr;
      pal->Blue  = avr;

      pal ++;
    }
}



