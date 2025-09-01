#pragma once

// World variables		//////////
extern HWND g_hWnd;

// Macros				//////////
#define		PURE				= 0
#define		WINCX				600
#define		WINCY				720
#define		OBJ_DESTROY			1
#define		OBJ_NOEVENT			0
#define		PI					3.14159f
#define		RAD(_fAngle)		(((_fAngle) * PI) / 180.f)

// player mecro
#define IPLATER_LIFE 3
#define IMAX_POWER 5
#define M_VPLAYER_PIVOT_X 100.f
#define M_VPLAYER_PIVOT_Y 100.f
#define M_VSIZE_X 60.f
#define M_VSIZE_Y 60.f
#define M_FPLAYER_SPEED 8.f

// monster mecro
#define M_VMON_CURVE_SIZE_X 50.f
#define M_VMON_CURVE_SIZE_Y 50.f
#define M_VMON_CURVE_SPEED 1.f

#define M_VMON_STRAIGHT_SIZE_X 40.f
#define M_VMON_STRAIGHT_SIZE_Y 40.f
#define M_VMON_STRAIGHT_SPEED 5.f

#define M_VMON_SUICIDE_SIZE_X 30.f
#define M_VMON_SUICIDE_SIZE_Y 30.f
#define M_VMON_SUICIDE_SPEED 5.f

#define ULL_WSHOTINTERVAL 1000ULL


// enum 
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

// Template functions	//////////
template <typename T>
static void SafeDelete(T& _p)
{
	if (_p)
	{
		delete _p;
		_p = nullptr;
	}
}
