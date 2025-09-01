#pragma once

#include <windows.h>

// 전역 변수				//////////////

extern HWND g_hWnd;

// 매크로				//////////////

#define		PURE				= 0
#define		WINCX				600
#define		WINCY				720

#define		OBJ_NOEVENT			0
#define		OBJ_DESTROY			1
#define		OBJ_PLAYERDEAD		2

#define		PI					3.14159f
#define		RAD(_fAngle)		(((_fAngle) * PI) / 180.f)

//// 플레이어 초기값 매크로	////

#define PL_LIFE					3
#define PL_MAXPOWER				5
#define PL_PIVOT_X				100.f
#define PL_PIVOT_Y				100.f
#define PL_SIZE_X				60.f
#define PL_SIZE_Y				60.f
#define PL_SPEED				8.f

//// 몬스터 초기값 매크로		////

#define MON_CURVE_SIZE_X		50.f
#define MON_CURVE_SIZE_Y		50.f
#define MON_CURVE_SPEED			1.f

#define ULL_WSHOTINTERVAL 1000ULL

#define MON_STRAIGHT_SIZE_X		40.f
#define MON_STRAIGHT_SIZE_Y		40.f
#define MON_STRAIGHT_SPEED		5.f

#define MON_SUICIDE_SIZE_X		30.f
#define MON_SUICIDE_SIZE_Y		30.f
#define MON_SUICIDE_SPEED		5.f

// 열거체				//////////////

// 오브젝트 리스트에서 생성할 때 사용
enum OBJECT				
{
	PLAYER,
	MONSTER,
	BULLET,
	ITEM,

	OBJ_END
};

enum COLLISION_FLAG
{
	RECT_TO_RECT,
	CIRCLE_TO_CIRCLE,
	RECT_TO_CIRCLE,
	CIRCLE_TO_RECT,

	COL_FLAG_END
};

// 오브젝트의 타입을 저장해서 충돌 판정에서 사용
enum class OBJECT_TYPE	
{
	PLAYER,
	MONSTER,
	BOSS,
	PLAYER_BULLET,
	MONSTER_BULLET,
	ITEM_LIFE,
	ITEM_POWER,

	END
};

// 함수 템플릿			//////////////

template <typename T>
static void SafeDelete(T& _p)
{
	if (_p)
	{
		delete _p;
		_p = nullptr;
	}
}
