#include "pch.h"
#include "CItem.h"

CItem::CItem()
{
}

CItem::~CItem()
{
}

void CItem::Initialize()
{
	m_vPivot = { 400, 300 };
	m_vSize = { 100, 100 };
}

int CItem::Update()
{
	if (m_bDestroy) return OBJ_DESTROY;

	__super::UpdateRect();

	return OBJ_NOEVENT;
}

void CItem::LateUpdate()
{
}

void CItem::Render(HDC _hDC)
{
	Rectangle(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CItem::Release()
{
}
