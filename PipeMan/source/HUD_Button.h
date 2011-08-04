/***********************************************
 * Filename:  		HUD_Button.h
 * Date:      		2/3/2011
 * Mod. Date: 		2/3/2011
 * Mod. Initials:	AD
 * Author:    		Anthony De La Rosa
 * Purpose:   		HUD buttons to enable functions?
 ************************************************/
#ifndef _HUD_BUTTON_H
#define _HUD_BUTTON_H

#include "HUD_Panel.h"
#include "HUD_Text.h"
#include "HUD_Tooltip.h"

class HUD_Button : public HUD_Panel
{
protected:
	HUD_Text m_ButtonText;
	HUD_Tooltip m_ToolTip;

public:
	
	HUD_Button();
	~HUD_Button();

	virtual void Init();
	virtual void Update(float fTime);
	virtual void Render();

	/*****************************************************************
	 *  Accessors
	 *****************************************************************/
	D3DCOLOR TextColor() { return m_ButtonText.Color(); }
	HUD_Tooltip* Tooltip() { return &m_ToolTip; }
	LPTSTR Text() { return m_ButtonText.szText; }
	FONTID Font() { return m_ButtonText.nFont; }

	/*****************************************************************
	 *  Mutators
	 *****************************************************************/
	void TextColor(D3DCOLOR Color) { m_ButtonText.Color(Color); }
	void Tooltip(HUD_Tooltip pToolTip) { m_ToolTip = pToolTip; }
	void Text( LPTSTR szText ) { m_ButtonText.szText = szText; }
	void Font( FONTID nFont ) { m_ButtonText.nFont = nFont; }

	// properties
	__declspec(property(get= TextColor, put= TextColor)) D3DCOLOR textcolor;
	__declspec(property(get= Text, put= Text)) LPCTSTR text;
};
#endif