#include <age.h>


void main()
{
    AGE::Init();

    _Screen.Load( "test.pic" );
    _Screen.RealizePalette();

    TEXT t;
    t.PutString( "‹aŸ± Â‰b µ¹A" );

    KEY::Get();

    AGE::Close();
}

