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

#ifndef ___AGE_OBJ__H__
#define ___AGE_OBJ__H__

#pragma library ("age_obj.lib");

#include <stdlib.h>
#include "age_type.h"
#include "age_low.h"
#include "age_res.h"
#include "age_grp.h"


// Regions Classe

class  REGIONS {
  public:
    REGIONS( void );
    REGIONS( INT Count );
    REGIONS( STRING FileName );
    ~REGIONS();

  public:
    INT      Count;
    REGION  *Regions;

    void     Reset( void );

    BOOL     Load( STRING FileName );

    void     SetCount( INT Count );
    INT      GetCount( void );

    void     AddRegion( REGION &Region );
    BOOL     SetRegion( INT Index, REGION &Region );
    BOOL     GetRegion( INT Index, REGION *Region );
    REGION  *GetRegion( INT Index );
};


// Character Model Class

class  CHRMODEL {
  public:
    CHRMODEL( void );
    CHRMODEL( STRING FileName );
    CHRMODEL( STRING SprFile, STRING RgnFile1, STRING RgnFile2 );
    CHRMODEL( SPRITE *Sprite, REGIONS *Regions1, REGIONS *Regions2 );
    ~CHRMODEL();
   
  private:
    static INT         CurClassID;

  public:
    INT         ClassID;
    INT         Count;

    SPRITE     *Sprite;
    REGIONS    *Regions1, *Regions2;

  public:
    void        Reset( void );

    BOOL        Load( STRING FileName );
    BOOL        Load( STRING SprFile, STRING RgnFile1, STRING RgnFile2 );
    void        Write( STRING FileName );

    void        SetSprite( SPRITE *Sprite );
    void        SetRegions1( REGIONS *Regions );
    void        SetRegions2( REGIONS *Regions );
};


// Object Message Constants

enum {
    OM_DUMMY,
    OM_CREATE,
    OM_PAINT,
    OM_KEYDOWN,
    OM_KEYPRESSED,
    OM_KEYUP,
    OM_TIMER,
    OM_DESTROY,
    OM_USER = 0x10000
};


// Message Class

class OBJECT;

struct MESSAGE {
    OBJECT     *ObjPtr;
    HMSG        hMsg;
    LONG        lParam;
};

class  MESSAGEMNG {
  public:
    MESSAGEMNG( void );
    virtual ~MESSAGEMNG();

  public:
    static MESSAGE    *MessageQue;
    static int         Start;
    static int         Length;

    static void        Reset( void );

    static BOOL        SendMessage( OBJECT *ObjPtr, HMSG hMsg, LONG lParam );
    static MESSAGE    *PopMessage( void );
    static void        Process( void );

    static inline INT         GetLength( void ) { return( Length ); }
};


// Object Class

#define MAX_OBJECT 1024

class  OBJECT : public MESSAGEMNG {
  public:
    OBJECT( void );
    virtual ~OBJECT();
   
  private:
    static OBJECT *ObjectList[ MAX_OBJECT ];
    static INT      CurObjectID;
    static INT      CurFindClassID;
    static INT      CurFindPos;

  public:
    INT        ClassID;
    INT        ObjectID;
    INT        DisplayLevel;

    static void        Reset( void );
    static void        Process( void );
    static void        DisplayAll( void );
    static void        DisplayFront( INT BaseLevel );
    static void        DisplayBack( INT BaseLevel );

    static BOOL        SendMessage( OBJECT *ObjPtr, HMSG hMsg, LONG lParam );
    static void        SendMessage( INT ClassID, HMSG hMsg, LONG lParam );

    static OBJECT     *FindFirst( INT ClassID );
    static OBJECT     *FindNext( void );

    void        SetDisplayLevel( INT DisplayLevel );

  public:
    virtual INT      ObjProc( HMSG hMsg, LONG lParam );
};


// Character Class

class  CHARACTER : public OBJECT {
  public:
    CHARACTER( CHRMODEL &ChrModel );
    CHARACTER( INT X, INT Y, CHRMODEL &ChrModel );
    ~CHARACTER();

  private:
    CHRMODEL   *ChrModel;

  public:
    INT         X, Y;
    INT         Index;
    BOOL        Visible;
    INT         State;

    void        Reset( void );

    void        Move( INT X, INT Y );
    void        MoveTo( INT X, INT Y );

    IMAGE      *GetImagePtr( void );
    REGION      GetImageRegion( void );

    REGION     *GetCrashRegion( INT Index2 );
    REGION     *GetAttackRegion( INT Index2 );

    BOOL        IncIndex( INT Step );
    BOOL        DecIndex( INT Step );
    void        RotIndex( INT Start, INT End );

    virtual void        Put( void );
    virtual INT         ObjProc( HMSG hMsg, LONG lParam );
};


#endif

