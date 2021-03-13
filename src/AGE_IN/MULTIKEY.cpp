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
#include <conio.h>
#include <string.h>
#include "age_in.h"


MULTIKEY _Key;


/************************
  멀티키 개체의 생성자
*************************/
MULTIKEY :: MULTIKEY( void )
{
    OldKeyVect = NULL;

    Reset();
}


/************************
  멀티키 개체의 소멸자
*************************/
MULTIKEY :: ~MULTIKEY()
{
    Deactivate();
}


/******************************
  새로운 키 인터럽트 핸들러
*******************************/
static void __interrupt __far MULTIKEY :: NewKeyVect( void )
{
    _disable();

    int k    = inp( 0x60 );
    int flag = k & 0x80;

    k   &= 0x7F;

    if( !flag ){
      _Key.Last = (CHAR)k;

      if( !_Key.Scan[k] ){
        _Key.Scan[k] = TRUE;
        _Key.Press ++;
      }
    } else {
      if( _Key.Scan[k] ){
        _Key.Scan[k] = FALSE;
        _Key.Press --;
      }
    }

//    _Key.OldKeyVect();
    outp( 0x20, 0x20 );

    _enable();
}


/*********************
  데이터를 리셋한다.
**********************/
void MULTIKEY :: Reset( void )
{
    for( int i = 0; i < 128; i ++ ) Scan[i] = FALSE;

    Last = NULL;

    Press = 0;
}


/****************
  개체 활성화
*****************/
void MULTIKEY :: Activate( void )
{
    if( !OldKeyVect ){
      OldKeyVect = _dos_getvect( 0x09 );

      _dos_setvect( 0x09, NewKeyVect );
    }

    Reset();
}


/****************
  개체 비활성화
*****************/
void MULTIKEY :: Deactivate( void )
{
    if( OldKeyVect ){
      _dos_setvect( 0x09, OldKeyVect );

      OldKeyVect = NULL;
    }
}



