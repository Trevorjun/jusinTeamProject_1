#include "pch.h"
#include "CObject.h"

CObject::CObject() : m_fSpeed(0.f), m_bDestroy(0)
{
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_vPivot, sizeof(Vector2));
	ZeroMemory(&m_vSize, sizeof(Vector2));
	ZeroMemory(&m_vDir, sizeof(Vector2));
}

CObject::~CObject()
{
}

void CObject::UpdateRect()
{
	m_tRect.left	= (LONG)(m_vPivot.x - ( m_vSize.x * 0.5f ));
	m_tRect.top		= (LONG)(m_vPivot.y - ( m_vSize.y * 0.5f ));
	m_tRect.right	= (LONG)(m_vPivot.x + ( m_vSize.x * 0.5f ));
	m_tRect.bottom	= (LONG)(m_vPivot.y + ( m_vSize.y * 0.5f ));
}
