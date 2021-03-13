/*********************************

        >> PCX2PIC.CPP <<

                    - 주경민 -

**********************************/
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>


#define BACK_COLORS 256


typedef struct {
    unsigned char red, green, blue;
} palette_info;

typedef struct {
    char    header;
    char    version;
    char    encode;
    char    bitperpixel;
    short   x1, y1;
    short   x2, y2;
    short   hres;
    short   vres;
    palette_info palette[16];
    char    mode;
    char    nplanes;
    short   byteperline;
    short   palette_info;
    short   scaner_hres, scaner_vres;
    char    unused[54];
} PCXHeader;

typedef struct {
    char    Header[20];
    long    Ver;
    long    width, height;
} PICHeader;

int width, height;
FILE *in_file, *out_file;
char *data;


/*******************************
  가상 페이지에 PCX를 전개한다.
********************************/
void load_pcx_file()
{
    int l;
    char count, indata;
    char *s, *t, *d = data;


    l =  filelength( fileno(in_file) ) - 0x80 - (768 + 1);
    t = s = new char[ l ];
    fseek( in_file, 0x80, SEEK_SET );
    fread( s, l, 1, in_file );


    do{
      indata = *s++;
      if( (indata & 0xC0 ) == 0xC0 ){
        count = indata & 0x3F;
        indata = *s++;
        while( count-- )
          *d++ = indata;
       } else
        *d++ = indata;
     } while( d < data + width * height );

    delete  t;
}



main( int argc, char *argv[] )
{
    unsigned char pal[BACK_COLORS * 3];
    char in_filename[13], out_filename[13];
    PCXHeader pcxhead;
    PICHeader header;



    if( argc < 2 ){
      cputs("Usage : PCX2PIC <PCX file name>\n\r");
      exit( 0 );
    }

    strcpy( in_filename, argv[1] );
    strcpy( out_filename, argv[1] );
    strupr( in_filename );
    strupr( out_filename );
    strcat( in_filename,  ".PCX" );
    strcat( out_filename, ".PIC" );

    in_file  = fopen( in_filename, "rb" );
    if( in_file == NULL ){
      cputs( in_filename ); cputs( " file Not Found !!" );
      exit( 1 );
     }
    out_file = fopen( out_filename, "wb" );

    cputs( in_filename ); cputs( " ==> " ); cputs( out_filename );


    fread( &pcxhead, 0x80, 1, in_file );
    width  = pcxhead.x2 - pcxhead.x1 + 1;
    height = pcxhead.y2 - pcxhead.y1 + 1;

    strcpy( header.Header, "Amos Picture File;" );
    header.Ver = 2;
    header.width  = width;
    header.height = height;
    fwrite( &header, sizeof(header), 1, out_file );

    fseek( in_file, -768, SEEK_END );
    fread( pal, BACK_COLORS * 3, 1, in_file );
    fwrite( pal, BACK_COLORS * 3, 1, out_file );

    data = new char[ width*height + 100 ];

    load_pcx_file();
    fwrite( data, width*height, 1, out_file );

    delete data;

    fclose( in_file );
    fclose( out_file );
}


