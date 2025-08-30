#include "pch.h"
#include "CPlayer.h"

CPlayer::CPlayer()
	: m_pBullet(nullptr), m_pShield(nullptr),
	  m_iLife(0), m_iPower(0), m_iMaxPower(0),
	  m_bIsAlive(false), m_bIsInvincible(false),
	  m_dwAttackCooldown(10), m_dwLastAttackTime(0)
{
}

CPlayer::~CPlayer()
{
	CPlayer::Release();
}

void CPlayer::Initialize()
{
	m_vPivot = { 100.f, 100.f };
	m_vSize  = { 60.f, 60.f };
	m_fSpeed = 8.f;

	m_iLife     = 3;
	m_iMaxPower = 5;

	m_bIsAlive = true;
}

int CPlayer::Update()
{
	__super::UpdateRect();

	Key_Input();

	return 0;
}

void CPlayer::LateUpdate()
{
	HandleOutOfBound(IsOutOfBound());
}

void CPlayer::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release()
{
}

bool CPlayer::OnCollision(CObject* _pColObj)
{
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

void CPlayer::Key_Input()
{
	bool bDiagonalInput = false;

	if (GetAsyncKeyState(VK_SPACE))
	{
		//todo 파워에 따른 총알 생성 바리에이션 추가
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (GetAsyncKeyState(VK_UP))
		{
			bDiagonalInput = true;
			m_vPivot.x += m_fSpeed / sqrtf(2.f);
			m_vPivot.y -= m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			bDiagonalInput = true;
			m_vPivot.x += m_fSpeed / sqrtf(2.f);
			m_vPivot.y += m_fSpeed / sqrtf(2.f);
		}
		else
		{
			m_vPivot.x += m_fSpeed;
		}
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		if (GetAsyncKeyState(VK_UP))
		{
			bDiagonalInput = true;
			m_vPivot.x -= m_fSpeed / sqrtf(2.f);
			m_vPivot.y -= m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			bDiagonalInput = true;
			m_vPivot.x -= m_fSpeed / sqrtf(2.f);
			m_vPivot.y += m_fSpeed / sqrtf(2.f);
		}
		else
		{
			m_vPivot.x -= m_fSpeed;
		}
	}

	if (GetAsyncKeyState(VK_UP) && bDiagonalInput == false)
	{
		m_vPivot.y -= m_fSpeed;
	}

	if (GetAsyncKeyState(VK_DOWN) && bDiagonalInput == false)
	{
		m_vPivot.y += m_fSpeed;
	}

	if (GetAsyncKeyState('E'))
	{
		//m_pShield->push_back(AbstractFactory<Shield>::Create(this));
		//todo 실드 생성 테스트 추가
	}
}

void CPlayer::HandleOutOfBound(const tagObjBound tOutDir)
{
	if (tOutDir.bIsOutLeft)
		m_vPivot.x += static_cast<float>(0 - m_tRect.left);

	if (tOutDir.bIsOutRight)
		m_vPivot.x -= static_cast<float>(m_tRect.right - WINCX);

	if (tOutDir.bIsOutTop)
		m_vPivot.y += static_cast<float>(0 - m_tRect.top);

	if (tOutDir.bIsOutBottom)
		m_vPivot.y -= static_cast<float>(m_tRect.bottom - WINCY);
}
