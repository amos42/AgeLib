﻿/*******************************************

           >>> 리소스 메이커 <<<

                   Programming by 주 경 민

********************************************/
#include <stdio.h>
#include <malloc.h>
#include <io.h>
#include <string.h>
#include <age.h>
#include <list.h>


/*
    ex)
    // 모든 데이터를 만들 땐 4바이트를 기본정렬한다.

    c:\...> type game.rc

    #resname resource.res
    #compress on

    sprite1.spr
    tile1.til
    statge1.map
    etc.dat
    .
    .


    c:\...> makeres game[.rc]
*/

typedef struct {
    CHAR    Header[20];
    LONG    Version;
    LONG    FileCount;
    LONG    ResourceSize;
    CHAR    Dummy[40-(20+4+4+4)];
} RESOURCE_HEADER;

typedef struct {
    LONG    Index;              // Resource Index
    CHAR    FileName[8+1+3];    // 파일 명
    LONG    Offset;             // 헤더를 제외한 옵셋
    LONG    IsCompress;         // 압축 여부
    LONG    FileSize;           // 파일 사이즈
    LONG    FileOrgSize;        // 압축하기 전의 사이즈
} FILE_HEADER;


class FILE_NAME {
  public:
    INT     Index;
    CHAR    FileName[256];
    CHAR    FullName[256];
    BOOL    CompressMode;

    FILE_NAME( void )
    {
      Index = 0;
      memset( FileName, 0, 256 );
      memset( FullName, 0, 256 );
      CompressMode = TRUE;
    }

    ~FILE_NAME() {}

    FILE_NAME &operator = ( const FILE_NAME &x )
    {
      Index = x.Index;
      memcpy( FileName, x.FileName, 256 );
      memcpy( FullName, x.FullName, 256 );
      CompressMode = x.CompressMode;

      return( *this );
    }

    friend bool operator == ( const FILE_NAME &x, const FILE_NAME &y )
    {
      return( !strcmp( x.FileName, y.FileName ) );
    }

    friend bool operator < ( const FILE_NAME &x, const FILE_NAME &y )
    {
      return( strcmp( x.FileName, y.FileName ) < 0 );
    }

    friend bool operator > ( const FILE_NAME &x, const FILE_NAME &y )
    {
      return( strcmp( x.FileName, y.FileName ) > 0 );
    }
};


ULONG Encode( CHAR **DesData, CHAR *SrcData, ULONG DataSize );


char RESName[128] = "RESOURCE.RES";
BOOL CompressMode = TRUE;



/*****************************************
  스트링의 좌우 공백이나 '\n'을 제거한다.
******************************************/
void trim( STRING str )
{
    STRING s = str;

    while( *s != '\0' && *s != '\n' && (*s == ' ' || *s == '\t') ) s++;

    if( s != str ){
      STRING t = str;
      do
        *t++ = *s++;
      while( *s != '\0' );
    }

    int l = strlen( str );
    STRING t = s = str + l - 1;

    while( s != str && (*s == '\n' || *s == ' ' || *s == '\t') ) s--;

    if( s != t ) *(s + 1) = '\0';
}


/*********************
  코멘트를 제거한다.
**********************/
void RemoveComent( STRING str )
{
    STRING s = str;

    while( *s != '\0' && *s != ';' ) s ++;

    *s = '\0';

    trim( str );
}


/*********************************
  스트링의 끝에 '\n'을 제거한다.
**********************************/
void RemoveCR( STRING str )
{
    STRING s = str;

    while( *s != '\0' && *s != '\n' ) s ++;

    *s = '\0';
}


/***************************************
  패스명을 제외한 파일이름을 떼어낸다.
****************************************/
void RemoveFileExt( STRING filename )
{
    STRING s = filename;

    while( *s != '\0' && *s != '\n' ) s ++;
    s --;

    for( int i = 0; i < 3+1; i ++ ){
      if( *s == '.' ){
        *s = '\0';
        break;
      }
      s --;
    }
}


/*******************************
  파일명의 확장자를 제거한다.
********************************/
void ExtractFileName( STRING filename )
{
    STRING str = filename;
    int index = 0;
    int lastindex = -1;

    while( filename[index] != '\0' ){
      if( filename[index] == '\\' || filename[index] == '/' )
        lastindex = index;

      index ++;
    }

    if( lastindex >= 0 ){
      lastindex ++;

      for( int i = 0; i <= index - lastindex; i ++ )
        filename[i] = filename[i + lastindex];
    }
}


/***********************
  RC 파일을 분석한다.
************************/
BOOL AnalisisRCFile( STRING RC_FileName, list<FILE_NAME> &fl )
{
    FILE_NAME fn;
    char filename[256];
    FILE *Ifp, *fp;


    // RC 파일을 연다.
    if( (Ifp = fopen( RC_FileName, "rt" )) == NULL ){
      puts( "RC File open error!\n" );
      return( FALSE );
    }

    int index = 0;

    while( fgets( filename, 255, Ifp ) != NULL ){
      if( filename[0] == '#' ){
        BOOL SetErr = TRUE;
        if( !strncmp( &filename[1], "compress", 8 ) ){
          char tempstr[256];

          strcpy( tempstr, &filename[10] );
          trim( tempstr );
          if( !strncmp( tempstr, "on", 2 ) ){
            CompressMode = TRUE;
            SetErr = FALSE;
          } else if( !strncmp( tempstr, "off", 3 ) ){
            CompressMode = FALSE;
            SetErr = FALSE;
          }
        } else if( !strncmp( &filename[1], "resname", 7 ) ){
          SetErr = FALSE;
          strcpy( RESName, &filename[9] );
          trim( RESName );
        }

        if( SetErr ){
          RemoveCR( filename );
          printf( "Declation Syntex Error in \"%s\"!\n", filename );
          return( FALSE );
        }
      } else {
        trim( filename );

        if( filename[0] == '\0' || filename[0] == '\n' || filename[0] == ';' )
          continue;

        RemoveComent( filename );

        // CR 코드를 없앤다.
        if( (fp = fopen( filename, "rb" )) == NULL ){
          printf( "File Read Error for %s!\n", filename );
          return( FALSE );
        }
        fclose( fp );

        fn.Index = index ++;

        strupr( filename );
        strcpy( fn.FullName, filename );

        // 파일 이름을 얻는다.
        ExtractFileName( filename );
        strcpy( fn.FileName, filename );

        fn.CompressMode = CompressMode;

        fl.insert( fl.end(), fn );
      }
    }

    return( TRUE );
}


/***********************
  리소스를 생성해 낸다.
************************/
BOOL MakeResource( STRING RES_FileName, list<FILE_NAME> &fl )
{
    int i;
    list<FILE_NAME>::iterator fn;
    RESOURCE_HEADER rh = { "Amos Resource File;", 10, 0, 0, };
                         // 12345678901234567890
    FILE_HEADER *fh, *fh_back;
    FILE    *Ofp, *fp;
    char    *src, *des, *des2;
    INT     filesize, index = 0;
    INT     tOrgSize, tCompSize;


    // RES 파일을 연다.
    if( (Ofp = fopen( RES_FileName, "wb" )) == NULL ){
      puts( "Cannot Create RES File!\n" );
      return( FALSE );
    }

    // 일단 파일 헤더를 써 공간을 마련한다.
    rh.FileCount = fl.size();
    fwrite( &rh, sizeof(RESOURCE_HEADER), 1, Ofp );

    // 데이터 헤더 메모리 할당
    fh = fh_back = new FILE_HEADER[ rh.FileCount ];

    // 일단 데이터 헤더를 써 공간을 마련한다.
    fwrite( fh, sizeof(FILE_HEADER) * rh.FileCount, 1, Ofp );

    tOrgSize = tCompSize = 0;

    // 파일명의 첫번째 엘리먼트
    fn = fl.begin();

    // 각 데이터를 쓴다.
    for( i = 0; i < rh.FileCount; i ++ ){
        if( (fp = fopen( (*fn).FullName, "rb" )) == NULL ){
          printf( "File Read Error for %s!\n", (*fn).FullName );
          return( FALSE );
        }

        memset( fh->FileName, 0, 8+1+3 );
        strncpy( fh->FileName, (*fn).FileName, 8+1+3 );

        fh->Offset = index;
        filesize = filelength( fileno(fp) );
        fh->FileOrgSize = filesize;
        src = new char[ filesize ];
        fread( src, filesize, 1, fp );
        fclose( fp );

        if( (*fn).CompressMode ){
          // 파일을 압축한다.
          filesize = Encode( &des, src, (ULONG)filesize );
        } else {
          filesize = 0;
        }

        fh->Index = (*fn).Index;

        // 만약 압축이 되었다면...
        if( filesize > 0 ){
          free( src );
          fh->FileSize = filesize;
          fh->IsCompress = TRUE;
        } else {
          des = src;
          fh->FileSize = fh->FileOrgSize;
          fh->IsCompress = FALSE;
        }

        // 4 바이트 정렬을 위해...
        filesize = fh->FileSize;
        if( filesize % 4 > 0 ) filesize += 4 - filesize % 4;

        tOrgSize += fh->FileOrgSize;
        tCompSize += filesize;

        des2 = (char *)malloc( filesize );
        memset( des2, 0, filesize );
        memcpy( des2, des, fh->FileSize );

        fwrite( des2, filesize, 1, Ofp );
        free( des );
        free( des2 );

        index += filesize;

        // 화면에 과정 표시
        printf( "%-12s : %9ld ==> %9ld (Org %9ld) ... %5.1f%%\n",
                                                    (*fn).FileName, fh->FileOrgSize,
                                                    filesize, fh->FileSize,
                                                    (float)fh->FileSize / fh->FileOrgSize * 100 );

        fh ++;
        fn ++;
    }

    // 제대로 된 파일 헤더를 쓴다.
    rh.ResourceSize = sizeof(RESOURCE_HEADER) + tCompSize;
    fseek( Ofp, 0, SEEK_SET );
    fwrite( &rh, sizeof(RESOURCE_HEADER), 1, Ofp );

    // 데이터 헤더를 다시 쓴다.
    fwrite( fh_back, sizeof(FILE_HEADER) * rh.FileCount, 1, Ofp );

    // 데이터 헤더 메모리 해제
    free( fh_back );

    fclose( Ofp );

    printf( "\nOriginal Size : %d ==> Compress Size : %d\n", tOrgSize, tCompSize );

    return( TRUE );
}


void main( int argc, char *argv[] )
{
    BOOL result;
    char infile[128];
    list<FILE_NAME> fl;


    if( argc < 2 ){
        puts( "RESOURCE MAKER v0.5\n" );
        puts( "Uses : MAKERES game[.rc]\n" );
        exit( 1 );
    }

    strcpy( infile, argv[1] );
    if( !strstr( infile, "." ) ) strcat( infile, ".RC" );

    strcpy( RESName, argv[1] );
    RemoveFileExt( RESName );
    strcat( RESName, ".RES" );

    result = AnalisisRCFile( infile, fl ) ;
    if( !result ) return;

    fl.sort();
    result = MakeResource( RESName, fl );
}


