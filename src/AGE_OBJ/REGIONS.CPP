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

#include <string.h>
#include "age_obj.h"


// 영역 파일의 헤더 구조체
typedef struct {
    CHAR    Header[20];
    INT     Ver;
    INT     Count;
} RGN_HEADER;


/********************
  영역의 생성자.
*********************/
REGIONS :: REGIONS( void )
{
    Regions = (REGION *)NULL;

    Reset();
}


/********************
  영역의 생성자.
*********************/
REGIONS :: REGIONS( INT Count )
{
    Regions = (REGION *)NULL;

    SetCount( Count );
}


/********************
  영역의 생성자.
*********************/
REGIONS :: REGIONS( STRING FileName )
{
    Regions = (REGION *)NULL;

    Load( FileName );
}


/********************
  영역의 소멸자.
*********************/
REGIONS :: ~REGIONS()
{
    // 영역을 리셋시킨다.
    Reset();
}


/****************************************
  리소스에서 영역 데이터를 읽어 들인다.
*****************************************/
BOOL REGIONS :: Load( STRING FileName )
{
    // 리소스 매니저로부터 영역을 읽는다.
    char *res;
    if( !_Resource.Load( FileName, &res ) ) return( FALSE );
    char *temp = res;

    // 헤더 세트
    RGN_HEADER *rh = (RGN_HEADER *)res;
    res += sizeof(RGN_HEADER);

    // 만약 식별자가 틀렸으면 종료
    if( strcmp( rh->Header, "Amos Regions File;" ) ) return( FALSE );
                                  
    // 만약 버전 1.0이 아니라면 종료
    if( rh->Ver != 1 ) return( FALSE );

    // 크기를 재설정한다.
    SetCount( rh->Count );

    // 데이터 세트
    memcpy( Regions, res, rh->Count * sizeof(REGION) );

    // 임시 리소스 소멸
    free( temp );

    // 데이터 로드 성공
    return( TRUE );
}


/********************
  영역을 리셋한다.
*********************/
void REGIONS :: Reset( void )
{
    // 카운트 초기화
    Count = 0;

    // 만약 기존 영역이 설정되어 있으면...
    if( Regions ){
      // 영역 소멸
      free( Regions );
      // 포인터 초기화
      Regions = NULL;
    }
}


/****************
  영역 재설정
*****************/
void REGIONS :: SetCount( INT Count )
{
    // 리셋시킨다.
    Reset();

    // 카운트 세트
    this->Count = Count;

    // 영역에 해당하는 메모리 할당
    Regions = (REGION *)malloc( Count * sizeof(REGION) );

    // 영역 초기화
    memset( Regions, 0, Count * sizeof(REGION) );
}


/**********************
  영역 갯수를 얻는다.
***********************/
INT REGIONS :: GetCount( void )
{
    return( Count );
}


/*******************
  영역을 세트한다.
********************/
BOOL REGIONS :: SetRegion( INT Index, REGION &Region )
{
    // 만약 유효한 인덱스라면...
    if( Index < Count ){
      // 영역 데이터 갱신
      Regions[Index] = Region;
      return( TRUE );
    } else
      return( FALSE );
}


/***********************
  영역 정보를 얻는다.
************************/
BOOL REGIONS :: GetRegion( INT Index, REGION *Region )
{
    // 만약 유효한 인덱스라면...
    if( Index < Count ){
      *Region = Regions[ Index ];
      return( TRUE );
    } else
      return( FALSE );
}


/***********************
  영역 정보를 얻는다.
************************/
REGION *REGIONS :: GetRegion( INT Index )
{
    // 만약 유효한 인덱스라면...
    if( Index < Count )
      return( &Regions[ Index ] );
    else
      return( NULL );
}


/*************************
  영역 정보를 추가한다.
**************************/
void REGIONS :: AddRegion( REGION &Region )
{
    // 만약 Count가 0보다 크면...
    if( Count > 0 ){
      // 기존 영역 확장
      int PtrSize = (Count + 1) * sizeof(REGION);
      Regions = (REGION *)realloc( Regions, PtrSize );
    } else {
      // 영역 초기화
      SetCount( 1 );
    }

    // 영역을 세트한다.
    Regions[ Count++ ] = Region;
}


