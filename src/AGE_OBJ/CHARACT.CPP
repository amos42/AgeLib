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


/********************
  캐릭터의 생성자.
*********************/
CHARACTER :: CHARACTER( CHRMODEL &ChrModel ) : OBJECT()
{
    // 캐릭터를 리셋한다.
    Reset();

    this->ChrModel = &ChrModel;

    ChrModel.Count ++;
}


/********************
  캐릭터의 생성자.
*********************/
CHARACTER :: CHARACTER( INT X, INT Y, CHRMODEL &ChrModel ) : OBJECT()
{
    // 캐릭터를 리셋한다.
    Reset();

    this->ChrModel = &ChrModel;

    ChrModel.Count ++;

    MoveTo( X, Y );
}


/********************
  캐릭터의 소멸자.
*********************/
CHARACTER :: ~CHARACTER()
{
    // 캐릭터를 리셋한다.
    Reset();

    ChrModel->Count --;

    ChrModel = NULL;
}


/*********************
  캐릭터를 리셋한다.
**********************/
void CHARACTER :: Reset( void )
{
    // 캐릭터를 화면 최좌상단으로 이동
    MoveTo( 0, 0 );

    // 첫번째 스프라이트 표시
    Index = 0;

    // 현재 상태 초기화 및 화면 출력 가능
    State = 0;
    Visible = TRUE;
}


/************************************
  캐릭터를 주어진 값만큼 이동시킨다.
*************************************/
void CHARACTER :: Move( INT X, INT Y )
{
    // 주어진 좌표값만큼 해당 방향으로 이동
    this->X += X;
    this->Y += Y;
}


/**********************************
  캐릭터를 절대좌표로 이동시킨다.
***********************************/
void CHARACTER :: MoveTo( INT X, INT Y )
{
    // 절대 좌표로 이동
    this->X = X;
    this->Y = Y;
}


/**********************************
  캐릭터의 현재 이미지를 리턴한다.
***********************************/
IMAGE* CHARACTER :: GetImagePtr( void )
{
    // 현재의 인덱스에 맞는 이미지 포인터를 얻는다.
    return( ChrModel->Sprite->GetImagePtr( Index ) );
}


/***************************************
  현재 캐릭터 이미지의 영역을 리턴한다.
****************************************/
REGION CHARACTER :: GetImageRegion( void )
{
    // 현재 이미지를 얻는다.
    IMAGE *img = GetImagePtr();

    // 영역을 생성하여 이미지의 시작좌표와 크기 세트
    REGION r( X + img->LogX, Y + img->LogY,
              img->Width, img->Height );

    // 영역 리턴
    return( r );
}


/*************************************
  현재 캐릭터의 충돌 영역을 리턴한다.
**************************************/
REGION *CHARACTER :: GetCrashRegion( INT Index2 )
{
    REGIONS *r = &ChrModel->Regions1[Index];

    if( Index2 < r->Count )
      return( r->GetRegion( Index2 ) );
    else
      return( NULL );
}


/***************************************
  현재 캐릭터의 공격 영역을 리턴한다.
****************************************/
REGION *CHARACTER :: GetAttackRegion( INT Index2 )
{
    REGIONS *r = &ChrModel->Regions2[Index];

    if( Index2 < r->Count )
      return( r->GetRegion( Index2 ) );
    else
      return( NULL );
}


/**************************
  캐릭터의 인덱스를 증가
***************************/
BOOL CHARACTER :: IncIndex( INT Step )
{
    Index += Step;

    if( Index >= ChrModel->Sprite->Count ){
      Index = ChrModel->Sprite->Count - 1;
      return( TRUE );
    } else {
      return( FALSE );
    }
}


/***************************
  캐릭터의 인덱스를 감소
****************************/
BOOL CHARACTER :: DecIndex( INT Step )
{
    Index -= Step;

    if( Index < 0 ){
      Index = 0;
      return( TRUE );
    } else {
      return( FALSE );
    }
}


/********************************************
  캐릭터의 인덱스를 정해진 영역 내에서 순환
  만약 End가 -1이면 끝까지 순환
*********************************************/
void CHARACTER :: RotIndex( INT Start, INT End )
{
    if( End < 0 ) End = ChrModel->Sprite->Count - 1;

    Index ++;

    if( Index > End ){
      Index = Start;
    }
}


/********************************************
  캐릭터를 찍는다.
  오브젝트 매니저에 의해 호출되는 가상 함수
*********************************************/
void CHARACTER :: Put( void )
{
    if( ChrModel->Sprite ) ChrModel->Sprite->PutChar( X, Y, Index );
}


/********************************************
  오브젝트 이벤트 핸들러
  오브젝트 매니저에 의해 호출되는 가상 함수
*********************************************/
INT CHARACTER :: ObjProc( HMSG hMsg, LONG lParam )
{
    switch( hMsg ){
      case OM_PAINT : if( Visible ) Put();
                      break;
    }

    return( 0 );
}


