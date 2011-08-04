////////////////////////////////////////////////////////////////////////////////////////////////////
//	File:		RenderManager.h
//	Creator:	Samuel Ratledge Jr.
//	Purpose:	Initializes DirectX and renders 2D images. Also holds a list of textures.
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "RenderManager.h"
#include "Texture.h"
#include "Rect.h"
#include <D3dx9math.h>


CRenderManager::CRenderManager(void)
{
	m_pD3D9				= NULL;
	m_pDevice			= NULL;
	m_pSpriteManager	= NULL;
	m_pLine				= NULL;
	m_arrTextures.clear();
	memset(&m_PresentParameters, NULL, sizeof(D3DPRESENT_PARAMETERS));
	
	m_hWnd				= 0;
	m_nScreenWidth		= 0;
	m_nScreenHeight		= 0;
	m_bIsWindowed		= false;
}

CRenderManager::~CRenderManager(void)
{
	Shutdown();
}

CRenderManager * CRenderManager::GetInstance(void)
{
	static CRenderManager Instance;
	return &Instance;
}

void CRenderManager::Initialize(HWND const _hWnd, int const _nScreenWidth, int const _nScreenHeight, bool const _bWindowed, bool const _bVSync)
{
	if(!_hWnd)
	{
		MessageBox(0, "Handle to the window is invalid.", "Initialize", MB_OK);
		return;
	}

	if(m_pD3D9)
	{
		MessageBox(0, "CRenderManager has already been initialized.", "Initialize", MB_OK);
		return;
	}

	m_hWnd			= _hWnd;
	m_nScreenWidth  = _nScreenWidth;
	m_nScreenHeight = _nScreenHeight;
	m_bIsWindowed	= _bWindowed;

	// Create the d3d object
	if(NULL == (m_pD3D9 = Direct3DCreate9(D3D_SDK_VERSION)))
	{	
		MessageBox(0, "Failed to create the D3D Object.", "Initialize", MB_OK);
		return;
	}

	// Present Parameters
 	m_PresentParameters.hDeviceWindow			= m_hWnd;
 	m_PresentParameters.BackBufferWidth			= m_nScreenWidth;
 	m_PresentParameters.BackBufferHeight		= m_nScreenHeight;
 	m_PresentParameters.Windowed				= m_bIsWindowed;
	m_PresentParameters.PresentationInterval	= D3DPRESENT_INTERVAL_IMMEDIATE;
	m_PresentParameters.SwapEffect				= D3DSWAPEFFECT_DISCARD;

	// Create the Device
	if(FAILED(m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT,
									D3DDEVTYPE_HAL,
									m_hWnd,
									D3DCREATE_HARDWARE_VERTEXPROCESSING,
									&m_PresentParameters,
									&m_pDevice)))
	{
		MessageBox(0, "Failed to create the Device.", "Initialize", MB_OK);
		return;
	}

	// Create the Sprite
	if(FAILED(D3DXCreateSprite(m_pDevice, &m_pSpriteManager)))
	{
		MessageBox(0, "Failed to create the Sprite Manager.", "Initialize", MB_OK);
		return;
	}

	// Create the line
	if(FAILED(D3DXCreateLine(m_pDevice, &m_pLine)))
		MessageBox(0, "Failed to create Line.", "Initialize", MB_OK);
}

void CRenderManager::Shutdown(void)
{
	// Released in opposite order of initialization
	list<CTexture*>::iterator Iter;
	for(Iter = m_arrTextures.begin(); Iter != m_arrTextures.end(); ++Iter)
		delete (*Iter);

	m_arrTextures.clear();

	SAFE_RELEASE(m_pLine);
	SAFE_RELEASE(m_pSpriteManager);
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pD3D9);
}

void CRenderManager::Render(CTexture const * _pTexture,
							CRect const * _rImgRect,
							D3DXVECTOR2 const & _vPosition,
							D3DXVECTOR2 const & _vScale,
							D3DCOLOR const _ImgColor,
							D3DXVECTOR2 const & _vCenter,
							float const _fLocalRotAmount,
							float const _fGlobalRotAmount,
							D3DXVECTOR2 const & _vRotationVector) const
{
	RECT _rRect;

	if(_rImgRect)
	{
		_rRect.top		= _rImgRect->m_nY;
		_rRect.bottom	= _rImgRect->m_nY + _rImgRect->m_nHeight;
		_rRect.left		= _rImgRect->m_nX;
		_rRect.right	= _rImgRect->m_nX + _rImgRect->m_nWidth;
	}

	/* NOTE */
	// Expensive call, transforming even when values are 0.

	/* NOTE */
	// Don't need to call identity on any of the matrices. Once the DirectX function gets call (Scale, Rotate, Translate),
	// the matrix becomes identity with the applied values from the function.
	D3DXMATRIX mTransform;

	// Order (SRT -> Scale, Rotate, Translate)
	// Scale
	D3DXMATRIX mScale;
 	D3DXMatrixScaling(&mScale, _vScale.x, _vScale.y, 0.0f);

	// Local Rotation
	D3DXMATRIX mLocalRotation;
	D3DXMATRIX mRotationTranslate;
	D3DXMatrixTranslation(&mRotationTranslate, -_vCenter.x, -_vCenter.y, 0.0f);
 	D3DXMatrixRotationAxis(&mLocalRotation, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), _fLocalRotAmount);
	mLocalRotation = mRotationTranslate * mLocalRotation;

	// Translate
	D3DXMATRIX mTranslation;
	D3DXMatrixTranslation(&mTranslation, (_vPosition.x + _vCenter.x), (_vPosition.y + _vCenter.y), 0.0f);

	// Global Rotation
	D3DXMATRIX mGlobalRotation;
	D3DXMatrixTranslation(&mRotationTranslate, _vRotationVector.x, _vRotationVector.y, 0.0f);
	D3DXMatrixRotationAxis(&mGlobalRotation, &D3DXVECTOR3(0.0f, 0.0f, 1.0f), _fGlobalRotAmount);
	mGlobalRotation = mRotationTranslate * mGlobalRotation;

	// Multiply all the matrices together
	mTransform = mScale * mLocalRotation * mGlobalRotation * mTranslation;

	// Set the transform to move the position, draw, then reset back to origin
	m_pSpriteManager->SetTransform(&mTransform);
	m_pSpriteManager->Draw(_pTexture->GetTexture(), _rImgRect ? (&_rRect) : NULL, 0, 0, _ImgColor);

	// Now reset the picture back to top left of window
	D3DXMatrixIdentity(&mTransform);
	m_pSpriteManager->SetTransform(&mTransform);
}

CTexture * CRenderManager::LoadTexture(char const * _szFileName, D3DCOLOR const _ColorKey)
{
	if(NULL == _szFileName)
	{
		MessageBox(0, "Filename was invalid.", "LoadTexture", MB_OK);
		return NULL;
	}

	// Look if the texture has already been loaded
	list<CTexture*>::iterator IterText = m_arrTextures.begin();
	for( ; IterText != m_arrTextures.end(); ++IterText)
	{
		if(0 == strcmp((*IterText)->GetName().c_str(), _szFileName))
			return (*IterText);
	}

	// Look for the first available slot where the struct is NULL
	for(IterText = m_arrTextures.begin(); IterText != m_arrTextures.end(); ++IterText)
	{
		if(NULL == (*IterText))
		{
			IDirect3DTexture9 * pTexture = NULL;

			// Set the texture
			if(FAILED(D3DXCreateTextureFromFileEx(m_pDevice, _szFileName, 0, 0, 0, 0, D3DFMT_UNKNOWN,
												  D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
												  _ColorKey, 0, 0, &pTexture)))
			{
				MessageBox(0, "Failed to create texture.", "LoadTexture", MB_OK);
				return NULL;
			}

			CTexture * pNew = new CTexture();

			std::string szName = _szFileName;
			pNew->SetName(szName);
			pNew->SetTexture(pTexture);
			pNew->SetColor(_ColorKey);

			D3DSURFACE_DESC description;
			pTexture->GetLevelDesc(0, &description);
			pNew->SetWidth(description.Width);
			pNew->SetHeight(description.Height);
			pNew->SetTexture(pTexture);
			(*IterText) = pNew;

			return (*IterText);
		}
	}

	IDirect3DTexture9 * pTexture = NULL;

	// Set the texture
	if(FAILED(D3DXCreateTextureFromFileEx(m_pDevice, _szFileName, 0, 0, 0, 0, D3DFMT_UNKNOWN,
										  D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
										  _ColorKey, 0, 0, &pTexture)))
	{
		MessageBox(0, "Failed to create texture.", "LoadTexture", MB_OK);
		return NULL;
	}

	CTexture * pNew = new CTexture();

	std::string szName = _szFileName;
	pNew->SetName(szName);
	pNew->SetTexture(pTexture);
	pNew->SetColor(_ColorKey);

	D3DSURFACE_DESC description;
	pTexture->GetLevelDesc(0, &description);
	pNew->SetWidth(description.Width);
	pNew->SetHeight(description.Height);
	pNew->SetTexture(pTexture);

	m_arrTextures.push_back(pNew);
	return pNew;
}

void CRenderManager::UnloadTexture(CTexture const * _pTexture)
{
	list<CTexture*>::iterator IterText = m_arrTextures.begin();
	for( ; IterText != m_arrTextures.end(); ++IterText)
	{
		if((*IterText) == _pTexture)
		{
			delete (*IterText);
			m_arrTextures.remove( (*IterText) );
 			return; //(*IterText) = NULL;
		}
	}
}