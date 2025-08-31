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

	list<CObject*>* GetMonsterList() { return m_pObjectList[MONSTER]; }

public :
	static CStageManager* Get_Instance();
	void Set_ObjectList(list<CObject*> (*_pObjectList)[OBJ_END]) { m_pObjectList = _pObjectList; }

private:
	static const int cTotalStage = 3;
	CStage* m_stages[cTotalStage];
	int m_iCurrentStage;

	ULONGLONG m_fLastMonsterSpawned;
	float m_fStageSpawnTime;

private :
	static CStageManager* m_instance;
	list<CObject*> (*m_pObjectList)[OBJ_END];
};