#include "pch.h"
#include "CMonster_Curve.h"

CMonster_Curve::CMonster_Curve() : fBulletDegree(0.f), fMonsterMoveToX(2.f)
{

}
CMonster_Curve::~CMonster_Curve()
{

}

void		CMonster_Curve::Initialize()
{
	m_vPivot = { 400, 100 };
	m_vSize = { 50, 50 };
	m_fSpeed = { 1.f };
}
int			CMonster_Curve::Update()
{
	if (m_bDestroy)
	{
		return OBJ_DESTROY;
	}
	m_vPivot.x += m_fSpeed * cosf(270.f * (PI / 180.f)) + fMonsterMoveToX * (m_fSpeed * cosf(fBulletDegree * PI / 180.f));
	m_vPivot.y -= m_fSpeed * sinf(270.f * (PI / 180.f)) - (m_fSpeed * sinf(fBulletDegree * PI / 180.f));
	fBulletDegree += m_fSpeed;

	__super::UpdateRect();

	return OBJ_NOEVENT;
}
void		CMonster_Curve::LateUpdate()
{

}
bool CMonster_Curve::OnCollision(CObject* _pObjCol)
{
	return false;
}
void		CMonster_Curve::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}
void		CMonster_Curve::Release()
{

}