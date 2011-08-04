//////////////////////////////////////////////////////////////////////////
//	File:		Color.h
//	Purpose:	Encapsulates a DWORD (unsigned long) for color values.
//////////////////////////////////////////////////////////////////////////
#ifndef _COLOR_H_
#define _COLOR_H_

//////////////////////////////////////////////////////////////////////////
//	Preset color #defines
//////////////////////////////////////////////////////////////////////////
#define COLOR_WHITE	0xFFFFFFFF	//	white
#define COLOR_BLACK	0xFF000000	//	black
#define COLOR_RED	0xFFFF0000	//	red
#define COLOR_GREEN	0xFF00FF00	//	green
#define COLOR_BLUE	0xFF0000FF	//	blue

//////////////////////////////////////////////////////////////////////////
//	Class Declaration
//////////////////////////////////////////////////////////////////////////
class CColor
{
public:
	union
	{
		unsigned long m_dwColor;	//	32 bit color value

		struct  
		{	
			unsigned char m_uiB;	// 8 bit blue value
			unsigned char m_uiG;	// 8 bit green value
			unsigned char m_uiR;	// 8 bit red value
			unsigned char m_uiA;	// 8 bit alpha value
		};
	};

	//////////////////////////////////////////////////////////////////////////
	//	Constructors
	//////////////////////////////////////////////////////////////////////////
	CColor() : m_dwColor(0) { }
	CColor(const unsigned long dwColor) : m_dwColor(dwColor) { }
	CColor(const unsigned char uiRed, const unsigned char uiGreen, const unsigned char uiBlue, const unsigned char uiAlpha)
		: m_uiR(uiRed), m_uiG(uiGreen), m_uiB(uiBlue), m_uiA(uiAlpha) { }
	CColor(const CColor& alColor) : m_dwColor(alColor.m_dwColor) { }

	//////////////////////////////////////////////////////////////////////////
	//	Assignment operators
	//////////////////////////////////////////////////////////////////////////
	CColor& operator=(const CColor& alColor)
	{
		if(this != &alColor)
		{
			m_dwColor = alColor.m_dwColor;
		}
		return *this;
	}

	CColor& operator=(const unsigned long dwColor)
	{
		m_dwColor = dwColor;
		return *this;
	}
};

#endif