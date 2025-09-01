#include "pch.h"
#include "CRotateBullet.h"

CRotateBullet::CRotateBullet()
	: m_fRotAngle(180.f), m_fRotSpeed(25.f), m_fDisToCen(20.f)
{}

CRotateBullet::~CRotateBullet()
{
	CRotateBullet::Release();
}

void CRotateBullet::Initialize()
{
	m_eObjectType = OBJECT_TYPE::PLAYER_BULLET;

	//todo 플레이어쪽인지 몬스터 쪽인지는 Create를 새로 만들어서 전달하면 좋을듯?

	m_vSize     = { 15.f, 15.f };
	m_fSpeed    = 10.f;
	m_fShootDeg = 90.f;
}

int CRotateBullet::Update()
{
	if (m_bDestroy)
		return OBJ_DESTROY;

	m_vCenter.x = m_fSpeed * cosf(RAD(m_fShootDeg));
	m_vCenter.y = m_fSpeed * sinf(RAD(m_fShootDeg));

	m_fRotAngle += m_fRotSpeed;

	m_vPivot.x += m_vCenter.x + m_fDisToCen * cosf(RAD(m_fRotAngle));
	m_vPivot.y -= m_vCenter.y + m_fDisToCen * -sinf(RAD(m_fRotAngle));

	CObject::UpdateRect();

	return OBJ_NOEVENT;
}

void CRotateBullet::LateUpdate()
{
	//__super::HandleOutOfBound(IsOutOfBound(50));
}

void CRotateBullet::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CRotateBullet::Release()
{}

bool CRotateBullet::OnCollision(CObject* _pObjCol)
{
	__super::OnCollision(_pObjCol);

	return false;
}
