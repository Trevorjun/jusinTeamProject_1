#include "pch.h"
#include "CRazorBullet.h"

CRazorBullet::CRazorBullet()
{}

CRazorBullet::~CRazorBullet()
{
	CRazorBullet::Release();
}

void CRazorBullet::Initialize()
{
	m_eObjectType = OBJECT_TYPE::PLAYER_BULLET;

	//todo 플레이어쪽인지 몬스터 쪽인지는 Create를 새로 만들어서 전달하면 좋을듯?

}

int CRazorBullet::Update()
{
	if (m_bDestroy)
		return OBJ_DESTROY;

	CObject::UpdateRect();

	return OBJ_NOEVENT;
}

void CRazorBullet::LateUpdate()
{}

void CRazorBullet::Render(HDC _hDC)
{
	//Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	//todo 다른 모양으로 만들어보자
}

void CRazorBullet::Release()
{}

bool CRazorBullet::OnCollision(CObject* _pObjCol)
{
	__super::OnCollision(_pObjCol);

	return false;
}
