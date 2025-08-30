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

bool CItem::OnCollision(CObject* _pColObj)
{

	return false;
}

void CItem::Render(HDC _hDC)
{
	
}

void CItem::Release()
{
}


