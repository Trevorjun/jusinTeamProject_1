#include "pch.h"
#include "CRotateBullet.h"

CRotateBullet::CRotateBullet()
	: m_fRotateAngle(180.f)
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

	m_vCenter.x += m_fSpeed * cosf(RAD(m_fShootDeg)) * 0.01f;
	m_vCenter.y -= m_fSpeed * sinf(RAD(m_fShootDeg)) * 0.01f;
	//! 0.01f : 속도 늦추는 보정값

	m_vPivot.x += m_vCenter.x + 30.f * cosf(RAD(m_fRotateAngle));
	m_vPivot.y += m_vCenter.y + 30.f * sinf(RAD(m_fRotateAngle));
	//! 30.f : 회전하는 반경을 조정

	m_fRotateAngle += 50.f;
	//! 50.f : 회전하는 속도를 조정

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
