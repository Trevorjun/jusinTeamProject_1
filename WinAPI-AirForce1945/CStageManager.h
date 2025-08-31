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
	void		Render(HDC _hDC);
	void		Release();

public: // monster
	CObject* Create_Monster();
	CObject* Create_Item(Vector2 _vPos);

	void On_MonsterKilled(CObject* _pKilledObj);
	void On_PlayerDead(CObject* _pPlayer);

public :// stage
	void Check_Clear();
	void Transition_Stage();
	void Handle_GameOver();
	void Display_GameOver(HDC _hDC);
	void Display_GameClear(HDC _hDC);

public: // singleton
	static CStageManager* Get_Instance();

public: // getter-setter
	void Set_ObjectList(list<CObject*>(*_pObjectList)[OBJ_END]) { m_pObjectList = _pObjectList; }
	bool Get_GameOver() const { return bGameOver; }
	bool Get_GameClear() const { return bGameClear; }

// member_variables
private: // stage 
	static const int cTotalStage = 3;
	CStage* m_stages[cTotalStage];
	int m_iCurrentStage;

	ULONGLONG m_fLastMonsterSpawned;
	float m_fStageSpawnTime;

	bool bGameOver;
	bool bGameClear;

private :
	static CStageManager* m_instance;
	list<CObject*> (*m_pObjectList)[OBJ_END];

private : // ui elements
	RECT rStageInfo;
	RECT rPlayerInfo;
	RECT rGameOver;
	RECT rGameClear;
	TCHAR tStageInfos[128];
	TCHAR tPlayerInfos[128];
	long long lDisplayElapsedTime;

#pragma region TEST
public :
	void Test_StageManager();
	long long Test_Call_OnPlayerDead;
	long long Test_Call_OnMonsterDead;
	bool tested = false;
#pragma endregion

};