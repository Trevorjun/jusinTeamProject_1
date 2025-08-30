#pragma once
#include "Define.h"

class CObject
{
public:
	CObject();
	virtual ~CObject();
public:
	const RECT&			GetRect()		{ return m_tRect; }
	const Vector2&		GetPivot()		{ return m_vPivot; }
	const Vector2&		GetSize()		{ return m_vSize; }
	const Vector2&		GetDir()		{ return m_vDir; }
	const float&		GetSpeed()		{ return m_fSpeed; }
	const bool&			GetCollision()	{ return m_bCollision; }

	void	SetPivot(const Vector2& _vPivot)	{ m_vPivot = _vPivot; }
	void	SetSize(const Vector2& _vSize)		{ m_vSize = _vSize; }
	void	SetDir(const Vector2& _vDir)		{ m_vDir = _vDir; }
	void	SetSpeed(const float& _fSpeed)		{ m_fSpeed = _fSpeed; }
	void	SetDestroy()						{ m_bDestroy = true; }
	void	SetCollision(const bool& _isCol)	{ m_bCollision = _isCol; }
public:
	virtual void		Initialize()						PURE;
	virtual int			Update()							PURE;
	virtual void		LateUpdate()						PURE;
	virtual bool		OnCollision(CObject* _pColObj)		PURE;
	virtual void		Render(HDC _hDC)					PURE;
	virtual void		Release()							PURE;

protected:
	void	UpdateRect();

	/**
	* \brief 오브젝트가 있어야 할 범위를 벗어났는지 여부를 확인하는 함수
	*
	* 주로 LateUpdate()에서 호출하며, 범위 밖으로 나갈 시 오브젝트 제거 등 다양하게 사용 가능
	*
	* \param	_iMargin
	* 경계선 판정 시 경계를 늘리거나 줄이는 데 사용. 디폴트로 사용 시 정해진 화면과 동일한 범위
	*
	* \return	tagObjBound:
	* 범위 밖으로 나갈 시 각 방향의 bool값이 true가 되는 구조체
	*/
	tagObjBound	IsOutOfBound(const int _iMargin = 0);

protected:
	RECT			m_tRect;
	Vector2			m_vPivot;
	Vector2			m_vSize;
	Vector2			m_vDir;

	float			m_fSpeed;
	bool			m_bDestroy;
private:
	bool			m_bCollision;
};

