#pragma once
#include "CBullet.h"

class CRotateBullet : public CBullet
{
public:
	CRotateBullet();
	~CRotateBullet() override;

public:
	void Initialize() override;
	int  Update() override;
	void LateUpdate() override;
	void Render(HDC _hDC) override;
	void Release() override;

public:
	bool OnCollision(CObject* _pColObj) override;
};
