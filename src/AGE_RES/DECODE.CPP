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
#include "age_res.h"


#define BITS_PER_COLOR  8
#define CLEAR_CODE      (1 << BITS_PER_COLOR)
#define EOF_CODE        (CLEAR_CODE + 1)
#define BIT_MASK        (CLEAR_CODE - 1)


static char *InBuff;

static short Suffix[4096], Prefix[4096], OutCode[2048];
static int CodeSize, ReadMask;
static int BitPos;


static int ReadCode(void)
{
    int i;
    long RawCode;

    RawCode = *(long *)InBuff;

    i = (RawCode >> BitPos) & ReadMask;

    BitPos += CodeSize;
    InBuff += BitPos >> 3;    /* InBuff += BitPos / 8 */
    BitPos &= 0x07;           /* BitPos %= 8;         */

    return( i );
}



/***********************
  압축된 이미지를 푼다.
************************/
void Decode( CHAR **DesData, CHAR *SrcData, ULONG DataSize )
{
    int i, OutCount;
    int Code, InCode, CurCode, OldCode, FinChar;
    int MaxCode, FirstFree, FreeCode;
    BYTE *DataPtr, *DataEndPtr;


    if( DataSize == 0 ) return;

    InBuff = SrcData;
    DataPtr = (BYTE *)malloc( DataSize );
    memset( DataPtr, 0, DataSize );
    *DesData = (CHAR *)DataPtr;

    DataEndPtr = DataPtr + DataSize - 1;


    /* Initialize */
    OldCode   = FinChar = 0;
    FirstFree = FreeCode  = CLEAR_CODE + 2;
    MaxCode   = CLEAR_CODE * 2;
    ReadMask  = MaxCode - 1;
    OutCount  = 0;

    CodeSize  = BITS_PER_COLOR + 1;


    BitPos = 0;
    Code = ReadCode();

    while( DataPtr <= DataEndPtr && Code != EOF_CODE ){
      if( Code == CLEAR_CODE ){
         CodeSize = BITS_PER_COLOR + 1;
         MaxCode = (1 << CodeSize);
         ReadMask = MaxCode - 1;
         FreeCode = FirstFree;
         OldCode = ReadCode();
         FinChar = OldCode & BIT_MASK;
         *DataPtr++ = (BYTE)FinChar;
      } else {
         CurCode = InCode = Code;
         if( CurCode >= FreeCode ){
           CurCode = OldCode;
           OutCode[ OutCount++ ] = (short)FinChar;
         }

         while( CurCode > BIT_MASK ){
           if( OutCount > 2047 ) return;
           OutCode[ OutCount++ ] = Suffix[ CurCode ];
           CurCode = Prefix[ CurCode ];
         }
         FinChar = CurCode & BIT_MASK;
         OutCode[OutCount++] = (short)FinChar;

         for( i = OutCount-1; i >= 0; i-- ){
           *DataPtr++ = (BYTE)OutCode[i];
           if( DataPtr > DataEndPtr ) break;
         }

         OutCount = 0;

         Prefix[ FreeCode ] = (short)OldCode;
         Suffix[ FreeCode ] = (short)FinChar;
         OldCode = InCode;

         FreeCode ++;
         if( FreeCode >= MaxCode ){
           if( CodeSize < 12 ){
              CodeSize++;
              MaxCode *= 2;
              ReadMask = MaxCode - 1;
           }
         }
      }

      Code = ReadCode();
    }
}


