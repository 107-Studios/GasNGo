////////////////////////////////////////////////////////
// File:	“CVector2f.cpp”
//
// Author: Eric Tjader (ET)
// 
// Purpose: This is a float vector class
////////////////////////////////////////////////////////
#include "Vector2f.h"
#include <Math.h>
#include <float.h>

CVector2f::CVector2f(float fX,float fY) : m_fX(fX),m_fY(fY)
{
}
CVector2f::CVector2f(const CVector2f& v) : m_fX(v.m_fX),m_fY(v.m_fY)
{
}

CVector2f& CVector2f::operator =(const CVector2f& v)
{
	m_fX = v.m_fX;
	m_fY = v.m_fY;
	return *this;
}

CVector2f CVector2f::operator +(const CVector2f& v) const
{
	return CVector2f(m_fX + v.m_fX, m_fY + v.m_fY);
}

CVector2f CVector2f::operator -(const CVector2f& v) const
{
	return CVector2f(m_fX - v.m_fX, m_fY - v.m_fY);
}

CVector2f CVector2f::operator /(float f) const
{
	return CVector2f(m_fX / f, m_fY / f);
}

CVector2f CVector2f::operator *(float f) const
{
	return CVector2f(m_fX * f, m_fY * f);
}

CVector2f operator *(float f,const CVector2f& v)
{
	return CVector2f(v.m_fX * f, v.m_fY * f);
}

void CVector2f::operator +=(const CVector2f& v)
{
	m_fX += v.m_fX;
	m_fY += v.m_fY;
}

void CVector2f::operator -=(const CVector2f& v)
{
	m_fX -= v.m_fX;
	m_fY -= v.m_fY;
}

void CVector2f::operator /=(float f)
{
	m_fX /= f;
	m_fY /= f;
}

void CVector2f::operator *=(float f)
{
	m_fX *= f;
	m_fY *= f;
}

float CVector2f::operator *(const CVector2f& v) const
{
	return m_fX * v.m_fX + m_fY * v.m_fY;
}

bool CVector2f::operator ==(const CVector2f& v) const
{
	return (m_fX == v.m_fX && m_fY == v.m_fY);
}

bool CVector2f::operator !=(const CVector2f& v) const
{
	return !(*this == v);
}

float CVector2f::Norm() const
{
	return sqrt(m_fX * m_fX + m_fY * m_fY);
}

CVector2f CVector2f::Normalize() const
{
	float f = Norm();
	if (f != 0.0f)
	{
		return CVector2f(*this) / f;
	}
	return CVector2f(*this);
}

CVector2f CVector2f::Cross() const
{
	return CVector2f(m_fY, -m_fX);
}

float CVector2f::Component(const CVector2f& v)const
{
	return (*this) * v.Normalize();
}

CVector2f CVector2f::Project(const CVector2f& v)const
{
	return Component(v) * v.Normalize();
}

float CVector2f::AngleRads(const CVector2f& v)const
{
	float fRadians = acos( (this->operator *(v)) / (Norm() * v.Norm()) );
	if (_isnan(fRadians))
		return 0.0f;
	return fRadians;
}

float CVector2f::AngleDegs(const CVector2f& v) const
{
	return AngleRads(v) * (float)M_PI / 180.0f;
}

float CVector2f::AngleBetweenEx(const CVector2f _vector1, const CVector2f _vector2)
{
	CVector2f vecBetween = _vector2 - _vector1;

	if( vecBetween.GetX() < 0 )
	{
		// 2 * PI
		return (6.28f) + atan2(vecBetween.GetX(), -vecBetween.GetY());
	}
	else
		return atan2(vecBetween.GetX(), -vecBetween.GetY());

}

CVector2f CVector2f::Rotate(float f)const
{
	return CVector2f((cos(f) * m_fX) - (sin(f) * m_fY), (sin(f) * m_fX) + (cos(f) * m_fY));
}

float CVector2f::Dot(const CVector2f& v) const
{
	return m_fX * v.m_fX + m_fY * v.m_fY;
}


//	// Target position - ship position
//	CVector2f targetNormal = targetPosition - myPosition;
//	// Normalize
//	targetNormal = targetNormal.Normalize();
//	// Ship normal dot normalized
//	float angle = myNormal.Angle(targetNormal) * 3.14 / 180;
//	if (angle != 0.0f)
//	{
//		float rotDirection = myNormal.Cross().Dot(targetNormal);
//		float rotAmount = fRotSpeed * fElapsedTime;
//		if (rotDirection > 0)
//		{
//			rotAmount = -rotAmount;
//		}
//		myNormal = myNormal.Rotate(rotAmount);
//		fTotalRoation += rotAmount;
//	}