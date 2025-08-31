#pragma once
#include "CObject.h"

class CBullet : public CObject
{
public:
	CBullet();
	~CBullet() override;

public:
	void Initialize() override;
	int  Update() override;
	void LateUpdate() override;
	void Render(HDC _hDC) override;
	void Release() override;

private:
	// 화면 밖으로 나가지 않게 만드는 기능의 함수
	void HandleOutOfBound(const tagObjBound tOutDir);
};
