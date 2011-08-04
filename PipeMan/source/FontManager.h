#ifndef _FONTMANAGER_H_
#define _FONTMANAGER_H_

#include <vector>
#include <wtypes.h>
#include <d3dx9core.h>
using std::vector;

typedef int FONTID;

struct FontAttributes 
{
	bool m_bItalic;
	int m_nFontSize;

	FontAttributes()
	{
		m_bItalic = false;
		m_nFontSize = 32;
	}
};

struct CFont
{
	LPCTSTR m_szFontFile;
	LPCTSTR m_szFontName;
	LPD3DXFONT m_pFontObject;
	FontAttributes m_pAttributes;
};

class CFontManager
{
private:
	//////////////////////////////////////////////////////////////////////////
	//	constructors
	//////////////////////////////////////////////////////////////////////////
	CFontManager();
	~CFontManager();

	//////////////////////////////////////////////////////////////////////////
	//	disabled for singleton
	//////////////////////////////////////////////////////////////////////////
	CFontManager(const CFontManager&);
	CFontManager& operator=(const CFontManager&) { return *this; }

	LPDIRECT3DDEVICE9 m_pDevice;
	LPD3DXSPRITE m_pSprite;
	vector<CFont*> m_vFonts;

	void RecreateFont( FONTID );

public:

	static CFontManager* GetInstance()
	{
		static CFontManager instance;
		return &instance;
	}

	// methods
	void Initialize(LPDIRECT3DDEVICE9, LPD3DXSPRITE);
	void Shutdown();
	FONTID LoadFont( LPCTSTR, LPCTSTR, FontAttributes );
	FONTID FontExists( LPCTSTR );
	void ChangeFontAttributes( FONTID, FontAttributes );
	int DrawText( FONTID, LPCTSTR, LPRECT, D3DCOLOR = D3DCOLOR_ARGB(255, 255, 255, 0), DWORD = DT_TOP | DT_LEFT );
	RECT CalculateRect( FONTID, LPTSTR );
};

#endif