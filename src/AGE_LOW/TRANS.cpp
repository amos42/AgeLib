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

#include <stdlib.h>
#include <memory.h>
#include "age_low.h"


TRANSTABLE _ShadeTransTable( 256 ),
           _ImageTransTable( 256 * 256 );


/*************************
  반투명 테이블의 생성자
**************************/
TRANSTABLE :: TRANSTABLE( INT TableSize )
{
    Size  = TableSize;

    Table = new COLOR[ TableSize ];
}


/*************************
  반투명 테이블의 소멸자
**************************/
TRANSTABLE :: ~TRANSTABLE()
{
    delete Table;
}


/****************************
  반투명 테이블을 세트한다.
*****************************/
void TRANSTABLE :: Set( COLOR *TransTable )
{
    memcpy( Table, TransTable, Size );
}


/****************************
  반투명 테이블을 얻는다.
*****************************/
COLOR * TRANSTABLE :: Get( void )
{
    return( Table );
}


