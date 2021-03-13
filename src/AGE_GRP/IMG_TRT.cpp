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


/*********************************
  지정된 좌 의 점을 읽어온다.
**********************************/
void IMAGE :: DrawTextureRect( INT StartX, INT StartY, INT EndX, INT EndY )
{
    RECT r = _Clip;

    _Clip.StartX = StartX;
    _Clip.StartY = StartY;
    _Clip.EndX = EndX;
    _Clip.EndY = EndY;

    int w = Width;
    int h = Height;

    int x = EndX - StartX + 1;
    int wcount = x / w;
    if( x % w ) wcount ++;

    int y = EndY - StartY + 1;
    int hcount = y / h;
    if( y % h ) hcount ++;

    y = StartY;
    for( int i = 0; i < hcount; i ++ ){
      x = StartX;

      for( int j = 0; j < wcount; j ++ ){
        Put( x, y );
        x += w;
      }

      y += h;
    }

    _Clip = r;
}



#if 0
void DrawTextureRect( INT StartX, INT StartY, INT EndX, INT EndY, IMAGE *Texture )
{
    int i, j;
    PIXEL *ScrPtr, *ImgPtr;
    int width, height;
    int tw, th;
    int wc, w2, hc, h2;
    int skip, bnk;
    char *s, *e;


    tw = Width;
    th = Height;

    width = EndX - StartX + 1;
    wc = width / tw;
    w2 = width % tw;

    height = EndY - StartY + 1;
    hc = height / th;
    h2 = height % th;

    ImgPtr = Bitmap;
    s = ImgPtr;
    e = ImgPtr + tw * th;

    ScrPtr = CALC_ADDR( StartX, StartY );

    skip = VMEM_WIDTH - width;

    for( i = 0; i < height; i ++ ){
      for( j = 0; j < wc; j ++ ){
        memcpy( ScrPtr, ImgPtr, tw );
        ScrPtr += tw;
      }
      if( w2 > 0 ){
        memcpy( ScrPtr, ImgPtr, w2 );
        ScrPtr += w2;
      }

      ImgPtr += tw;
      if( ImgPtr >= e ) ImgPtr = s;

      ScrPtr += skip;
    }
}
#endif



