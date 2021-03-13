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


/*******************************
  속이 채워진 삼각형을 그린다.
********************************/
void DTRIANGLE :: DrawTrans( INT X1, INT Y1, INT X2, INT Y2, INT X3, INT Y3, COLOR *TransTable )
{
    int i;
    FIXED d12, d13, d23;
    FIXED dl, dr;
    FIXED xl, xr;
    long temp;
    BOOL IsInv = FALSE;


    /* y좌표를 소트한다. */
    if( Y1 > Y2 ){
      temp = Y1; Y1 = Y2; Y2 = temp;
      temp = X1; X1 = X2; X2 = temp;
    }
    if( Y1 > Y3 ){
      temp = Y1; Y1 = Y3; Y3 = temp;
      temp = X1; X1 = X3; X3 = temp;
    }
    if( Y2 > Y3 ){
      temp = Y2; Y2 = Y3; Y3 = temp;
      temp = X2; X2 = X3; X3 = temp;
    }


    if( Y1 > _Clip.EndY ) return;
    if( Y3 < _Clip.StartY ) return;

    if( Y1 == Y3 ){
      X1 = (X1 < X2) ? ((X1 < X3) ? X1 : X3) : ((X2 < X3) ? X2 : X3);
      X3 = (X1 > X2) ? ((X1 > X3) ? X1 : X3) : ((X2 > X3) ? X2 : X3);
      DLINE::DrawHorizTrans( X1, Y1, (X3 - X1) + 1, TransTable );
      return;
    }


    d13 = (Y3 != Y1)? INTTOFIXED(X3 - X1) / (Y3 - Y1) : 0;
    d12 = (Y2 != Y1)? INTTOFIXED(X2 - X1) / (Y2 - Y1) : 0;
    d23 = (Y3 != Y2)? INTTOFIXED(X3 - X2) / (Y3 - Y2) : 0;


    xl = xr = INTTOFIXED(X1);

    if( Y1 < _Clip.StartY ){
      temp = _Clip.StartY - Y1;
      Y1 = _Clip.StartY;

      xl += d12 * temp;
      if( Y2 < _Clip.StartY ){
        xr += d23 * (_Clip.StartY - Y2);
        Y2 = _Clip.StartY;
      } else {
        xr += d13 * temp;
      }
    }

    if( Y3 > _Clip.EndY ){
      Y3 = _Clip.EndY;

      if( Y2 > _Clip.EndY ){
        Y2 = _Clip.EndY;
      }
    }


    if( Y1 != Y2 ){
      if( d12 < d13 ){
        dl = d12; dr = d13;
      } else {
        dl = d13; dr = d12;
        temp = xl; xl = xr; xr = temp;
        IsInv = TRUE;
      }

      for( i = Y1; i <= Y2; i ++ ){
        DLINE::DrawHorizTrans( FIXEDTOINT(xl), i, FIXEDTOINT(xr - xl) + 1, TransTable );
        xl += dl;
        xr += dr;
      }
    } else {
      if( X1 < X2 ) IsInv = TRUE;
    }


    if( Y2 != Y3 ){
      if( !IsInv ){
        xl = INTTOFIXED(X2);
        dl = d23; dr = d13;
      } else {
        xr = INTTOFIXED(X2);
        dl = d13; dr = d23;
      }

      for( i = Y2; i <= Y3; i ++ ){
        DLINE::DrawHorizTrans( FIXEDTOINT(xl), i, FIXEDTOINT(xr - xl) + 1, TransTable );
        xl += dl;
        xr += dr;
      }
    }
}


/*******************************
  속이 채워진 삼각형을 그린다.
********************************/
void DTRIANGLE :: DrawTrans( void )
{
    DrawTrans( X1, Y1, X2, Y2, X3, Y3, _ShadeTransTable.Get() );
}



