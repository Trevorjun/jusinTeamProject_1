#pragma once
#include "CObject.h"

class CBullet : public CObject
{
public:
	CBullet();
	~CBullet() override;

public:
	void Initialize() override PURE;
	int  Update() override PURE;
	void LateUpdate() override;				// 이것만 순수가상이 아니므로 자식의 LateUpdate()에서 호출할것
	void Render(HDC _hDC) override PURE;
	void Release() override PURE;

public:
	bool OnCollision(CObject* _pColObj) override;

private:
	// 총알이 화면 밖으로 나가면 사라지게 만드는 기능의 함수
	void HandleOutOfBound(const tagObjBound _tOutDir);
};
