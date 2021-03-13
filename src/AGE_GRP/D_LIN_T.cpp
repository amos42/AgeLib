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


/*******************************
  양 끝 점을 잇는 선을 그린다.
********************************/
void DLINE :: DrawTrans( INT StartX, INT StartY, INT EndX, INT EndY, COLOR *TransTable )
{
    int i;
    COLOR *p;
    int dx, dy;
    int temp, flag = 0;
    int half, err = 0;


    dx = EndX - StartX;
    if( dx < 0 ){
      dx = -dx;
      temp = StartX; StartX = EndX; EndX = temp;
      flag ++;
    }
    dy = EndY - StartY;
    if( dy < 0 ){
      dy = -dy;
      temp = StartY; StartY = EndY; EndY = temp;
      flag ++;
    }
    flag &= 0x1;


    if( StartX > _Clip.EndX || StartY > _Clip.EndY ) return;
    if( StartX < _Clip.StartX ){
      StartY += (_Clip.StartX - StartX) * dy / dx;
      StartX = _Clip.StartX;
    }
    if( StartY < _Clip.StartY ){
      StartX += (_Clip.StartY - StartY) * dx / dy;
      StartY = _Clip.StartY;
    }
    if( EndX < _Clip.StartX || EndY > _Clip.StartY ) return;
    if( EndX > _Clip.EndX ){
      EndX = _Clip.EndX;
    }
    if( EndY > _Clip.EndY ){
      EndY = _Clip.EndY;
    }


    if( dx >= dy ){
      half = dx >> 1;

      if( !flag ){
        p = CALC_ADDR( StartX, StartY );

        for( i = StartX; i <= EndX; i ++ ){
          *p = TransTable[ *p ];
          p ++;
          err += dy;
          if( err > half ){
            p += VMEM_WIDTH;
            err -= dx;
          }
        }
      } else {
        p = CALC_ADDR( StartX, EndY );

        for( i = StartX; i <= EndX; i ++ ){
          *p = TransTable[ *p ];
          p ++;
          err += dy;
          if( err > half ){
            p -= VMEM_WIDTH;
            err -= dx;
          }
        }
      }
    } else {
      half = dy >> 1;

      if( !flag ){
        p = CALC_ADDR( StartX, StartY );

        for( i = StartY; i <= EndY; i ++ ){
          *p = TransTable[ *p ];
          p += VMEM_WIDTH;
          err += dx;
          if( err > half ){
            p ++;
            err -= dy;
          }
        }
      } else {
        p = CALC_ADDR( EndX, StartY );

        for( i = StartY; i <= EndY; i ++ ){
          *p = TransTable[ *p ];
          p += VMEM_WIDTH;
          err += dx;
          if( err > half ){
            p --;
            err -= dy;
          }
        }
      }
    }
}



