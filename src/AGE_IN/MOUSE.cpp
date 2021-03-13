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

#include <stdlib.h>
#include <i86.h>
#include "age_in.h"


/***********************
  마우스를 초기화 한다.
************************/
BOOL MOUSE :: Reset( void )
{
#if 0
    union REGS r;

    r.w.ax = 0;
    int386( 0x33, &r, &r );

    return( (BOOL)r.w.ax );
#endif

    BOOL r;

    __asm {
        mov ax, 0
        int 33h
        mov [r], eax
    };

    return( r );
}


/***********************
  마우스를 초기화 한다.
************************/
void MOUSE :: GetState( INT *Button, INT *X, INT *Y )
{
#if 0
    union REGS r;

    r.w.ax = 3;
    int386( 0x33, &r, &r );

    *Button = r.w.bx;
    *X = r.w.cx >> 1;
    *Y = r.w.dx;
#endif

    __asm {
        mov ax, 3
        int 33h

        mov eax, [Button]
        mov [eax], bx
        shr cx, 1
        mov eax, [X]
        mov [eax], cx
        mov eax, [Y]
        mov [eax], dx
    };

}


/***********************
  마우스를 초기화 한다.
************************/
void MOUSE :: GetButton( INT *Button )
{
#if 0
    union REGS r;

    r.w.ax = 3;
    int386( 0x33, &r, &r );

    *Button = r.w.bx;
#endif

    __asm {
        mov ax, 3
        int 33h

        mov eax, [Button]
        mov [eax], bx
    };
}


/***********************
  마우스를 초기화 한다.
************************/
void MOUSE :: GetPosition( INT *X, INT *Y )
{
#if 0
    union REGS r;

    r.w.ax = 3;
    int386( 0x33, &r, &r );

    *X = r.w.cx >> 1;
    *Y = r.w.dx;
#endif

    __asm {
        mov ax, 3
        int 33h

        shr cx, 1
        mov eax, [X]
        mov [eax], cx
        mov eax, [Y]
        mov [eax], dx
    };
}


/******************************************
  원하는 위치로 마우스 커서를 이동시킨다.
*******************************************/
void MOUSE :: SetPosition( INT X, INT Y )
{
#if 0
    union REGS r;

    r.w.cx = X << 1;
    r.w.dx = Y;
    r.w.ax = 4;
    int386( 0x33, &r, &r );
#endif

    __asm {
        mov ecx, [X]
        shl cx, 1
        mov edx, [Y]

        mov ax, 4
        int 33h
    };
}


/********************************
  마우스 커서의 속도를 세트한다.
*********************************/
void MOUSE :: SetPixelRatio( INT MickeyX, INT MickeyY )
{
#if 0
    union REGS r;

    r.w.dx = MickeyX;
    r.w.cx = MickeyY;
    r.w.ax = 0xF;
    int386( 0x33, &r, &r );
#endif

    __asm {
        mov edx, [MickeyX]
        mov ecx, [MickeyY]

        mov ax, 0Fh
        int 33h
    };
}


/****************************
  마우스의 감도를 설정한다.
*****************************/
void MOUSE :: SetSensitivity( INT SpeedX, INT SpeedY, INT DoubleClick )
{
#if 0
    union REGS r;

    r.w.bx = SpeedX;
    r.w.cx = SpeedY;
    r.w.dx = DoubleClick;
    r.w.ax = 0x1a;
    int386( 0x33, &r, &r );
#endif

    __asm {
        mov ebx, [SpeedX]
        mov ecx, [SpeedY]
        mov edx, [DoubleClick]

        mov ax, 1Ah
        int 33h
    };
}


/**************************************
  마우스 커서의 좌표 범위를 설정한다.
***************************************/
void MOUSE :: SetWindow( INT StartX, INT StartY, INT EndX, INT EndY )
{
#if 0
    union REGS r;

    r.w.cx = StartX;
    r.w.dx = EndX << 1;
    r.w.ax = 7;
    int386( 0x33, &r, &r );

    r.w.cx = StartY;
    r.w.dx = EndY;
    r.w.ax = 8;
    int386( 0x33, &r, &r );
#endif

    __asm {
        mov ecx, [StartX]
        mov edx, [EndX]
        shl dx, 1
        mov ax, 7
        int 33h

        mov ecx, [StartY]
        mov edx, [EndY]
        mov ax, 8
        int 33h
    };
}


/****************************
  이벤트 핸들러를 설치한다.
*****************************/
void MOUSE :: SetHandler( void (__far *Handler)() )
{
    union REGS   r;
    struct SREGS s;

    segread( &s );
    s.es = FP_SEG( Handler );
    r.x.edx = FP_OFF( Handler );
    r.w.cx = 0x1f;
    r.w.ax = 0xc;
    int386x( 0x33, &r, &r, &s );
}



