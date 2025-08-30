#include "pch.h"
#include "CCollisionManager.h"

void CCollisionManager::RTRCollision(list<CObject*>& _Src1, list<CObject*>& _Src2)
{
	RECT tDst{};
	for (auto& Src1 : _Src1)
		for (auto& Src2 : _Src2)
		{
			if (IntersectRect(&tDst, &(Src1->GetRect()), &(Src2->GetRect())))
			{
				Src1->OnCollision(Src2);
				Src2->OnCollision(Src1);
				Src1->SetCollision(true);
				Src2->SetCollision(true);
			}
			else
			{
				Src1->SetCollision(false);
				Src2->SetCollision(false);
			}
		}
}

void CTCCollision(list<CObject*>& _Src1, list<CObject*>& _Src2)
{
	for (auto& Src1 : _Src1)
		for (auto& Src2 : _Src2)
		{
			Vector2 vDst = { fabsf(Src2->GetPivot().x - Src1->GetPivot().x)
							, fabsf(Src2->GetPivot().y - Src1->GetPivot().y) };

			float fDiagonal = sqrtf(vDst.GetSquared());
			float fSumRadius = (Src2->GetSize().x + Src1->GetSize().x) * 0.5f;

			if (fSumRadius >= fDiagonal)
			{
				Src1->OnCollision(Src2);
				Src2->OnCollision(Src1);
				Src1->SetCollision(true);
				Src2->SetCollision(true);
			}
			else
			{
				Src1->SetCollision(false);
				Src2->SetCollision(false);
			}
		}
}
