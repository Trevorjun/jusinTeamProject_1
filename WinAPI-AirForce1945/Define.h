#pragma once

// world variable
extern		HWND		g_hWnd;

// mecro
#define		PURE				= 0
#define		WINCX				600
#define		WINCY				720
#define		OBJ_DESTROY			1
#define		OBJ_NOEVENT			0
#define		PI					3.14159f
#define		RAD(_fAngle)		((_fAngle * PI) / 180.f)					
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

/**
 * \brief 각 사방의 범위 밖으로 나갈 경우를 체크하기 위한 구조체
 *
 * \details
 * - bIsOutLeft:	왼쪽으로 벗어난 경우 true
 * - bIsOutRight:	오른쪽으로 벗어난 경우 true
 * - bIsOutTop:	위쪽으로 벗어난 경우 true
 * - bIsOutBottom:	아래쪽으로 벗어난 경우 true
 */
struct tagObjBound
{
	bool bIsOutLeft = false;
	bool bIsOutRight = false;
	bool bIsOutTop = false;
	bool bIsOutBottom = false;
};

template <typename T>
static void SafeDelete(T& _p)
{
	if (_p)
	{
		delete _p;
		_p = nullptr;
	}
}