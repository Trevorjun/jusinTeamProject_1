#include "pch.h"
#include "CMonster.h"

#include "CStageManager.h"

CMonster::CMonster() : iHp(0), fPlayerVX(0.f), fPlayerVY(0.f), m_pBullet(nullptr), ull_wLastShotTime(0)
{

}
CMonster::~CMonster()
{

}

bool CMonster::OnCollision(CObject* _pObjCol)
{
	switch (_pObjCol->GetObjectType())
	{
	case OBJECT_TYPE::PLAYER:
	{
		CStageManager::Get_Instance()->On_MonsterKilled(this);
		m_bDestroy = true;
	}
	break;
	case OBJECT_TYPE::PLAYER_BULLET:
	{
 		CStageManager::Get_Instance()->On_MonsterKilled(this);
		m_bDestroy = true;
	}
	break;
	default:
		break;
	}

	return false;
}
