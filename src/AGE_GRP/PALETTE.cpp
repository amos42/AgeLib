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
  蘨滱薬 垇罙穪 瑮竌
************************/
PALETTE :: PALETTE( void )
{
}


/***********************
  蘨滱薬 垇罙穪 瑮竌
************************/
PALETTE :: PALETTE( DACVALUE Red, DACVALUE Green, DACVALUE Blue )
{
    Set( Red, Green, Blue );
}


/***********************
  蘨滱薬 垇罙穪 竌
************************/
PALETTE :: ~PALETTE()
{
}


/********************
  RGB坱穒 瑼薬衑攁.
*********************/
void PALETTE :: Set( DACVALUE Red, DACVALUE Green, DACVALUE Blue )
{
    this->Red   = Red;
    this->Green = Green;
    this->Blue  = Blue;
}


/******************************
  薭各 瑐瑆穪 RGB坱穒 藩揺攁.
*******************************/
void PALETTE :: Get( COLOR Color, DACVALUE *Red, DACVALUE *Green, DACVALUE *Blue )
{
    outp( 0x3C7, Color );

    *Red   = (DACVALUE)inp( 0x3C9 );
    *Green = (DACVALUE)inp( 0x3C9 );
    *Blue  = (DACVALUE)inp( 0x3C9 );
}


/******************************
  薭各 瑐瑆穪 RGB坱穒 藩揺攁.
*******************************/
void PALETTE :: Get( COLOR Color )
{
    Get( Color, &Red, &Green, &Blue );
}


/*******************************
  瑐瑆 衋恆穪 RGB 坱穒 巺攁.
********************************/
void PALETTE :: Put( COLOR Color, DACVALUE Red, DACVALUE Green, DACVALUE Blue )
{
    outp( 0x3C8, Color );

    outp( 0x3C9, Red   );
    outp( 0x3C9, Green );
    outp( 0x3C9, Blue  );
}


/*******************************
  瑐瑆 衋恆穪 RGB 坱穒 巺攁.
********************************/
void PALETTE :: Put( COLOR Color )
{
    Put( Color, Red, Blue, Green );
}


/**************************
  弧各朎 蘨滱薬潯 巺攁.
***************************/
void PALETTE :: Clear( DACVALUE Red, DACVALUE Green, DACVALUE Blue )
{
    for( int i = 0; i < 256; i ++ )
      Put( (COLOR)i, Red, Green, Blue );
}


/**************************
  弧各朎 蘨滱薬潯 巺攁.
***************************/
void PALETTE :: Clear( void )
{
    Clear( Red, Green, Blue );
}


