#include "pch.h"
#include "CMonster_Curve.h"
#include "CBulletTest.h"

CMonster_Curve::CMonster_Curve() : fBulletDegree(0.f), fMonsterMoveToX(2.f)
{

}
CMonster_Curve::~CMonster_Curve()
{
	CMonster_Curve::Release();
}

void		CMonster_Curve::Initialize()
{
	m_vSize = { M_VMON_CURVE_SIZE_X, M_VMON_CURVE_SIZE_Y };
	m_fSpeed = { M_VMON_CURVE_SPEED };
	m_eObjectType = OBJECT_TYPE::MONSTER;
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
	ULONGLONG dwCurrentTime = GetTickCount64();

	if (dwCurrentTime - ull_wLastShotTime >= ULL_WSHOTINTERVAL)
	{
		ShootBullet();
		ull_wLastShotTime = dwCurrentTime;
	}
}
bool CMonster_Curve::OnCollision(CObject* _pObjCol)
{
	__super::OnCollision(_pObjCol);

	return false;
}
void		CMonster_Curve::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}
void		CMonster_Curve::Release()
{

}

void CMonster_Curve::ShootBullet()
{
	m_pBullet->push_back(CAbstractFactory<CBulletTest>::Create(m_vPivot.x, m_vPivot.y + m_vSize.y / 2));
	m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(m_vPivot.x, m_vPivot.y - m_vSize.y / 2));
}