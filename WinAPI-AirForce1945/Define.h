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

// Enums				//////////
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
