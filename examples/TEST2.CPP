#include <age.h>


void main()
{
    AGE::Init();

    _Screen.Load( "test.pic" );
    _Screen.RealizePalette();

    SPRITE spr( "test.spr" );
    spr.PutChar( 100, 100, 0 );

    TEXT t;
    t.PutString( "�a�a�a���a �b ���A" );

    KEY::Get();

    AGE::Close();
}

