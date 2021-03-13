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

#ifndef ___AGE_GRP__H__
#define ___AGE_GRP__H__

#pragma library ("age_grp.lib");

#include <stdlib.h>
#include "age_type.h"
#include "age_low.h"
#include "age_res.h"


// Graphics methods

class PIXEL : public POINT {
  public:
    PIXEL( void ) : POINT() { Color = 255; }
    PIXEL( INT X, INT Y, COLOR Color ) : POINT( X, Y ) { this->Color = Color; }
    ~PIXEL();

  public:
    COLOR   Color;

    void    Set( INT X, INT Y, COLOR Color )
    {
        POINT::Set( X, Y );
        this->Color = Color;
    }

    static COLOR   Get( INT X, INT Y );
    static void    Put( INT X, INT Y, COLOR Color );

    COLOR   Get( void );
    void    Put( void );
};


class DLINE : public RECT {
  public:
    DLINE( void ) : RECT() {};
    DLINE( INT StartX, INT StartY, INT EndX, INT EndY, COLOR Color ) :
     RECT( StartX, StartY, EndX, EndY ) { this->Color = Color; }
    ~DLINE();

  public:
    COLOR   Color;

    void    Set( INT StartX, INT StartY, INT EndX, INT EndY, COLOR Color )
    {
        RECT::Set( StartX, StartY, EndX, EndY );
        this->Color = Color;
    }

    static void    Draw( INT StartX, INT StartY, INT EndX, INT EndY, COLOR Color );
    static void    DrawHoriz( INT StartX, INT StartY, INT Length, COLOR Color );
    static void    DrawHoriz2( INT StartX, INT StartY, INT EndX, COLOR Color );
    static void    DrawVert( INT StartX, INT StartY, INT Length, COLOR Color );
    static void    DrawVert2( INT StartX, INT StartY, INT EndY, COLOR Color );
    static void    DrawCross( INT X, INT Y, INT Length, COLOR Color );
    static void    DrawHorizTrans( INT StartX, INT StartY, INT Length, COLOR *TransTable );
    static void    DrawVertTrans( INT StartX, INT StartY, INT Length, COLOR *TransTable );
    static void    DrawHorizXOR( INT StartX, INT StartY, INT Length );
    static void    DrawVertXOR( INT StartX, INT StartY, INT Length );

    void    Draw( void );
};


class DRECT : public RECT {
  public:
    DRECT( void ) : RECT() { Color = 255; }
    DRECT( INT StartX, INT StartY, INT EndX, INT EndY, COLOR Color ) :
     RECT( StartX, StartY, EndX, EndY ) { this->Color = Color; }
    ~DRECT() {}

  public:
    COLOR   Color;

    void    Set( INT StartX, INT StartY, INT Width, INT Height, COLOR Color )
    {
        RECT::Set( StartX, StartY, EndX, EndY );
        this->Color = Color;
    }

    static void    Draw( INT StartX, INT StartY, INT EndX, INT EndY, COLOR Color );
    static void    DrawFill( INT StartX, INT StartY, INT EndX, INT EndY, COLOR Color );
    static void    DrawTrans( INT StartX, INT StartY, INT EndX, INT EndY, COLOR *TransTable );
    static void    DrawXOR( INT StartX, INT StartY, INT EndX, INT EndY );

    void    Draw( void );
    void    DrawFill( void );
    void    DrawTrans( void );
    void    DrawXOR( void );
};

class DREGION : public REGION {
  public:
    DREGION( void ) : REGION() { Color = 255; }
    DREGION( INT StartX, INT StartY, INT Width, INT Height, COLOR Color ) :
     REGION( StartX, StartY, Width, Height ) { this->Color = Color; }
    ~DREGION() {}

  public:
    COLOR   Color;

    void    Set( INT StartX, INT StartY, INT Width, INT Height, COLOR Color )
    {
        REGION::Set( StartX, StartY, Width, Height );
        this->Color = Color;
    }

    static void    Draw( INT StartX, INT StartY, INT Width, INT Height, COLOR Color );
    static void    DrawFill( INT StartX, INT StartY, INT Width, INT Height, COLOR Color );
    static void    DrawTrans( INT StartX, INT StartY, INT Width, INT Height, COLOR *TransTable );
    static void    DrawXOR( INT StartX, INT StartY, INT Width, INT Height );

    void    Draw( void );
    void    DrawFill( void );
    void    DrawTrans( void );
    void    DrawXOR( void );
};

class DCIRCLE : public PIXEL {
  public:
    DCIRCLE( void ) : PIXEL() { Color = 255; }
    DCIRCLE( INT X, INT Y, INT Ratio, COLOR Color ) : PIXEL( X, Y, Color )
    {
        this->Ratio = Ratio;
    }
    ~DCIRCLE() {}

  public:
    INT     Ratio;

    void    Set( INT X, INT Y, INT Ratio, COLOR Color )
    {
        PIXEL::Set( X, Y, Color );
        this->Ratio = Ratio;
    }

    static void    Draw( INT X, INT Y, INT Ratio, COLOR Color );
    static void    DrawFill( INT X, INT Y, INT Ratio, COLOR Color );
    static void    DrawTrans( INT X, INT Y, INT Ratio, COLOR *TransTable );
    static void    DrawXOR( INT X, INT Y, INT Ratio );

    void    Draw( void );
    void    DrawFill( void );
    void    DrawTrans( void );
};

class DTRIANGLE {
  public:
    DTRIANGLE( void )
    {
        Set( 0, 0, 0, 0, 0, 0, 255 );
    }
    DTRIANGLE( INT X1, INT Y1, INT X2, INT Y2, INT X3, INT Y3, COLOR Color )
    {
        Set( X1, Y1, X2, Y2, X3, Y3, Color );
    }
    ~DTRIANGLE() {}

  public:
    INT     X1, Y1, X2, Y2, X3, Y3;
    COLOR   Color;

    void    Set( INT X1, INT Y1, INT X2, INT Y2, INT X3, INT Y3, COLOR Color )
    {
        this->X1 = X1; this->Y1 = Y1;
        this->X2 = X2; this->Y2 = Y2;
        this->X3 = X3; this->Y3 = Y3;
        this->Color = Color;
    }

    static void    Draw( INT X1, INT Y1, INT X2, INT Y2, INT X3, INT Y3, COLOR Color );
    static void    DrawFill( INT X1, INT Y1, INT X2, INT Y2, INT X3, INT Y3, COLOR Color );
    static void    DrawTrans( INT X1, INT Y1, INT X2, INT Y2, INT X3, INT Y3, COLOR *TransTable );

    void    Draw( void );
    void    DrawFill( void );
    void    DrawTrans( void );
};


// Palette Class

class PALETTE {
  public:
    PALETTE( void );
    PALETTE( DACVALUE Red, DACVALUE Green, DACVALUE Blue );
    ~PALETTE();

  public:
    DACVALUE  Red, Green, Blue;

    void    Set( DACVALUE Red, DACVALUE Green, DACVALUE Blue );

    static void    Get( COLOR Color, DACVALUE *Red, DACVALUE *Green, DACVALUE *Blue );
    static void    Put( COLOR Color, DACVALUE Red, DACVALUE Green, DACVALUE Blue );
    static void    Clear( DACVALUE Red, DACVALUE Greeen, DACVALUE Blue );

    void    Get( COLOR Color );
    void    Put( COLOR Color );
    void    Clear( void );
};


// Palette Map Class

class PALETTEMAP {
  public:
    PALETTEMAP( void );
    PALETTEMAP( STRING FileName ) { _Resource.Load( FileName, (CHAR **)&Palette ); }
    ~PALETTEMAP() { delete Palette; }

  public:
    PALETTE    *Palette;

    PALETTEMAP &operator = ( const PALETTEMAP &Palette );

    void    Set( PALETTE *Palette );
    BOOL    Load( STRING FileName );
    void    Write( STRING FileName );
    void    GrayPalette( void );
    void    GrayPalette( COLOR StartPal, COLOR EndPal );
    void    AnimatePalette( INT StartColor, INT EndColor );
    void    FadePalette( DACVALUE Red, DACVALUE Green, DACVALUE Blue, INT Step );
    void    FadePalette( DACVALUE Red, DACVALUE Green, DACVALUE Blue, INT Step, INT StartColor, INT EndColor );
    void    RealizePalette( void );

    COLOR   FindColor( DACVALUE Red, DACVALUE Green, DACVALUE Blue );
    COLOR   FindColor( DACVALUE Red, DACVALUE Green, DACVALUE Blue, COLOR StartColor, COLOR EndColor );
    COLOR   FindColor( PALETTE &Palette );
    COLOR   FindColor( PALETTE &Palette, COLOR StartColor, COLOR EndColor );
};


// Screen Class

class  SCREEN : public PALETTEMAP {
  public:
    SCREEN( void );
    SCREEN( COLOR *Video );
    SCREEN( STRING FileName );
    ~SCREEN();

  private:
    BOOL        IsVirtual;

  public:
    COLOR      *Video;

    SCREEN &operator = ( const SCREEN &Screen );
    SCREEN &operator << ( const SCREEN &Screen );
    SCREEN &operator >> ( SCREEN &Screen );

    void    Clear( COLOR Color );
    void    Reset( void );
    void    Copy( SCREEN &DesScreen, SCREEN &SrcScreen );
    BOOL    Load( STRING FileName );
    void    Write( STRING FileName );
    void    Save( SCREEN &Screen, INT StartX, INT StartY, INT EndX, INT EndY );
    void    Restore( SCREEN &Screen, INT StartX, INT StartY, INT EndX, INT EndY );
    void    Display( void );

    inline void    Activate( void ) { _Video = Video; }
    inline void    Save( SCREEN &Screen ) { Screen = *this; }
    inline void    Restore( SCREEN &Screen ) { *this = Screen; }

    void    ScrollUp( INT StartX, INT StartY, INT EndX, INT EndY, INT Distance );
    void    ScrollUp( INT Distance );
    void    ScrollDown( INT StartX, INT StartY, INT EndX, INT EndY, INT Distance );
    void    ScrollDown( INT Distance );
    void    ScrollLeft( INT StartX, INT StartY, INT EndX, INT EndY, INT Distance );
    void    ScrollLeft( INT Distance );
    void    ScrollRight( INT StartX, INT StartY, INT EndX, INT EndY, INT Distance );
    void    ScrollRight( INT Distance );
};

extern SCREEN    _Screen;


// Text Output Class

class  TEXT {
  public:
    TEXT( void );
    TEXT( STRING HanFileName, STRING EngFileName );
    ~TEXT();

  private:
    U16  *HanFont1, *HanFont2, *HanFont3;
    U8   *EngFont;
    BOOL  IsDefaultHan;
    BOOL  IsDefaultEng;

    U8*  GetHanImage( U16 c );
    void (*PutHanFont)( COLOR *di, U8 *si, COLOR Color );
    void (*PutEngFont)( COLOR *di, U8 *si, COLOR Color );

  public:
    enum {
        FS_NORMAL,
        FS_MULTI,
        FS_SHADOW
    };

    POINT   CP;
    COLOR   ForeColor, BackColor;

    void    MoveCP( INT X, INT Y );
    BOOL    LoadHanFont( STRING FileName );
    BOOL    LoadEngFont( STRING FileName );
    void    FreeHanFont( void );
    void    FreeEngFont( void );
    void    SetFontColor( COLOR Color );
    void    SetFontStyle( INT Style );

    virtual void    PutString( STRING StrData );
    virtual void    PutString( INT X, INT Y, STRING StrData );
    virtual INT     Printf( const char *format, ... );
};

extern TEXT  _Text;


// Image Class

class  IMAGE {
  public:
    IMAGE( void );
    IMAGE( INT Width, INT Height );
    IMAGE( INT Width, INT Height, COLOR *Bitmap );
    IMAGE( STRING FileName );
    ~IMAGE();

  public:
    INT    Width, Height;
    INT    LogX, LogY;
    COLOR *Bitmap;

    IMAGE &operator = ( const IMAGE &Image );

    void    Reset( void );
    BOOL    Load( STRING FileName );
    void    Write( STRING FileName );
    void    SetSize( INT Width, INT Height );
    void    SetBitmap( COLOR *Bitmap );
    void    SetLogPosition( INT LogX, INT LogY );

    BOOL    IsValidate( void );

    COLOR   GetPixel( INT X, INT Y );

    INT     FindTopBound( void );
    INT     FindBottomBound( void );
    INT     FindLeftBound( void );
    INT     FindRightBound( void );

    void    Compact( void );

    void    Get( INT X, INT Y );
    void    Put( INT X, INT Y );
    void    PutStretch( INT X, INT Y, INT tWidth, INT tHeight );
    void    PutScale( INT X, int Y, FIXED Scale );
    void    PutChar( INT X, INT Y );
    void    PutCharStretch( INT X, INT Y, INT tWidth, INT tHeight );
    void    PutCharScale( INT X, int Y, FIXED Scale );
    void    PutShadow( INT X, INT Y );
    void    PutShadowStretch( INT X, INT Y, INT tWidth, INT tHeight );
    void    PutShadowScale( INT X, int Y, FIXED Scale );
    void    PutShadowTrans( INT X, INT Y, COLOR *TransTable );
    void    PutShadowTransStretch( INT X, INT Y, INT tWidth, INT tHeight, COLOR *TransTable );
    void    PutShadowTransScale( INT X, INT Y, FIXED Scale, COLOR *TransTable );
    void    PutTrans( INT X, INT Y, COLOR *TransTable );
    void    PutTransStretch( INT X, INT Y, INT tWidth, INT tHeight, COLOR *TransTable );
    void    PutTransScale( INT X, int Y, FIXED Scale, COLOR *TransTable );

    void    DrawTextureRect( INT StartX, INT StartY, INT EndX, INT EndY );
};

#define NULL_IMAGE (*(IMAGE *)NULL)


// Sprite Class

class  SPRITE {
  public:
    SPRITE( void );
    SPRITE( STRING FileName );
    ~SPRITE();

  public:
    INT     Count;
    IMAGE  *Image;

    void    Reset( void );
    BOOL    Load( STRING FileName );
    void    Write( STRING FileName );
    void    AddImage( IMAGE &Image );
    void    InsertImage( INT Index, IMAGE &Image );
    void    DeleteImage( INT Index );
    BOOL    SetImage( INT Index, IMAGE &Image );

    IMAGE  *GetImagePtr( INT Index );

    BOOL    IsValidate( INT Index );

    void    Put( INT X, INT Y, INT Index );
    void    PutStretch( INT X, INT Y, INT tWidth, INT tHeight, INT Index );
    void    PutScale( INT X, INT Y, FIXED Scale, INT Index );
    void    PutChar( INT X, INT Y, INT Index );
    void    PutCharStretch( INT X, INT Y, INT tWidth, INT tHeight, INT Index );
    void    PutCharScale( INT X, int Y, FIXED Scale, INT Index );
    void    PutShadow( INT X, INT Y, INT Index );
    void    PutShadowStretch( INT X, INT Y, INT tWidth, INT tHeight, INT Index );
    void    PutShadowScale( INT X, INT Y, FIXED Scale, INT Index );
    void    PutShadowTrans( INT X, INT Y, INT Index );
    void    PutShadowTransStretch( INT X, INT Y, INT tWidht, INT tHeight, INT Index );
    void    PutShadowTransScale( INT X, INT Y, FIXED Scale, INT Index );
    void    PutTrans( INT X, INT Y, INT Index );
    void    PutTransStretch( INT X, INT Y, INT tWidth, INT tHeight, INT Index );
    void    PutTransScale( INT X, INT Y, FIXED Scale, INT Index );
};


// Tile & Map

class TILE {
  public:
    TILE( void );
    TILE( STRING FileName );
    ~TILE();

  public:
    INT     Count;
    INT     Width, Height;
    CHAR   *Bitmap;

    BOOL    Load( STRING FileName );
    void    Clear( void );

    void    Put( INT X, INT Y, INT Index );
};


class MAP {
  public:
    MAP( void );
    MAP( STRING FileName );
    ~MAP();

  public:
    POINT   ViewPos;
    SIZE    ViewSize;
    POINT   MapPos;
    SIZE    MapSize;
    SIZE    TileCount;
    S16    *Map;
    TILE   *Tile;

    BOOL    Load( STRING FileName );
    void    Clear( void );

    void    SetTile( TILE *Tile );
    void    SetViewSize( INT Width, INT Height );
    void    SetViewPos( INT X, INT Y );
    void    SetMapPos( INT X, INT Y );

    void    Put( void );
};


#endif


