/***********************************************
 * Filename:  		HUD_Text.h
 * Date:      		1/24/2011
 * Mod. Date: 		1/24/2011
 * Mod. Initials:	AD
 * Author:    		Anthony De La Rosa
 * Purpose:   		Text used on HUD
 ************************************************/
#ifndef _HUD_TEXT_H
#define _HUD_TEXT_H

#include <d3dx9core.h>
#include "FontManager.h"

#include "HUD_Object.h"

class HUD_Text : public HUD_Object
{
protected:
	FONTID m_nFontID;
	LPTSTR m_szDisplayText;
	DWORD m_dwFormat;

public:

	HUD_Text();
	~HUD_Text();

	virtual void Init( LPCTSTR, D3DCOLOR = D3DCOLOR_ARGB(255, 255, 255, 0), DWORD = DT_LEFT | DT_TOP | DT_WORDBREAK);
	virtual void Update(float fTime);
	virtual void Render();
	void CalculateRect();
	void ChangeFont( LPCTSTR );

	/*****************************************************************
	 *  Accessors
	 *****************************************************************/
	LPTSTR Text()   { return m_szDisplayText; }
	DWORD TextFormat()   { return m_dwFormat; }
	FONTID FontID()  { return m_nFontID; }

	/*****************************************************************
	 *  Mutators
	 *****************************************************************/
	void Text(LPTSTR szText)   { m_szDisplayText = szText; }
	void TextFormat(DWORD dwFormat) { m_dwFormat = dwFormat; }
	void FontID(FONTID nFontID) { m_nFontID = nFontID; }

	// Properties
	__declspec(property(get= Text, put= Text)) LPTSTR szText;
	__declspec(property(get= FontID, put= FontID)) FONTID nFont;
};
#endif