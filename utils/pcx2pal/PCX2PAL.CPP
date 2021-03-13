/*********************************

         >> PCX2PAL.C <<

                 - 주경민 -

 PCX화일을 Game13h의 표준 팔래트
 포맷인 PAL화일로 바꾼다.

**********************************/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


main( int argc, char *argv[] )
{
    FILE *fp;
    char in_filename[13], out_filename[13];
    unsigned char data[768];

    if( argc < 2 ){
      printf("Usage : PCX2PAL <PCX file name>\n");
      exit( 1 );
     }

    strcpy( in_filename, argv[1] );
    strcpy( out_filename, argv[1] );
    strupr( in_filename );
    strupr( out_filename );
    strcat( in_filename,  ".PCX" );
    strcat( out_filename, ".PAL" );

    printf("%s ==> %s ...", in_filename, out_filename );

    if( (fp = fopen( in_filename, "rb" )) == NULL ){
      cputs( in_filename ); cputs( " file Not Found !!" );
      exit( 1 );
     }

    fseek( fp, -768, SEEK_END );
    fread( data, 256*3, 1, fp );
    fclose( fp );

    fp = fopen( out_filename, "wb" );
    fwrite( data, 256*3, 1, fp );
    fclose( fp );
}


