#pragma once
#include <cmath>

typedef struct Vector2
{
public:
	Vector2() : x(0.f), y(0.f) { };
	Vector2(const int& _x, const int& _y) : x((float)_x), y((float)_y) { };
	Vector2(const float& _x, const float& _y) : x(_x), y(_y) { };
	Vector2(const Vector2& _rhs)
	{
		x = _rhs.x;
		y = _rhs.y;
	}
	Vector2& operator=(const Vector2& _rhs)				// this = �����μ� | ��ȯ�� : this
	{
		x = _rhs.x;
		y = _rhs.y;
		return *this;
	}
	Vector2 operator+(const Vector2& _vVec)				// this + ���� | ��ȯ�� : �� ����
	{
		return Vector2(x + _vVec.x, x + _vVec.x);
	}
	Vector2 operator*(const int& _scalar)				// this * ���� | ��ȯ�� : �� ����
	{
		return Vector2( x * _scalar, y* _scalar );
	}
	Vector2 operator*(const float& _scalar)				// this * �Ǽ� | ��ȯ�� : �� ����
	{
		return Vector2( x * _scalar, y * _scalar );
	}
	Vector2& operator*=(const int& _scalar)				// this *= ���� | ��ȯ�� : this
	{
		x *= _scalar;
		y *= _scalar;
		return *this;
	}
	Vector2& operator*=(const float& _scalar)			// this *= �Ǽ� | ��ȯ�� : this
	{
		x *= _scalar;
		y *= _scalar;
		return *this;
	}
	Vector2& operator-=(const Vector2& _vVec)			// this -= ���� | ��ȯ�� : this
	{
		x -= _vVec.x;
		y -= _vVec.y;
		return *this;
	}
	Vector2& operator+=(const Vector2& _vVec)			// this += ���� | ��ȯ�� : this
	{
		x += _vVec.x;
		y += _vVec.y;
		return *this;
	}
	
	const float GetSquared() const						// this Vec2 x����, y���� | ��ȯ 
	{
		return x * x + y * y;
	}
	Vector2 GetNomalized() const						// this�� x, y�� ���� ��Ÿ��� ���� ����
	{													// x, y�� �밢��(����)�� ������
		return Nomalize(*this);
	}
	Vector2& Rotate(const float& _fDegree)
	{
		float fRad = _fDegree * 3.14159f / 180.f * -1.f;
		float fCosx = cosf(fRad);
		float fSiny = sinf(fRad);

		float fHypot = sqrtf(GetSquared());
		x = fCosx * fHypot;
		y = fSiny * fHypot;
		return *this;
	}

	static Vector2 Nomalize(const Vector2& _vVec);		// _vVec�� ���� �밢�� ��ȯ(���� �Լ�)

public:
	float x;
	float y;

	static const Vector2 UnitX;							// (1.f, 0.f)
	static const Vector2 UnitY;							// (0.f, 1.f)
	static const Vector2 Zero;							// (0.f, 0.f)
	static const Vector2 One;							// (1.f, 1.f)
};


