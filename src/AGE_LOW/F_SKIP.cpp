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

#include <dos.h>
#include <string.h>
#include <conio.h>
#include "age_low.h"


FRAMESKIP _FS;


/***********************
  프레임 스키핑 생성자
************************/
FRAMESKIP :: FRAMESKIP( void ) : MULTITIMER( 0, NULL )
{
    DelayHandler = DummyFunction;
}


/***********************
  프레임 스키핑 소멸자
************************/
FRAMESKIP :: ~FRAMESKIP()
{
}


/***********************
  타이머를 초기화한다.
************************/
void FRAMESKIP :: Enable()
{
    Reset();
    MULTITIMER::Enable();
}


/***********************
  타이머를 해제한다.
************************/
void FRAMESKIP :: Disable( void )
{
    MULTITIMER::Disable();
}


/******************************
  기존 타이머 값을 리셋시킨다.
*******************************/
void FRAMESKIP :: Reset( void )
{
    MULTITIMER::Reset();
}


/*******************************************
  출력순간인가를 판단한다.(Frame Skipping)
********************************************/
BOOL FRAMESKIP :: IsDisplayTime( void )
{
    return( Counter <= TIMER_RATE / FPS );
}


/**************************
  엔진의 내부를 처리한다.
***************************/
void FRAMESKIP :: DoEvents( void )
{
    do {
      DelayHandler();
    } while( Counter < TIMER_RATE / FPS );

    Counter -= TIMER_RATE / FPS;
}


