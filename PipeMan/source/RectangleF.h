//////////////////////////////////////////////////////////////////////////
//	File:		RectangleF.h
//	Purpose:	Rectangle class, can be cast to a windows RECT struct.
//////////////////////////////////////////////////////////////////////////
#ifndef _RECTANGLEF_H_
#define _RECTANGLEF_H_

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//////////////////////////////////////////////////////////////////////////
//	Class Declaration
//////////////////////////////////////////////////////////////////////////
class CRectangleF
{
public:
	float m_fX;		// x coordinate of the top left corner of the rectangle
	float m_fY;		// y coordinate of the top left corner of the rectangle
	float m_fWidth;	// width of the rectangle
	float m_fHeight;	// height of the rectangle

	//////////////////////////////////////////////////////////////////////////
	//	Constructors
	//////////////////////////////////////////////////////////////////////////
	inline CRectangleF() : m_fX(0), m_fY(0), m_fWidth(0), m_fHeight(0) { }

	inline CRectangleF(const float fX,	  const float fY, 
				   const float fWidth, const float fHeight) :	m_fX(fX), m_fY(fY), 
															m_fWidth(fWidth), 
															m_fHeight(fHeight) { }

	//	casting operator overloaded to be able to cast to a windows rect structure
	inline operator RECT() const { RECT tRect = { long(m_fX), long(m_fY), long(m_fHeight), long(m_fWidth)}; return tRect; }

	// collision function
	bool Collision( CRectangleF* rectA );

	static bool Collision( CRectangleF* rectA, CRectangleF* rectB );
};
#endif