#include "pch.h"
#include "CMonster_Boss.h"

CMonster_Boss::CMonster_Boss()
{

}
CMonster_Boss::~CMonster_Boss()
{
	Release();
}

void		CMonster_Boss::Initialize()
{
	m_eObjectType = OBJECT_TYPE::BOSS;

	m_vPivot = { WINCX >> 1, 100 };
	m_vSize = { 250, 250 };
	m_fSpeed = { 1.f };
}
int			CMonster_Boss::Update()
{
	if (m_bDestroy)
	{
		return OBJ_DESTROY;
	}

	if(m_vPivot.y < ((WINCY >> 1) - 150.f))
	{
		m_vPivot.y += m_fSpeed;
	}

	__super::UpdateRect();

	return OBJ_NOEVENT;
}
void		CMonster_Boss::LateUpdate()
{

}
bool CMonster_Boss::OnCollision(CObject* _pObjCol)
{
	return false;
}
void		CMonster_Boss::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}
void		CMonster_Boss::Release()
{

}