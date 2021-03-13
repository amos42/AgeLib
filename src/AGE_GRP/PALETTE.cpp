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
  �i�A�a ���A�� �����a
************************/
PALETTE :: PALETTE( void )
{
}


/***********************
  �i�A�a ���A�� �����a
************************/
PALETTE :: PALETTE( DACVALUE Red, DACVALUE Green, DACVALUE Blue )
{
    Set( Red, Green, Blue );
}


/***********************
  �i�A�a ���A�� ���i�a
************************/
PALETTE :: ~PALETTE()
{
}


/********************
  RGB�t�i �A�a�e�a.
*********************/
void PALETTE :: Set( DACVALUE Red, DACVALUE Green, DACVALUE Blue )
{
    this->Red   = Red;
    this->Green = Green;
    this->Blue  = Blue;
}


/******************************
  �b�� ���w�� RGB�t�i ���e�a.
*******************************/
void PALETTE :: Get( COLOR Color, DACVALUE *Red, DACVALUE *Green, DACVALUE *Blue )
{
    outp( 0x3C7, Color );

    *Red   = (DACVALUE)inp( 0x3C9 );
    *Green = (DACVALUE)inp( 0x3C9 );
    *Blue  = (DACVALUE)inp( 0x3C9 );
}


/******************************
  �b�� ���w�� RGB�t�i ���e�a.
*******************************/
void PALETTE :: Get( COLOR Color )
{
    Get( Color, &Red, &Green, &Blue );
}


/*******************************
  ���w �a�a�� RGB �t�i �a���a.
********************************/
void PALETTE :: Put( COLOR Color, DACVALUE Red, DACVALUE Green, DACVALUE Blue )
{
    outp( 0x3C8, Color );

    outp( 0x3C9, Red   );
    outp( 0x3C9, Green );
    outp( 0x3C9, Blue  );
}


/*******************************
  ���w �a�a�� RGB �t�i �a���a.
********************************/
void PALETTE :: Put( COLOR Color )
{
    Put( Color, Red, Blue, Green );
}


/**************************
  �����E �i�A�a�� �a���a.
***************************/
void PALETTE :: Clear( DACVALUE Red, DACVALUE Green, DACVALUE Blue )
{
    for( int i = 0; i < 256; i ++ )
      Put( (COLOR)i, Red, Green, Blue );
}


/**************************
  �����E �i�A�a�� �a���a.
***************************/
void PALETTE :: Clear( void )
{
    Clear( Red, Green, Blue );
}


