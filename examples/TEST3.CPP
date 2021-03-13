#include <age.h>


void main()
{
    AGE::Init();

    SCREEN pgVirt1( "test.pic" );
    pgVirt1.RealizePalette();
    pgVirt1.Activate();

    TEXT t;
    t.PutString( "¯aÏaœa·¡Ëa ´“¡¡A·¡­e µ¹A" );

    SCREEN pgVirt2;
    pgVirt2.Activate();

    SPRITE spr( "test.spr" );

    for( int i = 0; i < 320; i ++ ){
      pgVirt2 = pgVirt1;
      spr.PutChar( i, 100, 0 );
      pgVirt2.Display();
    }

    KEY::Get();

    AGE::Close();
}

