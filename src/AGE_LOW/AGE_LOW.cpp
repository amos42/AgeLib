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

#include "age_low.h"


INT         _State = 0;
COLOR      *_Video = (COLOR *)0xA0000;
RECT        _Clip( 0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1 );
COLOR       _TransColor = (COLOR)0xFF;
COLOR       _ShadowColor = (COLOR)0;


/***************************
  아무 것도 하지 않는 함수
****************************/
void DummyFunction()
{
}


/***************
  엔진 초기화
****************/
void AGE :: Init( void )
{
    CRTC::SetGraphicMode();
}


/************
  엔진 종료
*************/
void AGE :: Close( void )
{
    CRTC::SetTextMode();
}


