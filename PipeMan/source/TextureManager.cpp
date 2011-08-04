//////////////////////////////////////////////////////////////////////////
//	File:		TextureManager.cpp
//	Purpose:	A manager to handle the loading and unloading of textures
//////////////////////////////////////////////////////////////////////////
#include "TextureManager.h"
#include <d3dx9.h>

//////////////////////////////////////////////////////////////////////////
//	Func Name:	Initialize
//	Purpose:	Initializes the texture manager
//	In:			IDirect3DDevice9* pDevice -- pointer to the D3D device
//	Out:		None
//	Return:		bool -- true if successfully initialized
//////////////////////////////////////////////////////////////////////////
bool CTextureManager::Initialize(IDirect3DDevice9* pDevice)
{
	//	check for valid device
	if(!pDevice)
		return false;

	//	save the address of the device
	m_pDevice = pDevice;

	//	initialization complete
	return true;
}

//////////////////////////////////////////////////////////////////////////
//	Func Name:	LoadTexture
//	Purpose:	Loads a texture from a file
//	In:			const char* szFileName			-- name of the texture to be loaded
//				const unsigned long dwColorKey  -- specifies a color to avoid when
//												   drawing
//	Out:		None
//	Return:		CTexture* -- pointer to the loaded texture
//////////////////////////////////////////////////////////////////////////
CTexture* CTextureManager::LoadTexture(const char* szFileName, const unsigned long dwColorKey)
{
	//	check for invalid string
	if(!szFileName)
		return 0;

	//	create an iterator for the list of textures
	list<CTexture>::iterator iter = m_Textures.begin();

	//	iterate through the textures to see if the
	//	texture already loaded
	while(iter != m_Textures.end())
	{
		//	file names match
		if((*iter).m_szString == szFileName)
		{
			//	increment the reference count to texture
			(*iter).m_nRef++;
			//	return the address of the texture
			return &(*iter);
		}
		// continue to the next item in the list
		++iter;
	}

	//	create a texture
	CTexture tTexture(szFileName, dwColorKey);

	//	load the texture from file
	if(FAILED(D3DXCreateTextureFromFileEx(	m_pDevice,				//	the Device
											szFileName,				//	file name
											0, 0,					//	width, height
											D3DX_DEFAULT,			//	mipmap levels
											0,						//	render target
											D3DFMT_UNKNOWN,			//	file format
											D3DPOOL_DEFAULT,		//	memory pool
											D3DX_FILTER_TRIANGLE | D3DX_FILTER_DITHER,	//	texture filters
											D3DX_FILTER_BOX,		//	mipmap filer
											dwColorKey,				//	color key
											0, 0,					//	source info and pallet entry
											&tTexture.m_pTexture)))	//	pointer to the texture
	{
		//	failed to load the texture, show a message box
		//	with the name of the texture that failed to load
		char szBuffer[128];
		wsprintf(szBuffer, "Failed to load texture: %s", szFileName);
		MessageBox(0, szBuffer, "Failed to load texture", MB_OK);
		// return a null pointer
		return 0;
	}

	//	set the reference count to one
	tTexture.m_nRef = 1;

	//	get the surface description of the texture
	D3DSURFACE_DESC d3dDesc;
	tTexture.m_pTexture->GetLevelDesc(0, &d3dDesc);

	//	save the width and height of the texture
	tTexture.m_uiWidth	= d3dDesc.Width;
	tTexture.m_uiHeight = d3dDesc.Height;

	//	add the texture to the list of existing textures
	m_Textures.push_back(tTexture);

	//	return the address of the texture
	return &m_Textures.back();
}

//////////////////////////////////////////////////////////////////////////
//	Func Name:	UnloadTexture
//	Purpose:	Unloads a texture from memory if reference count reaches 0
//	In:			CTexture* pTexture -- texture to unload
//	Out:		None
//	Return:		Void
//////////////////////////////////////////////////////////////////////////
void CTextureManager::UnloadTexture(CTexture* pTexture)
{
	//	check for valid texture and reference count
	if(pTexture && --pTexture->m_nRef <= 0)
	{
		//	create an iterator for the texture list
		list<CTexture>::iterator iter = m_Textures.begin();

		//	iterate through the texutres looking for the texture
		//	being passed in
		while(iter != m_Textures.end())
		{
			//	if the addresses match
			if(&(*iter) == pTexture)
			{
				//	release the texture
				pTexture->m_pTexture->Release();
				//	set the texture pointer to null
				pTexture->m_pTexture = 0;

				//	remove the texture from the list
				m_Textures.erase(iter);
				return;
			}
			//	continue iterating through the list of textures
			++iter;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//	Func Name:	Shutdown
//	Purpose:	Shuts down the texture manager and unloads all textures
//	In:			Void
//	Out:		None
//	Return:		Void
//////////////////////////////////////////////////////////////////////////
void CTextureManager::Shutdown()
{
	//	while there are textures in the list
	while(m_Textures.size() != 0)
	{
		//	unload the texture
		UnloadTexture(&(*(m_Textures.begin())));
	}
}

