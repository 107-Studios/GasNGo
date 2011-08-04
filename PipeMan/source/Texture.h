//////////////////////////////////////////////////////////////////////////
//	File:		Texture.h
//	Purpose:	Encapsulates the directX IDirect3DTexture9 structure. Used
//				in conjunction with the texture manager.
//////////////////////////////////////////////////////////////////////////
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>
#include <d3d9.h>
#include <D3dx9math.h>

class CTexture
{
private:
	std::string			m_szString;
	unsigned int		m_uiWidth;
	unsigned int		m_uiHeight;
	D3DCOLOR			m_Color;
	IDirect3DTexture9 *	m_pTexture;
	
public:		// Accessors
	inline std::string GetName(void) const { return m_szString; }
	inline unsigned int GetWidth(void) const { return m_uiWidth; }
	inline unsigned int GetHeight(void) const { return m_uiHeight; }
	inline D3DXVECTOR2 GetCenter(void) const { return D3DXVECTOR2(float(m_uiWidth)/2.0f, float(m_uiHeight)/2.0f); } // HACK: doesn't support sprite sheet
	inline D3DCOLOR GetColor(void) const { return m_Color; }
	inline IDirect3DTexture9 * GetTexture(void) const { return m_pTexture; }

public:		// Mutators
	void SetName(std::string const _szFileName) { m_szString = _szFileName; }
	void SetWidth(unsigned int const _uiWidth) { m_uiWidth = _uiWidth; }
	void SetHeight(unsigned int const _uiHeight) { m_uiHeight = _uiHeight; }
	void SetColor(D3DCOLOR const _dwColor) { m_Color = _dwColor; }
	void SetTexture(LPDIRECT3DTEXTURE9 _pTexture) { m_pTexture = _pTexture; }

public:		// Functions
	CTexture(void)
	{
		m_uiWidth = 0;
		m_uiHeight = 0;
		m_Color = 0xFFFFFFFF;	// White
		m_pTexture = NULL;
	}

	~CTexture(void)
	{
		m_szString.clear();

		if(m_pTexture)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}

	}
};

#endif