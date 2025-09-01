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
		//case 2:
		//	PatternThree();
		//	break;
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
	Vector2 vPos(m_vPivot.x, m_vPivot.y + m_vSize.y / 2);
	for (int i = 0; i < 5; ++i)
	{
		m_pBullet->push_back(CAbstractFactory<CNormalBullet>
			::Create(vPos.x, vPos.y, OBJECT_TYPE::MONSTER_BULLET, 5.f, 230.f + i * 20.f));
	}
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
	m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(m_vPivot.x, m_vPivot.y + m_vSize.y / 2, OBJECT_TYPE::MONSTER_BULLET, 4.f, 
		(acos((fPlayerVX - this->GetPivot().x) / sqrtf((fPlayerVX - this->GetPivot().x) * (fPlayerVX - this->GetPivot().x) + (fPlayerVY - this->GetPivot().y) * (fPlayerVY - this->GetPivot().y))) * PI / 180.f)));
	m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(m_vPivot.x, m_vPivot.y + m_vSize.y / 2, OBJECT_TYPE::MONSTER_BULLET, 4.f, 290.f));
}

void CMonster_Boss::PatternFour()
{
}
