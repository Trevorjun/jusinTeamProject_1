#pragma once

#include "CObject.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObject* Create(CObject* pTarget = nullptr)
	{
		CObject* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObject* Create(float fX, float fY)
	{
		CObject* pObj = new T;
		pObj->Initialize();
		pObj->SetPivot({ fX,fY });

		return pObj;
	}
};
