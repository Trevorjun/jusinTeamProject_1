#pragma once
#include "CMonster.h"

class CMonster_Boss : public CMonster
{
public:
	CMonster_Boss();
	~CMonster_Boss() override;

	void		Initialize() override;
	int			Update() override;
	void		LateUpdate() override;
	bool OnCollision(CObject* _pObjCol) override;
	void		Render(HDC _hDC) override;
	void		Release() override;

	void PatternOne();
	void PatternTwo();
	void PatternThree();
	float checkDegree();
	void PatternFour();
};