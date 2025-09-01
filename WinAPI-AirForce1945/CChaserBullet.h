#pragma once
#include "CBullet.h"

class CObject;
class CChaserBullet final : public CBullet
{
public:
	CChaserBullet();
	~CChaserBullet() override;

public:
	
	void	SetMonsterList(list<CObject*>& _refMonsterList) { m_pMonsterList = &_refMonsterList; }


public:
	void	Initialize()		override;
	int		Update()			override;
	void	LateUpdate()		override;
	void	Render(HDC _hDC)	override;
	void	Release()			override;
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

