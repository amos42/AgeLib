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

#include <conio.h>
#include "age_low.h"


/*************************************
  베사 모드(320x200-256c)로 세트한다.
**************************************/
void CRTC :: SetGraphicMode( void )
{
#if 0
    extern void _SetGraphicMode( void );
    #pragma aux _SetGraphicMode =   \
        "mov ax, 13h"               \
        "int 10h"                   \
    modify [ax];

    _SetGraphicMode();
#endif

    __asm {
        mov ax, 13h
        int 10h
    };
}


/**********************************
  텍스트 모드로 세트한다.
***********************************/
void CRTC :: SetTextMode( void )
{
#if 0
    extern void _SetTextMode( void );
    #pragma aux _SetTextMode =  \
        "mov ax, 0003h"         \
        "int 10h"               \
    modify [ax];

    _SetTextMode();
#endif

    __asm {
        mov ax, 3h
        int 10h
    };
}


/*****************************
  수직 동기 신호를 기다린다.
******************************/
void CRTC :: WaitVert( void )
{
    while( !(inp( 0x3DA ) & 0x08) ){};
}


