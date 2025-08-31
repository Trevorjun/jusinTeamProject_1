#pragma once

#include "CStage.h"
#include "Define.h"

class CObject;

class CStageManager
{
public:
	CStageManager();
	~CStageManager();

public:
	void		Initialize();
	void		Update();
	void		LateUpdate();
	void		Render();
	void		Release();

public:
	CObject* Create_Monster();
	CObject* Create_Item(Vector2 _vPos);

	void On_MonsterKilled(CObject* _pKilledObj);

	void Check_Clear();
	void Transition_Stage();

	list<CObject*>* GetMonsterList() { return m_pMonsterList; }

public :
	static CStageManager* Get_Instance();
	void Set_Player(list<CObject*>& _pObjectList) { m_pPlayer = _pObjectList.front(); }
	void Set_BulletList(list<CObject*>& _pObjectList) { m_pBulletList = &_pObjectList; }
	void Set_MonsterList(list<CObject*>& _pObjectList) { m_pMonsterList = &_pObjectList; }
	void Set_ItemList(list<CObject*>& _pObjectList) { m_pItemList = &_pObjectList; }

private:
	static const int cTotalStage = 3;
	CStage* m_stages[cTotalStage];
	int m_iCurrentStage;

	ULONGLONG m_fLastMonsterSpawned;
	float m_fStageSpawnTime;

private :
	static CStageManager* m_instance;
	CObject*		m_pPlayer;
	list<CObject*>* m_pBulletList;
	list<CObject*>* m_pMonsterList;
	list<CObject*>* m_pItemList;
};