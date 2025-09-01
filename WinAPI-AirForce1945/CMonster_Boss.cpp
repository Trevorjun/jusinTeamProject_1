#include "pch.h"
#include "CMonster_Boss.h"
#include <random>

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
	m_iHp = 500;
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
	random_device rd;
	mt19937 gen(rd());
	vector<int> iRandNum(3, 0);
	for (int i = 0; i < 3; i++)
	{
		iRandNum[i] = i;
	}
	shuffle(iRandNum.begin(), iRandNum.end(), gen);

	if (dwCurrentTime - ull_wLastShotTime >= ULL_WSHOTINTERVAL)
	{
		switch (iRandNum.front())
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
	if (_pObjCol->GetObjectType() == OBJECT_TYPE::PLAYER_BULLET)
	{
		if (m_iHp == 0) 
		{
			m_bDestroy = true;
			return false;
		}

		m_iHp -= 1;
	}
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
	m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(m_vPivot.x, m_vPivot.y + m_vSize.y / 2, OBJECT_TYPE::MONSTER_BULLET, 5.f, 230.f));
	m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(m_vPivot.x, m_vPivot.y + m_vSize.y / 2, OBJECT_TYPE::MONSTER_BULLET, 5.f, 250.f));
	m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(m_vPivot.x, m_vPivot.y + m_vSize.y / 2, OBJECT_TYPE::MONSTER_BULLET, 5.f, 270.f));
	m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(m_vPivot.x, m_vPivot.y + m_vSize.y / 2, OBJECT_TYPE::MONSTER_BULLET, 5.f, 290.f));
	m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(m_vPivot.x, m_vPivot.y + m_vSize.y / 2, OBJECT_TYPE::MONSTER_BULLET, 5.f, 310.f));
}
void CMonster_Boss::PatternTwo()
{
	float fBossDegree = 0.f;
	while (fBossDegree < 360.f)
	{
		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(m_vPivot.x, m_vPivot.y, OBJECT_TYPE::MONSTER_BULLET, 3.f, fBossDegree));
		fBossDegree += 30.f;
	}
}
void CMonster_Boss::PatternThree()
{
	float fDegree = checkDegree();
	m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(m_vPivot.x, m_vPivot.y + m_vSize.y / 2, OBJECT_TYPE::MONSTER_BULLET, 7.f, fDegree * 180.f / PI));
}

float CMonster_Boss::checkDegree()
{
	if (fPlayerVY > m_vPivot.y)
		return 2 * PI - acosf((fPlayerVX - m_vPivot.x) / sqrt(
			(fPlayerVX - m_vPivot.x) * (fPlayerVX - m_vPivot.x) + (fPlayerVY - m_vPivot.y) * (fPlayerVY - m_vPivot.y)));
	return acosf((fPlayerVX - m_vPivot.x) / sqrt(
		(fPlayerVX - m_vPivot.x) * (fPlayerVX - m_vPivot.x) + (fPlayerVY - m_vPivot.y) * (fPlayerVY - m_vPivot.y)));
}