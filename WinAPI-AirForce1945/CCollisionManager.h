#pragma once
#include "CObject.h"

/// <summary>
/// COLLISION_FLAG에 따라 충돌 방식을 내부적으로 처리합니다.
/// 인수1 : 오브젝트 리스트1, 인수2 : 오브젝트 리스트2, 인수3 : 충돌 객체 구성 플레그 값
/// </summary>
class CCollisionManager
{
public:
	static void Collision(list<CObject*>& _Src1, list<CObject*>& _Src2, COLLISION_FLAG _eFlag)
	{
		switch (_eFlag)
		{
		case RECT_TO_RECT:		RTRCollision(_Src1, _Src2);		break;
		case CIRCLE_TO_CIRCLE:	CTCCollision(_Src1, _Src2);		break;
		case RECT_TO_CIRCLE:	CTCCollision(_Src1, _Src2);		break;
		case CIRCLE_TO_RECT:	CTCCollision(_Src1, _Src2);		break;
		default:				break;
		}
	}
private:
	static void RTRCollision(list<CObject*>& _Src1, list<CObject*>& _Src2);
	static void CTCCollision(list<CObject*>& _Src1, list<CObject*>& _Src2);
};

