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
  주어진 RGB값에 가장 근접한 색을 찾는다.
******************************************/
COLOR PALETTEMAP :: FindColor( DACVALUE Red, DACVALUE Green, DACVALUE Blue )
{
    int mini = 0;
    int mindist = 256*256*3;
    PALETTE *pal = Palette;


    for( int i = 0; i < 256; i ++ ){
      int r = (int)Red   - pal->Red;
      int g = (int)Green - pal->Green;
      int b = (int)Blue  - pal->Blue;

      int dist = (r * r) + (g * g) + (b * b);

      if( dist < mindist ){
        mindist = dist;
        mini = i;
      }

      pal ++;
    }

    return( mini );
}


/************************************************************
  주어진 RGB값에 가장 근접한 색을 지정된 범위 내에서 찾는다.
*************************************************************/
COLOR PALETTEMAP :: FindColor( DACVALUE Red, DACVALUE Green, DACVALUE Blue, COLOR StartColor, COLOR EndColor )
{
    int mini = StartColor;
    int mindist = 256*256*3;
    PALETTE *pal = Palette;


    for( int i = StartColor; i <= EndColor; i ++ ){
      int r = (int)Red   - pal->Red;
      int g = (int)Green - pal->Green;
      int b = (int)Blue  - pal->Blue;

      int dist = (r * r) + (g * g) + (b * b);

      if( dist < mindist ){
        mindist = dist;
        mini = i;
      }

      pal ++;
    }

    return( mini );
}


/*****************************************
  주어진 RGB값에 가장 근접한 색을 찾는다.
******************************************/
COLOR PALETTEMAP :: FindColor( PALETTE &Palette )
{
    int mini = 0;
    int mindist = 256*256*3;
    PALETTE *pal = this->Palette;


    int Red   = Palette.Red;
    int Green = Palette.Green;
    int Blue  = Palette.Blue;

    for( int i = 0; i < 256; i ++ ){
      int r = (int)Red   - pal->Red;
      int g = (int)Green - pal->Green;
      int b = (int)Blue  - pal->Blue;

      int dist = (r * r) + (g * g) + (b * b);

      if( dist < mindist ){
        mindist = dist;
        mini = i;
      }

      pal ++;
    }

    return( mini );
}


/************************************************************
  주어진 RGB값에 가장 근접한 색을 지정된 범위 내에서 찾는다.
*************************************************************/
COLOR PALETTEMAP :: FindColor( PALETTE &Palette, COLOR StartColor, COLOR EndColor )
{
    int mini = StartColor;
    int mindist = 256*256*3;
    PALETTE *pal = this->Palette;


    int Red   = Palette.Red;
    int Green = Palette.Green;
    int Blue  = Palette.Blue;

    for( int i = StartColor; i <= EndColor; i ++ ){
      int r = (int)Red   - pal->Red;
      int g = (int)Green - pal->Green;
      int b = (int)Blue  - pal->Blue;

      int dist = (r * r) + (g * g) + (b * b);

      if( dist < mindist ){
        mindist = dist;
        mini = i;
      }

      pal ++;
    }

    return( mini );
}



