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
