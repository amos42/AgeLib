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
#include <io.h>
#include <string.h>
#include <malloc.h>
#include "age_res.h"
#include "age_err.h"


struct RESOURCE_HEADER {
    CHAR    Header[20];
    LONG    Version;
    LONG    FileCount;
    LONG    ResourceSize;
    CHAR    Dummy[40-(20+4+4+4)];
};


RESOURCE  _Resource;


/*************************
  리소스 매니저의 생성자
**************************/
RESOURCE :: RESOURCE( void )
{
    Header = NULL;
}


/*************************
  리소스 매니저의 생성자
**************************/
RESOURCE :: RESOURCE( STRING FileName )
{
    Header = NULL;

    Set( FileName );
}


/*************************
  리소스 매니저의 소멸자
**************************/
RESOURCE :: ~RESOURCE()
{
    if( Header ) delete Header;
}


/*******************************
  리소스 파일을 세트한다.
  ""을 지정하면 직접 파일 로드
********************************/
BOOL RESOURCE :: Set( STRING FileName )
{
    FILE *fp;
    RESOURCE_HEADER rh;


    if( Header ) delete Header;

    Header = NULL;
    FileCount = 0;

    if( !strcmp( FileName, "" ) ) return( FALSE );

    if( (fp = fopen( FileName, "rb" )) == NULL )
      return( FALSE );

    fread( &rh, sizeof(RESOURCE_HEADER), 1, fp );

    if( strcmp( rh.Header, "Amos Resource File;" ) )
      return( FALSE );

    Header = new FILE_HEADER[ rh.FileCount ];
    fread( (char *)Header, sizeof(FILE_HEADER) * rh.FileCount, 1, fp );

    fclose( fp );
    FileCount = rh.FileCount;

    strcpy( this->FileName, FileName );

    return( TRUE );
}


/*********************
  리소스를 로드한다.
**********************/
static int cmpfunc( const void *a, const void *b )
{
    return( strncmp( (STRING)a, ((RESOURCE::FILE_HEADER *)b)->FileName, 8+1+3 ) );
}
ULONG RESOURCE :: Load( STRING FileName, CHAR **DesPtr )
{
    long  offs, flen;
    char filename[8+1+3 + 1];
    FILE_HEADER *fh;
    char *data;
    FILE *fp;


    if( Header == NULL ){
      fp = fopen( FileName, "rb" );
      flen = filelength( fileno(fp) );
      *DesPtr = data = new char[ flen ];
      fread( data, flen, 1, fp );
      fclose( fp );

      return( flen );
    } else {
      memset( filename, '\0', 8+1+3+1 );
      strncpy( filename, FileName, 8+1+3 );
      strupr( filename );

      fh = (FILE_HEADER *)bsearch( filename, Header, FileCount,
                                    sizeof(FILE_HEADER), cmpfunc );
      if( fh == NULL ) return( 0 );

      offs = sizeof(RESOURCE_HEADER) + FileCount * sizeof(FILE_HEADER)
                                     + fh->Offset;

      fp = fopen( this->FileName, "rb" );
      fseek( fp, offs, SEEK_SET );
      data = new char[ fh->FileSize ];
      fread( data, fh->FileSize, 1, fp );
      fclose( fp );

      if( fh->IsCompress ){
        Decode( DesPtr, data, fh->FileOrgSize );
        delete data;
      } else {
        *DesPtr = data;
      }

      return( fh->FileOrgSize );
    }
}


/*****************************
  인덱스로 리소스를 로드한다.
******************************/
ULONG RESOURCE :: Load( INT Index, CHAR **DesPtr )
{
    long  offs;
    FILE_HEADER *fh, *tfh;
    char *data;
    FILE *fp;


    if( Header == NULL ){
      return( 0 );
    } else {
      tfh = Header;
      fh = NULL;

      for( int i = 0; i < FileCount; i ++ ){
        if( Index == tfh->Index ){
          fh = tfh;
          break;
        }
        tfh ++;
      }
      if( fh == NULL ) return( 0 );

      offs = sizeof(RESOURCE_HEADER) + FileCount * sizeof(FILE_HEADER)
                                     + fh->Offset;

      fp = fopen( this->FileName, "rb" );
      fseek( fp, offs, SEEK_SET );
      data = (char *)malloc( fh->FileSize );
      fread( data, fh->FileSize, 1, fp );
      fclose( fp );

      if( fh->IsCompress ){
        Decode( DesPtr, data, fh->FileOrgSize );
        free( data );
      } else {
        *DesPtr = data;
      }

      return( fh->FileOrgSize );
    }
}


/*****************************
  파일의 존재 여부를 얻는다.
******************************/
BOOL RESOURCE :: IsExist( STRING FileName )
{
    char filename[8+1+3 + 1];
    FILE_HEADER *fh;
    FILE *fp;


    if( Header == NULL ){
      fp = fopen( FileName, "rb" );
      fclose( fp );
      return( fp != NULL );
    } else {
      memset( filename, '\0', 8+1+3+1 );
      strncpy( filename, FileName, 8+1+3 );
      strupr( filename );

      fh = (FILE_HEADER *)bsearch( filename, Header, FileCount,
                                   sizeof(FILE_HEADER), cmpfunc );
      return( fh != NULL );
    }
}


/*********************
  리소스를 해제한다.
**********************/
void RESOURCE :: Free( CHAR *ResPtr )
{
    free( ResPtr );
}


