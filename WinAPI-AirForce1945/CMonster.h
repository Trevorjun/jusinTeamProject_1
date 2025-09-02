#pragma once
#include "CObject.h"

#include "CAbstractFactory.h"
#include "CNormalBullet.h"

class CMonster : public CObject
{
protected:
	short m_iHp;
	float m_fPlayerVX;
	float m_fPlayerVY;

	ULONGLONG ull_wLastShotTime;

	list<CObject*>* m_pBullet;
public:
	CMonster();
	~CMonster() override;

public:
	void Initialize() override PURE;
	int  Update() override PURE;
	void LateUpdate() override PURE;
	bool OnCollision(CObject* _pObjCol) override;
	void Render(HDC _hDC) override PURE;
	void Release() override PURE;

	/*virtual void ShootBullet() PURE;*/

	int  getHp() const { return m_iHp; }
	void setHp(short _iHp) { m_iHp = _iHp; }
	void setPlayerVXY(CObject* pObj) { m_fPlayerVX = pObj->GetPivot().x; m_fPlayerVY = pObj->GetPivot().y; }
	void SetBullet(list<CObject*>* _m_pBullet) { m_pBullet = _m_pBullet; }

};
