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

#ifndef  ___AGE_TYPE__H__
#define  ___AGE_TYPE__H__

#include <stdlib.h>


#define TRUE            1
#define FALSE           0

/* ‹¡¥¥ •A·¡Èá Ñw */
typedef unsigned char   BYTE;
typedef unsigned short  WORD;
typedef unsigned long   DWORD;
typedef unsigned int    UINT;
typedef char            CHAR;
typedef int             INT;
typedef long            LONG;
typedef unsigned long   ULONG;
typedef INT             BOOL;
typedef unsigned char   U8;
typedef signed char     S8;
typedef unsigned short  U16;
typedef signed short    S16;
typedef unsigned long   U32;
typedef signed long     S32;

/* œa·¡§aœáŸ¡ ‰·É· •A·¡Èá Ñw */
typedef CHAR*           STRING;
typedef U8              COLOR;
typedef U8              DACVALUE;
typedef INT             ERROR;

/* Handle type */
typedef INT             HANDLE;
typedef HANDLE          HOBJ;
typedef HANDLE          HOBJCLASS;
typedef HANDLE          HMSG;
typedef HANDLE          HTIMER;

/* Event Handler */
// typedef void (EVENTHANDLER)( OBJECT *ObjPtr, HMSG Message, LONG lParam );
typedef void (EVENTHANDLER)( HMSG Message, LONG lParam );


// Point Class

class  POINT {
  public:
    POINT( void ) { Set( 0, 0 ); }
    POINT( INT X, INT Y ) { Set( X, Y ); }
    ~POINT( void ) {}

  public:
    INT X, Y;

    BOOL operator == ( const POINT &Point )
    {
        return( (X == Point.X) && (Y == Point.Y) );
    }
    BOOL operator != ( const POINT &Point )
    {
        return( (X != Point.X) || (Y != Point.Y) );
    }

    inline void    Set( INT X, INT Y ) { this->X = X; this->Y = Y; }
    inline INT     GetX( void ) { return( X ); }
    inline INT     GetY( void ) { return( Y ); }
};


// Size Class

class  SIZE {
  public:
    SIZE( void ) { Set( 0, 0 ); }
    SIZE( INT Width, INT Height ) { Set( Width, Height ); }
    ~SIZE( void ) {}

  public:
    INT Width, Height;

    BOOL operator == ( const SIZE &Size )
    {
        return( (Width == Size.Width) && (Height == Size.Height) );
    }
    BOOL operator != ( const SIZE &Size )
    {
        return( (Width != Size.Width) || (Height != Size.Height) );
    }

    inline void    Set( INT Width, INT Height ) { this->Width = Width; this->Height = Height; }
    inline INT     GetWidth( void )  { return( Width ); }
    inline INT     GetHeight( void ) { return( Height ); }
};


// Fixed Point Function

typedef signed long     FIXED;

#define RADIX_SIZE      16

#define INTTOFIXED(a)   ((FIXED)((a) << RADIX_SIZE))
#define FIXEDTOINT(a)   ((FIXED)(a) >> RADIX_SIZE)
#define FLOATTOFIXED(a) ((FIXED)((float)(a) * ((1 << RADIX_SIZE) * 1.0)))
#define FIXEDTOFLOAT(a) ((FLOAT)(a) / ((1 << RADIX_SIZE) * 1.0)))

#pragma aux FixedMul =          \
    "mov ebx, edx"              \
    "imul ebx"                  \
    "shrd eax, edx, 16"         \
parm [eax] [edx]                \
modify [ebx]                    \
value [eax];
FIXED   FixedMul( FIXED a, FIXED b );

#pragma aux FixedDiv =          \
    "mov  ebx, edx"             \
    "cdq"                       \
    "shld edx, eax, 16"         \
    "shl  eax, 16"              \
    "idiv ebx"                  \
parm [eax] [edx]                \
modify [ebx]                    \
value [eax];
FIXED   FixedDiv( FIXED a, FIXED b );

#pragma aux FixedMulDiv =       \
    "imul edx"                  \
    "idiv ebx"                  \
parm [eax] [edx] [ebx]          \
value [eax];
FIXED   FixedMulDiv( FIXED a, FIXED b, FIXED c );


#endif


