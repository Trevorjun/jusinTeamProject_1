#pragma once
#include "Define.h"

/**
 * \brief 각 사방의 범위 밖으로 나갈 경우를 체크하기 위한 구조체
 *
 * \details
 * - bIsOutLeft:	왼쪽으로 벗어난 경우 true
 * - bIsOutRight:	오른쪽으로 벗어난 경우 true
 * - bIsOutTop:	위쪽으로 벗어난 경우 true
 * - bIsOutBottom:	아래쪽으로 벗어난 경우 true
 */
struct tagObjBound
{
	bool bIsOutLeft = false;
	bool bIsOutRight = false;
	bool bIsOutTop = false;
	bool bIsOutBottom = false;
};

class CObject
{
public:
	CObject();
	virtual ~CObject();
public:
	const OBJECT&		GetObjectType()	{ return m_eObjectType; }
	const RECT&			GetRect()		{ return m_tRect; }
	const Vector2&		GetPivot()		{ return m_vPivot; }
	const Vector2&		GetSize()		{ return m_vSize; }
	const Vector2&		GetDir()		{ return m_vDir; }
	const float&		GetAngle()		{ return m_fAngle; }
	const float&		GetSpeed()		{ return m_fSpeed; }
	const bool&			GetCollision()	{ return m_bCollision; }

	void	SetObjectType(const OBJECT& _eObjectType)	{ m_eObjectType = _eObjectType; }
	void	SetPivot(const Vector2& _vPivot)			{ m_vPivot = _vPivot; }
	void	SetSize(const Vector2& _vSize)				{ m_vSize = _vSize; }
	void	SetDir(const Vector2& _vDir)				{ m_vDir = _vDir; }
	void	SetSpeed(const float& _fSpeed)				{ m_fSpeed = _fSpeed; }
	void	SetAngle(const float& _fAngle)				{ m_fAngle = _fAngle; }
	void	SetDestroy()								{ m_bDestroy = true; }
	void	SetCollision(const bool& _isCol)			{ m_bCollision = _isCol; }
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
	* \param	_iMargin
	* 경계선 판정 시 경계를 늘리거나 줄임. 음수값은 범위를 줄이고 양수값은 범위를 늘림.
	* \return	tagObjBound:
	* 범위 밖으로 나갈 시 각 방향의 bool값이 true가 되는 구조체
	*/
	tagObjBound	IsOutOfBound(const int _iMargin = 0);

protected:
	OBJECT			m_eObjectType;
	RECT			m_tRect;
	Vector2			m_vPivot;
	Vector2			m_vSize;
	Vector2			m_vDir;

	float			m_fSpeed;
	float			m_fAngle;		//  Degree 각 (총알 발사각에 사용)
	bool			m_bDestroy;

private:
	bool			m_bCollision;
};

