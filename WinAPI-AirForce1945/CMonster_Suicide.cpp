#include "pch.h"
#include "CMonster_Suicide.h"
#include "CPlayer.h"

CMonster_Suicide::CMonster_Suicide()
	: fMonsterRadian(0.f)
{
}

CMonster_Suicide::~CMonster_Suicide()
{
	CMonster_Suicide::Release();
}

void		CMonster_Suicide::Initialize()
{
	m_vSize = { M_VMON_SUICIDE_SIZE_X, M_VMON_SUICIDE_SIZE_Y };
	m_fSpeed = { M_VMON_SUICIDE_SPEED };
	m_eObjectType = OBJECT_TYPE::MONSTER;
}

int			CMonster_Suicide::Update()
{
	if (m_bDestroy)
	{
		return OBJ_DESTROY;
	}
	fMonsterRadian = checkDegree(fPlayerVX, fPlayerVY);

	if (fPlayerVY > m_vPivot.y)
	{
		m_vPivot.x += m_fSpeed * cosf(fMonsterRadian);
		m_vPivot.y -= m_fSpeed * sinf((360.f * PI / 180.f) - fMonsterRadian);
	}

	else
	{
		m_vPivot.x += m_fSpeed * cosf(fMonsterRadian);
		m_vPivot.y -= m_fSpeed * sinf(fMonsterRadian);
	}

	__super::UpdateRect();

	return OBJ_NOEVENT;
}

void		CMonster_Suicide::LateUpdate()
{
}

bool CMonster_Suicide::OnCollision(CObject* _pObjCol)
{
	__super::OnCollision(_pObjCol);

	return false;
}

void		CMonster_Suicide::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void		CMonster_Suicide::Release()
{
}

float CMonster_Suicide::checkDegree(float fPlayerVX, float fPlayerVY)
{
	float fRadian;

	fRadian = acosf((fPlayerVX - m_vPivot.x) / sqrt(
		(fPlayerVX - m_vPivot.x) * (fPlayerVX - m_vPivot.x) + (fPlayerVY - m_vPivot.y) * (fPlayerVY - m_vPivot.y)));

	return fRadian;
}
