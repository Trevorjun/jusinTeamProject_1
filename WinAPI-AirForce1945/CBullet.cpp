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
	//todo 공용 코드 구현

	switch (_pObjCol->GetObjectType())
	{
	case OBJECT_TYPE::PLAYER:
	{
		//todo if : 자기 자신이 MONSTER_BULLET이면 실행
	}
	break;
	case OBJECT_TYPE::MONSTER:
	{
		//todo if : 자기 자신이 PLAYER_BULLET이면 실행

		if (m_eObjectType == OBJECT_TYPE::PLAYER_BULLET)
			m_bDestroy = true;
	}
	break;
	default:
		break;
	}

	return false;
}

void CBullet::HandleOutOfBound(const tagObjBound _tOutDir)
{
	if (_tOutDir.bIsOutLeft || _tOutDir.bIsOutRight
		|| _tOutDir.bIsOutTop || _tOutDir.bIsOutBottom)
		m_bDestroy = true;
	//todo 총알 삭제도 매니저에게 부탁하기...?
}
