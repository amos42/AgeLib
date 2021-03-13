/*#################################################################
-------------------------------------------------------------------

                                 AGE
                       (* =================== *)
                           Amos Game Engine

 Author         : Chu, Kyong-min( Amos )

 Date           : 1997/02/08
 C Compiler     : WATCOM 10.5
 Assembler      : WASM 10.5

-------------------------------------------------------------------
###################################################################*/

#include <string.h>
#include "age_obj.h"


#define MAX_MESSAGE     1024


MESSAGE     *MESSAGEMNG::MessageQue;
INT          MESSAGEMNG::Start;
INT          MESSAGEMNG::Length;


/*****************************
  메세지 리스트를 초기화한다.
******************************/
MESSAGEMNG :: MESSAGEMNG( void )
{
    MessageQue = new MESSAGE[ MAX_MESSAGE ];
    memset( MessageQue, 0, sizeof(MESSAGE) * MAX_MESSAGE );

    Start = Length = 0;
}


/*****************************
  메세지 리스트를 초기화한다.
******************************/
MESSAGEMNG :: ~MESSAGEMNG()
{
    delete MessageQue;
}


/*******************************
  메시지를 오브젝트에 전송한다.
********************************/
BOOL MESSAGEMNG :: SendMessage( OBJECT *ObjPtr, HMSG hMsg, LONG lParam )
{
    // 메시지 큐가 꽉 찼으면 종료
    if( Length > MAX_MESSAGE ) return( FALSE );
    // 메시지를 전달받을 오브젝트가 NULL이면 종료
    if( ObjPtr == NULL ) return( FALSE );

    // 큐의 push 포인터
    int i = Start + Length;
    // 만약 끝으로 벗어났으면 앞쪽으로 계속 (원형큐이기 때문)
    if( i >= MAX_MESSAGE ) i -= MAX_MESSAGE;

    // 메시지를 저장한다.
    MessageQue[ i ].ObjPtr   = ObjPtr;
    MessageQue[ i ].hMsg     = hMsg;
    MessageQue[ i ].lParam   = lParam;

    // 큐 버퍼 크기 증가
    Length ++;

    return( TRUE );
}


/**********************************
  메시지 큐에서 메시지를 꺼내온다.
***********************************/
MESSAGE *MESSAGEMNG :: PopMessage( void )
{
    // 메시지 큐가 비었으면 종료
    if( Length <= 0 ) return( NULL );

    // 큐의 pop 부분
    MESSAGE *msg = MessageQue + Start;
    // pop 부분 증가
    Start ++;
    // 만약 끝으로 벗어났으면 앞쪽으로 계속 (원형큐이기 때문)
    if( Start >= MAX_MESSAGE ) Start -= MAX_MESSAGE;

    // 큐 버퍼 크기 증가
    Length --;

    return( msg );
}


/*********************
  메세지를 처리한다.
**********************/
void MESSAGEMNG :: Process( void )
{
/*
    if( Length <= 0 ) return;

    MESSAGE *msg = MessageQue + Start;

    Start += Length;
    if( Start >= MAX_MESSAGE ) Start -= MAX_MESSAGE;

    int ml = Length;
    Length = 0;

    for( int i = 0; i < ml; i ++ ){
      msg->ObjPtr->ObjProc( msg->Message, msg->lParam );

      msg ++;
      if( msg > EndPtr ) msg -= MAX_MESSAGE;
    }
*/
}


