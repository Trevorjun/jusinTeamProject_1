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

bool CBullet::OnCollision(CObject* _pObjCol)
{
	if (this->m_eObjectType == OBJECT_TYPE::MONSTER_BULLET
		&& _pObjCol->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		m_bDestroy = true;
	}
	else if (m_eObjectType == OBJECT_TYPE::PLAYER_BULLET
		&& _pObjCol->GetObjectType() == OBJECT_TYPE::MONSTER)
	{
		m_bDestroy = true;
	}
	else if (m_eObjectType == OBJECT_TYPE::PLAYER_BULLET
		&& _pObjCol->GetObjectType() == OBJECT_TYPE::BOSS)
	{
		m_bDestroy = true;
	}

	return false;
}

void CBullet::HandleOutOfBound(const tagObjBound _tOutDir)
{
	if (_tOutDir.bIsOutLeft || _tOutDir.bIsOutRight
		|| _tOutDir.bIsOutTop || _tOutDir.bIsOutBottom)
		m_bDestroy = true;
}
