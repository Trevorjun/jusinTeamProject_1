#include "pch.h"
#include "CBullet.h"

//todo 불릿 팩토리 구성 시 필요한 것들
/*
 * 1. 생성 위치를 플레이어 앞쪽에서 나오도록 지정
 * 2. 속도를 Set으로 지정
 */

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	CBullet::Release();
}

void CBullet::Initialize()
{
}

int CBullet::Update()
{
	if (m_bDestroy)
		return OBJ_DESTROY;

	__super::UpdateRect();

	return OBJ_NOEVENT;
}

void CBullet::LateUpdate()
{
	

	HandleOutOfBound(IsOutOfBound());
}

void CBullet::Render(HDC _hDC)
{
}

void CBullet::Release()
{
}

void CBullet::HandleOutOfBound(const tagObjBound tOutDir)
{

}
