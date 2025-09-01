#include "pch.h"
#include "CMonster_Straight.h"
#include "CBulletTest.h"

CMonster_Straight::CMonster_Straight()
{

}
CMonster_Straight::~CMonster_Straight()
{
	Release();
}

void		CMonster_Straight::Initialize()
{
	m_vSize = { M_VMON_STRAIGHT_SIZE_X, M_VMON_STRAIGHT_SIZE_Y };
	m_fSpeed = { M_VMON_STRAIGHT_SPEED };
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
	ULONGLONG dwCurrentTime = GetTickCount64();

	if (dwCurrentTime - ull_wLastShotTime >= ULL_WSHOTINTERVAL)
	{
		ShootBullet();
		ull_wLastShotTime = dwCurrentTime;
	}
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

	// need to change define value / collision with player
	if (sqrt((fPlayerVX - m_vPivot.x) * (fPlayerVX - m_vPivot.x) + (fPlayerVY - m_vPivot.y) * (fPlayerVY - m_vPivot.y))
		< 60.f + M_VMON_STRAIGHT_SIZE_X)
	{
		return true;
	}

	return false;
}
void CMonster_Straight::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}
void CMonster_Straight::Release()
{

}

void CMonster_Straight::ShootBullet()
{
	m_pBullet->push_back(CAbstractFactory<CBulletTest>::Create(m_vPivot.x, m_vPivot.y + m_vSize.y / 2));
}