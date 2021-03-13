/*#################################################################
-------------------------------------------------------------------

                             AGE (Ver 1.0)
                       (* =================== *)
                           Amos Game Engine

 Author         : Chu, Kyong-min( Amos )

 Date           : 1997/02/08
 C Compiler     : WATCOM 11.0
 Assembler      : WASM 11.0

-------------------------------------------------------------------
###################################################################*/

#include "age_grp.h"


/***************
  원을 그린다.
****************/
void DCIRCLE :: Draw( INT X, INT Y, INT Ratio, COLOR Color )
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
     } else{
       thres += 10 + ((x - y) << 2);
       y --;
     }

     PIXEL::Put( X+x, Y+y, Color ); PIXEL::Put( X+y, Y+x, Color );
     PIXEL::Put( X-x, Y+y, Color ); PIXEL::Put( X-y, Y+x, Color );
     PIXEL::Put( X+x, Y-y, Color ); PIXEL::Put( X+y, Y-x, Color );
     PIXEL::Put( X-x, Y-y, Color ); PIXEL::Put( X-y, Y-x, Color );
   }
}


/***************
  원을 그린다.
****************/
void DCIRCLE :: Draw( void )
{
    Draw( X, Y, Ratio, Color );
}



