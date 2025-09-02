#pragma once
#include "CObject.h"

template <typename T>
class CAbstractFactory
{
public:
	// 생성 및 Initialize만 수행하는 기본 Create
	static CObject* Create()
	{
		CObject* pObject = new T;
		pObject->Initialize();

		return pObject;
	}

	/**
	 * \brief 초기 Pivot을 지정하는 Create
	 * \param _fX		오브젝트의 m_vPivot.x
	 * \param _fY		오브젝트의 m_vPivot.y
	 */
	static CObject* Create(float _fX, float _fY)
	{
		CObject* pObject = new T;
		pObject->Initialize();
		pObject->SetPivot({ _fX, _fY });

		return pObject;
	}

	/**
	 * \brief 총알 발사에 사용하는 투사체 속도, 발사각 제공하는 Create
	 * \param _fX			오브젝트의 m_vPivot.x
	 * \param _fY			오브젝트의 m_vPivot.y
	 * \param _fSpeed		발사 속도
	 * \param _fShootDeg	발사각 (90도 : 위, 270도 : 아래)
	 */
	static CObject* Create(float _fX, float _fY, OBJECT_TYPE _eObjectType, float _fSpeed = 10.f, float _fShootDeg = 90.f)
	{
		CObject* pObject = new T;
		pObject->Initialize();
		pObject->SetPivot({ _fX, _fY });
		pObject->SetAngle(_fShootDeg);
		pObject->SetSpeed(_fSpeed);
		pObject->SetObjectType(_eObjectType);

		return pObject;
	}
};
