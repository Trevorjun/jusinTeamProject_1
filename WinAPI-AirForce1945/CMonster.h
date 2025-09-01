#pragma once
#include "CObject.h"

#include "CAbstractFactory.h"
#include "CNormalBullet.h"
class CMonster : public CObject
{
protected:
	short iHp;
	float fPlayerVX;
	float fPlayerVY;
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

	int getHp() const { return iHp; }
	void setHp(short _iHp) { iHp = _iHp; }
	void setPlayerVXY(CObject* pObj) { fPlayerVX = pObj->GetPivot().x; fPlayerVY = pObj->GetPivot().y; }
	void SetBullet(list<CObject*>* _m_pBullet) { m_pBullet = _m_pBullet; }
};
