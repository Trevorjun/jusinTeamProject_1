#pragma once
#include "CBullet.h"

class CRazorBullet : public CBullet
{
public:
	CRazorBullet();
	~CRazorBullet() override;

public:
	void Initialize() override;
	int  Update() override;
	void LateUpdate() override;
	void Render(HDC _hDC) override;
	void Release() override;

public:
	bool OnCollision(CObject* _pObjCol) override;
};
