#include "pch.h"
#include "CMainGame.h"
#include "CObject.h"
#include "CItem.h"

#include "CCollisionManager.h"
#include "CPlayer.h"

#include "CPowerItem.h"
#include "CLifeItem.h"

#include "CAbstractFactory.h"
#include "CMonster_Curve.h"
#include "CMonster_Straight.h"
#include "CMonster_Suicide.h"
#include "CNormalBullet.h"
#include "CMonster_Boss.h"

CMainGame::CMainGame()
	: m_hDC(nullptr)
{}

CMainGame::~CMainGame()
{}

void CMainGame::Initialize()
{
	srand(static_cast<unsigned>(time(NULL)));
	m_hDC = GetDC(g_hWnd);

	CStageManager::Get_Instance()->Initialize();
	CStageManager::Get_Instance()->Set_ObjectList(&m_ObjectList);

#pragma region player 테스트 코드
	CObject* pPlayer = new CPlayer;

	m_ObjectList[OBJECT::PLAYER].push_back(pPlayer);

	m_ObjectList[OBJECT::PLAYER].front()->Initialize();

	dynamic_cast<CPlayer*>(m_ObjectList[OBJECT::PLAYER].front())
		->Set_Bullet(&m_ObjectList[OBJECT::BULLET]);

#pragma endregion

	//#pragma region bullet 테스트 코드
	//	CObject* pBullet = new CNormalBullet;
	//
	//	m_ObjectList[OBJECT::BULLET].push_back(pBullet);
	//
	//	m_ObjectList[OBJECT::BULLET].front()->Initialize();
	//#pragma endregion

#pragma region 테스트 코드
	//CObject* pObj = new CPowerItem();
	//pObj->Initialize();

	//m_ObjectList[ITEM].push_back(pObj);

	//pObj = new CLifeItem();
	//pObj->Initialize();

	//m_ObjectList[ITEM].push_back(pObj);

}

void CMainGame::Update()
{
	CStageManager::Get_Instance()->Update();

	bool bIsDestroy(false);
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjectList[i].begin(); iter != m_ObjectList[i].end();)
		{
			bIsDestroy = (*iter)->Update();

#pragma region 테스트 코드(monster에 player 주소 가지고 오기)
			if (i == MONSTER)
			{
				dynamic_cast<CMonster*>(*iter)->setPlayerVXY(m_ObjectList[PLAYER].front());
			}
#pragma endregion

			if (bIsDestroy)
			{
				SafeDelete<CObject*>((*iter));
				iter = m_ObjectList[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CMainGame::LateUpdate()
{
	for (auto& list : m_ObjectList)
		for (auto& obj : list)	
		{
			CMonster* pMonster = dynamic_cast<CMonster*>(obj);
			if (pMonster)
			{
				pMonster->SetBullet(&m_ObjectList[BULLET]);
			}
			obj->LateUpdate();
		}

	CStageManager::Get_Instance()->Check_Clear();

	CCollisionManager::Collision(m_ObjectList[PLAYER], m_ObjectList[ITEM], CIRCLE_TO_RECT);
	CCollisionManager::Collision(m_ObjectList[PLAYER], m_ObjectList[MONSTER], CIRCLE_TO_CIRCLE);
	CCollisionManager::Collision(m_ObjectList[BULLET], m_ObjectList[MONSTER], CIRCLE_TO_CIRCLE);
}

void CMainGame::Render()
{
	Rectangle(m_hDC, -10, -10, WINCX + 10, WINCY + 10);

	if (CStageManager::Get_Instance()->Get_GameOver())
	{
		CStageManager::Get_Instance()->Display_GameOver(m_hDC);
		return;
	}
	if (CStageManager::Get_Instance()->Get_GameClear())
	{
		CStageManager::Get_Instance()->Display_GameClear(m_hDC);
		return;
	}

	for (auto& list : m_ObjectList)

		for (auto& obj : list)
			obj->Render(m_hDC);

	CStageManager::Get_Instance()->Render(m_hDC);
}

void CMainGame::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjectList[i].begin(), m_ObjectList[i].end()
				 , [](CObject* _p) -> void
				 {
					 if (_p)
					 {
						 delete _p;
						 _p = nullptr;
					 }
				 });
	}

	CStageManager::Get_Instance()->Release();

	if (CStageManager::Get_Instance())
		delete CStageManager::Get_Instance();
}
