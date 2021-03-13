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

#ifndef ___AGE_LOW__H__
#define ___AGE_LOW__H__

#pragma library ("age_low.lib");

#include <stdlib.h>
#include "age_type.h"


#define VMEM_ADDR       0xA0000

#define VMEM_WIDTH      320
#define VMEM_HEIGHT     200
#define SCREEN_WIDTH    320
#define SCREEN_HEIGHT   200

#define VMEM_SIZE       ( VMEM_WIDTH * VMEM_HEIGHT )

// Calculate Screen Address Macro

#define CALC_OFFS( x, y ) ((x) + ((y) << 8) + ((y) << 6))
#define CALC_ADDR( x, y ) (_Video + CALC_OFFS((x), (y)))


// AGE Initialize

class AGE {
  public:
    static void Init( void );
    static void Close( void );
};


// Rectangle Class

class  RECT {
  public:
    RECT( void )
    {
        Set( 0, 0, 0, 0 );
    }
    RECT( INT StartX, INT StartY, INT EndX, INT EndY )
    {
        Set( StartX, StartY, EndX, EndY );
    }
    ~RECT() {}

  public:
    INT StartX, StartY;
    INT EndX,   EndY;

    inline void    Set( INT StartX, INT StartY, INT EndX, INT EndY )
    {
        this->StartX = StartX;
        this->StartY = StartY;
        this->EndX   = EndX;
        this->EndY   = EndY;
    }

    void    Normal( void );
    BOOL    IsInnerPoint( INT X, INT Y );
    BOOL    IsInnerPoint( POINT &Point );
    BOOL    IsIntersect( RECT &Rect );
    void    Intersect( RECT *DesRect, RECT &Rect );
};


// Region Class

class  REGION {
  public:
    REGION( void )
    {
        Set( 0, 0, 0, 0 );
    }
    REGION( INT StartX, INT StartY, INT Width, INT Height )
    {
        Set( StartX, StartY, Width, Height );
    }
    ~REGION() {}

  public:
    INT StartX, StartY;
    INT Width, Height;

    inline void    Set( INT StartX, INT StartY, INT Width, INT Height )
    {
        this->StartX = StartX;
        this->StartY = StartY;
        this->Width  = Width;
        this->Height = Height;
    }

    BOOL    IsInnerPoint( INT X, INT Y );
    BOOL    IsInnerPoint( POINT &Point );
    BOOL    IsIntersect( REGION &Reg );
    void    Intersect( REGION *DesReg, REGION &Reg );
};


// Common Function

void    DummyFunction( void );
INT     Sqrt( INT N );

// Fixed Sqrt

#define FIXEDSQRT(a)    ((FIXED)(Sqrt(a) << (RADIX_SIZE/2)))


// Common Data

extern    INT     _State;
extern    COLOR  *_Video;
extern    COLOR   _TransColor;
extern    COLOR   _ShadowColor;
extern    RECT    _Clip;


// CRT Control Class

class CRTC {
  public:
    static void    SetGraphicMode( void );
    static void    SetTextMode( void );
    static void    WaitVert( void );
};


// Trans table class

class TRANSTABLE {
  public:
    TRANSTABLE( INT TableSize );
    ~TRANSTABLE();

  public:
    INT     Size;
    COLOR  *Table;

    void    Set( COLOR *TransTable );
    COLOR  *Get( void );
};

extern TRANSTABLE  _ShadeTransTable,
                   _ImageTransTable;


// Multi Timer

#define TIMER_RATE  1000

#define MTIMER_COUNT 4

class MULTITIMER {
  public:
    MULTITIMER( void );
    MULTITIMER( INT Period, void (*Handler)(void) );
    ~MULTITIMER();

  public:
    static LONG     OrgTick;

    static void InitTimer( void );
    static void CloseTimer( void );

  private:
    INT     TimerID;

  public:
    INT     Period;
    INT     Tick;
    INT     Counter;
    void    (*Handler)(void);

    void    Reset( void );
    void    SetHandler( void (*Handler)(void) );
    void    SetPeriod( INT Period );
    BOOL    Enable( void );
    BOOL    Disable( void );
};


// Frame Skipping

#define FPS 60

class FRAMESKIP : public MULTITIMER {
  public:
    FRAMESKIP( void );
    ~FRAMESKIP();

  private:
    void  (*DelayHandler)(void);

  public:
    void    SetDelayHandler( void (*DelayHandler)(void) );
    void    ResetDelayHandler( void );

    void    Enable( void );
    void    Disable( void );
    void    Reset( void );

    BOOL    IsDisplayTime( void );
    void    DoEvents( void );
};

extern FRAMESKIP _FS;


// Triangle Function

#define DEG_RATIO   10
#define MAX_ANGLE   (360*DEG_RATIO)

#define SIN(x) SinTable[x]
#define COS(x) CosTable[x]
#define TAN(x) TanTable[x]

extern FIXED CosTable[ MAX_ANGLE ];
extern FIXED SinTable[ MAX_ANGLE ];
extern FIXED TanTable[ MAX_ANGLE ];


#endif

