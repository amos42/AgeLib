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
#include "age_obj.h"


// 캐릭터 파일의 헤더 구조체
typedef struct {
    CHAR    Header[20];
    INT     Ver;
    INT     Count;
} CHR_HEADER;


INT CHRMODEL::CurClassID = 0;


/***********************
  캐릭터 모델의 생성자.
************************/
CHRMODEL :: CHRMODEL( void )
{
    // 변수 초기화
    Sprite = NULL;
    Regions1 = Regions2 = NULL;

    ClassID = CurClassID ++;
    Count = 0;
}


/***********************
  캐릭터 모델의 생성자.
************************/
CHRMODEL :: CHRMODEL( STRING FileName )
{
    // 변수 초기화
    Sprite = NULL;
    Regions1 = Regions2 = NULL;

    // 주어진 파일명으로 파일을 연다.
    Load( FileName );

    ClassID = CurClassID ++;
    Count = 0;
}


/***********************
  캐릭터 모델의 생성자.
************************/
CHRMODEL :: CHRMODEL( STRING SprFile, STRING RgnFile1, STRING RgnFile2 )
{
    // 변수 초기화
    Sprite = NULL;
    Regions1 = Regions2 = NULL;

    Load( SprFile, RgnFile1, RgnFile2 );

    ClassID = CurClassID ++;
    Count = 0;
}


/***********************
  캐릭터 모델의 생성자.
************************/
CHRMODEL :: CHRMODEL( SPRITE *Sprite, REGIONS *Regions1, REGIONS *Regions2 )
{
    // 스프라이트 지정
    SetSprite( Sprite );

    // 영역 지정
    SetRegions1( Regions1 );
    SetRegions2( Regions2 );

    ClassID = CurClassID ++;
    Count = 0;
}


/***********************
  캐릭터 모델의 소멸자
************************/
CHRMODEL :: ~CHRMODEL()
{
    // 리셋한다.
    Reset();
}
    

/****************************
  캐릭터 모델을 리셋시킨다.
*****************************/
void CHRMODEL :: Reset( void )
{
    // 만약 스프라이트가 있으면 소멸
    if( Sprite ){
      delete Sprite;
      Sprite = NULL;
    }

    // 만약 지정된 영역이 있으면 소멸
    if( Regions1 ){
      delete Regions1;
      Regions1 = NULL;
    }
    if( Regions2 ){
      delete Regions2;
      Regions2 = NULL;
    }
}


/****************************
  캐릭터를 파일에서 읽는다.
*****************************/
BOOL CHRMODEL :: Load( STRING FileName )
{
    return( TRUE );
}


/****************************
  캐릭터를 파일에서 읽는다.
*****************************/
BOOL CHRMODEL :: Load( STRING SprFile, STRING RgnFile1, STRING RgnFile2 )
{
    // 캐릭터 모델을 리셋시킨다.
    Reset();

    // 주어진 파일명으로 파일을 연다.
    if( SprFile )
      SetSprite( new SPRITE( SprFile ) );

    if( RgnFile1 )
      SetRegions1( new REGIONS( RgnFile1 ) );

    if( RgnFile2 )
      SetRegions2( new REGIONS( RgnFile2 ) );

    return( TRUE );
}


/**********************************
  디스크에 캐릭터를 저장한다.
***********************************/
void CHRMODEL :: Write( STRING FileName )
{
}


/****************************
  스프라이트를 지정한다.
*****************************/
void CHRMODEL :: SetSprite( SPRITE *Sprite )
{
    this->Sprite = Sprite;
}


/****************************
  영역1을 지정한다.
*****************************/
void CHRMODEL :: SetRegions1( REGIONS *Regions )
{
    Regions1 = Regions;
}


/****************************
  영역2를 지정한다.
*****************************/
void CHRMODEL :: SetRegions2( REGIONS *Regions )
{
    Regions2 = Regions;
}


