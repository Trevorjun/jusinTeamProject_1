#include "pch.h"
#include "CAccelBullet.h"

CAccelBullet::CAccelBullet()
{}

CAccelBullet::~CAccelBullet()
{
	CAccelBullet::Release();
}

void CAccelBullet::Initialize()
{}

int CAccelBullet::Update()
{
	if (m_bDestroy)
		return OBJ_DESTROY;

	CObject::UpdateRect();

	return OBJ_NOEVENT;
}

void CAccelBullet::LateUpdate()
{}

void CAccelBullet::Render(HDC _hDC)
{
	//Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	//todo 다른 모양으로 만들어보자
}

void CAccelBullet::Release()
{}

bool CAccelBullet::OnCollision(CObject* _pColObj)
{
	return true;
}
