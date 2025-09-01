#include "pch.h"
#include "CBulletTest.h"

CBulletTest::CBulletTest()
{
}

CBulletTest::~CBulletTest()
{
}

void CBulletTest::Initialize()
{
	m_vSize = { 15.f, 15.f };
	m_fSpeed = 6.f;
}

int CBulletTest::Update()
{
	if (m_bDestroy)
		return OBJ_DESTROY;

	CObject::UpdateRect();

	m_vPivot.y += m_fSpeed;

	return OBJ_NOEVENT;
}

void CBulletTest::LateUpdate()
{
}

void CBulletTest::Render(HDC _hDC)
{
	Ellipse(_hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBulletTest::Release()
{
}
