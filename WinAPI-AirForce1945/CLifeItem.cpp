#include "pch.h"
#include "CLifeItem.h"

CLifeItem::CLifeItem()
{
}

CLifeItem::~CLifeItem()
{
}

void CLifeItem::Initialize()
{
	m_tRect = { 0, };
	m_vPivot = { 100, 300 };
	m_vSize = { 15, 25 };
	m_vDir = { 0, 1 };

	m_fSpeed = 2.5f;
	m_bDestroy = false;
}

int CLifeItem::Update()
{
	return __super::Update();
}

void CLifeItem::LateUpdate()
{
	__super::LateUpdate();
}

bool CLifeItem::OnCollision(CObject* _pObjCol)
{
	return false;
}

void CLifeItem::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CLifeItem::Release()
{
}

void CLifeItem::Apply_Effect(CObject* pObj)
{
	// TODO : 플레이어 클래스 설계 완료 후 구현
	m_bDestroy = true;
}
