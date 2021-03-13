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

#include <malloc.h>
#include <string.h>
#include <age.h>


#define BITS_PER_PIXEL  8
#define CLEAR_CODE      (1 << BITS_PER_PIXEL)
#define EOF_CODE        (CLEAR_CODE + 1)


static char *OutBuff;
static short Suffix[4097], Prefix[4097], Next[4097];
static short CodeSize, MaxCode, FreeCode;
static ULONG BytePos, BitPos;


static void OutCode( int code )
{
    *(long *)(OutBuff + BytePos) += ((long)code << BitPos);

    BitPos  += CodeSize;
    BytePos += BitPos >> 3;    /* BytePos += BitPos / 8 */
    BitPos  &= 0x07;           /* BitPos  %= 8;         */
}


static void Initialize( void )
{
    int i;

    FreeCode = CLEAR_CODE + 2;
    MaxCode  = CLEAR_CODE * 2;

    for( i = 0; i < 4097; i ++ )
      Prefix[i] = Suffix[i] = Next[i] = -1;

    OutCode( CLEAR_CODE );

    CodeSize = BITS_PER_PIXEL + 1;
}


static void Append( int pre, int suf )
{
    int i;

    if( Suffix[ suf ] == -1 )
      Suffix[ suf ] = FreeCode;
    else{
      suf = Suffix[ suf ];
      while( (i = Next[ suf ]) != -1 ) suf = i;
      Next[ suf ] = FreeCode;
    }

    Prefix[ FreeCode ] = pre;
}


/*********************
  이미지를 압축한다.
**********************/
ULONG Encode( CHAR **DesData, CHAR *SrcData, ULONG DataSize )
{
    short i, j;
    CHAR *DataEndPtr;
    WORD CurCode = 0;


    OutBuff = (char *)malloc( DataSize + 10 );
    memset( OutBuff, 0, DataSize );

    DataEndPtr = SrcData + DataSize - 1;

    BitPos = 0;
    BytePos = 0;

    CodeSize = BITS_PER_PIXEL + 1;
    Initialize();

    i = (short)*(BYTE *)SrcData++;

    while( SrcData <= DataEndPtr ){
      j = i;

      if( Prefix[i] == -1 ){
         Prefix[i] = CurCode = i;
         i = (short)*(BYTE *)SrcData++;
      } else {
        while( j != -1 ){
          CurCode = j;
          j = Suffix[ CurCode ];
          i = (short)*(BYTE *)SrcData++;
          while( j != -1 && i != Prefix[j] ) j = Next[j];
          if( SrcData > DataEndPtr ) break;
        }
      }

      if( BytePos >= DataSize ){
        BytePos = 0;
        break;
      }

      OutCode( CurCode );

      if( SrcData <= DataEndPtr ){
        Append( i, CurCode );

        if( FreeCode++ >= MaxCode ){
          MaxCode <<= 1;
          if( CodeSize < 12 )
            CodeSize++;
          else
            Initialize();
        }
      } else {
        OutCode( i );
      }
    }

    if( BytePos > 0 ){
      OutCode( EOF_CODE );
      if( BitPos > 0 ) BytePos ++;
      if( BytePos < DataSize ){
        *DesData = (CHAR *)malloc( BytePos );
        memcpy( *DesData, OutBuff, BytePos );
      } else {
        BytePos = 0;
      }
    }

    free( OutBuff );

    return( BytePos );
}


