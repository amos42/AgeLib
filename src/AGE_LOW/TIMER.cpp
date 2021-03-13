/*#################################################################
-------------------------------------------------------------------

                             AGE (Ver 1.0)
                       (* =================== *)
                           Amos Game Engine

 Author         : Chu, Kyong-min( Amos )

 Date           : 1998/01/08
 C Compiler     : WATCOM 11.0
 Assembler      : WASM 11.0

-------------------------------------------------------------------
###################################################################*/

#include <dos.h>
#include <conio.h>
#include "age_low.h"


// 타이머 값을 저장할 전역변수
LONG MULTITIMER::OrgTick = 0;

static void (__interrupt __far *OldTimerVect)( void ) = NULL;
static int OldTick = 0;
static MULTITIMER *_MultiTimer[ MTIMER_COUNT+1 ] = { NULL, };


/**************************************
  새로운 타이머 인터럽트(=08h) 핸들러
***************************************/
static void __interrupt __far __loadds NewTimerVect( void )
{
    // 인터럽트 중지
    _disable();

    // 타이머 값 증가
    MULTITIMER::OrgTick ++;

    // 멀티 타이머
    MULTITIMER *mt;

    // 멀티 타이머를 처리한다.
    for( int i = 1; i <= MTIMER_COUNT; i ++ ){
      // 일단 멀티 타이머 한개를 얻는다.
      mt = _MultiTimer[i];
      // 만약 타이머가 설정되었다면...
      if( mt ){
        // 타이머 틱을 하나 증가
        mt->Tick ++;
        // 타이머 틱이 지정된 주기를 넘어서면...
        if( mt->Tick >= mt->Period ){
          // 틱은 리셋
          mt->Tick = 0;
          mt->Counter ++;
          // 타이머 핸들러 호출
          if( mt->Handler ) mt->Handler();
        }
      }
    }

    // 이전의 타이머 인터럽트 핸들러를 동기화
    if( ++OldTick >= TIMER_RATE / 18.2 ){
      OldTick = 0;
      OldTimerVect();
    }

    // 하위 레벨 인터럽트 신호 인가
    outp( 0x20, 0x20 );

    // 인터럽트 활성화
    _enable();
}


/***********************
  타이머를 초기화한다.
************************/
void MULTITIMER :: InitTimer( void )
{
    // 인터럽트 중지
    _disable();

    // 타이머 관련 전역 변수 초기화
    OrgTick = 0;
    OldTick = 0;

    // 멀티 타이머 초기화
    for( int i = 0; i <= MTIMER_COUNT; i ++ )
      _MultiTimer[i]  = NULL;

    // 8253 타이머의 주파수를 1000Hz로 늘린다.
    outp( 0x43, 0x3C );
    outp( 0x40, (1193180 / TIMER_RATE) & 0xFF );
    outp( 0x40, (1193180 / TIMER_RATE) >> 8 );

    // 이전 타이머 인터럽트 핸들을 얻는다.
    OldTimerVect = _dos_getvect( 0x08 );

    // 새로운 인터럽트 핸들러 설정
    _dos_setvect( 0x08, NewTimerVect );

    // 인터럽트 활성화
    _enable();
}


/***********************
  타이머를 중지시킨다.
************************/
void MULTITIMER :: CloseTimer( void )
{
    // 만약 기존 타이머가 설정되었다면
    if( OldTimerVect ){
      // 타이머 인터럽트 핸들러 복귀
      _dos_setvect( 0x08, OldTimerVect );

      // 8253 타이머의 주파수를 정상(18.2Hz)로 돌린다.
      outp( 0x43, 0x3C );
      outp( 0x40, 0 );
      outp( 0x40, 0 );
    }

    // 각 멀티 타이머를 비활성화시킨다.
    for( int i = 0; i <= MTIMER_COUNT; i ++ )
      if( _MultiTimer[i] )
        _MultiTimer[i]->Disable();
}


/*********************
  멀티 타이머 생성자
**********************/
MULTITIMER :: MULTITIMER( void )
{
    TimerID = 0;
    Tick    = 0;
    Counter = 0;
    Period  = 0;

    Handler = NULL;
}


/*********************
  멀티 타이머 생성자
**********************/
MULTITIMER :: MULTITIMER( INT Period, void (*Handler)(void) )
{
    TimerID = 0;
    Tick    = 0;
    Counter = 0;

    this->Period  = Period;
    this->Handler = Handler;
}


/*********************
  멀티 타이머 소멸자
**********************/
MULTITIMER :: ~MULTITIMER()
{
    Disable();
}


/*******************
  멀티 타이머 리셋
********************/
void MULTITIMER :: Reset( void )
{
    Tick = 0;
    Counter = 0;
}


/**************************
  멀티 타이머 핸들러 설치
***************************/
void MULTITIMER :: SetHandler( void (*Handler)(void) )
{
    this->Handler = Handler;
}


/*************************
  멀티 타이머 주기 설정
**************************/
void MULTITIMER :: SetPeriod( INT Period )
{
    this->Period = Period;
}


/*********************
  멀티 타이머 활성화
**********************/
BOOL MULTITIMER :: Enable( void )
{
    // 빈 타이머를 찾는다.
    for( int i = 1; i <= MTIMER_COUNT; i ++ )
      // 사용하지 않는 타이머가 있다면...
      if( !_MultiTimer[i] ){
        // 타이머를 설정한다.
        TimerID = i;
        _MultiTimer[i] = this;
        return( TRUE );
      }

    return( FALSE );
}


/************************
  멀티 타이머 사용 중지
*************************/
BOOL MULTITIMER :: Disable( void )
{
    // 타이머가 활성화 되어 있다면...
    if( TimerID ){
      // 해당 타이머 핸들러 리스트를 삭제
      _MultiTimer[ TimerID ] = (MULTITIMER *)NULL;
      return( TRUE );
    } else
      return( FALSE );
}


