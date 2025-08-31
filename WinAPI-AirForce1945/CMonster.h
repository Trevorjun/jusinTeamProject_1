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
	~CMonster() override;

public:
	void Initialize() override PURE;
	int  Update() override PURE;
	void LateUpdate() override PURE;
	bool OnCollision(CObject* _pObjCol) override;
	void Render(HDC _hDC) override PURE;
	void Release() override PURE;

public:
	int  getHp() const { return iHp; }
	void setHp(short _iHp) { iHp = _iHp; }

public:
	void setPlayerVXY(CObject* pObj)
	{
		fPlayerVX = pObj->GetPivot().x;
		fPlayerVY = pObj->GetPivot().y;
	}
};
