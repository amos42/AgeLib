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
#include "age_grp.h"


/*******************
  삼각형을 그린다.
********************/
void DTRIANGLE::Draw( INT X1, INT Y1, INT X2, INT Y2, INT X3, INT Y3, COLOR Color )
{
    if( Color == _TransColor ) return;

    DLINE::Draw( X1, Y1, X2, Y2, Color );
    DLINE::Draw( X1, Y1, X3, Y3, Color );
    DLINE::Draw( X2, Y2, X3, Y3, Color );
}


/*******************
  삼각형을 그린다.
********************/
void DTRIANGLE::Draw( void )
{
    Draw( X1, Y1, X2, Y2, X3, Y3, Color );
}


