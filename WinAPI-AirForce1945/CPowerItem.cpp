#include "pch.h"
#include "CPowerItem.h"

#include "CPlayer.h"

CPowerItem::CPowerItem() { }

CPowerItem::~CPowerItem() { }

void CPowerItem::Initialize()
{
	m_tRect = { 0, };
	m_vSize = { 25, 25 };
	m_vDir = { 0, 1 };

	m_fSpeed = 2.f;
	m_bDestroy = false;

	iPowerEffect = 1;
}

int CPowerItem::Update()
{
	return __super::Update();
}

void CPowerItem::LateUpdate()
{
	__super::LateUpdate();
}

bool CPowerItem::OnCollision(CObject* _pObjCol)
{
	switch (_pObjCol->GetObjectType())
	{
	case OBJECT_TYPE::PLAYER:
	{
		m_bDestroy = true;
	}
	break;
	default:
		break;
	}

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
	CPlayer* pPlayer = static_cast<CPlayer*>(pObj);
	pPlayer->AddPower(iPowerEffect);

	m_bDestroy = true;
}
