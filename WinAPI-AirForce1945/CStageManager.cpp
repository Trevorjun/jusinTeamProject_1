#include "pch.h"
#include "CStageManager.h"
#include "CObject.h"
#include "CLifeItem.h"
#include "CPowerItem.h"

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
	ZeroMemory(m_stages, sizeof(m_stages));
	m_iCurrentStage = 0;
	m_fLastMonsterSpawned = 0.f;
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
void CStageManager::Render()
{

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

		// TODO : add create monster logic
		// TODO : delete create item logic
		Create_Item({iX, iY});
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
