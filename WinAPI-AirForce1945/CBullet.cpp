#include "pch.h"
#include "CBullet.h"

CBullet::CBullet()
{}

CBullet::~CBullet()
{
	CBullet::Release();
}

void CBullet::LateUpdate()
{
	HandleOutOfBound(IsOutOfBound(50));
}

void CBullet::Release()
{}

bool CBullet::OnCollision(CObject* _pColObj)
{
	return false;
}

void CBullet::HandleOutOfBound(const tagObjBound _tOutDir)
{
	if (_tOutDir.bIsOutLeft || _tOutDir.bIsOutRight
		|| _tOutDir.bIsOutTop || _tOutDir.bIsOutBottom)
		m_bDestroy = true;
}
