#pragma once
class CStage
{
public:
	CStage()
		: iCurrentStage(0)        // Current stage number
		, iRequiredKillCount(0)  
		, iCurrentKillCount(0)   
		, fSpawnMonsterTime(0.0f)
		, fItemDropRate(0.0f)    
		, bClear(false) {
	}
	CStage(int currentStage, int requiredKillCount, float spawnMonsterTime, float itemDropRate)
		: iCurrentStage(currentStage)
		, iRequiredKillCount(requiredKillCount)
		, iCurrentKillCount(0)
		, fSpawnMonsterTime(spawnMonsterTime)
		, fItemDropRate(itemDropRate)
		, bClear(false)
	{
	}
	~CStage() {};

public:
	int Get_CurrentStage() const { return iCurrentStage; }
	int Get_LeftMonsterCount() const { return iRequiredKillCount - iCurrentKillCount; }
	int Get_CurrentKillCount() const { return iCurrentKillCount; }
	float Get_SpawnTime() const { return fSpawnMonsterTime; }
	float Get_ItemDropRate() const { return fItemDropRate; }
	bool Get_Clear() const { return bClear; }

	void Set_CurrentStage(int _stage) { iCurrentStage = _stage; }
	void Set_CurrentKillCount(int _count) { iCurrentKillCount = _count; }
	void Set_Clear(bool _clear) { bClear = _clear; }


private:
	int iCurrentStage;

	int iRequiredKillCount;
	int iCurrentKillCount;

	float fSpawnMonsterTime;
	float fItemDropRate;

	bool bClear;

};