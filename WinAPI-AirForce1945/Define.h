#pragma once

// world variable
extern		HWND		g_hWnd;

// mecro
#define		PURE				= 0
#define		WINCX				600
#define		WINCY				720
#define		OBJ_DESTROY			1
#define		OBJ_NOEVENT			0

// enum 
enum OBJECT
{
	PLAYER,
	MONSTER,
	BULLET,

	OBJ_END
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