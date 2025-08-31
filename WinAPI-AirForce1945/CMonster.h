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

	list<CObject*>* m_pBullet;
public:
	CMonster();
	virtual ~CMonster();

	virtual void		Initialize()		PURE;
	virtual int			Update()			PURE;
	virtual void		LateUpdate()		PURE;
	bool OnCollision(CObject* _pObjCol)		PURE;
	virtual void		Render(HDC _hDC)	PURE;
	virtual void		Release()			PURE;

	/*virtual void ShootBullet() PURE;*/

	int getHp() const { return iHp; }
	void setHp(short _iHp) { iHp = _iHp; }
	void setPlayerVXY(CObject* pObj) { fPlayerVX = pObj->GetPivot().x; fPlayerVY = pObj->GetPivot().y; }
	void SetBullet(list<CObject*>* _m_pBullet) { m_pBullet = _m_pBullet; }
};