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
	bool OnCollision(CObject* _pObjCol) override;

private:
	Vector2 m_vCenter;			// 가상 중심점
	float   m_fRotAngle;		// 회전 각도
	float	m_fRotSpeed;		// 회전 속도
	float	m_fDisToCen;		// 총알과 중심점 사이 거리
};
