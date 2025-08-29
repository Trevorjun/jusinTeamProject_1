#include "pch.h"
#include "CMainGame.h"
#include "CObject.h"

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

}

void CMainGame::LateUpdate()
{

}

void CObject::Render(HDC _hDC)
{
}

void CMainGame::Render()
{
	
}

void CMainGame::Release()
{

}
