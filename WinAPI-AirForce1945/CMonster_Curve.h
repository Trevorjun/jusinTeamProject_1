#pragma once
#include "CMonster.h"

class CMonster_Curve : public CMonster
{
private:
	float fBulletDegree;
	float fMonsterMoveToX;
public:
	CMonster_Curve();
	~CMonster_Curve() override;

	void		Initialize() override;
	int			Update() override;
	void		LateUpdate() override;
	bool OnCollision(CObject* _pObjCol) override;
	void		Render(HDC _hDC) override;
	void		Release() override;
};