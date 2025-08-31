#include "pch.h"
#include "CMonster.h"

CMonster::CMonster() : iHp(0), fPlayerVX(0.f), fPlayerVY(0.f)
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
		m_bDestroy = true;
	}
	break;
	case OBJECT_TYPE::PLAYER_BULLET:
	{
		m_bDestroy = true;
	}
	break;
	default:
		break;
	}

	return false;
}
