#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CNormalBullet.h"
#include "CRotateBullet.h"
#include "CChaserBullet.h"

CPlayer::CPlayer()
	: m_pBullet(nullptr), m_pShield(nullptr), m_iLife(0), m_iPower(0), m_iMaxPower(0),
	  m_qwAttackCooldown(150), m_qwLastAttackTime(0), m_dwInvincibleDuration(0), m_qwInvincibleEndTime(0),
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
	m_iMaxPower = PL_MAXPOWER;

	m_bIsAlive = true;
}

int CPlayer::Update()
{
	if (m_bDestroy)
		return OBJ_DESTROY;

	if (!m_bIsAlive)
		//return OBJ_PLAYERDEAD;
		Revive();

	if (m_bIsInvincible)
	{
		//todo 몬스터 및 총알과 충돌에서 무적

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

	HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN hOldPen = static_cast<HPEN>(SelectObject(_hDC, hNewPen));

	// head
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	// body
	long int iBodyLen = m_vSize.y;
	Rectangle(_hDC, m_tRect.left, m_tRect.bottom, m_tRect.right, m_tRect.bottom + iBodyLen);

	// arm
	MoveToEx(_hDC, m_tRect.left, m_tRect.bottom, NULL);
	LineTo(_hDC, m_tRect.left - m_vSize.x / 2.f, m_tRect.bottom + m_vSize.y / 2.f);
	MoveToEx(_hDC, m_tRect.right, m_tRect.bottom, NULL);
	LineTo(_hDC, m_tRect.right + m_vSize.x / 2.f, m_tRect.bottom + m_vSize.y / 2.f);

	// leg
	MoveToEx(_hDC, m_tRect.left + m_vSize.x / 4.f, m_tRect.bottom + iBodyLen, NULL);
	LineTo(_hDC, m_tRect.left + m_vSize.x / 4.f, m_tRect.bottom + iBodyLen * 2.f);
	MoveToEx(_hDC, m_tRect.right - m_vSize.x / 4.f, m_tRect.bottom + iBodyLen, NULL);
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

	m_qwInvincibleEndTime = GetTickCount64() + m_dwInvincibleDuration;
}

bool CPlayer::OnCollision(CObject* _pObjCol)
{
	switch (_pObjCol->GetObjectType())
	{
	case OBJECT_TYPE::MONSTER:
	{
		this->AddLife(-1);
	}
	break;
	case OBJECT_TYPE::MONSTER_BULLET:
	{
		//todo 몬스터 총알만 판정하도록
	}
	break;
	case OBJECT_TYPE::ITEM_LIFE:
	{
		this->AddLife(1);
	}
	break;
	case OBJECT_TYPE::ITEM_POWER:
	{
		this->AddPower(1);
	}
	break;
	default:
		break;
	}

	if (m_iLife <= 0)
		m_bIsAlive = false;

	return false;
}

void CPlayer::AddLife(const int _iLifeChange)
{
	m_iLife += _iLifeChange;

	if (m_iLife < 0)
		m_iLife = 0;
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
			m_vPivot.x, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 50.f, 90.f));
	}
	break;
	case 5:
	{
		m_qwAttackCooldown = 50;

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
		m_pBullet->push_back(CAbstractFactory<CChaserBullet>::Create(
			m_vPivot.x, m_vPivot.y - m_vSize.y / 2, OBJECT_TYPE::PLAYER_BULLET, 15.f, 90.f));
	}
	break;
	default:
		break;
	}
}
