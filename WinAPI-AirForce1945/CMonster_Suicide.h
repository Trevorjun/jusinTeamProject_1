#pragma once
#include "CMonster.h"

class CMonster_Suicide : public CMonster
{
private:
	float fMonsterRadian;
public:
	CMonster_Suicide();
	~CMonster_Suicide() override;

	void		Initialize() override;
	int			Update() override;
	void		LateUpdate() override;
	bool OnCollision(CObject* _pObjCol) override;
	void		Render(HDC _hDC) override;
	void		Release() override;

	float checkDegree(float playerVX, float playerVY);
};