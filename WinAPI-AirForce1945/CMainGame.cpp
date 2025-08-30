#include "pch.h"
#include "CMainGame.h"
#include "CObject.h"
#include "CItem.h"

#include "CCollisionManager.h"

CMainGame::CMainGame() : m_hDC(nullptr)
{
}

CMainGame::~CMainGame()
{
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
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

	// TODO : 충돌 처리 추가 여기서 해주세요
	//CCollisionManager::Collision(m_ObjectList[PLAYER], m_ObjectList[ITEM], RECT_TO_RECT);
}

void CMainGame::Render()
{
	for (auto& list : m_ObjectList)
		for (auto& obj : list)
			obj->Render(m_hDC);	
}

void CMainGame::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
		for_each(m_ObjectList[i].begin(), m_ObjectList[i].end(), SafeDelete<CObject*>);
}
