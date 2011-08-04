////////////////////////////////////////////////////////
// File:	“CVector2f.h”
//
// Author: Eric Tjader (ET)
// 
// Purpose: This is a float vector class
////////////////////////////////////////////////////////
#ifndef _VECTOR2F_H_
#define _VECTOR2F_H_

#define M_PI 3.14159265358979323846

class CVector2f
{
	float m_fX;
	float m_fY;
public:
	//Constructors
	CVector2f(float fX = 0.0f,float fY = 0.0f);
	CVector2f(const CVector2f&);
	CVector2f& operator =(const CVector2f&);
	//Methods

	//////////////////////////////////////////////////////////////////
	// Function: “Norm”
	//
	// Purpose: Return the norm of the vector
	//////////////////////////////////////////////////////////////////
	float Norm()const;

	//////////////////////////////////////////////////////////////////
	// Function: “Normalize”
	//
	// Purpose: Return the normal of the vector
	//////////////////////////////////////////////////////////////////
	CVector2f Normalize()const;
	
	//////////////////////////////////////////////////////////////////
	// Function: “Cross”
	//
	// Purpose: Return the perpendicular vector
	//////////////////////////////////////////////////////////////////
	CVector2f Cross()const;
	
	//////////////////////////////////////////////////////////////////
	// Function: “Cross”
	//
	// Purpose: Return the perpendicular vector
	//////////////////////////////////////////////////////////////////
	float Component(const CVector2f&)const;
	
	//////////////////////////////////////////////////////////////////
	// Function: “Cross”
	//
	// Purpose: Return the perpendicular vector
	//////////////////////////////////////////////////////////////////
	CVector2f Project(const CVector2f&)const;
	
	//////////////////////////////////////////////////////////////////
	// Function: “Rotate”
	//
	// Purpose: Returns the rotation of this vector based input
	//////////////////////////////////////////////////////////////////
	CVector2f Rotate(float)const;

	//////////////////////////////////////////////////////////////////
	// Function: “Dot”
	//
	// Purpose: Returns the dot product between two vectors
	//////////////////////////////////////////////////////////////////
	float Dot(const CVector2f&) const;
	
	//////////////////////////////////////////////////////////////////
	// Function: “Angle”
	//
	// Purpose: Return the angle between this and input vector
	//////////////////////////////////////////////////////////////////
	float AngleRads(const CVector2f&)const;
	float AngleDegs(const CVector2f&)const;
	float AngleBetweenEx(const CVector2f _vector1, const CVector2f _vector2);
	//Operators
	float operator *(const CVector2f&)const;
	bool operator ==(const CVector2f&)const;
	bool operator !=(const CVector2f&)const;
	CVector2f operator +(const CVector2f&)const;
	CVector2f operator -(const CVector2f&)const;
	CVector2f operator /(float)const;
	CVector2f operator *(float)const;
	friend CVector2f operator *(float,const CVector2f&);
	void operator +=(const CVector2f&);
	void operator -=(const CVector2f&);
	void operator /=(float);
	void operator *=(float);

	////////////////////////////////////////////////
	//  Function: Accessors
	//
	//  Purpose : Returns the specified type.
	////////////////////////////////////////////////
	void Set(float fX = 0.0f,float fY = 0.0f)	{m_fX = fX;  m_fY = fY;	}
	void SetX(float fX = 0.0f)					{m_fX = fX;				}
	void SetY(float fY = 0.0f)					{m_fY = fY;				}

	////////////////////////////////////////////////
	// Function: Modifiers
	//
	//  Purpose: Modifies the specified type.
	////////////////////////////////////////////////
	float GetX()const							{return m_fX;			}
	float GetY()const							{return m_fY;			}
	int GetNX()const							{return (int)m_fX;		}
	int GetNY()const							{return (int)m_fY;		}
};
#endif