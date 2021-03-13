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


/*****************************************
  테이블에 의해 변환된 이미지를 출력한다.
******************************************/
void IMAGE :: PutTrans( INT X, INT Y, COLOR *TransTable )
{
    COLOR *ScrPtr, *ImgPtr, pixel;
    int i, j, width, height;
    int t, sskip, iskip;
    COLOR tc = _TransColor;


    if( TransTable == NULL ) return;

    width = Width;
    height = Height;

    if( width == 0 || height == 0 ) return;

    ImgPtr = Bitmap;

    X += LogX;
    Y += LogY;

    if( Y > _Clip.EndY ) return;
    if( Y < _Clip.StartY ){
      height -= _Clip.StartY - Y;
      ImgPtr += (_Clip.StartY - Y) * width;
      Y = _Clip.StartY;
    }

    t = Y + height - 1;
    if( t < _Clip.StartY ) return;
    if( t > _Clip.EndY ){
      height -= t - _Clip.EndY;
    }

    iskip = 0;
    if( X > _Clip.EndX ) return;
    if( X < _Clip.StartX ){
      width -= _Clip.StartX - X;
      ImgPtr += _Clip.StartX - X;
      iskip += _Clip.StartX - X;
      X = _Clip.StartX;
    }
    t = X + width - 1;
    if( t < _Clip.StartX ) return;
    if( t > _Clip.EndX ){
      width -= t - _Clip.EndX;
      iskip += t - _Clip.EndX;
    }

    ScrPtr = CALC_ADDR( X, Y );
    sskip = VMEM_WIDTH - width;

    for( i = 0; i < height; i ++ ){
      for( j = 0; j < width; j ++ ){
        pixel = *ImgPtr++;
        if( pixel != tc )
          *ScrPtr = TransTable[ *ScrPtr << 8 | pixel ];
        ScrPtr ++;
      }

      ScrPtr += sskip;
      ImgPtr += iskip;
    }
}


/*****************************
  이미지를 늘려서 출력한다.
******************************/
void IMAGE :: PutTransStretch( INT X, INT Y, INT tWidth, INT tHeight, COLOR *TransTable )
{
    int i, j, t;
    COLOR *ScrPtr, *ImgPtr, *sa, pixel;
    int width, height, xx, yy;
    FIXED dx, dy;
    int sskip;
    COLOR tc = _TransColor;


    width = Width;
    height = Height;

    if( width == 0 || height == 0 ) return;

    dx = INTTOFIXED(width)  / tWidth;
    dy = INTTOFIXED(height) / tHeight;

    X += LogX * tWidth  / width;
    Y += LogY * tHeight / height;

    ImgPtr = Bitmap;

    if( Y > _Clip.EndY ) return;
    if( Y < _Clip.StartY ){
      tHeight -= _Clip.StartY - Y;
      ImgPtr += FIXEDTOINT( (_Clip.StartY - Y) * dy ) * width;
      Y = _Clip.StartY;
    }
    t = Y + tHeight - 1;
    if( t < _Clip.StartY ) return;
    if( t > _Clip.EndY ){
      tHeight -= t - _Clip.EndY;
    }

    if( X > _Clip.EndX ) return;
    if( X < _Clip.StartX ){
      tWidth -= _Clip.StartX - X;
      ImgPtr += FIXEDTOINT( (_Clip.StartX - X) * dx );
      X = _Clip.StartX;
    }
    t = X + tWidth - 1;
    if( t < _Clip.StartX ) return;
    if( t > _Clip.EndX ){
      tWidth -= t - _Clip.EndX;
    }

    ScrPtr = CALC_ADDR( X, Y );

    sskip = VMEM_WIDTH - tWidth;
    yy = 0;

    for( i = 0; i < tHeight; i ++ ){
      sa = ImgPtr + FIXEDTOINT(yy) * width;

      xx = 0;
      for( j = 0; j < tWidth; j ++ ){
        pixel = *(sa + FIXEDTOINT(xx));
        if( pixel != tc )
          *ScrPtr = TransTable[ *ScrPtr << 8 | pixel ];
        ScrPtr ++;
        xx += dx;
      }

      ScrPtr += sskip;
      yy += dy;
    }
}


/**************************************
  이미지를 일정 배율 늘려서 출력한다.
***************************************/
void IMAGE :: PutTransScale( INT X, INT Y, FIXED Scale, COLOR *TransTable )
{
    int w = FIXEDTOINT( Width  * Scale );
    int h = FIXEDTOINT( Height * Scale );

    if( w == 0 || h == 0 ) return;

    PutTransStretch( X, Y, w, h, TransTable );
}



