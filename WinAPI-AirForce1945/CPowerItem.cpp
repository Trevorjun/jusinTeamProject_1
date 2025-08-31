#include "pch.h"
#include "CPowerItem.h"

CPowerItem::CPowerItem() { }

CPowerItem::~CPowerItem() { }

void CPowerItem::Initialize()
{
	m_tRect = { 0, };
	m_vPivot = { 400, 300 };
	m_vSize = { 25, 25 };
	m_vDir = { 0, 1 };

	m_fSpeed = 2.f;
	m_bDestroy = false;
}

int CPowerItem::Update()
{
	return __super::Update();
}

void CPowerItem::LateUpdate()
{
}

bool CPowerItem::OnCollision(CObject* _pObjCol)
{
	return false;
}

void CPowerItem::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPowerItem::Release()
{
}

void CPowerItem::Apply_Effect(CObject* pObj)
{
	// TODO : 플레이어 클래스 설계 완료 후 구현

	// static_cast<CPlayer*>(pObj)->Create_Posin();

	m_bDestroy = true;
}
