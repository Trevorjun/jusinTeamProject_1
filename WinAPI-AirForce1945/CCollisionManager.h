#pragma once
#include "CObject.h"

class CCollisionManager
{
public:
	static void Collision(list<CObject*>& _Src1, list<CObject*>& _Src2, COLLIISION_FLAG _eFlag)
	{
		switch (_eFlag)
		{
		case RECT_TO_RECT:		RTRCollision(_Src1, _Src2);		break;
		case CIRCLE_TO_CIRCLE:	break;
		case RECT_TO_CIRCLE:	break;
		case CIRCLE_TO_RECT:	break;
		case COL_FLAG_END:		break;
		default:
			break;
		}
	}
private:
	static void RTRCollision(list<CObject*>& _Src1, list<CObject*>& _Src2)
	{
		RECT tDst{};
		for (auto& Src1 : _Src1)
		{
			for (auto& Src2 : _Src2)
			{
				if (IntersectRect(&tDst, &(Src1->GetRect()), &(Src2->GetRect())))
				{
					Src1->SetDestroy();
					Src2->SetDestroy();
				}
			}
		}
	}
};

