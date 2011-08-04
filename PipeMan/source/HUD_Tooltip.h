/***********************************************
 * Filename:  		HUD_Tooltip.h
 * Date:      		1/24/2011
 * Mod. Date: 		1/24/2011
 * Mod. Initials:	AD
 * Author:    		Anthony De La Rosa
 * Purpose:   		used for little info about objects
 ************************************************/
#ifndef _HUD_TOOLTIP_H
#define _HUD_TOOLTIP_H

#include "HUD_Text.h"
#include "HUD_Panel.h"
#include "RectangleF.h"

class HUD_Tooltip
{
protected:
	HUD_Object* m_pParent;
	HUD_Text m_txtHeader;
	HUD_Text m_txtBody;
	HUD_Panel m_Panel;
	CRectangleF m_rBorder;
	bool m_bEnabled;
	bool m_bDisplay;
	bool m_bAutoResize;

private:
	void Resize();

public:

	HUD_Tooltip();
	~HUD_Tooltip();

	void Init();
	void Update(float fTime);
	void Render();

	/*****************************************************************
	 *  Accessors
	 *****************************************************************/
	bool Enabled() { return m_bEnabled; }
	bool Display() { return m_bDisplay; }
	bool AutoResize() { return m_bAutoResize; }
	HUD_Object* Parent() { return m_pParent; }

	float xPosition() { return m_rBorder.m_fX; }
	float yPosition() { return m_rBorder.m_fY; }
	float Width() { return m_rBorder.m_fWidth; }
	float Height() { return m_rBorder.m_fHeight; }

	/*****************************************************************
	 *  Mutators
	 *****************************************************************/
	void Enabled( bool bEnable ) { m_bEnabled = bEnable; }
	void Display( bool bDisplay) { m_bDisplay = bDisplay; }
	void AutoResize( bool bAutoResize ) { m_bAutoResize = bAutoResize; }
	void Parent( HUD_Object* pParent ) { m_pParent = pParent; }

	void xPosition( float xPos ) { m_rBorder.m_fX = xPos; }
	void yPosition( float yPos ) { m_rBorder.m_fY = yPos; }
	void Width( float width )	{ m_rBorder.m_fWidth = width; }
	void Height( float height ) { m_rBorder.m_fHeight = height; }

	void HeaderText( LPTSTR szText ) { m_txtHeader.Text(szText); if (m_bAutoResize) Resize();}
	void HeaderColor( D3DCOLOR Color ) { m_txtHeader.Color(Color); }
	void HeaderFont( FONTID nFontID ) { m_txtHeader.FontID(nFontID); }
	void HeaderFormat( DWORD dwFormat ) { m_txtHeader.TextFormat(dwFormat); }

	void BodyText( LPTSTR szText )	{ m_txtBody.Text(szText); if (m_bAutoResize) Resize();}
	void BodyColor( D3DCOLOR Color ) { m_txtBody.Color(Color); }
	void BodyFont( FONTID nFontID )  { m_txtBody.FontID(nFontID); }
	void BodyFormat(DWORD dwFormat)  { m_txtBody.TextFormat(dwFormat); }
};
#endif