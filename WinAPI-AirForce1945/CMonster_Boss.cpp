#include "pch.h"
#include "CMonster_Boss.h"
#include "CStageManager.h"
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
	m_iMaxHp = 150;
	m_iHp = m_iMaxHp;

	m_vBarSize = { 100, 10 };
	rHPBackgrond = { static_cast<LONG>(m_vPivot.x - m_vBarSize.x), static_cast<LONG>(m_vPivot.y - m_vBarSize.y),
								static_cast<LONG>(m_vPivot.x + m_vBarSize.x), static_cast<LONG>(m_vPivot.y + m_vBarSize.y) };
	rHPFill = { static_cast<LONG>(m_vPivot.x - m_vBarSize.x), static_cast<LONG>(m_vPivot.y - m_vBarSize.y),
								static_cast<LONG>(m_vPivot.x + m_vBarSize.x), static_cast<LONG>(m_vPivot.y + m_vBarSize.y) };
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

			// Request to StageManager to execute clear logic!
			CStageManager::Get_Instance()->Set_BossDead();

			return false;
		}

		m_iHp -= 1;
	}
	return false;
}
void		CMonster_Boss::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	Render_HPBar(_hDC);



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
	float fDegree = checkDegree();
	m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(m_vPivot.x, m_vPivot.y + m_vSize.y / 2, OBJECT_TYPE::MONSTER_BULLET, 7.f, fDegree * 180.f / PI));
}

float CMonster_Boss::checkDegree()
{
	if (m_fPlayerVY > m_vPivot.y)
		return 2 * PI - acosf((m_fPlayerVX - m_vPivot.x) / sqrt(
			(m_fPlayerVX - m_vPivot.x) * (m_fPlayerVX - m_vPivot.x) + (m_fPlayerVY - m_vPivot.y) * (m_fPlayerVY - m_vPivot.y)));
	return acosf((m_fPlayerVX - m_vPivot.x) / sqrt(
		(m_fPlayerVX - m_vPivot.x) * (m_fPlayerVX - m_vPivot.x) + (m_fPlayerVY - m_vPivot.y) * (m_fPlayerVY - m_vPivot.y)));
}


void CMonster_Boss::PatternFour()
{
}

void CMonster_Boss::Render_HPBar(HDC _hDC)
{
	int saved = SaveDC(_hDC);

	rHPBackgrond = { static_cast<LONG>(m_vPivot.x - m_vBarSize.x), static_cast<LONG>(m_vPivot.y - m_vBarSize.y),
							static_cast<LONG>(m_vPivot.x + m_vBarSize.x), static_cast<LONG>(m_vPivot.y + m_vBarSize.y) };

	LONG newRight = rHPBackgrond.left + m_vBarSize.x * 2.f * ((float)m_iHp / (float)m_iMaxHp);

	rHPFill = { rHPBackgrond.left, rHPBackgrond.top,
					newRight, rHPBackgrond.bottom};

	Rectangle(_hDC, rHPBackgrond.left, rHPBackgrond.top, rHPBackgrond.right, rHPBackgrond.bottom);

	HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(0xff, 0x00, 0x00));;
	HPEN hOldPen = static_cast<HPEN>(SelectObject(_hDC, hNewPen));

	Rectangle(_hDC, rHPFill.left, rHPFill.top, rHPFill.right, rHPFill.bottom);

	DeleteObject(SelectObject(_hDC, hOldPen));
	RestoreDC(_hDC, saved);
}
