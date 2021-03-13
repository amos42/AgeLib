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
static void tLine( INT StartX, INT StartY, INT EndX, INT EndY, COLOR Color )
{
    int temp;
    COLOR *p;
    int dx, dy;
    int inc, half, err = 0;


    dx = EndX - StartX;
    dy = EndY - StartY;
    if( dx < 0 ) dx = -dx;
    if( dy < 0 ) dy = -dy;

    if( dx >= dy ){
      if( StartX > EndX ){
        temp = StartX; StartX = EndX; EndX = temp;
        temp = StartY; StartY = EndY; EndY = temp;
      }

      inc = (StartY <= EndY) ? VMEM_WIDTH : -VMEM_WIDTH;

      half = dx >> 1;

      p = CALC_ADDR( StartX, StartY );

      for( int i = StartX; i <= EndX; i ++ ){
        *p = Color;
        p ++;
        err += dy;
        if( err > half ){
          p += inc;
          err -= dx;
        }
      }
    } else {
      if( StartY > EndY ){
        temp = StartX; StartX = EndX; EndX = temp;
        temp = StartY; StartY = EndY; EndY = temp;
      }

      inc = (StartX <= EndX) ? 1 : -1;

      half = dy >> 1;

      p = CALC_ADDR( StartX, StartY );

      for( int i = StartY; i <= EndY; i ++ ){
        *p = Color;
        p += VMEM_WIDTH;
        err += dx;
        if( err > half ){
          p += inc;
          err -= dy;
        }
      }
    }
}


/******************************************
  클리핑하여 양 끝 점을 잇는 선을 그린다.
*******************************************/
void DLINE :: Draw( INT StartX, INT StartY, INT EndX, INT EndY, COLOR Color )
{
    int code1, code2;
    int xl, xr, yl, yr;
    long dx, dy, off  ;

    code1 = code2 = 0 ;

    if( StartX < _Clip.StartX ) code1 += 4;
    if( StartX > _Clip.EndX   ) code1 += 8;
    if( StartY < _Clip.StartY ) code1 += 1;
    if( StartY > _Clip.EndY   ) code1 += 2;

    if( EndX   < _Clip.StartX ) code2 += 4 ;
    if( EndX   > _Clip.EndX   ) code2 += 8 ;
    if( EndY   < _Clip.StartY ) code2 += 1 ;
    if( EndY   > _Clip.EndY   ) code2 += 2 ;


    if( code1 & code2 ) return;

    if( code1 == 0 && code2 == 0 ){
      tLine( StartX, StartY, EndX, EndY, Color );
      return;
    }

    if( StartX == EndX ){
      DLINE::DrawVert( StartX, StartY, EndY - StartY + 1, Color );
      return;
    }
    if( StartY == EndY ){
      DLINE::DrawHoriz( StartX, StartY, EndX - StartX + 1, Color );
      return;
    }

    if( code1 > code2 ){
      int t;
      t = code1;  code1  = code2; code2 = t;
      t = StartX; StartX = EndX;  EndX  = t;
      t = StartY; StartY = EndY;  EndY  = t;
    }

    dx = EndX - StartX;
    dy = EndY - StartY;
    off= EndX * StartY - EndY * StartX;

    xl = (dx * _Clip.StartY - off) / dy;
    yl = (dy * _Clip.StartX + off) / dx;
    xr = (dx * _Clip.EndY   - off) / dy;
    yr = (dy * _Clip.EndX   + off) / dx;

    if( code1 == 0 ){
      switch( code2 ){
        case 1 : EndX = xl;
                 EndY=_Clip.StartY;
                 break;
        case 2 : EndX = xr;
                 EndY=_Clip.EndY;
                 break;
        case 4 : EndX = _Clip.StartX;
                 EndY = yl;
                 break;
        case 8 : EndX = _Clip.EndX;
                 EndY = yr;
                 break;
        case 5 : EndX = _Clip.StartX;
                 EndY = yl;
                 if( EndY < _Clip.StartY || _Clip.EndY < EndY ){
                   EndX = xl;
                   EndY = _Clip.StartY;
                 }
                 break;
        case 6 : EndX = _Clip.StartX;
                 EndY = yl;
                 if( EndY < _Clip.StartY || _Clip.EndY < EndY ){
                   EndX = xr;
                   EndY = _Clip.EndY;
                 }
                 break;
        case 9 : EndX = _Clip.EndX;
                 EndY = yr;
                 if( EndY < _Clip.StartY || _Clip.EndY < EndY ){
                   EndX = xl;
                   EndY = _Clip.StartY;
                 }
                 break;
        case 10: EndX = _Clip.EndX;
                 EndY = yr;
                 if( EndY < _Clip.StartY || _Clip.EndY < EndY ){
                   EndX = xr;
                   EndY = _Clip.EndY;
                 }
                 break;
      }

      tLine( StartX, StartY, EndX, EndY, Color );
    } else {
      int n = 0;
      int x[2], y[2];

      if( _Clip.StartX <  xl && xl <  _Clip.EndX ){ x[n] = xl; y[n++]= _Clip.StartY; }
      if( _Clip.StartY <= yl && yl <= _Clip.EndY ){ y[n] = yl; x[n++]= _Clip.StartX; }
      if( _Clip.StartX <  xr && xr <  _Clip.EndX ){ x[n] = xr; y[n++]= _Clip.EndY; }
      if( _Clip.StartY <= yr && yr <= _Clip.EndY ){ y[n] = yr; x[n++]= _Clip.EndX; }

      if( n == 1 )
        PIXEL::Put( x[0], y[0], Color );
      else if( n == 2 )
        tLine( x[0], y[0], x[1], y[1], Color );
    }
}


/******************************************
  클리핑하여 양 끝 점을 잇는 선을 그린다.
*******************************************/
void DLINE :: Draw( void )
{
    Draw( StartX, StartY, EndX, EndY, Color );
}


