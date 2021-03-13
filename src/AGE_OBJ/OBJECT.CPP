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

#include <stdio.h>
#include <string.h>
#include "age_obj.h"


// 오브젝트 리스트
INT OBJECT::CurObjectID = 0;
OBJECT *OBJECT::ObjectList[ MAX_OBJECT ] = { NULL, };

INT OBJECT::CurFindClassID = 0;
INT OBJECT::CurFindPos = 0;


/**********************
  OBJECT의 생성자
***********************/
OBJECT :: OBJECT( void ) : MESSAGEMNG()
{
    for( int i = 0; i < MAX_OBJECT; i ++ ){
      if( ObjectList[i] == NULL ){
        ObjectID = i;
        ObjectList[i] = this;
        break;
      }
    }

    ClassID = 0;
    ObjectID = CurObjectID ++;

    DisplayLevel = 0;
}


/**********************
  OBJECT의 소멸자
***********************/
OBJECT :: ~OBJECT()
{
    ObjectList[ ObjectID ] = NULL;
}


/***************************
  OBJECT를 리셋한다.
****************************/
void OBJECT :: Reset( void )
{
    for( int i = 0; i < MAX_OBJECT; i ++ )
      if( ObjectList[i] != NULL ) delete ObjectList[i];
}


/*******************************
  메세지를 오브젝트에 전송한다.
********************************/
BOOL OBJECT :: SendMessage( OBJECT *ObjPtr, HMSG hMsg, LONG lParam )
{
    switch( hMsg ){
      case OM_DUMMY   : ObjPtr->ObjProc( OM_DUMMY, lParam );
                        break;
      case OM_CREATE  : ObjPtr->ObjProc( OM_CREATE, (LONG)NULL );
                        break;
      case OM_TIMER   : ObjPtr->ObjProc( OM_TIMER, (LONG)NULL );
                        break;
      case OM_PAINT   : ObjPtr->ObjProc( OM_PAINT, (LONG)NULL );
                        break;
      case OM_DESTROY : ObjPtr->ObjProc( OM_DESTROY, lParam );
                        delete ObjPtr;
                        break;
      default         : return( MESSAGEMNG::SendMessage( ObjPtr, hMsg, lParam ) );
    }

    return( TRUE );
}


/***************************************************
  특정 클래스의 오브젝트 전체에게 메시지를 보내다.
****************************************************/
OBJECT *OBJECT :: FindFirst( INT ClassID )
{
    CurFindClassID = ClassID;
    CurFindPos = 0;

    OBJECT **obj = ObjectList;

    while( CurFindPos++ < MAX_OBJECT ){
      if( *obj && (*obj)->ClassID == ClassID )
        return( *obj );

      obj ++;
    }

    return( NULL );
}


/***************************************************
  특정 클래스의 오브젝트 전체에게 메시지를 보내다.
****************************************************/
OBJECT *OBJECT :: FindNext( void )
{
    if( CurFindPos >= MAX_OBJECT ) return( NULL );

    int ClassID = CurFindClassID;

    OBJECT **obj = &ObjectList[ CurFindPos ];

    while( CurFindPos++ < MAX_OBJECT ){
      if( *obj && (*obj)->ClassID == ClassID )
        return( *obj );

      obj ++;
    }

    return( NULL );
}


/***************************************************
  특정 클래스의 오브젝트 전체에게 메시지를 보내다.
****************************************************/
void OBJECT :: SendMessage( INT ClassID, HMSG hMsg, LONG lParam )
{
    OBJECT **obj = ObjectList;

    for( int i = 0; i < MAX_OBJECT; i ++ ){
      if( *obj && (*obj)->ClassID == ClassID )
        SendMessage( *obj, hMsg, lParam );

      obj ++;
    }
}


/***************************
  OBJECT를 처리한다.
****************************/
void OBJECT :: Process( void )
{
    OBJECT **obj = ObjectList;

    for( int i = 0; i < MAX_OBJECT; i ++ ){
      if( *obj != NULL )
        SendMessage( *obj, OM_TIMER, 0 );

      obj ++;
    }

    int ml = MESSAGEMNG::GetLength();
    if( ml <= 0 ) return;

    for( i = 0; i < ml; i ++ ){
      MESSAGE *msg = MESSAGEMNG::PopMessage();
      msg->ObjPtr->ObjProc( msg->hMsg, msg->lParam );
    }
}


/***************************
  OBJECT의 이벤트 핸들러
****************************/
INT OBJECT :: ObjProc( HMSG hMsg, LONG lParam )
{
    return( 0 );
}


/*****************************
  오브젝트 표시 레벨을 결정
******************************/
void OBJECT :: SetDisplayLevel( INT DisplayLevel )
{
    this->DisplayLevel = DisplayLevel;
}


//===============


struct DISPLAYOBJ {
    OBJECT     *ObjPtr;
    INT         DisplayLevel;
};
static DISPLAYOBJ DisplayObjectList[ MAX_OBJECT ] = { NULL, };
static DisplayCount = 0;


/*****************************
  오브젝트를 찍고
  OM_PAINT 메시지를 전송한다.
******************************/
static int CmpObjOrder( const void *disp1, const void *disp2 )
{
    return( ((DISPLAYOBJ *)disp1)->DisplayLevel
          - ((DISPLAYOBJ *)disp2)->DisplayLevel );
}
static void DisplayObjects( void )
{
    DISPLAYOBJ *disp = DisplayObjectList;
    int count = DisplayCount;

    qsort( (void *)disp, count, sizeof(DISPLAYOBJ), CmpObjOrder );

    for( int i = 0; i < count; i ++ ){
      OBJECT::SendMessage( disp->ObjPtr, OM_PAINT, i );
      disp ++;
    }
}


/*****************************
  모든 오브젝트를 찍는다.
******************************/
void OBJECT :: DisplayAll( void )
{
    OBJECT **obj = ObjectList;
    DISPLAYOBJ *disp = DisplayObjectList;

    int count = 0;

    for( int i = 0; i < MAX_OBJECT; i ++ ){
      if( *obj ){
        disp->ObjPtr       = *obj;
        disp->DisplayLevel = (*obj)->DisplayLevel;

        disp ++;
        count ++;
      }
      obj ++;
    }

    DisplayCount = count;
    DisplayObjects();
}


/********************************
  표시레벨이 0보다 크거나 같은
  오브젝트만을 골라 찍는다.
*********************************/
void OBJECT :: DisplayFront( INT BaseLevel )
{
    OBJECT **obj = ObjectList;
    DISPLAYOBJ *disp = DisplayObjectList;

    int count = 0;

    for( int i = 0; i < MAX_OBJECT; i ++ ){
      if( *obj && (*obj)->DisplayLevel >= BaseLevel ){
        disp->ObjPtr       = *obj;
        disp->DisplayLevel = (*obj)->DisplayLevel;

        disp ++;
        count ++;
      }
      obj ++;
    }

    DisplayCount = count;
    DisplayObjects();
}


/********************************
  표시레벨이 0보다 작은
  오브젝트만을 골라 찍는다.
*********************************/
void OBJECT :: DisplayBack( INT BaseLevel )
{
    OBJECT **obj = ObjectList;
    DISPLAYOBJ *disp = DisplayObjectList;

    int count = 0;

    for( int i = 0; i < MAX_OBJECT; i ++ ){
      if( *obj && (*obj)->DisplayLevel < BaseLevel ){
        disp->ObjPtr       = *obj;
        disp->DisplayLevel = (*obj)->DisplayLevel;

        disp ++;
        count ++;
      }
      obj ++;
    }

    DisplayCount = count;
    DisplayObjects();
}


