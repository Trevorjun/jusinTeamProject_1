#include "pch.h"
#include "CNormalBullet.h"

CNormalBullet::CNormalBullet()
{
}

CNormalBullet::~CNormalBullet()
{
}

void CNormalBullet::Initialize()
{
}

int CNormalBullet::Update()
{
	if (m_bDestroy)
		return OBJ_DESTROY;

	CObject::UpdateRect();

	return OBJ_NOEVENT;
}

void CNormalBullet::LateUpdate()
{
	__super::LateUpdate();
}

void CNormalBullet::Render(HDC _hDC)
{
}

void CNormalBullet::Release()
{
}
