/**********************************
         >> TEST.CPP <<

                   1998. 5. 8
                      주 경 민
***********************************/
#include <stdlib.h>
#include "age.h"
#include "age_obj.h"

#define OM_CLASH (OM_USER + 1)


// random 매크로 함수 정의
#define random(a) (rand() % (a))

// 전체 슬라임 갯수
#define MAX 20


// 사용될 캐릭터 모델
CHRMODEL cmSlime, cmBall;

//======================================

// 슬라임 캐릭터 클래스
class SLIME : public CHARACTER
{
  public:
    // 생성자
    SLIME(int x, int y, CHRMODEL &cm): CHARACTER( x, y, cm )
    {
      dx = random(5) - 2;
      dy = random(5) - 2;
      idx = random(4);
      r = 0;
    }
    // 소멸자
    ~SLIME() {}

    int idx, r;
    int dx, dy;

    INT ObjProc( HMSG hMsg, LONG lParam );
};

/*********************************
  슬라임 캐릭터의 이벤트 핸들러
**********************************/
INT SLIME :: ObjProc( HMSG hMsg, LONG lParam )
{
    // 인덱스 테이블
    static int tbl[4] = { 0, 1, 2, 1 };

    switch( hMsg ){
      // 타이머 메시지
      case OM_TIMER: // 6번 한번씩은 인덱스 변경
                     if( !(r++ % 6) ) Index = tbl[ idx++ % 4 ];
                     // dx, dy만큼 움직인다.
                     Move( dx, dy );
                     // 만약 화면 모서리에 부딪히면 반사
                     if( X > 320 || X < 0 ) dx = -dx;
                     if( Y > 200 || Y < 0 ) dy = -dy;
                     break;
      // 충돌 메시지
      case OM_CLASH: // 현재 오브젝트를 파괴한다.
                     delete this;
                     break;

      // 그 외의 메시지
      default: CHARACTER::ObjProc( hMsg, lParam );
    }

    return( 0 );
}

// 공 캐릭터 클래스
class BALL : public CHARACTER
{
  public:
    // 생성자
    BALL(int x, int y, CHRMODEL &cm): CHARACTER( x, y, cm )
    {
      dx = random(5)+2 - 3;
      dy = random(5)+2 - 3;
    }
    // 소멸자
    ~BALL() {}

    int dx, dy;

    INT ObjProc( HMSG hMsg, LONG lParam );
};

/*********************************
  공 캐릭터의 이벤트 핸들러
**********************************/
INT BALL :: ObjProc( HMSG hMsg, LONG lParam )
{
    SLIME *s;

    switch( hMsg ){
      // 타이머 메시지
      case OM_TIMER: // dx, dy만큼 움직인다.
                     Move( dx, dy );
                     // 만약 화면 모서리에 부딪히면 반사
                     if( X > 320 || X < 0 ) dx = -dx;
                     if( Y > 200 || Y < 0 ) dy = -dy;

                     // 슬라임을 찾는다.
                     s = (SLIME *)FindFirst( cmSlime.ClassID );
                     // 슬라임이 없을 때까지 반복
                     while( s != NULL ){
                       // 만약 공의 중앙점이 슬라임 이미지 영역 안쪽이면
                       if( s->GetImageRegion().IsInnerPoint(X, Y) ){
                         // 슬라임에게 충돌 메시지 전달
                         SendMessage( s, OM_CLASH, 0 );
                       }
                       // 다음 슬라임을 찾는다.
                       s = (SLIME *)FindNext();
                     }
                     break;

      // 그 외의 메시지
      default: CHARACTER::ObjProc( hMsg, lParam );
    }

    return( 0 );
}

//======================================

// Main 함수
void main()
{
    // 캐릭터 모델을 생성한다.
    cmSlime.Load( "slime.spr", (STRING)NULL, (STRING)NULL );
    cmBall.Load( "ball.spr", (STRING)NULL, (STRING)NULL );

    // MAX개만큼 캐릭터를 생성
    SLIME *c;
    for( int i = 0; i < MAX; i ++ )
      c = new SLIME( random(320), random(200), cmSlime );
    // 공을 하나 생성한다.
    BALL *b = new BALL( random(320), random(200), cmBall );

    // AGE 초기화
    AGE::Init();

    // 그림 페이지를 생성한 후 그림을 로드한다.
    SCREEN pgPic( "face25.pic" );
    // 팔레트 변경
    pgPic.RealizePalette();

    // 작업 페이지를 생성한 후 활성화시킨다.
    SCREEN pgWork;
    pgWork.Activate();

    TEXT tt;

    // 키를 누를 때까지 반복...
    while( !KEY::GetSync() && cmSlime.Count > 0 ){
      // 그림을 작업 화면으로 복사
      pgWork = pgPic;

      // 오브젝트 처리
      OBJECT::Process();

      // 오브젝트 표시
      OBJECT::DisplayAll();

      // 캐릭터 갯수를 표시한다.
      tt.Printf( 0, 0, "SLIME : %d", cmSlime.Count );

      // 작업 페이지 표시
      pgWork.Display();
    }

    // AGE를 종료한다.
    AGE::Close();

    // 오브젝트 리셋
    OBJECT::Reset();
}


