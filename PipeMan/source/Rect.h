//////////////////////////////////////////////////////////////////////////
//	File:		Rect.h
//	Purpose:	Rectangle class, can be cast to a windows RECT struct.
//////////////////////////////////////////////////////////////////////////
#ifndef _RECT_H_
#define _RECT_H_

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//////////////////////////////////////////////////////////////////////////
//	Class Declaration
//////////////////////////////////////////////////////////////////////////
class CRect
{
public:
	long m_nX;		// x coordinate of the top left corner of the rectangle
	long m_nY;		// y coordinate of the top left corner of the rectangle
	long m_nWidth;	// width of the rectangle
	long m_nHeight;	// height of the rectangle

	//////////////////////////////////////////////////////////////////////////
	//	Constructors
	//////////////////////////////////////////////////////////////////////////
	inline CRect() : m_nX(0), m_nY(0), m_nWidth(0), m_nHeight(0) { }

	inline CRect(const long nX,	  const long nY, 
				   const long nWidth, const long nHeight) :	m_nX(nX), m_nY(nY), 
															m_nWidth(nWidth), 
															m_nHeight(nHeight) { }

	//	casting operator overloaded to be able to cast to a windows rect structure
	inline operator RECT() const { RECT tRect = { m_nX, m_nY, m_nHeight, m_nWidth}; return tRect; }
};

#endif