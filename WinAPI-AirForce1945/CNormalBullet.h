#pragma once
#include "CBullet.h"

// 직선으로 날아가는 기본 총알
class CNormalBullet final : public CBullet
{
public:
	CNormalBullet();
	~CNormalBullet() override;

public:
	void Initialize() override;
	int  Update() override;
	void LateUpdate() override;
	void Render(HDC _hDC) override;
	void Release() override;

public:
	bool OnCollision(CObject* _pColObj) override;
};
