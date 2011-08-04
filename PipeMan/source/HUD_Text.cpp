#include "HUD_Text.h"
#include <wingdi.h>
#include <assert.h>

HUD_Text::HUD_Text() : HUD_Object()
{
	m_pParent= NULL;
	m_nFontID= -1;
	m_bEnabled= true;
	m_bDisplay= true;
}

HUD_Text::~HUD_Text()
{
	
}

void HUD_Text::Init( LPCTSTR szFontName, D3DCOLOR Color, DWORD dwFormat )
{
	m_szDisplayText= "text";
	m_d3dColor= Color;
	m_dwFormat= dwFormat;
	ChangeFont( szFontName );
	assert( m_nFontID != -1 );
}

void HUD_Text::Update( float fTime )
{
	HUD_Object::Update(fTime);
}

void HUD_Text::Render()
{
	HUD_Object::Render();

	RECT rBorder,
		 rParentBorder;

	rBorder.left = long(m_rObjectBox.m_fX);
	rBorder.top = long(m_rObjectBox.m_fY);
	rBorder.right = long(m_rObjectBox.m_fX + m_rObjectBox.m_fWidth);
	rBorder.bottom = long(m_rObjectBox.m_fY + m_rObjectBox.m_fHeight);

	if (Parent())
	{
		rParentBorder.left = long(m_pParent->fX) + long(m_rObjectBox.m_fX);
		rParentBorder.top = long(m_pParent->fY) + long(m_rObjectBox.m_fY);
		rParentBorder.right = long(m_pParent->fX + m_pParent->fWidth);
		rParentBorder.bottom = long(m_pParent->fY + m_pParent->fHeight);
	}

	CFontManager::GetInstance()->DrawText( m_nFontID, 
											m_szDisplayText, 
											m_pParent ? &rParentBorder : &rBorder,
											m_d3dColor,
											m_dwFormat);
}

void HUD_Text::ChangeFont( LPCTSTR szNewFont )
{
	FONTID nNewFont = CFontManager::GetInstance()->FontExists(szNewFont);
	
	if (nNewFont != -1)
		m_nFontID= nNewFont;
}

void HUD_Text::CalculateRect()
{
	RECT rCalculatedRect = RECT();

	CFontManager::GetInstance()->DrawText(  m_nFontID,
											m_szDisplayText,
											&rCalculatedRect,
											D3DCOLOR_ARGB(255, 255, 255, 255),
											DT_CALCRECT);

	m_rObjectBox.m_fWidth= float(rCalculatedRect.right) ;
	m_rObjectBox.m_fHeight= float(rCalculatedRect.bottom);
}
