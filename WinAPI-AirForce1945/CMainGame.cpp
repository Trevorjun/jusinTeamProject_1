#include "pch.h"
#include "CMainGame.h"
#include "CObject.h"
#include "CItem.h"

#include "CCollisionManager.h"
#include "CPlayer.h"

#include "CPowerItem.h"
#include "CLifeItem.h"

CMainGame::CMainGame() : m_hDC(nullptr)
{
}

CMainGame::~CMainGame()
{
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

#pragma region player 테스트 코드
	CObject* pObject = new CPlayer;

	m_ObjectList[OBJECT::PLAYER].push_back(pObject);

	m_ObjectList[OBJECT::PLAYER].front()->Initialize();
#pragma endregion

#pragma region 테스트 코드
	CObject* pObj = new CPowerItem();
	pObj->Initialize();

	m_ObjectList[ITEM].push_back(pObj);

	pObj = new CLifeItem();
	pObj->Initialize();

	m_ObjectList[ITEM].push_back(pObj);

#pragma endregion

}

void CMainGame::Update()
{
	bool bIsDestroy(false);
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto iter = m_ObjectList[i].begin(); iter != m_ObjectList[i].end();)
		{
			bIsDestroy = (*iter)->Update();

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
			obj->LateUpdate();

	CCollisionManager::Collision(m_ObjectList[PLAYER], m_ObjectList[ITEM], RECT_TO_RECT);
}

void CMainGame::Render()
{
	Rectangle(m_hDC, -10, -10, WINCX + 10, WINCY + 10);

	for (auto& list : m_ObjectList)
		for (auto& obj : list)
			obj->Render(m_hDC);
}

void CMainGame::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
		for_each(m_ObjectList[i].begin(), m_ObjectList[i].end()
			, [](CObject* _p) -> void {
				if (_p)
				{
					delete _p;
					_p = nullptr;
				}
			});
}
