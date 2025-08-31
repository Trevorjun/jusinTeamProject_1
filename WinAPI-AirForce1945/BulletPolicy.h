#pragma once
#include "Define.h"

using B_Info = struct tagBulletInfo
{
	Vector2 vPivot;
	Vector2 vSize;
	Vector2 vtDir;

	float fSpeed = 0.f;
	int   iCount       = 1;
	float fAngle       = 0;
};

class BulletPolicy
{
public:
	BulletPolicy();
	virtual  ~BulletPolicy() PURE;

public:
	//virtual void CreateBullet(B_Info _tBInfo, )

};
