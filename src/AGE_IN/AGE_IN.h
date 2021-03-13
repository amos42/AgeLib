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

#ifndef  ___AGE_IN__H__
#define  ___AGE_IN__H__

#pragma library ("age_in.lib");

#include "age_type.h"


// Key low-level Function

class KEY {
  public:
    static BOOL    IsBuffer( void );
    static void    Clear( void );
    static void    Put( CHAR Key );
    static U16     Get( void );
    static U16     GetSync( void );
};


// Multi key Class

class  MULTIKEY {
  public:
    MULTIKEY( void );
    ~MULTIKEY();

  private:
    void (__interrupt __far *OldKeyVect)( void );
    static void __interrupt __far NewKeyVect( void );

  public:
    CHAR    Scan[128];
    CHAR    Last;
    INT     Press;

    void    Reset( void );
    void    Activate( void );
    void    Deactivate( void );
};

extern MULTIKEY _Key;


// Mouse low-level Function

class MOUSE {
  public:
    static BOOL    Reset( void );
    static void    SetHandler( void (__far *Handler)() );
    static void    GetState( INT *Button, INT *X, INT *Y );
    static void    GetButton( INT *Button );
    static void    GetPosition( INT *X, INT *Y );
    static void    SetPosition( INT X, INT Y );
    static void    SetPixelRatio( INT MickeyX, INT MickeyY );
    static void    SetSensitivity( INT SpeedX, INT SpeedY, INT DoubleClick );
    static void    SetWindow( INT StartX, INT StartY, INT EndX, INT EndY );
};


#endif


