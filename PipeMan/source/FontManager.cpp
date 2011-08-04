#include "FontManager.h"
#include <assert.h>


CFontManager::CFontManager()
{

}

CFontManager::~CFontManager()
{

}

void CFontManager::Initialize( LPDIRECT3DDEVICE9 pDevice, LPD3DXSPRITE pSprite)
{
	assert( pDevice != NULL );
	assert( pSprite != NULL );

	m_pDevice = pDevice;
	m_pSprite = pSprite;
}

void CFontManager::Shutdown()
{
	vector<CFont*>::iterator pPosition = m_vFonts.begin();

	for (; pPosition != m_vFonts.end(); pPosition++)
	{
		(*pPosition)->m_pFontObject->Release();
		delete (*pPosition);
	}

	m_vFonts.clear();
}

FONTID CFontManager::LoadFont( LPCTSTR szFontFile, LPCTSTR szFontName, FontAttributes pAttributes )
{
	FONTID nResult = FontExists(szFontName);
	if (nResult != -1)
		return nResult;

	CFont* pNewObject = new CFont();
	pNewObject->m_szFontFile = szFontFile;
	pNewObject->m_szFontName = szFontName;
	pNewObject->m_pAttributes = pAttributes;

	assert(0 != AddFontResourceEx(pNewObject->m_szFontFile, FR_PRIVATE, 0) );
	D3DXCreateFont( m_pDevice,
		pNewObject->m_pAttributes.m_nFontSize, 0,
		FW_NORMAL,
		1,
		pNewObject->m_pAttributes.m_bItalic,
		DEFAULT_CHARSET,
		OUT_DEVICE_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE | DEFAULT_PITCH,
		pNewObject->m_szFontName,
		&pNewObject->m_pFontObject );

	m_vFonts.push_back(pNewObject);

	return m_vFonts.size() - 1;
}

FONTID CFontManager::FontExists( LPCTSTR szFontName)
{
	vector<CFont*>::iterator position = m_vFonts.begin();
	int nCurrent = 0;

	for ( ; position != m_vFonts.end(); position++)
	{
		if ( (*position)->m_szFontName == szFontName )
			return nCurrent;

		nCurrent++;
	}

	return -1;
}

int CFontManager::DrawText( FONTID nID, LPCTSTR szText, LPRECT pRect, D3DCOLOR d3dColor, DWORD dwFormat )
{
	vector<CFont*>::iterator pPosition = m_vFonts.begin();

	pPosition += nID;

	return (*pPosition)->m_pFontObject->DrawTextA(m_pSprite,
											szText,
											strlen(szText),
											pRect,
											dwFormat,
											d3dColor);
}

void CFontManager::RecreateFont( FONTID nID )
{
	m_vFonts[nID]->m_pFontObject->Release();
	m_vFonts[nID]->m_pFontObject = NULL;

	D3DXCreateFont( m_pDevice,
		m_vFonts[nID]->m_pAttributes.m_nFontSize, 0,
		FW_NORMAL,
		1,
		m_vFonts[nID]->m_pAttributes.m_bItalic,
		DEFAULT_CHARSET,
		OUT_DEVICE_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE | DEFAULT_PITCH,
		m_vFonts[nID]->m_szFontName,
		&m_vFonts[nID]->m_pFontObject );
}

void CFontManager::ChangeFontAttributes( FONTID nID, FontAttributes pAttributes)
{
	m_vFonts[nID]->m_pAttributes = pAttributes;
	RecreateFont(nID);
}

RECT CFontManager::CalculateRect( FONTID nFontID, LPTSTR szString)
{
	RECT rTempRect = RECT();

	if (szString == NULL)
		return rTempRect;

	DrawText(nFontID, szString, &rTempRect, D3DCOLOR_ARGB(255, 255, 255, 255), DT_CALCRECT);

	return rTempRect;
}
