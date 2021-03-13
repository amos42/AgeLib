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

#include "age_in.h"


/********************************
  키 버퍼가 비었는가를 체크한다.
*********************************/
BOOL KEY :: IsBuffer( void )
{
#if 0
    extern BOOL _IsBuffer( void );
    #pragma aux _IsBuffer =    \
        "mov ah, 1"         \
        "int 16h"           \
        "jz @@skip"         \
        "mov ax, 1"         \
        "jmp @@exit"        \
      "@@skip:"             \
        "xor ax, ax"        \
      "@@exit:"             \
    value [ax];

    return( _IsBuffer() );
#endif

    BOOL r;

    __asm {
        mov ah, 1
        int 16h
        jz @@skip
        mov eax, 1
        jmp @@exit
      @@skip:
        xor eax, eax
      @@exit:
        mov [r], eax
    };

    return( r );
}


/********************
  키버퍼를 제거한다.
*********************/
void KEY :: Clear( void )
{
    *(S16 *)0x41A = *(S16 *)0x41C;
}


/*******************************************
  키버퍼에 키값을 넣는다.(키버퍼는 클리어)
********************************************/
void KEY :: Put( CHAR Key )
{
    Clear();

    *(CHAR *)0x41E = Key;

    *(S16 *)0x41A = 0x1E;
    *(S16 *)0x41C = 0x20;
}


/*******************
  키를 입력받는다.
********************/
U16 KEY :: Get( void )
{
#if 0
    extern U16 _GetKey( void );
    #pragma aux _GetKey =       \
      "@@loop:"             \
        "xor ah, ah"        \
        "int 16h"           \
        "mov bx, ax"        \
        "mov ah, 1"         \
        "int 16h"           \
        "jnz @@loop"        \
        "test bl, bl"       \
        "jz @@no_change"    \
        "xor bh, bh"        \
      "@@no_change:"        \
        "mov ax, bx"        \
    modify [ax bx]          \
    value [ax];

    return( _GetKey() );
#endif

    U16 r;

    __asm {
      @@loop:
        xor ah, ah
        int 16h
        mov bx, ax
        mov ah, 1
        int 16h
        jnz @@loop
        test bl, bl
        jz @@no_change
        xor bh, bh
      @@no_change:
        mov ax, bx

        mov [r], ax
    };

    return( r );
}


/*****************************
  실시간으로 키를 입력받는다.
******************************/
U16 KEY :: GetSync( void )
{
    if( IsBuffer() )
      return( Get() );
    else
      return( NULL );
}



