#include "pch.h"
#include "CMonster_Straight.h"

CMonster_Straight::CMonster_Straight()
{

}
CMonster_Straight::~CMonster_Straight()
{
	Release();
}

void		CMonster_Straight::Initialize()
{
	m_vPivot = { 300, 100 };
	m_vSize = { 50, 50 };
	m_fSpeed = { 3.f };
}
int			CMonster_Straight::Update()
{
	if (m_bDestroy)
	{
		return OBJ_DESTROY;
	}
	m_vPivot.y += m_fSpeed;
	__super::UpdateRect();

	return OBJ_NOEVENT;
}
void		CMonster_Straight::LateUpdate()
{

}
bool CMonster_Straight::OnCollision(CObject* _pObjCol)
{
	// collision with edge
	if (m_vPivot.x - (m_vSize.x / 2) > WINCX ||
		m_vPivot.x + (m_vSize.x / 2) < 0.f ||
		m_vPivot.y - (m_vSize.y / 2) > WINCY)
	{
		return true;
	}

	// need to chage define value / collision with player
	if (sqrt((fPlayerVX - m_vPivot.x) * (fPlayerVX - m_vPivot.x) + (fPlayerVY - m_vPivot.y) * (fPlayerVY - m_vPivot.y))
		< 60.f + 50.f)
	{
		return true;
	}

	return false;
}
void		CMonster_Straight::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}
void		CMonster_Straight::Release()
{

}