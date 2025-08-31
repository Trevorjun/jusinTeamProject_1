#include "pch.h"
#include "CNormalBullet.h"

CNormalBullet::CNormalBullet()
{}

CNormalBullet::~CNormalBullet()
{
	CNormalBullet::Release();
}

void CNormalBullet::Initialize()
{
	m_vSize  = { 15.f, 15.f };
	m_fSpeed = 6.f;
	m_fAngle = 270.f;
}

int CNormalBullet::Update()
{
	if (m_bDestroy)
		return OBJ_DESTROY;

	CObject::UpdateRect();

	m_vPivot.x += m_fSpeed * cosf(RAD(m_fAngle));
	m_vPivot.y += m_fSpeed * sinf(RAD(m_fAngle));

	return OBJ_NOEVENT;
}

void CNormalBullet::LateUpdate()
{
	__super::HandleOutOfBound(IsOutOfBound(50));
}

void CNormalBullet::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CNormalBullet::Release()
{}

bool CNormalBullet::OnCollision(CObject* _pColObj)
{
	return true;
}
