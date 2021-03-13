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

#include <stdio.h>
#include <string.h>
#include "age_grp.h"


struct MAP_HEADER {
    CHAR    Header[20];
    LONG    Ver;
    LONG    Width, Height;
};


/***************
  MAP의 생성자
****************/
MAP :: MAP( void )
{
    Map = NULL;
    Tile = NULL;

    Clear();
}


/***************
  MAP의 생성자
****************/
MAP :: MAP( STRING FileName )
{
    Map = NULL;
    Tile = NULL;

    Load( FileName );
}


/***************
  MAP의 소멸자
****************/
MAP :: ~MAP()
{
    Clear();
}


/***************
  MAP을 지운다.
****************/
void MAP :: Clear( void )
{
    SetViewPos( 0, 0 );
    SetViewSize( 0, 0 );
    SetMapPos( 0, 0 );

    MapSize.Set( 0, 0 );
    TileCount.Set( 0, 0 );

    if( Map ) delete Map;
    Map = NULL;
}


/**************************************
  리소스로부터 스프라이트를 로드한다.
***************************************/
BOOL MAP :: Load( STRING FileName )
{
    Clear();

    char *res;
    if( !_Resource.Load( FileName, &res ) ) return( FALSE );
    char *temp = res;

    MAP_HEADER *mh = (MAP_HEADER *)res;
    res += sizeof(MAP_HEADER);
    if( strcmp( mh->Header, "Amos Map File;" ) ) return( 2 );

    TileCount.Width  = mh->Width;
    TileCount.Height = mh->Height;

    int ms = TileCount.Width * TileCount.Height * sizeof(S16);

    Map = new S16[ ms ];
    memcpy( Map, res, ms );

    free( temp );

    if( Tile ){
      MapSize.Width  = TileCount.Width  * Tile->Width;
      MapSize.Height = TileCount.Height * Tile->Height;
    }

    return( TRUE );
}


/*******************
  타일을 지정한다.
********************/
void MAP :: SetTile( TILE *Tile )
{
    this->Tile = Tile;

    if( Tile ){
      MapSize.Width  = TileCount.Width  * Tile->Width;
      MapSize.Height = TileCount.Height * Tile->Height;
    } else {
      MapSize.Width  = 0;
      MapSize.Height = 0;
    }
}


/********************************
  실제 보이는 크기를 지정한다.
*********************************/
void MAP :: SetViewSize( INT Width, INT Height )
{
    ViewSize.Set( Width, Height );
}


/***********************************
  화면에 표시되는 위치를 지정한다.
************************************/
void MAP :: SetViewPos( INT X, INT Y )
{
    ViewPos.Set( X, Y );
}


/***********************************
  보이게 되는 맵의 위치를 지정한다.
************************************/
void MAP :: SetMapPos( INT X, INT Y )
{
    MapPos.Set( X, Y );
}


/***************
  맵을 찍는다.
****************/
void MAP :: Put( void )
{
    if( !Tile ) return;

    int tw = Tile->Width;
    int th = Tile->Height;
    int vw = ViewSize.Width;
    int vh = ViewSize.Height;

    int mx = MapPos.X / tw;
    int my = MapPos.Y / th;
    int dx = MapPos.X % tw;
    int dy = MapPos.Y % th;

    int X = ViewPos.X - dx;
    int Y = ViewPos.Y - dy;
    vw += dx;
    vh += dy;

    int WCount = vw / tw;
    if( vw % tw > 0 ) WCount ++;

    int HCount = vh / th;
    if( vh % th > 0 ) HCount ++;

    S16 *si = &Map[ mx + my * TileCount.Width ];

    INT ttx = X;
    int skip = TileCount.Width - WCount;

    for( int i = 0; i < HCount; i ++ ){
      for( int j = 0; j < WCount; j ++ ){
        Tile->Put( X, Y, *si++ );
        X += tw;
      }

      X = ttx;
      Y += th;
      si += skip;
    }
}



