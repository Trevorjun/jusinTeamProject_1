#include "pch.h"
#include "CMonster_Boss.h"

CMonster_Boss::CMonster_Boss()
{

}
CMonster_Boss::~CMonster_Boss()
{
	Release();
}

void		CMonster_Boss::Initialize()
{
	m_eObjectType = OBJECT_TYPE::BOSS;

	m_vSize = { 250, 250 };
	m_fSpeed = { 1.f };
}
int			CMonster_Boss::Update()
{
	if (m_bDestroy)
	{
		return OBJ_DESTROY;
	}

	if(m_vPivot.y < ((WINCY >> 1) - 150.f))
	{
		m_vPivot.y += m_fSpeed;
	}

	__super::UpdateRect();

	return OBJ_NOEVENT;
}
void		CMonster_Boss::LateUpdate()
{
	ULONGLONG dwCurrentTime = GetTickCount64();
	srand(unsigned(GetTickCount64()));
	int sRandNum = rand() % 3;

	if (dwCurrentTime - ull_wLastShotTime >= ULL_WSHOTINTERVAL)
	{
		switch (sRandNum)
		{
		case 0:
			PatternOne();
			break;
		case 1:
			PatternTwo();
			break;
		case 2:
			PatternThree();
			break;
		default:
			break;
		}
		ull_wLastShotTime = dwCurrentTime;
	}
}
bool CMonster_Boss::OnCollision(CObject* _pObjCol)
{
	return false;
}
void		CMonster_Boss::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}
void		CMonster_Boss::Release()
{

}

void CMonster_Boss::PatternOne()
{
	for(float fBossDegree = 230.f; fBossDegree >= 310.f; fBossDegree += 20.f)
	{
		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(m_vPivot.x, m_vPivot.y + m_vSize.y / 2, OBJECT_TYPE::MONSTER_BULLET, 5.f, fBossDegree));
	}
}
void CMonster_Boss::PatternTwo()
{
	float fBossDegree = 0.f;
	while (fBossDegree < 360.f)
	{
		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(m_vPivot.x, m_vPivot.y, OBJECT_TYPE::MONSTER_BULLET, 5.f, fBossDegree));
		fBossDegree += 30.f;
	}
}
void CMonster_Boss::PatternThree()
{

}