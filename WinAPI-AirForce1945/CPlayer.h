#pragma once
#include "CObject.h"

class CPlayer final : public CObject
{
public:
	CPlayer();
	~CPlayer() override;

public:
	void Initialize() override;
	int  Update() override;
	void LateUpdate() override;
	void Render(HDC _hDC) override;
	void Release() override;

public:
	int   GetLife() const { return m_iLife; }
	int   GetPower() const { return m_iPower; }
	bool  GetIsAlive() const { return m_bIsAlive; }
	bool  GetIsInvincible() const { return m_bIsInvincible; }
	DWORD GetAttackCooldown() const { return m_dwAttackCooldown; }
	DWORD GetLastAttackTime() const { return m_dwLastAttackTime; }

	// SetLife는 플레이어 생성, 부활 등에 사용할 것. Life 추가는 AddLife 함수 사용 바람
	void SetLife(const int _iLife) { m_iLife = _iLife; }
	// SetPower는 플레이어 생성, 부활 등에 사용할 것. Power 추가는 AddPower 함수 사용 바람
	void SetPower(const int _iPower) { m_iLife = _iPower; }
	void SetIsAlive(const bool _bIsAlive) { m_bIsAlive = _bIsAlive; }
	void SetIsInvincible(const bool _bIsInvincible) { m_bIsInvincible = _bIsInvincible; }
	void SetAttackCooldown(const DWORD _dwAttackCooldown) { m_dwAttackCooldown = _dwAttackCooldown; }
	void SetLastAttackTime(const DWORD _dwLastAttackTime) { m_dwLastAttackTime = _dwLastAttackTime; }

public:
	// AddLife는 플레이어 Life 추가시 사용할 것. 플레이어 생성, 부활 등은 SetLife 함수 사용 바람
	void AddLife(const int _iLifeChange);
	// AddPower는 플레이어 Power 추가시 사용할 것. 플레이어 생성, 부활 등은 SetPower 함수 사용 바람
	void AddPower(const int _iPowerChange);

private:
	void Key_Input();
	// 화면 밖으로 나가지 않게 만드는 기능의 함수
	void HandleOutOfRange(const OUTOFRANGE_DIR eOutDir);

private:
	list<CObject*>* m_pBullet;
	list<CObject*>* m_pShield;

	int m_iLife;
	int m_iPower;
	int m_iMaxPower;
	// int m_iScore;			// 사용 미정

	bool m_bIsAlive;
	bool m_bIsInvincible;		// 피격, 부활 시 true -> 무적

	DWORD m_dwAttackCooldown;	// 공격간 딜레이 설정
	DWORD m_dwLastAttackTime;	// 마지막 공격 시간 저장
};
