#include "pch.h"
#include "CStageManager.h"
#include "CAbstractFactory.h"

#include "CObject.h"
#include "CLifeItem.h"
#include "CPowerItem.h"

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
	rInfoBound ={ WINCX - 170, 0, WINCX, 100 };

	ZeroMemory(m_stages, sizeof(m_stages));
	m_iCurrentStage = 0;
	m_fLastMonsterSpawned = 0;
	m_fStageSpawnTime = 0.f;
	m_pObjectList = nullptr;
}

CStageManager::~CStageManager()
{
	Release();
}

void CStageManager::Initialize()
{
	m_stages[0] = new CStage(1, 7, 3.f, 0.3f);
	m_stages[1] = new CStage(2, 10, 2.5f, 0.5f);
	m_stages[2] = new CStage(3, 12, 2.1f, 0.65f);

	m_iCurrentStage = 0;

	m_fStageSpawnTime = m_stages[m_iCurrentStage]->Get_SpawnTime();
	m_fLastMonsterSpawned = GetTickCount64();
}
void CStageManager::Update()
{
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
	Rectangle(_hDC, rInfoBound.left, rInfoBound.top, rInfoBound.right, rInfoBound.bottom);

	// Set current stage text info
	wsprintf(tInfos, TEXT("\nSTAGE : %d\nREQUIRED KILL : %d\nCURRENT KILL : %d"), 
		m_stages[m_iCurrentStage]->Get_CurrentStage(),
		m_stages[m_iCurrentStage]->Get_RequiredKillCount(),
		m_stages[m_iCurrentStage]->Get_CurrentKillCount());

	DrawText(_hDC, tInfos, -1, &rInfoBound, DT_VCENTER | DT_CENTER);
}
void CStageManager::Release()
{
	// TODO : stages created need to call Safe_Delete!! 
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

		CObject* pMonster;

		switch (iRand)
		{
		case 0: 
			pMonster = CAbstractFactory<CMonster_Curve>::Create();
			break;
		case 1 :
			pMonster = CAbstractFactory<CMonster_Straight>::Create();
			break;
		case 2 :
			pMonster = CAbstractFactory<CMonster_Boss>::Create();
			break;
		case 3 :
		default:
			pMonster = CAbstractFactory<CMonster_Suicide>::Create();
			break;
		}

		pMonster->SetPivot({iX, iY});

		// TODO : inject player's pointer to monster object
		// (*m_pObjectList)[PLAYER].front()

		(*m_pObjectList)[MONSTER].push_back(pMonster);

		// Create_Item({iX, iY});
		m_fLastMonsterSpawned = GetTickCount64();
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

	(*m_pObjectList)[ITEM].push_back(pItem);

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
	m_iCurrentStage++;
	if (m_iCurrentStage >= cTotalStage)
	{
		// TODO : add game clear logic
	}
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
