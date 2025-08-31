#pragma once
#include "CBullet.h"

class CObject;

class CChaserBullet : public CBullet
{
public:
	CChaserBullet();
	virtual ~CChaserBullet() override;

public:
	// TODO : 몬스터 List 받아오는 방식을 CMainGame 검출에서 변경해야함
	void	SetMonsterList(list<CObject*>& _refMonsterList) { m_pMonsterList = &_refMonsterList; }


public:
	void	Initialize() override;
	int		Update() override;
	void	Render(HDC _hDC) override;

public:
	bool	OnCollision(CObject* _pColObj) override;

private:
	void		SetTarget();
	float		GetHypotenuse(Vector2 _vForm, Vector2 _vTo);


private:
	CObject*		m_pTarget;
	list<CObject*>* m_pMonsterList;
	HPEN			m_hPen;
};

