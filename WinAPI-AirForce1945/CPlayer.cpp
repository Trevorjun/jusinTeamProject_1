#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CNormalBullet.h"

CPlayer::CPlayer()
	: m_pBullet(nullptr), m_pShield(nullptr), m_iLife(0), m_iPower(0), m_iMaxPower(0),
	  m_qwAttackCooldown(200), m_qwLastAttackTime(0), m_dwInvincibleDuration(0), m_qwInvincibleEndTime(0),
	  m_bIsAlive(false), m_bIsInvincible(false)
{
}

CPlayer::~CPlayer()
{
	CPlayer::Release();
}

void CPlayer::Initialize()
{
	m_eObjectType = OBJECT::PLAYER;

	m_vPivot = { M_VPLAYER_PIVOT_X, M_VPLAYER_PIVOT_Y };
	m_vSize  = { 60.f, 60.f };
	m_fSpeed = 8.f;

	m_iLife     = IPLATER_LIFE;
	m_iMaxPower = IMAX_POWER;

	m_bIsAlive = true;
}

int CPlayer::Update()
{
	if (m_bIsInvincible)
	{
		//todo 몬스터 및 총알과 충돌에서 무적

		if (GetTickCount64() >= m_qwInvincibleEndTime)
			m_bIsInvincible = false;
	}

	if (m_bDestroy)
		return OBJ_DESTROY;

	if (m_iLife <= 0)
		m_bIsAlive = false;

	__super::UpdateRect();

	Key_Input(IsOutOfBound(-10));

	

	return OBJ_NOEVENT;
}

void CPlayer::LateUpdate()
{
}

void CPlayer::Render(HDC _hDC)
{
	int saved = SaveDC(_hDC);

	HPEN hNewPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	HPEN hOldPen = static_cast<HPEN>(SelectObject(_hDC, hNewPen));

	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	DeleteObject(SelectObject(_hDC, hOldPen));
	RestoreDC(_hDC, saved);
}

void CPlayer::Release()
{
}

void CPlayer::Revive()
{
	m_vPivot = { M_VPLAYER_PIVOT_X, M_VPLAYER_PIVOT_Y };
	m_iLife  = IPLATER_LIFE;
	m_iPower = 0;

	m_bIsInvincible = true;
	m_bIsAlive      = true;

	m_qwInvincibleEndTime = GetTickCount64() + m_dwInvincibleDuration;
}

bool CPlayer::OnCollision(CObject* _pColObj)
{
	//! Collision을 메인 게임의 LateUpdate에서 했을 때 그 안에서 호출되는, 충돌 시 할 작업들

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

void CPlayer::Key_Input(const tagObjBound _tOutDir)
{
	bool bDiagonalInput = false;

	if (GetAsyncKeyState(VK_SPACE))
	{
		ULONGLONG qwCurrentTime = GetTickCount64();

		if (qwCurrentTime - m_qwLastAttackTime >= m_qwAttackCooldown)
		{
			m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
				m_vPivot.x, m_vPivot.y - m_vSize.y / 2));
			m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(
				m_vPivot.x - 20, m_vPivot.y - m_vSize.y / 2));

			m_qwLastAttackTime = qwCurrentTime;
		}

		//todo 파워에 따른 총알 생성 바리에이션 추가
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
