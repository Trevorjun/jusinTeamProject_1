#pragma once
#include "CMonster.h"

class CMonster_Straight : public CMonster
{
private:
	short test;
public:
	CMonster_Straight();
	~CMonster_Straight() override;

	void		Initialize() override;
	int			Update() override;
	void		LateUpdate() override;
	bool OnCollision(CObject* _pObjCol) override;
	void		Render(HDC _hDC) override;
	void		Release() override;

	void ShootBullet();
};