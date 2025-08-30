#pragma once
#include "CObject.h"

class CMonster : public CObject
{
protected:
	short iHp;
	float fPlayerVX;
	float fPlayerVY;
public:
	CMonster();
	virtual ~CMonster();

	virtual void		Initialize()		PURE;
	virtual int			Update()			PURE;
	virtual void		LateUpdate()		PURE;
	bool OnCollision(CObject* _pObjCol)		PURE;
	virtual void		Render(HDC _hDC)	PURE;
	virtual void		Release()			PURE;

	int getHp() const { return iHp; }
	void setHp(short _iHp) { iHp = _iHp; }
	void setPlayerVXY(CObject* pObj) { fPlayerVX = pObj->GetPivot().x; fPlayerVY = pObj->GetPivot().y; }
};