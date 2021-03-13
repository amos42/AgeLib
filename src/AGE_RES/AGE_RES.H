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

#ifndef  __AGE_RES__H__
#define  __AGE_RES__H__

#pragma library ("age_res.lib");

#include <stdlib.h>
#include "age_type.h"


/* Compress Function */

ULONG   Encode( CHAR **DesData, CHAR *SrcData, ULONG DataSize );
void    Decode( CHAR **DesData, CHAR *SrcData, ULONG DataSize );


class  RESOURCE {
  public:
    RESOURCE( void );
    RESOURCE( STRING FileName );
    ~RESOURCE();

  private:
    struct FILE_HEADER {
        LONG    Index;              // Resource Index
        CHAR    FileName[8+1+3];    // 화일 명
        LONG    Offset;             // 헤더를 제외한 옵셋
        LONG    IsCompress;         // 압축 여부
        LONG    FileSize;           // 화일 사이즈
        LONG    FileOrgSize;        // 압축하기 전의 사이즈
    };

  public:
    FILE_HEADER  *Header;
    INT  FileCount;
    char FileName[128];

    BOOL    Set( STRING FileName );
    ULONG   Load( STRING FileName, CHAR **DesPtr );
    ULONG   Load( INT Index, CHAR **DesPtr );

    BOOL    IsExist( STRING FileName );

    static void    Free( CHAR *ResPtr );
};

extern    RESOURCE _Resource;


#endif


