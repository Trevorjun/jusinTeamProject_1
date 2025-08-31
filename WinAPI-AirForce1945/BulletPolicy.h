#pragma once

struct tagBulletInfo
{
	Vector2 vBulletPivot;
	Vector2 vBulletSize;
	Vector2 vBulletDir;

	float fBulletSpeed = 0.f;
};

class BulletPolicy
{
};
