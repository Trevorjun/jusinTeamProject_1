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
	 * \brief 총알 발사에 사용하는 발사각 제공하는 Create
	 * \param _fX		오브젝트의 m_vPivot.x
	 * \param _fY		오브젝트의 m_vPivot.y
	 * \param _fAngle	초기 발사각
	 */
	static CObject* Create(float _fX, float _fY, float _fAngle)
	{
		CObject* pObject = new T;
		pObject->Initialize();
		pObject->SetPivot({ _fX, _fY });
		pObject->SetAngle(_fAngle);

		return pObject;
	}


};
