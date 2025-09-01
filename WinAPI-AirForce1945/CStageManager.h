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

public: // reference getset of stage object 
	void Set_Player(list<CObject*>& _pObjectList)		{ m_pPlayer = _pObjectList.front(); }
	void Set_BulletList(list<CObject*>& _pObjectList)	{ m_pBulletList = &_pObjectList; }
	void Set_MonsterList(list<CObject*>& _pObjectList)	{ m_pMonsterList = &_pObjectList; }
	void Set_ItemList(list<CObject*>& _pObjectList)		{ m_pItemList = &_pObjectList; }

	CObject*			Get_Player()		{ return m_pPlayer; }
	list<CObject*>*		Get_BulletList()	{ return m_pBulletList; }
	list<CObject*>*		Get_MonsterList()	{ return m_pMonsterList; }
	list<CObject*>*		Get_ItemList()		{ return m_pItemList; }

public: // getter-setter
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
	CObject*		m_pPlayer;
	list<CObject*>* m_pBulletList;
	list<CObject*>* m_pMonsterList;
	list<CObject*>* m_pItemList;

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