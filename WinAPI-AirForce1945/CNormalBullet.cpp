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
	m_vSize     = { 15.f, 15.f };
	m_fSpeed    = 10.f;
	m_fShootDeg = 90.f;
}

int CNormalBullet::Update()
{
	if (m_bDestroy)
		return OBJ_DESTROY;

	m_vPivot.x += m_fSpeed * cosf(RAD(m_fShootDeg));
	m_vPivot.y -= m_fSpeed * sinf(RAD(m_fShootDeg));

	CObject::UpdateRect();

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

bool CNormalBullet::OnCollision(CObject* _pObjCol)
{
	__super::OnCollision(_pObjCol);

	return false;
}
