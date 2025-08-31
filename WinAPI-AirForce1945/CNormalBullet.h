#pragma once
#include "CBullet.h"

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

private:
};
