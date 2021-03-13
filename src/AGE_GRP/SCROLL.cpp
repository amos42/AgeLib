/*#################################################################
-------------------------------------------------------------------

                             AGE (Ver 1.0)
                       (* =================== *)
                           Amos Game Engine

 Author         : Chu, Kyong-min( Amos )

 Date           : 1998/02/27
 C Compiler     : WATCOM 11.0
 Assembler      : WASM 11.0

-------------------------------------------------------------------
###################################################################*/

#include <string.h>
#include "age_grp.h"


/********************************
  화면을 윗쪽으로 스크롤 시킨다.
*********************************/
void SCREEN :: ScrollUp( INT StartX, INT StartY, INT EndX, INT EndY, INT Distance )
{
    if( StartX > EndX ){
      int t = StartX; StartX = EndX; EndX = t;
    }
    if( StartY > EndY ){
      int t = StartY; StartY = EndY; EndY = t;
    }

    if( (StartX > _Clip.EndX) || (EndX < _Clip.StartX) ||
        (StartY > _Clip.EndY) || (EndY < _Clip.StartY) )
      return;

    if( StartX < _Clip.StartX ) StartX = _Clip.StartX;
    if( EndX   > _Clip.EndX   ) EndX   = _Clip.EndX;
    if( StartY < _Clip.StartY ) StartY = _Clip.StartY;
    if( EndY   > _Clip.EndY   ) EndY   = _Clip.EndY;

    int width  = EndX - StartX + 1;
    int height = EndY - StartY + 1 - Distance;

    COLOR *DesPtr = Video + CALC_OFFS( StartX, StartY );
    COLOR *SrcPtr = DesPtr + Distance * VMEM_WIDTH;

#if 0
    for( int i = 0; i < height; i ++ ){
      memcpy( DesPtr, SrcPtr, width );

      SrcPtr += VMEM_WIDTH;
      DesPtr += VMEM_WIDTH;
    }
#endif

#if 0
    extern void _ScrollUp( COLOR *des, COLOR *src, int width, int height );
    #pragma aux _ScrollUp =     \
        "mov ebx, 320"          \
        "sub ebx, eax"          \
        "cld"                   \
      "@@loop:"                 \
        "mov ecx, eax"          \
        "shr ecx, 1"            \
        "jnc @@no1"             \
        "movsb"                 \
      "@@no1:"                  \
        "shr ecx, 1"            \
        "jnc @@no2"             \
        "movsw"                 \
      "@@no2:"                  \
        "jcxz @@no3"            \
        "rep movsd"             \
      "@@no3:"                  \
        "add esi, ebx"          \
        "add edi, ebx"          \
        "dec edx"               \
        "jnz @@loop"            \
    parm [edi] [esi] [eax] [edx]\
    modify [ebx ecx];

    _ScrollUp( DesPtr, SrcPtr, width, height );
#endif

    __asm {
        mov edi, [DesPtr]
        mov esi, [SrcPtr]
        mov eax, [width]
        mov edx, [height]
        mov ebx, 320
        sub ebx, eax
        cld
      @@loop:
        mov ecx, eax
        shr ecx, 1
        jnc @@no1
        movsb
      @@no1:
        shr ecx, 1
        jnc @@no2
        movsw
      @@no2:
        jcxz @@no3
        rep movsd
      @@no3:
        add esi, ebx
        add edi, ebx
        dec edx
        jnz @@loop
    };

}


/**********************************
  전화면을 윗쪽으로 스크롤 시킨다.
***********************************/
void SCREEN :: ScrollUp( INT Distance )
{
#if 0
    int next = Distance * VMEM_WIDTH;

    memcpy( Video, Video + next, VMEM_WIDTH * SCREEN_HEIGHT - next );
#endif

#if 0
    extern void _ScrollUpFull( COLOR *video, int Distance );
    #pragma aux _ScrollUpFull =     \
        "mov ecx, 320"          \
        "mul ecx"               \
        "mov edi, esi"          \
        "add esi, eax"          \
        "mov ecx, 64000"        \
        "sub ecx, eax"          \
        "shr ecx, 2"            \
        "cld"                   \
        "rep movsd"             \
    parm [esi] [eax]            \
    modify [edi ecx];

    _ScrollUpFull( Video, Distance );
#endif

    COLOR *v = Video;
    __asm {
        mov esi, [v]
        mov eax, [Distance]
        mov ecx, 320
        mul ecx
        mov edi, esi
        add esi, eax
        mov ecx, 64000
        sub ecx, eax
        shr ecx, 2
        cld
        rep movsd
    };
}


/**********************************
  화면을 아랫쪽으로 스크롤 시킨다.
***********************************/
void SCREEN :: ScrollDown( INT StartX, INT StartY, INT EndX, INT EndY, INT Distance )
{
    if( StartX > EndX ){
      int t = StartX; StartX = EndX; EndX = t;
    }
    if( StartY > EndY ){
      int t = StartY; StartY = EndY; EndY = t;
    }

    if( (StartX > _Clip.EndX) || (EndX < _Clip.StartX) ||
        (StartY > _Clip.EndY) || (EndY < _Clip.StartY) )
      return;

    if( StartX < _Clip.StartX ) StartX = _Clip.StartX;
    if( EndX   > _Clip.EndX   ) EndX   = _Clip.EndX;
    if( StartY < _Clip.StartY ) StartY = _Clip.StartY;
    if( EndY   > _Clip.EndY   ) EndY   = _Clip.EndY;

    int width  = EndX - StartX + 1;
    int height = EndY - StartY + 1 - Distance;

    COLOR *DesPtr = Video + CALC_OFFS( StartX, EndY );
    COLOR *SrcPtr = DesPtr - Distance * VMEM_WIDTH;

#if 0
    for( int i = 0; i < height; i ++ ){
      memcpy( DesPtr, SrcPtr, width );

      SrcPtr -= VMEM_WIDTH;
      DesPtr -= VMEM_WIDTH;
    }
#endif

#if 0
    extern void _ScrollDown( COLOR *des, COLOR *src, int width, int height );
    #pragma aux _ScrollDown =   \
        "mov ebx, 320"          \
        "add ebx, eax"          \
        "cld"                   \
      "@@loop:"                 \
        "mov ecx, eax"          \
        "shr ecx, 1"            \
        "jnc @@no1"             \
        "movsb"                 \
      "@@no1:"                  \
        "shr ecx, 1"            \
        "jnc @@no2"             \
        "movsw"                 \
      "@@no2:"                  \
        "jcxz @@no3"            \
        "rep movsd"             \
      "@@no3:"                  \
        "sub esi, ebx"          \
        "sub edi, ebx"          \
        "dec edx"               \
        "jnz @@loop"            \
    parm [edi] [esi] [eax] [edx]\
    modify [ebx ecx];

    _ScrollDown( DesPtr, SrcPtr, width, height );
#endif

    __asm {
        mov edi, [DesPtr]
        mov esi, [SrcPtr]
        mov eax, [width]
        mov edx, [height]

        mov ebx, 320
        add ebx, eax
        cld
      @@loop:
        mov ecx, eax
        shr ecx, 1
        jnc @@no1
        movsb
      @@no1:
        shr ecx, 1
        jnc @@no2
        movsw
      @@no2:
        jcxz @@no3
        rep movsd
      @@no3:
        sub esi, ebx
        sub edi, ebx
        dec edx
        jnz @@loop
    };

}


/**********************************
  전화면을 윗쪽으로 스크롤 시킨다.
***********************************/
void SCREEN :: ScrollDown( INT Distance )
{
#if 0
    int next = Distance * VMEM_WIDTH;

    memmove( Video + next, Video, VMEM_WIDTH * SCREEN_HEIGHT - next );
#endif

#if 0
    extern void _ScrollDownFull( COLOR *video, int Distance );
    #pragma aux _ScrollDownFull =     \
        "mov ecx, 320"          \
        "mul ecx"               \
        "add esi, 63996"        \
        "mov edi, esi"          \
        "sub esi, eax"          \
        "mov ecx, 64000"        \
        "sub ecx, eax"          \
        "shr ecx, 2"            \
        "std"                   \
        "rep movsd"             \
        "cld"                   \
    parm [esi] [eax]            \
    modify [edi ecx];

    _ScrollDownFull( Video, Distance );
#endif

    COLOR *v = Video;
    __asm {
        mov esi, [v]
        mov eax, [Distance]

        mov ecx, 320
        mul ecx
        add esi, 64000-4
        mov edi, esi
        sub esi, eax
        mov ecx, 64000
        sub ecx, eax
        shr ecx, 2
        std
        rep movsd
        cld
    };

}


/********************************
  화면을 왼쪽으로 스크롤 시킨다.
*********************************/
void SCREEN :: ScrollLeft( INT StartX, INT StartY, INT EndX, INT EndY, INT Distance )
{
    if( StartX > EndX ){
      int t = StartX; StartX = EndX; EndX = t;
    }
    if( StartY > EndY ){
      int t = StartY; StartY = EndY; EndY = t;
    }

    if( (StartX > _Clip.EndX) || (EndX < _Clip.StartX) ||
        (StartY > _Clip.EndY) || (EndY < _Clip.StartY) )
      return;

    if( StartX < _Clip.StartX ) StartX = _Clip.StartX;
    if( EndX   > _Clip.EndX   ) EndX   = _Clip.EndX;
    if( StartY < _Clip.StartY ) StartY = _Clip.StartY;
    if( EndY   > _Clip.EndY   ) EndY   = _Clip.EndY;

    int width  = EndX - StartX + 1 - Distance;
    int height = EndY - StartY + 1;

    COLOR *DesPtr = Video + CALC_OFFS( StartX, StartY );
    COLOR *SrcPtr = DesPtr + Distance;

#if 0
    for( int i = 0; i < height; i ++ ){
      memcpy( DesPtr, SrcPtr, width );

      SrcPtr += VMEM_WIDTH;
      DesPtr += VMEM_WIDTH;
    }
#endif

#if 0
    extern void _ScrollLeft( COLOR *des, COLOR *src, int width, int height );
    #pragma aux _ScrollLeft =   \
        "mov ebx, 320"          \
        "sub ebx, eax"          \
        "cld"                   \
      "@@loop:"                 \
        "mov ecx, eax"          \
        "shr ecx, 1"            \
        "jnc @@no1"             \
        "movsb"                 \
      "@@no1:"                  \
        "shr ecx, 1"            \
        "jnc @@no2"             \
        "movsw"                 \
      "@@no2:"                  \
        "jcxz @@no3"            \
        "rep movsd"             \
      "@@no3:"                  \
        "add esi, ebx"          \
        "add edi, ebx"          \
        "dec edx"               \
        "jnz @@loop"            \
    parm [edi] [esi] [eax] [edx]\
    modify [ebx ecx];

    _ScrollLeft( DesPtr, SrcPtr, width, height );
#endif

    __asm {
        mov edi, [DesPtr]
        mov esi, [SrcPtr]
        mov eax, [width]
        mov edx, [height]

        mov ebx, 320
        sub ebx, eax
        cld
      @@loop:
        mov ecx, eax
        shr ecx, 1
        jnc @@no1
        movsb
      @@no1:
        shr ecx, 1
        jnc @@no2
        movsw
      @@no2:
        jcxz @@no3
        rep movsd
      @@no3:
        add esi, ebx
        add edi, ebx
        dec edx
        jnz @@loop
    };
}


/**********************************
  전화면을 왼쪽으로 스크롤 시킨다.
***********************************/
void SCREEN :: ScrollLeft( INT Distance )
{
    ScrollLeft( 0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1, Distance );
}


/**********************************
  화면을 오른쪽으로 스크롤 시킨다.
***********************************/
void SCREEN :: ScrollRight( INT StartX, INT StartY, INT EndX, INT EndY, INT Distance )
{
    if( StartX > EndX ){
      int t = StartX; StartX = EndX; EndX = t;
    }
    if( StartY > EndY ){
      int t = StartY; StartY = EndY; EndY = t;
    }

    if( (StartX > _Clip.EndX) || (EndX < _Clip.StartX) ||
        (StartY > _Clip.EndY) || (EndY < _Clip.StartY) )
      return;

    if( StartX < _Clip.StartX ) StartX = _Clip.StartX;
    if( EndX   > _Clip.EndX   ) EndX   = _Clip.EndX;
    if( StartY < _Clip.StartY ) StartY = _Clip.StartY;
    if( EndY   > _Clip.EndY   ) EndY   = _Clip.EndY;

    int width  = EndX - StartX + 1 - Distance;
    int height = EndY - StartY + 1;

    COLOR *DesPtr = Video + CALC_OFFS( EndX, StartY );
    COLOR *SrcPtr = DesPtr - Distance;

#if 0
    int skip = VMEM_WIDTH + width;

    for( int i = 0; i < height; i ++ ){
      for( int j = 0; j < width; j ++ )
        *DesPtr-- = *SrcPtr--;

      SrcPtr += skip;
      DesPtr += skip;
    }
#endif

#if 0
    extern void _ScrollRight( COLOR *des, COLOR *src, int width, int height );
    #pragma aux _ScrollRight =  \
        "mov ebx, 320"          \
        "add ebx, eax"          \
        "std"                   \
      "@@loop:"                 \
        "mov ecx, eax"          \
        "shr ecx, 2"            \
        "jcxz @@no1"            \
        "sub esi, 3"            \
        "sub edi, 3"            \
        "rep movsd"             \
        "add esi, 3"            \
        "add edi, 3"            \
      "@@no1:"                  \
        "mov ecx, eax"          \
        "and ecx, 11b"          \
        "jcxz @@no2"            \
        "rep movsb"             \
      "@@no2:"                  \
        "add esi, ebx"          \
        "add edi, ebx"          \
        "dec edx"               \
        "jnz @@loop"            \
        "cld"                   \
    parm [edi] [esi] [eax] [edx]\
    modify [ebx ecx];

    _ScrollRight( DesPtr, SrcPtr, width, height );
#endif

    __asm {
        mov edi, [DesPtr]
        mov esi, [SrcPtr]
        mov eax, [width]
        mov edx, [height]

        mov ebx, 320
        add ebx, eax
        std
      @@loop:
        mov ecx, eax
        shr ecx, 2
        jcxz @@no1
        sub esi, 3
        sub edi, 3
        rep movsd
        add esi, 3
        add edi, 3
      @@no1:
        mov ecx, eax
        and ecx, 11b
        jcxz @@no2
        rep movsb
      @@no2:
        add esi, ebx
        add edi, ebx
        dec edx
        jnz @@loop
        cld
    };
}

/************************************
  전화면을 오른쪽으로 스크롤 시킨다.
*************************************/
void SCREEN :: ScrollRight( INT Distance )
{
    ScrollRight( 0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1, Distance );
}



