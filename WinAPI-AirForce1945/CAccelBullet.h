#pragma once
#include "CBullet.h"

class CAccelBullet : public CBullet
{
public:
	CAccelBullet();
	~CAccelBullet() override;

public:
	void Initialize() override;
	int  Update() override;
	void LateUpdate() override;
	void Render(HDC _hDC) override;
	void Release() override;

public:
	bool OnCollision(CObject* _pColObj) override;
};
