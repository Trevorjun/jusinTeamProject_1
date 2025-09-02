#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CNormalBullet.h"
#include "CRotateBullet.h"
#include "CStageManager.h"
#include "CChaserBullet.h"

CPlayer::CPlayer()
	: m_pBullet(nullptr), m_pShield(nullptr),
	  m_iLife(0), m_iMaxLife(0), m_iPower(0), m_iMaxPower(0),
	  m_qwAttackCooldown(0), m_qwLastAttackTime(0),
	  m_qwChaserCooldown(0), m_qwLastChaserAttackTime(0),
	  m_qwInvincibleDuration(0), m_qwInvincibleEndTime(0),
	  m_bIsAlive(false), m_bIsInvincible(false)
{}

CPlayer::~CPlayer()
{
	CPlayer::Release();
}

void CPlayer::Initialize()
{
	m_eObjectType = OBJECT_TYPE::PLAYER;

	m_vPivot = { PL_PIVOT_X, PL_PIVOT_Y };
	m_vSize  = { 40.f, 40.f };
	m_fSpeed = 8.f;

	m_iLife     = PL_LIFE;
	m_iMaxLife  = PL_LIFE;
	m_iMaxPower = PL_MAXPOWER;

	m_qwAttackCooldown     = 150;
	m_qwChaserCooldown     = 500;
	m_qwInvincibleDuration = 1000;

	m_bIsAlive = true;
}

int CPlayer::Update()
{
	if (m_bDestroy)
		return OBJ_DESTROY;

	if (m_bIsInvincible)
	{
		if (GetTickCount64() >= m_qwInvincibleEndTime)
			m_bIsInvincible = false;
	}

	KeyInput(IsOutOfBound(-10));

	__super::UpdateRect();

	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate()
{}

void CPlayer::Render(HDC _hDC)
{
	int saved = SaveDC(_hDC);

	int iR = 0, iG = 255, iB = 0;

	if (!m_bIsInvincible)
		iG = 255;
	else
	{
		if (GetTickCount64() < m_qwInvincibleEndTime - 1000)
		{
			iR = 255;
			iG = 200;
			iB = 0;
		}
		else if (GetTickCount64() < m_qwInvincibleEndTime - 900)
		{
			iR = 0;
			iG = 255;
			iB = 0;
		}
		else if (GetTickCount64() < m_qwInvincibleEndTime - 800)
		{
			iR = 255;
			iG = 200;
			iB = 0;
		}
		else if (GetTickCount64() < m_qwInvincibleEndTime - 700)
		{
			iR = 0;
			iG = 255;
			iB = 0;
		}
		else if (GetTickCount64() < m_qwInvincibleEndTime - 600)
		{
			iR = 255;
			iG = 200;
			iB = 0;
		}
		else if (GetTickCount64() < m_qwInvincibleEndTime - 500)
		{
			iR = 0;
			iG = 255;
			iB = 0;
		}
		else if (GetTickCount64() < m_qwInvincibleEndTime - 400)
		{
			iR = 255;
			iG = 200;
			iB = 0;
		}
		else if (GetTickCount64() < m_qwInvincibleEndTime - 300)
		{
			iR = 0;
			iG = 255;
			iB = 0;
		}
		else if (GetTickCount64() < m_qwInvincibleEndTime - 200)
		{
			iR = 255;
			iG = 200;
			iB = 0;
		}
	}

	HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(iR, iG, iB));;
	HPEN hOldPen = static_cast<HPEN>(SelectObject(_hDC, hNewPen));

	// head
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	// body
	long int iBodyLen = m_vSize.y;
	Rectangle(_hDC, m_tRect.left, m_tRect.bottom, m_tRect.right, m_tRect.bottom + iBodyLen);

	// arm
	MoveToEx(_hDC, m_tRect.left, m_tRect.bottom, nullptr);
	LineTo(_hDC, m_tRect.left - m_vSize.x / 2.f, m_tRect.bottom + m_vSize.y / 2.f);
	MoveToEx(_hDC, m_tRect.right, m_tRect.bottom, nullptr);
	LineTo(_hDC, m_tRect.right + m_vSize.x / 2.f, m_tRect.bottom + m_vSize.y / 2.f);

	// leg
	MoveToEx(_hDC, m_tRect.left + m_vSize.x / 4.f, m_tRect.bottom + iBodyLen, nullptr);
	LineTo(_hDC, m_tRect.left + m_vSize.x / 4.f, m_tRect.bottom + iBodyLen * 2.f);
	MoveToEx(_hDC, m_tRect.right - m_vSize.x / 4.f, m_tRect.bottom + iBodyLen, nullptr);
	LineTo(_hDC, m_tRect.right - m_vSize.x / 4.f, m_tRect.bottom + iBodyLen * 2.f);

	DeleteObject(SelectObject(_hDC, hOldPen));
	RestoreDC(_hDC, saved);
}

void CPlayer::Release()
{}

void CPlayer::Revive()
{
	m_vPivot = { PL_PIVOT_X, PL_PIVOT_Y };
	m_iLife  = PL_LIFE;
	m_iPower = 0;

	m_bIsInvincible = true;
	m_bIsAlive      = true;

	m_qwInvincibleEndTime = GetTickCount64() + m_qwInvincibleDuration;
}

bool CPlayer::OnCollision(CObject* _pObjCol)
{
	if (!m_bIsAlive)
		return false;

	if (m_bIsInvincible)
		return false;

	switch (_pObjCol->GetObjectType())
	{
	case OBJECT_TYPE::MONSTER:
	{
		if (!m_bIsInvincible)
		{
			this->AddLife(-1);
			m_bIsInvincible       = true;
			m_qwInvincibleEndTime = GetTickCount64() + m_qwInvincibleDuration;
		}
	}
	break;
	case OBJECT_TYPE::BOSS:
	{
		if (!m_bIsInvincible)
		{
			this->AddLife(-1);
			m_bIsInvincible       = true;
			m_qwInvincibleEndTime = GetTickCount64() + m_qwInvincibleDuration;
		}
	}
	break;
	case OBJECT_TYPE::MONSTER_BULLET:
	{
		if (!m_bIsInvincible)
		{
			this->AddLife(-1);
			m_bIsInvincible       = true;
			m_qwInvincibleEndTime = GetTickCount64() + m_qwInvincibleDuration;
		}
	}
	break;
	case OBJECT_TYPE::ITEM_LIFE:
	{
		//this->AddLife(1);
		//! 아이템 각자에서 Addlife 호출 방식으로 변경
	}
	break;
	case OBJECT_TYPE::ITEM_POWER:
	{
		//this->AddPower(1);
		//! 아이템 각자에서 AddPower 호출 방식으로 변경
	}
	break;
	default:
		break;
	}

	if (m_iLife <= 0)
	{
		m_bIsAlive = false;
		CStageManager::Get_Instance()->On_PlayerDead(this);
	}

	return false;
}

void CPlayer::AddLife(const int _iLifeChange)
{
	m_iLife += _iLifeChange;

	if (m_iLife < 0)
		m_iLife = 0;
	else if (m_iLife > m_iMaxLife)
		m_iLife = m_iMaxLife;
}

void CPlayer::AddPower(const int _iPowerChange)
{
	m_iPower += _iPowerChange;

	if (m_iPower < 0)
		m_iPower = 0;
	else if (m_iPower > m_iMaxPower)
		m_iPower = m_iMaxPower;
}

void CPlayer::KeyInput(const tagObjBound _tOutDir)
{
	bool bDiagonalInput = false;

	if (GetAsyncKeyState(VK_SPACE))
	{
		ULONGLONG qwCurrentTime = GetTickCount64();

		if (qwCurrentTime - m_qwLastAttackTime >= m_qwAttackCooldown)
		{
			ShootBullet();

			m_qwLastAttackTime = qwCurrentTime;
		}

		if (m_iPower >= 5 && qwCurrentTime - m_qwLastChaserAttackTime >= m_qwChaserCooldown)
		{
			m_pBullet->push_back(CAbstractFactory<CChaserBullet>::Create(
				m_vPivot.x - 40,
				m_vPivot.y - m_vSize.y / 2 + 50,
				OBJECT_TYPE::PLAYER_BULLET,
				15.f,
				90.f));

			m_pBullet->push_back(CAbstractFactory<CChaserBullet>::Create(
				m_vPivot.x + 40,
				m_vPivot.y - m_vSize.y / 2 + 50,
				OBJECT_TYPE::PLAYER_BULLET,
				15.f,
				90.f));

			m_qwLastChaserAttackTime = qwCurrentTime;
		}
	}

	if (GetAsyncKeyState('F') & 0x0001)
	{
		AddPower(1);
	}

	if (GetAsyncKeyState(VK_LEFT) && !_tOutDir.bIsOutLeft)
	{
		if (GetAsyncKeyState(VK_UP) && !_tOutDir.bIsOutTop)
		{
			bDiagonalInput = true;
			m_vPivot.x -= m_fSpeed / sqrtf(2.f);
			m_vPivot.y -= m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN) && !_tOutDir.bIsOutBottom)
		{
			bDiagonalInput = true;
			m_vPivot.x -= m_fSpeed / sqrtf(2.f);
			m_vPivot.y += m_fSpeed / sqrtf(2.f);
		}
		else
			m_vPivot.x -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_RIGHT) && !_tOutDir.bIsOutRight)
	{
		if (GetAsyncKeyState(VK_UP) && !_tOutDir.bIsOutTop)
		{
			bDiagonalInput = true;
			m_vPivot.x += m_fSpeed / sqrtf(2.f);
			m_vPivot.y -= m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN) && !_tOutDir.bIsOutBottom)
		{
			bDiagonalInput = true;
			m_vPivot.x += m_fSpeed / sqrtf(2.f);
			m_vPivot.y += m_fSpeed / sqrtf(2.f);
		}
		else
			m_vPivot.x += m_fSpeed;
	}

	if (GetAsyncKeyState(VK_UP)
		&& bDiagonalInput == false
		&& !_tOutDir.bIsOutTop)
		m_vPivot.y -= m_fSpeed;

	if (GetAsyncKeyState(VK_DOWN)
		&& bDiagonalInput == false
		&& !_tOutDir.bIsOutBottom)
		m_vPivot.y += m_fSpeed;

	//if (GetAsyncKeyState('E'))
	//{
	//	//m_pShield->push_back(AbstractFactory<Shield>::Create(this));
	//}
}

void CPlayer::ShootBullet()
{
	switch (m_iPower)
	{
	case 0:
	{
		m_qwAttackCooldown = 150;

		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 10.f, 90.f));
	}
	break;
	case 1:
	{
		m_qwAttackCooldown = 150;

		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x - 10, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 10.f, 90.f));
		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x + 10, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 10.f, 90.f));
	}
	break;
	case 2:
	{
		m_qwAttackCooldown = 150;

		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x - 12, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 10.f, 95.f));
		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 10.f, 90.f));
		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x + 12, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 10.f, 85.f));
	}
	break;
	case 3:
	{
		m_qwAttackCooldown = 150;

		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x - 16, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 10.f, 95.f));
		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x - 8, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 10.f, 90.f));
		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x + 8, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 10.f, 90.f));
		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x + 16, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 10.f, 85.f));
	}
	break;
	case 4:
	{
		m_qwAttackCooldown = 150;

		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x - 16, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 10.f, 96.f));
		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x + -6, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 10.f, 93.f));
		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 10.f, 90.f));
		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x + 6, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 10.f, 87.f));
		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x + 16, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 10.f, 84.f));

		m_pBullet->push_back(CAbstractFactory<CRotateBullet>::Create(
			m_vPivot.x, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 10.f, 90.f));
	}
	break;
	case 5:
	{
		m_qwAttackCooldown = 75;

		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x - 10, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 15.f, 90.f));
		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x - 5, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 15.f, 90.f));
		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 15.f, 90.f));
		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x + 5, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 15.f, 90.f));
		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
			m_vPivot.x + 10, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 15.f, 90.f));
	}
	break;
	default:
		break;
	}
}
