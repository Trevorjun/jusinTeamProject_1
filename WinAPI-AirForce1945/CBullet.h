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
	void LateUpdate() override PURE;
	void Render(HDC _hDC) override PURE;
	void Release() override;

public:
	// 일반 가상함수로 선언해서, 추가 동작이 필요할 경우만 자식에 내용을 추가할 것
	bool OnCollision(CObject* _pObjCol) override;

protected:
	// 총알이 화면 밖으로 나가면 사라지게 만드는 기능의 함수
	void HandleOutOfBound(const tagObjBound _tOutDir);
};