////////////////////////////////////////////////////////////////////////////////////////////////////
//	File:		RenderManager.h
//	Creator:	Samuel Ratledge Jr.
//	Purpose:	Initializes DirectX, renders 2D images, and acts as a texture manager.
// *Note*:		Rendering order:
//				Clear
//				BeginScene
//				SpriteBegin
//				Render (every image that needs to be rendered)
//				SpriteEnd
//				EndScene
//				Line Begin
//				Line Render
//				Line End
//				Present
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _RENDERMANAGER_H_
#define _RENDERMANAGER_H_

// Includes
#include <d3d9.h>
#include <d3dx9.h>

// Libraries
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <list>
#include "HUD_Scene.h"
using std::list;


// Preprocessor
#define SAFE_RELEASE(p)		{ if(p){ p->Release(); p = NULL;} }

class CTexture;
class CRect;


class CRenderManager
{
private:	// Private Data
	IDirect3D9 *				m_pD3D9;
	IDirect3DDevice9 *			m_pDevice;
	ID3DXSprite *				m_pSpriteManager;
	ID3DXLine *					m_pLine;

	list<CTexture*>				m_arrTextures;
	D3DPRESENT_PARAMETERS		m_PresentParameters;

	HWND						m_hWnd;
	int							m_nScreenWidth;
	int							m_nScreenHeight;
	bool						m_bIsWindowed;

public:		// Accessors
	inline ID3DXSprite * GetSprite(void) const { return m_pSpriteManager; }
	inline LPDIRECT3DDEVICE9 GetDevice(void) const { return m_pDevice; }
	inline HWND WindowHandle() const { return m_hWnd; }
	inline int GetScreenWidth(void) const { return m_nScreenWidth; }
	inline int GetScreenHeight(void) const { return m_nScreenHeight; }
	inline bool GetWindowStatus(void) const { return m_bIsWindowed; }

public:		// Methods
	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		Initialize
	// Parameter(s):	HWND const _hWnd			- Handle to the window
	//					int const _nScreenWidth		- Screen Width
	//					int const _nScreenHeight	- Screen Height
	//					bool const _bWindowed		- Is the window fullscreen or not?
	// Return:			void
	// Purpose:			Creates everything required to render from DirectX API and creates instance.
	////////////////////////////////////////////////////////////////////////////////////////////////
	void Initialize(HWND const _hWnd,
					int const _nScreenWidth,
					int const _nScreenHeight,
					bool const _bWindowed = true,
					bool const _bVSync = false);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		Shutdown
	// Parameter(s):	void
	// Return:			void
	// Purpose:			Deletes all DirectX variables and instance.
	////////////////////////////////////////////////////////////////////////////////////////////////
	void Shutdown(void);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		CRenderManager
	// Parameter(s):	void
	// Return:			CRenderManager *
	// Purpose:			Returns an instance of the manager so only one is created.
	////////////////////////////////////////////////////////////////////////////////////////////////
	static CRenderManager * GetInstance(void);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		Clear
	// Parameter(s):	D3DCOLOR const _ColorKey		- Color to clear the buffer.
	// Return:			void
	// Purpose:			Clears the backbuffer (only) for 2D rendering.
	////////////////////////////////////////////////////////////////////////////////////////////////
	inline void Clear(D3DCOLOR const _ColorKey = 0) const
	{ m_pDevice->Clear(0, 0, D3DCLEAR_TARGET, _ColorKey, 1.0f, 0); }

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		BeginScene
	// Parameter(s):	void
	// Return:			void
	// Purpose:			Begins describing the scene.
	////////////////////////////////////////////////////////////////////////////////////////////////
	inline void BeginScene(void) const { m_pDevice->BeginScene(); }

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		SpriteBegin
	// Parameter(s):	void
	// Return:			void
	// Purpose:			Begin 2D Sprite rendering.
	////////////////////////////////////////////////////////////////////////////////////////////////
	inline void SpriteBegin(void) const
	{ m_pSpriteManager->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_BACKTOFRONT); }

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		Render
	// Parameter(s):	int const _nTextureID				 - Texture ID
	// 					RECT const * _rImgRect				 - Part of the image to render
	// 					D3DXVECTOR2 const _vCenter			 - Center of the image
	// 					D3DXVECTOR2 const _vPosition		 - Position on screen to render
	// 					D3DCOLOR const _ImgColor			 - Color
	//					D3DXVECTOR2 const & _vScale			 - Scaling the image
	//					float const _fLocalRotAmount		 - Rotation about the Center Position
	//					float const _fGlobalRotAmount		 - Rotation translated out by vector
	//					D3DXVECTOR2 const & _vRotationVector - Translation vector for rotation
	//					char const * _szTag					 - Tag (ie. "FPS: %d ")
	//					char const * _szString				 - String (ie. "To Render")
	//					RECT * _rFontRect,					 - Font Rect
	//					D3DCOLOR const _FontColor			 - Font color
	// Return:			void
	// Purpose:			Presents the image to the screen.
	// *Note*:			Image Renders from Top Left
	////////////////////////////////////////////////////////////////////////////////////////////////
	void Render(CTexture const * _pTexture,
				CRect const * _rImgRect					= NULL,
				D3DXVECTOR2 const & _vPosition			= D3DXVECTOR2(0.0f, 0.0f),
				D3DXVECTOR2 const & _vScale				= D3DXVECTOR2(1.0f, 1.0f),
				D3DCOLOR const _ImgColor				= 0xFFFFFFFF,
				D3DXVECTOR2 const & _vCenter			= D3DXVECTOR2(0.0f, 0.0f),
				float const _fLocalRotAmount			= 0.0f,
				float const _fGlobalRotAmount			= 0.0f,
				D3DXVECTOR2 const & _vRotationVector	= D3DXVECTOR2(0.0f, 0.0f)) const;

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		SpriteEnd
	// Parameter(s):	void
	// Return:			void
	// Purpose:			End 2D Sprite rendering.
	////////////////////////////////////////////////////////////////////////////////////////////////
	inline void SpriteEnd(void) const { m_pSpriteManager->End(); }

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		EndScene
	// Parameter(s):	void
	// Return:			void
	// Purpose:			Swaps buffers and prepares the scene for presenting.
	////////////////////////////////////////////////////////////////////////////////////////////////
	inline void EndScene(void) const { m_pDevice->EndScene(); }

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		PresentScene
	// Parameter(s):	void
	// Return:			void
	// Purpose:			Presents the backbuffer to the screen.
	////////////////////////////////////////////////////////////////////////////////////////////////
	inline void PresentScene(void) const { m_pDevice->Present(0, 0, 0, 0); }

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		LineBegin
	// Parameter(s):	void
	// Return:			void
	// Purpose:			Begins the Line.
	////////////////////////////////////////////////////////////////////////////////////////////////
	inline void LineBegin(void) const { m_pLine->Begin(); }

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		RenderLine
	// Parameter(s):	D3DXVECTOR2 const * _pPoints	- Array of points
	//					unsigned int const _uArrayCount	- Number of elements in the array
	//					D3DCOLOR const _ColorKey		- Color key
	// Return:			void
	// Purpose:			Draws a line from though all the points in the array.
	////////////////////////////////////////////////////////////////////////////////////////////////
	inline void LineRender(D3DXVECTOR2 const * _pPoints,
						   unsigned int const _uArrayCount,
						   D3DCOLOR const _ColorKey = 0xFFFFFFFF) const
	{ m_pLine->Draw(_pPoints, _uArrayCount, _ColorKey); }

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		LineEnd
	// Parameter(s):	void
	// Return:			void
	// Purpose:			Ends the Line.
	////////////////////////////////////////////////////////////////////////////////////////////////
	inline void LineEnd(void) const { m_pLine->End(); }

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		Reset
	// Parameter(s):	void
	// Return:			void
	// Purpose:			Resets the window.
	////////////////////////////////////////////////////////////////////////////////////////////////
	void Reset(bool const _bResize = false) { }

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		LoadTexture
	// Parameter(s):	char const * _szFileName	- File name to load
	// Return:			int
	// Purpose:			Returns the index where the filename is created with a color value.
	////////////////////////////////////////////////////////////////////////////////////////////////
	CTexture * LoadTexture(char const * _szFileName, D3DCOLOR const _ColorKey = 0);

	////////////////////////////////////////////////////////////////////////////////////////////////
	// Function:		UnloadTexture
	// Parameter(s):	CTexture const * _pTexture
	// Return:			void
	// Purpose:			Removes the texture passed in from the list.
	////////////////////////////////////////////////////////////////////////////////////////////////
	void UnloadTexture(CTexture const * _pTexture);

private:	// Dummy Functions
	CRenderManager(void);
	~CRenderManager(void);
	CRenderManager(CRenderManager const &);
	CRenderManager& operator=(CRenderManager const &);
};

#endif