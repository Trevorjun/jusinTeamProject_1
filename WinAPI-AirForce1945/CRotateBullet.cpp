#include "pch.h"
#include "CRotateBullet.h"

CRotateBullet::CRotateBullet()
{}

CRotateBullet::~CRotateBullet()
{
	CRotateBullet::Release();
}

void CRotateBullet::Initialize()
{
	m_vSize = { 15.f, 15.f };
	m_fSpeed = 6.f;
	m_fAngle = 270.f;
}

int CRotateBullet::Update()
{
	if (m_bDestroy)
		return OBJ_DESTROY;

	CObject::UpdateRect();



	return OBJ_NOEVENT;
}

void CRotateBullet::LateUpdate()
{
	__super::HandleOutOfBound(IsOutOfBound(50));
}

void CRotateBullet::Render(HDC _hDC) {}

void CRotateBullet::Release()
{}

bool CRotateBullet::OnCollision(CObject* _pColObj)
{
	return true;
}
