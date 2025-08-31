#include "pch.h"
#include "CBullet.h"

CBullet::CBullet()
{}

CBullet::~CBullet()
{
	CBullet::Release();
}

void CBullet::Release()
{}

void CBullet::HandleOutOfBound(const tagObjBound _tOutDir)
{
	if (_tOutDir.bIsOutLeft || _tOutDir.bIsOutRight
		|| _tOutDir.bIsOutTop || _tOutDir.bIsOutBottom)
		m_bDestroy = true;
}
