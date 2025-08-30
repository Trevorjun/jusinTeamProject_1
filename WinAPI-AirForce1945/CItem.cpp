#include "pch.h"
#include "CItem.h"

CItem::CItem() { }

CItem::~CItem()
{
	Release();
}

void CItem::Initialize() {}

int CItem::Update()
{
	if (m_bDestroy) return OBJ_DESTROY;

	Move();

	__super::UpdateRect();

	return OBJ_NOEVENT;
}

void CItem::LateUpdate()
{
	m_bDestroy = Check_InBound() ? false : true;
}

void CItem::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CItem::Release() { }

void CItem::Move()
{
	m_vPivot += m_vDir * m_fSpeed;
}

bool CItem::Check_InBound()
{
	if (m_tRect.right <= 0 || m_tRect.left >= WINCX
		|| m_tRect.bottom <= 0 || m_tRect.top >= WINCY)
	{
		return false;
	}
	return true;
}
