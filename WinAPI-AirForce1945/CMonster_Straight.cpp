#include "pch.h"
#include "CMonster_Straight.h"
#include "CBulletTest.h"

CMonster_Straight::CMonster_Straight()
{}

CMonster_Straight::~CMonster_Straight()
{
	CMonster_Straight::Release();
}

void		CMonster_Straight::Initialize()
{
	m_vSize = { MON_STRAIGHT_SIZE_X, MON_STRAIGHT_SIZE_Y };
	m_fSpeed = { MON_STRAIGHT_SPEED };
	m_eObjectType = OBJECT_TYPE::MONSTER;
}

int			CMonster_Straight::Update()
{
	if (m_bDestroy)
	{
		return OBJ_DESTROY;
	}
	m_vPivot.y += m_fSpeed;
	__super::UpdateRect();

	tagObjBound tObjBound = __super::IsOutOfBound(50);

	if (tObjBound.bIsOutBottom || tObjBound.bIsOutTop || tObjBound.bIsOutRight || tObjBound.bIsOutLeft )
	{
		m_bDestroy = true;
	}


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
	__super::OnCollision(_pObjCol);

	//? 이 아래는 테스트 코드인듯?
	//! 몬스터 충돌처리 코드의 공통 구현부분을 __super::OnCollision로 CMonster에서 호출하는데,
	//! 보스의 경우만 따로 체력 감소 처리를 해야 하므로 거기서만 __super::OnCollision를 안쓰면 됨

	// collision with edge
	if (m_vPivot.x - (m_vSize.x / 2) > WINCX ||
		m_vPivot.x + (m_vSize.x / 2) < 0.f ||
		m_vPivot.y - (m_vSize.y / 2) > WINCY)
	{
		return true;
	}

	// need to change define value / collision with player
	if (sqrt((fPlayerVX - m_vPivot.x) * (fPlayerVX - m_vPivot.x) + (fPlayerVY - m_vPivot.y) * (fPlayerVY - m_vPivot.y))
		< 60.f + MON_STRAIGHT_SIZE_X)
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
	m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(m_vPivot.x, m_vPivot.y + m_vSize.y / 2, OBJECT_TYPE::MONSTER_BULLET, 6.f, 270.f));
}
