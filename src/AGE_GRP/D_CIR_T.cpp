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

#include "age_grp.h"


/***************************
  속이 채워진 원을 그린다.
****************************/
void DCIRCLE :: DrawTrans( INT X, INT Y, INT Ratio, COLOR *TransTable )
{
   int x, y, thres;


   if( Ratio == 0 ) Ratio = 1;

   y = Ratio;
   thres = 3 - (Ratio << 1);

   for( x = 0; x < y; x ++ ){
     if( thres < 0 ){
       thres += 6 + (x << 2);
     } else {
       thres += 10 + ((x - y) << 2);
       y --;
     }

     DLINE::DrawHorizTrans( X - x, Y + y, (x << 1) + 1, TransTable );
     DLINE::DrawHorizTrans( X - x, Y - y, (x << 1) + 1, TransTable );
     DLINE::DrawHorizTrans( X - y, Y + x, (y << 1) + 1, TransTable );
     DLINE::DrawHorizTrans( X - y, Y - x, (y << 1) + 1, TransTable );
   }
}


/***************************
  속이 채워진 원을 그린다.
****************************/
void DCIRCLE :: DrawTrans( void )
{
    DrawTrans( X, Y, Ratio, _ShadeTransTable.Get() );
}



