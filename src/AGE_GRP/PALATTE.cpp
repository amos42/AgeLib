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
#include "age_grp.h"


/***********************
  팔레트 개체의 생성자
************************/
PALETTE :: PALETTE( void )
{
}


/***********************
  팔레트 개체의 생성자
************************/
PALETTE :: PALETTE( DACVALUE Red, DACVALUE Green, DACVALUE Blue )
{
    Set( Red, Green, Blue );
}


/***********************
  팔레트 개체의 소멸자
************************/
PALETTE :: ~PALETTE()
{
}


/********************
  RGB값을 세트한다.
*********************/
void PALETTE :: Set( DACVALUE Red, DACVALUE Green, DACVALUE Blue )
{
    this->Red   = Red;
    this->Green = Green;
    this->Blue  = Blue;
}


/******************************
  특정 색상의 RGB값을 읽는다.
*******************************/
void PALETTE :: Get( COLOR Color, DACVALUE *Red, DACVALUE *Green, DACVALUE *Blue )
{
    outp( 0x3C7, Color );

    *Red   = (DACVALUE)inp( 0x3C9 );
    *Green = (DACVALUE)inp( 0x3C9 );
    *Blue  = (DACVALUE)inp( 0x3C9 );
}


/******************************
  특정 색상의 RGB값을 읽는다.
*******************************/
void PALETTE :: Get( COLOR Color )
{
    Get( Color, &Red, &Green, &Blue );
}


/*******************************
  색상 하나의 RGB 값을 바꾼다.
********************************/
void PALETTE :: Put( COLOR Color, DACVALUE Red, DACVALUE Green, DACVALUE Blue )
{
    outp( 0x3C8, Color );

    outp( 0x3C9, Red   );
    outp( 0x3C9, Green );
    outp( 0x3C9, Blue  );
}


/*******************************
  색상 하나의 RGB 값을 바꾼다.
********************************/
void PALETTE :: Put( COLOR Color )
{
    Put( Color, Red, Blue, Green );
}


/**************************
  지정된 팔레트로 바꾼다.
***************************/
void PALETTE :: Clear( DACVALUE Red, DACVALUE Green, DACVALUE Blue )
{
    for( int i = 0; i < 256; i ++ )
      Put( (COLOR)i, Red, Green, Blue );
}


/**************************
  지정된 팔레트로 바꾼다.
***************************/
void PALETTE :: Clear( void )
{
    Clear( Red, Green, Blue );
}



