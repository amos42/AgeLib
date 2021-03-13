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
#include <stdarg.h>
#include <string.h>
#include "age_grp.h"


#define NTYPES1 8   // 초성의 벌 수
#define NTYPES2 4   // 중성의 벌 수
#define NTYPES3 4   // 종성의 벌 수

#define NHAN1 19
#define NHAN2 21
#define NHAN3 27
#define NENG  95

#define INIT_FONT_COLOR 15


extern U16 HanFont1[NTYPES1 * NHAN1][16];
extern U16 HanFont2[NTYPES2 * NHAN2][16];
extern U16 HanFont3[NTYPES3 * NHAN3][16];
extern U8  EngFont[NENG][16];


TEXT _Text;


static void PutHanFontNormal( COLOR *di, U8 *si, COLOR Color )
{
    int i, j;
    int d;

    for( i = 0; i < 16; i ++ ){
      d = *si++;
      d = (d << 8) | *si++;

      for( j = 0; j < 16; j ++ ){
        if( d & 0x8000 ) *di = Color;
        d <<= 1;
        di ++;
      }
      di += VMEM_WIDTH - 16;
    }
}

static void PutEngFontNormal( COLOR *di, U8 *si, COLOR Color )
{
    int i, j;
    int d;

    for( i = 0; i < 16; i ++ ){
      d = *si++;
      for( j = 0; j < 8; j ++ ){
        if( d & 0x80 ) *di = Color;
        d <<= 1;
        di ++;
      }
      di += VMEM_WIDTH - 8;
    }
}

static void PutHanFontMulti( COLOR *di, U8 *si, COLOR Color )
{
    int i, j;
    int d;

    for( i = 0; i < 16; i ++ ){
      d = *si++;
      d = (d << 8) | *si++;
      for( j = 0; j < 16; j ++ ){
        if( d & 0x8000 ) *di = Color;
        d <<= 1;
        di ++;
      }
      Color ++;
      di += VMEM_WIDTH - 16;
    }
}

static void PutEngFontMulti( COLOR *di, U8 *si, COLOR Color )
{
    int i, j;
    int d;

    for( i = 0; i < 16; i ++ ){
      d = *si++;
      for( j = 0; j < 8; j ++ ){
        if( d & 0x80 ) *di = Color;
        d <<= 1;
        di ++;
      }
      Color ++;
      di += VMEM_WIDTH - 8;
    }
}


static void PutHanFontShadow( COLOR *di, U8 *si, COLOR Color )
{
    int i, j;
    int d, sc = _ShadowColor;

    for( i = 0; i < 16; i ++ ){
      d = *si++;
      d = (d << 8) | *si++;

      for( j = 0; j < 16; j ++ ){
        if( d & 0x8000 ){
          *di = Color;
          *(di + VMEM_WIDTH+1) = sc;
        }
        d <<= 1;
        di ++;
      }
      di += VMEM_WIDTH - 16;
    }
}

static void PutEngFontShadow( COLOR *di, U8 *si, COLOR Color )
{
    int i, j;
    int d, sc = _ShadowColor;

    for( i = 0; i < 16; i ++ ){
      d = *si++;
      for( j = 0; j < 8; j ++ ){
        if( d & 0x80 ){
          *di = Color;
          *(di + VMEM_WIDTH+1) = sc;
        }
        d <<= 1;
        di ++;
      }
      di += VMEM_WIDTH - 8;
    }
}


TEXT :: TEXT( void )
{
    MoveCP( 0, 0 );

    SetFontColor( INIT_FONT_COLOR );
    SetFontStyle( FS_NORMAL );

    HanFont1 = (U16 *)::HanFont1;
    HanFont2 = (U16 *)::HanFont2;
    HanFont3 = (U16 *)::HanFont3;
    EngFont  = (U8  *)::EngFont;

    IsDefaultHan = TRUE;
    IsDefaultEng = TRUE;
}


TEXT :: TEXT( STRING HanFileName, STRING EngFileName )
{
    MoveCP( 0, 0 );

    SetFontColor( INIT_FONT_COLOR );
    SetFontStyle( FS_NORMAL );

    IsDefaultHan = TRUE;
    IsDefaultEng = TRUE;
    LoadHanFont( HanFileName );
    LoadEngFont( EngFileName );
}


TEXT :: ~TEXT()
{
    FreeHanFont();
    FreeEngFont();
}


/****************************
  한글 폰트 파일을 로드한다.
*****************************/
BOOL TEXT :: LoadHanFont( STRING FileName )
{
    FreeHanFont();

    char *ch;
    if( !_Resource.Load( FileName, &ch ) ) return( FALSE );

    HanFont1 = (U16 *)malloc( NTYPES1 * NHAN1 * 16*2 );
    memcpy( HanFont1, ch,
            NTYPES1 * NHAN1 * 16*2 );

    HanFont2 = (U16 *)malloc( NTYPES2 * NHAN2 * 16*2 );
    memcpy( HanFont2, ch + NTYPES1 * NHAN1 * 16*2,
            NTYPES2 * NHAN2 * 16*2 );

    HanFont3 = (U16 *)malloc( NTYPES3 * NHAN3 * 16*2 );
    memcpy( HanFont3, ch + NTYPES1 * NHAN1 * 16*2 + NTYPES2 * NHAN2 * 16*2,
            NTYPES3 * NHAN3 * 16*2 );

    free( ch );
    IsDefaultHan = FALSE;

    return( TRUE );
}


/****************************
  영문 폰트 파일을 로드한다.
*****************************/
BOOL TEXT :: LoadEngFont( STRING FileName )
{
    FreeEngFont();

    int fl = _Resource.Load( FileName, (char **)&EngFont );

    return( fl != 0 );
}


/***********************************
  한글 폰트를 메모리에서 제거한다.
************************************/
void TEXT :: FreeHanFont( void )
{
    if( !IsDefaultHan ){
      free( HanFont1 );
      free( HanFont2 );
      free( HanFont3 );

      HanFont1 = (U16 *)::HanFont1;
      HanFont2 = (U16 *)::HanFont2;
      HanFont3 = (U16 *)::HanFont3;

      IsDefaultHan = TRUE;
    }
}


/***********************************
  영문 폰트를 메모리에서 제거한다.
************************************/
void TEXT :: FreeEngFont( void )
{
    if( !IsDefaultEng ){
      free( EngFont );

      EngFont = (U8 *)::EngFont;

      IsDefaultEng = TRUE;
    }
}


/********************************
   CP(Currect Point)를 옮긴다.
*********************************/
void TEXT :: MoveCP( INT X, INT Y )
{
    CP.Set( X, Y );
}


/************************
  폰트 색깔을 세트한다.
*************************/
void TEXT :: SetFontColor( COLOR Color )
{
    ForeColor = Color;
}


/************************
  폰트 속성을 세트한다.
*************************/
void TEXT :: SetFontStyle( INT style )
{
    switch( style ){
      case FS_NORMAL : PutHanFont = PutHanFontNormal;
                       PutEngFont = PutEngFontNormal;
                       break;
      case FS_MULTI  : PutHanFont = PutHanFontMulti;
                       PutEngFont = PutEngFontMulti;
                       break;
      case FS_SHADOW : PutHanFont = PutHanFontShadow;
                       PutEngFont = PutEngFontShadow;
                       break;
    }
}


/************************************
  한글 코드로 폰트 이미지를 얻는다.
*************************************/
U8* TEXT :: GetHanImage( U16 c )
{
    int h1, h2, h3;
    int type1, type2, type3;
    static U16 ib[16];     /* 한글 자형 버퍼 */
    static char idxtbl1[] = {           // 초성 인덱스 테이블
         0,  0,  1,  2,  3,  4,  5,  6,
         7,  8,  9, 10, 11, 12, 13, 14,
        15, 16, 17, 18, 19,  0,  0,  0,
         0,  0,  0,  0,  0,  0,  0,  0
    };
    static char idxtbl2[] = {           // 중성 인덱스 테이블
         0,  0,  0,  1,  2,  3,  4,  5,
         0,  0,  6,  7,  8,  9, 10, 11,
         0,  0, 12, 13, 14, 15, 16, 17,
         0,  0, 18, 19, 20, 21,  0,  0
    };
    static char idxtbl3[] = {           // 종성 인덱스 테이블
         0,  0,  1,  2,  3,  4,  5,  6,
         7,  8,  9, 10, 11, 12, 13, 14,
        15, 16,  0, 17, 18, 19, 20, 21,
        22, 23, 24, 25, 26, 27,  0,  0
    };
    static char type1tbl_no[]  = {      // 중성에 따른 초성 종류 / 받침 없음
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3,
        3, 3, 1, 2, 4, 4, 4, 2, 1, 3, 0
    };
    static char type1tbl_yes[] = {      // 중성에 따른 초성 종류 / 받침 있음
        5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 7,
        7, 7, 6, 6, 7, 7, 7, 6, 6, 7, 5
    };
    static char type3tbl[] = {          // 중성에 따른 종성 종류
        0, 0, 2, 0, 2, 1, 2, 1, 2, 3, 0,
        2, 1, 3, 3, 1, 2, 1, 3, 3, 1, 1
    };


    h1 = (c >> 10) & 0x1F;          // 초성 코드
    h2 = (c >> 5)  & 0x1F;          // 중성 코드
    h3 =  c        & 0x1F;          // 종성 코드

    h1 = idxtbl1[h1];                       // 초성 인덱스 코드
    h2 = idxtbl2[h2];                       // 중성 인덱스 코드
    h3 = idxtbl3[h3];                       // 종성 인덱스 코드

    type1 = h3 ? type1tbl_yes[h2] : type1tbl_no[h2];
    type2 = ((h1 == 0 || h1 == 1 || h1 == 16) ? 0 : 1) + (h3 ? 2 : 0);
    type3 = type3tbl[h2];

    if( h1 )
      memcpy( ib, HanFont1 + type1 * NHAN1*16 + (h1-1)*16, 16*2 );
    else
      memset( ib, 0, 16*2 );

    if( h2 ){
      long *des = (long *)ib;
      long *src = (long *)(HanFont2 + type2 * NHAN2*16 + (h2-1)*16);
      int len2 = 2*16 / 4;
      while( len2 -- ) *des++ |= *src++;
    }
    if( h3 ){
      long *des = (long *)ib;
      long *src = (long *)(HanFont3 + type3 * NHAN3*16 + (h3-1)*16);
      int len2 = 2*16 / 4;
      while( len2 -- ) *des++ |= *src++;
    }

    return( (U8 *)ib );
}


/********************
   문자열을 찍는다.
*********************/
void TEXT :: PutString( STRING StrData )
{
    int xx, yy;
    U16 ch;
    int hcode;
    U8 *si;
    COLOR *di;


    xx = CP.X;
    yy = CP.Y;
    di = CALC_ADDR( xx, yy );

    while( (ch = (U16)*StrData++) != '\0' ){
      if( ch & 0x80 ){
        hcode = (ch << 8) | (U16)*StrData;
        si = GetHanImage( hcode );
        PutHanFont( di, si, ForeColor );
        StrData ++;
        di += 16;
        xx += 16;
      } else {
        if( ch >= '!' && ch <= '~' ){
          si = EngFont + (ch - '!') * 16;
          PutEngFont( di, si, ForeColor );
        }
        di += 8;
        xx += 8;
      }

      if( ch == '\n' ){
        di += VMEM_WIDTH * 16 - (xx - CP.X);
        xx = CP.X;
        yy += 16;
      }
    }

    CP.X = xx;
    CP.Y = yy;
}


/********************
   문자열을 찍는다.
*********************/
void TEXT :: PutString( INT X, INT Y, STRING StrData )
{
    MoveCP( X, Y );
    PutString( StrData );
}


/***********************************
  printf 형식으로 문자열을 찍는다.
************************************/
INT TEXT :: Printf( const char *format, ... )
{
    int count;
    char str[128];
    va_list l;


    va_start( l, format );
    count = vsprintf( str, format, l );
    va_end( l );

    PutString( str );

    return( count );
}




