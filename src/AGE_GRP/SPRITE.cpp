/*#################################################################
-------------------------------------------------------------------

                             AGE (Ver 1.0)
                       (* =================== *)
                           Amos Game Engine

 Author         : Chu, Kyong-min( Amos )

 Date           : 1997/02/08
 C Compiler     : WATCOM 10.5
 Assembler      : WASM 11.0

-------------------------------------------------------------------
###################################################################*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "age_grp.h"
#include "age_err.h"


struct SPR_HEADER {
    CHAR    Header[20];
    INT     Ver;
    INT     Count;
};

struct IMG_HEADER {
    INT     Width, Height;
    INT     LogX,  LogY;
};


/*************************
  스프라이트의 생성자
**************************/
SPRITE :: SPRITE( void )
{
    Count = 0;
    Image = (IMAGE *)NULL;
}


/*************************
  스프라이트의 생성자
**************************/
SPRITE :: SPRITE( STRING FileName )
{
    Count = 0;
    Image = (IMAGE *)NULL;

    Load( FileName );
}


/*************************
  스프라이트의 소멸자
**************************/
SPRITE :: ~SPRITE()
{
    Reset();
}


/*************************
  스프라이트의 소멸자
**************************/
void SPRITE :: Reset( void )
{
    if( Count > 0 ){
      int count = Count;

      for( int i = 0; i < count; i ++ )
        free( Image[i].Bitmap );

      free( Image );

      Count = 0;
      Image = (IMAGE *)NULL;
    }
}


/**************************************
  리소스로부터 스프라이트를 로드한다.
***************************************/
BOOL SPRITE :: Load( STRING FileName )
{
    Reset();

    char *res;
    if( !_Resource.Load( FileName, &res ) ) return( FALSE );
    char *temp = res;

    SPR_HEADER *sh = (SPR_HEADER *)res;
    res += sizeof(SPR_HEADER);
    if( strcmp( sh->Header, "Amos Sprite File;" ) ) return( FALSE );
    if( sh->Ver != 2 ) return( FALSE );

    int count = sh->Count;

    for( int i = 0; i < count; i ++ ){
      IMG_HEADER *ih = (IMG_HEADER *)res;
      res += sizeof(IMG_HEADER);

      IMAGE *img = new IMAGE( ih->Width, ih->Height );
      img->SetLogPosition( ih->LogX, ih->LogY );

      int ImgSize = ih->Width * ih->Height;
      memcpy( img->Bitmap, res, ImgSize );

      // 워드 정렬을 위해...
      ImgSize = (ImgSize + 0x3) & ~0x3;
      res += ImgSize;

      AddImage( *img );
      delete img;
    }

    free( temp );

    return( TRUE );
}


/**********************************
  디스크에 스프라이트를 저장한다.
***********************************/
void SPRITE :: Write( STRING FileName )
{
    SPR_HEADER sh;
    IMG_HEADER ih;


    FILE *fp = fopen( FileName, "wb" );

    memcpy( sh.Header, "Amos Sprite File;", 20 );
    sh.Ver   = 2;
    sh.Count = Count;
    fwrite( &sh, sizeof(SPR_HEADER), 1, fp );

    for( int i = 0; i < Count; i ++ ){
      IMAGE *img = &Image[i];

      ih.Width  = img->Width;
      ih.Height = img->Height;
      ih.LogX   = img->LogX;
      ih.LogY   = img->LogY;

      fwrite( &ih, sizeof(IMG_HEADER), 1, fp );

      int ImgSize = img->Width * img->Height;

      // 워드 정렬을 위해...
      ImgSize = (ImgSize + 0x3) & ~0x3;

      fwrite( img->Bitmap, ImgSize, 1, fp );
    }

    fclose( fp );
}


/**********************************
  스프라이트의 이미지를 추가한다.
***********************************/
void SPRITE :: AddImage( IMAGE &Image )
{
    int PtrSize = (Count + 1) * sizeof(IMAGE);

    this->Image = (IMAGE *)realloc( this->Image, PtrSize );

    IMAGE *img = &this->Image[ Count ];
    img->Bitmap = (COLOR *)NULL;
    *img = Image;

    Count ++;
}


/**********************************
  스프라이트의 이미지를 삽입한다.
***********************************/
void SPRITE :: InsertImage( INT Index, IMAGE &Image )
{
    if( Index >= Count ){
      AddImage( Image );
      return;
    }
    if( Index < 0 ) Index = 0;

    int PtrSize = (Count + 1) * sizeof(IMAGE);

    IMAGE *ti = (IMAGE *)malloc( PtrSize );

    memcpy( ti, this->Image, Index * sizeof(IMAGE) );

    IMAGE *img = &ti[ Index ];
    img->Bitmap = (COLOR *)NULL;
    *img = Image;

    memcpy( &ti[Index + 1], &this->Image[Index],
            (Count - Index) * sizeof(IMAGE) );

    Count ++;

    free( this->Image );
    this->Image = ti;
}


/**********************************
  스프라이트의 이미지를 삭제한다.
***********************************/
void SPRITE :: DeleteImage( INT Index )
{
    if( Index >= Count || Index < 0 ){
      return;
    }

    int PtrSize = (Count - 1) * sizeof(IMAGE);

    IMAGE *ti = (IMAGE *)malloc( PtrSize );

    memcpy( ti, this->Image, Index * sizeof(IMAGE) );

    IMAGE *img = &this->Image[ Index ];
    img->Reset();

    Count --;

    memcpy( &ti[Index], &this->Image[Index + 1],
            (Count - Index) * sizeof(IMAGE) );

    free( this->Image );
    this->Image = ti;
}


/**********************************
  스프라이트의 이미지를 교체한다.
***********************************/
BOOL SPRITE :: SetImage( INT Index, IMAGE &Image )
{
    if( Index >= Count ) return( FALSE );

    IMAGE *img = &this->Image[ Index ];

    *img = Image;

    return( TRUE );
}                       


/*******************************
  스프라이트의 이미지를 얻는다.
********************************/
IMAGE * SPRITE :: GetImagePtr( INT Index )
{
    if( Index < 0 || Index >= Count ) return( NULL );

    return( &Image[ Index ] );
}


/********************************************
  스프라이트의 이미지가 유효한지를 살핀다.
*********************************************/
BOOL SPRITE :: IsValidate( INT Index )
{
    IMAGE *img = GetImagePtr( Index );
    if( !img ) return( FALSE );

    return( img->IsValidate() );
}                       


/***********************
  스프라이트를 찍는다.
************************/
void SPRITE :: Put( INT X, INT Y, INT Index )
{
    IMAGE *img = GetImagePtr( Index );
    if( !img ) return;

    img->Put( X, Y );
}


/***********************
  스프라이트를 찍는다.
************************/
void SPRITE :: PutStretch( INT X, INT Y, INT tWidth, INT tHeight, INT Index )
{
    IMAGE *img = GetImagePtr( Index );
    if( !img ) return;

    img->PutStretch( X, Y, tWidth, tHeight );
}


/***********************
  스프라이트를 찍는다.
************************/
void SPRITE :: PutScale( INT X, INT Y, FIXED Scale, INT Index )
{
    IMAGE *img = GetImagePtr( Index );
    if( !img ) return;

    img->PutScale( X, Y, Scale );
}


/***********************
  스프라이트를 찍는다.
************************/
void SPRITE :: PutChar( INT X, INT Y, INT Index )
{
    IMAGE *img = GetImagePtr( Index );
    if( !img ) return;

    img->PutChar( X, Y );
}


/***********************
  스프라이트를 찍는다.
************************/
void SPRITE :: PutCharStretch( INT X, INT Y, INT tWidth, INT tHeight, INT Index )
{
    IMAGE *img = GetImagePtr( Index );
    if( !img ) return;

    img->PutCharStretch( X, Y, tWidth, tHeight );
}


/***********************
  스프라이트를 찍는다.
************************/
void SPRITE :: PutCharScale( INT X, INT Y, FIXED Scale, INT Index )
{
    IMAGE *img = GetImagePtr( Index );
    if( !img ) return;

    img->PutCharScale( X, Y, Scale );
}


/***********************
  스프라이트를 찍는다.
************************/
void SPRITE :: PutShadow( INT X, INT Y, INT Index )
{
    IMAGE *img = GetImagePtr( Index );
    if( !img ) return;

    img->PutShadow( X, Y );
}


/***********************
  스프라이트를 찍는다.
************************/
void SPRITE :: PutShadowStretch( INT X, INT Y, INT tWidth, INT tHeight, INT Index )
{
    IMAGE *img = GetImagePtr( Index );
    if( !img ) return;

    img->PutShadowStretch( X, Y, tWidth, tHeight );
}


/***********************
  스프라이트를 찍는다.
************************/
void SPRITE :: PutShadowScale( INT X, INT Y, FIXED Scale, INT Index )
{
    IMAGE *img = GetImagePtr( Index );
    if( !img ) return;

    img->PutShadowScale( X, Y, Scale );
}


/***********************
  스프라이트를 찍는다.
************************/
void SPRITE :: PutShadowTrans( INT X, INT Y, INT Index )
{
    IMAGE *img = GetImagePtr( Index );
    if( !img ) return;

    img->PutShadowTrans( X, Y, _ShadeTransTable.Get() );
}


/***********************
  스프라이트를 찍는다.
************************/
void SPRITE :: PutShadowTransStretch( INT X, INT Y, INT tWidth, INT tHeight, INT Index )
{
    IMAGE *img = GetImagePtr( Index );
    if( !img ) return;

    img->PutShadowTransStretch( X, Y, tWidth, tHeight, _ShadeTransTable.Get() );
}


/***********************
  스프라이트를 찍는다.
************************/
void SPRITE :: PutShadowTransScale( INT X, INT Y, FIXED Scale, INT Index )
{
    IMAGE *img = GetImagePtr( Index );
    if( !img ) return;

    img->PutShadowTransScale( X, Y, Scale, _ShadeTransTable.Get() );
}


/***********************
  스프라이트를 찍는다.
************************/
void SPRITE :: PutTrans( INT X, INT Y, INT Index )
{
    IMAGE *img = GetImagePtr( Index );
    if( !img ) return;

    img->PutTrans( X, Y, _ImageTransTable.Get() );
}


/***********************
  스프라이트를 찍는다.
************************/
void SPRITE :: PutTransStretch( INT X, INT Y, INT tWidth, INT tHeight, INT Index )
{
    IMAGE *img = GetImagePtr( Index );
    if( !img ) return;

    img->PutTransStretch( X, Y, tWidth, tHeight, _ImageTransTable.Get() );
}


/***********************
  스프라이트를 찍는다.
************************/
void SPRITE :: PutTransScale( INT X, INT Y, FIXED Scale, INT Index )
{
    IMAGE *img = GetImagePtr( Index );
    if( !img ) return;

    img->PutTransScale( X, Y, Scale, _ImageTransTable.Get() );
}



