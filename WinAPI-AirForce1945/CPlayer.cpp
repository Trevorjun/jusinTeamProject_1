#include "pch.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CNormalBullet.h"

CPlayer::CPlayer()
	: m_pBullet(nullptr), m_pShield(nullptr),
	  m_iLife(0), m_iPower(0), m_iMaxPower(0),
	  m_dwAttackCooldown(10), m_dwLastAttackTime(0),
	  m_bIsAlive(false), m_bIsInvincible(false)
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
	if (m_bDestroy)
		return OBJ_DESTROY;

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

void CPlayer::Key_Input(const tagObjBound _tOutDir)
{
	bool bDiagonalInput = false;

	if (GetAsyncKeyState(VK_SPACE))
	{
		m_pBullet->push_back(CAbstractFactory<CNormalBullet>::Create(m_vPivot.x, m_vPivot.y - m_vSize.y / 2));

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
