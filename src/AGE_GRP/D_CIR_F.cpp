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
void DCIRCLE :: DrawFill( INT X, INT Y, INT Ratio, COLOR Color )
{
   int x, y, thres;


   if( Ratio == 0 ){
     PIXEL::Put( X, Y, Color );
     return;
   }

   y = Ratio;
   thres = 3 - (Ratio << 1);

   for( x = 0; x < y; x ++ ){
     if( thres < 0 ){
       thres += 6 + (x << 2);
     } else {
       thres += 10 + ((x - y) << 2);
       y --;
     }

     DLINE::DrawHoriz( X - x, Y + y, (x << 1) + 1, Color );
     DLINE::DrawHoriz( X - x, Y - y, (x << 1) + 1, Color );
     DLINE::DrawHoriz( X - y, Y + x, (y << 1) + 1, Color );
     DLINE::DrawHoriz( X - y, Y - x, (y << 1) + 1, Color );
   }
}


/***************************
  속이 채워진 원을 그린다.
****************************/
void DCIRCLE :: DrawFill( void )
{
    DrawFill( X, Y, Ratio, Color );
}



