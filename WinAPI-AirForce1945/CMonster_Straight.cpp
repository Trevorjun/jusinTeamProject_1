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
	return false;
}
void		CMonster_Straight::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}
void		CMonster_Straight::Release()
{

}