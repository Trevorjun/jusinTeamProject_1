#include "pch.h"
#include "CStageManager.h"
#include "CAbstractFactory.h"

#include "CObject.h"
#include "CLifeItem.h"
#include "CPowerItem.h"

#include "CPlayer.h"
#include "CMonster_Curve.h"
#include "CMonster_Straight.h"
#include "CMonster_Suicide.h"
#include "CMonster_Boss.h"

CStageManager* CStageManager::m_instance = nullptr;

CStageManager* CStageManager::Get_Instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new CStageManager();
	}
	return m_instance;
}

CStageManager::CStageManager()
{
	rStageInfo ={ WINCX - 170, 0, WINCX, 70 };
	rPlayerInfo = { 0, 0, 170, 70 };

	rGameOver = {( WINCX >> 1) - 100, ( WINCY >> 1) - 100,  (WINCX >> 1) + 100, (WINCY >> 1) + 100 };
	rGameClear = { (WINCX >> 1) - 100, (WINCY >> 1) - 100,  (WINCX >> 1) + 100, (WINCY >> 1) + 100 };

	ZeroMemory(m_stages, sizeof(m_stages));
	m_iCurrentStage = 0;
	m_fLastMonsterSpawned = 0;
	m_fStageSpawnTime = 0.f;

	m_pPlayer			= nullptr;
	m_pBulletList		= nullptr;
	m_pMonsterList		= nullptr;
	m_pItemList			= nullptr;

	bGameOver = false;
	bGameClear = false;
	bBossCreated = false;
	bBossDead = false;

	ZeroMemory(tStageInfos, sizeof(tStageInfos));
	ZeroMemory(tPlayerInfos, sizeof(tPlayerInfos));
}

CStageManager::~CStageManager()
{
	Release();
}

void CStageManager::Initialize()
{
	m_stages[0] = new CStage(1, 5, 2.5f, 0.3f);
	m_stages[1] = new CStage(2, 5, 2.2f, 0.35f);
	m_stages[2] = new CStage(3, 5, 1.9f, 0.4f);
	m_stages[3] = new CStage(4, 1, 0.f, 0.f); // boss stage

	m_iCurrentStage = 0;

	m_fStageSpawnTime = m_stages[m_iCurrentStage]->Get_SpawnTime();
	m_fLastMonsterSpawned = GetTickCount64();

	bBossCreated = false;
}

void CStageManager::Update()
{
	if (bGameOver)
	{
		Handle_GameOver();
	}

	if (m_iCurrentStage == cTotalStage - 1 && bBossDead)
	{
		bGameClear = true;
	}

	if (m_stages[m_iCurrentStage]->Get_Clear())
	{
		Transition_Stage();
	}
	Create_Monster();


}

void CStageManager::LateUpdate()
{
	Check_Clear();
}

void CStageManager::Render(HDC _hDC)
{
	// TODO : 
	Rectangle(_hDC, rStageInfo.left, rStageInfo.top, rStageInfo.right, rStageInfo.bottom);
	Rectangle(_hDC, rPlayerInfo.left, rPlayerInfo.top, rPlayerInfo.right, rPlayerInfo.bottom);

	// Set current stage text info
	wsprintf(tStageInfos, TEXT("\nSTAGE : %d\nREQUIRED KILL : %d\nCURRENT KILL : %d"), 
		m_stages[m_iCurrentStage]->Get_CurrentStage(),
		m_stages[m_iCurrentStage]->Get_RequiredKillCount(),
		m_stages[m_iCurrentStage]->Get_CurrentKillCount());

	DrawText(_hDC, tStageInfos, -1, &rStageInfo, DT_VCENTER | DT_CENTER);

	// Set current player text info
	wsprintf(tPlayerInfos, TEXT("\nLIFE : %d\nPOWER : %d"),
		static_cast<CPlayer*>(m_pPlayer)->GetLife(),
		static_cast<CPlayer*>(m_pPlayer)->GetPower());

	DrawText(_hDC, tPlayerInfos, -1, &rPlayerInfo, DT_VCENTER | DT_CENTER);

}

void CStageManager::Release()
{
	for (auto& stage : m_stages)
	{
		SafeDelete(stage);
	}
}

CObject* CStageManager::Create_Monster()
{

	if (m_fLastMonsterSpawned + m_fStageSpawnTime * 1000.f < GetTickCount64())
	{
		int iX = rand() % (WINCX - 100);
		int iY = 0;

		int iRand = rand() % 4;

		CObject* pMonster = nullptr;

		if (m_iCurrentStage == cTotalStage - 1 && !bBossCreated)
		{
			pMonster = On_BossStage();
			iX = WINCX >> 1;
			m_fLastMonsterSpawned = GetTickCount64();
		}
		else if (m_iCurrentStage < cTotalStage - 1)
		{
			switch (iRand)
			{
			case 0:
				pMonster = CAbstractFactory<CMonster_Curve>::Create();
				break;
			case 1:
				pMonster = CAbstractFactory<CMonster_Straight>::Create();
				break;
			case 2: default:
				pMonster = CAbstractFactory<CMonster_Suicide>::Create();
				break;
			}
		}

		if (pMonster)
		{
			pMonster->SetPivot({ iX, iY });
			m_pMonsterList->push_back(pMonster);
			m_fLastMonsterSpawned = GetTickCount64();

			dynamic_cast<CMonster*>(m_pMonsterList->back())->SetBullet(m_pBulletList);
		}
	}
	return nullptr;
}

CObject* CStageManager::Create_Item(Vector2 _vPos)
{
	int iItemType = 2;

	int iRand = rand() % iItemType;

	CObject* pItem;
	switch (iRand)
	{
	case 0:
		pItem = new CLifeItem();
		break;
	case 1:
	default:
		pItem = new CPowerItem();
		break;
	}
	pItem->Initialize();
	pItem->SetPivot(_vPos);

	m_pItemList->push_back(pItem);

	return pItem;
}

void CStageManager::Check_Clear()
{
	if (m_stages[m_iCurrentStage]->Get_LeftMonsterCount() <= 0)
	{
		m_stages[m_iCurrentStage]->Set_Clear(true);
	}
}

void CStageManager::Transition_Stage()
{

	if (m_iCurrentStage <= cTotalStage - 1)
	{
		m_fStageSpawnTime = m_stages[m_iCurrentStage]->Get_SpawnTime();

		m_iCurrentStage++; 
	}
}

void CStageManager::Handle_GameOver()
{
	while (bGameOver && lDisplayElapsedTime + 2000 < GetTickCount64())
	{
		bGameOver = false;

		//  Release only Bullet, Monster, Item 
		for (auto iter = m_pMonsterList->begin(); iter != m_pMonsterList->end();)
		{
			SafeDelete<CObject*>((*iter));
			iter = m_pMonsterList->erase(iter);
		}
		for (auto iter = m_pBulletList->begin(); iter != m_pBulletList->end();)
		{
			SafeDelete<CObject*>((*iter));
			iter = m_pBulletList->erase(iter);
		}
		for (auto iter = m_pItemList->begin(); iter != m_pItemList->end();)
		{
			SafeDelete<CObject*>((*iter));
			iter = m_pItemList->erase(iter);
		}

		static_cast<CPlayer*>(m_pPlayer)->Revive();
	}
}

void CStageManager::Display_GameOver(HDC _hDC)
{
	if (bGameOver)
	{
		DrawText(_hDC, L"=====GAME OVER=====", -1, &rGameOver, DT_VCENTER | DT_CENTER);
	}
}

void CStageManager::Display_GameClear(HDC _hDC)
{
	DrawText(_hDC, L"=====GAME CELAR=====", -1, &rGameClear, DT_VCENTER | DT_CENTER);
}

void CStageManager::On_MonsterKilled(CObject* pKilledObj)
{
	m_stages[m_iCurrentStage]->Set_CurrentKillCount(m_stages[m_iCurrentStage]->Get_CurrentKillCount() + 1);

	// create item by Item Drop Rate
	float fRand = (rand() % 100) / 100.f;

      	if (fRand <= m_stages[m_iCurrentStage]->Get_ItemDropRate())
	{
		Create_Item(pKilledObj->GetPivot());
	}
}

void CStageManager::On_BossKilled(CObject* _pBoss)
{
}

void CStageManager::On_PlayerDead(CObject* _pPlayer)
{
 	bGameOver = true;

	Release();
	Initialize();
	lDisplayElapsedTime = GetTickCount64();
}

CObject* CStageManager::On_BossStage()
{
	for (auto iter = m_pMonsterList->begin(); iter != m_pMonsterList->end();)
	{
		SafeDelete<CObject*>((*iter));
		iter = m_pMonsterList->erase(iter);
	}

	bBossCreated = true;

	m_stages[cTotalStage - 1]->Set_CurrentKillCount(0);

	return CAbstractFactory<CMonster_Boss>::Create();
}