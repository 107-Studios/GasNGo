/***********************************************
 * Filename:  		HUD_Panel.h
 * Date:      		1/19/2011
 * Mod. Date: 		1/19/2011
 * Mod. Initials:	AD
 * Author:    		Anthony De La Rosa
 * Purpose:   		The Heads up Display
 ************************************************/
#ifndef _HUD_PANEL_H
#define _HUD_PANEL_H

#include "HUD_Object.h"
#include "Texture.h"
#include "Rect.h"
#include <D3dx9math.h>

class HUD_Panel : public HUD_Object
{
protected:
	CTexture* m_pImage;
	CRect* m_pTexRect;

public:

	HUD_Panel();

	/*****************************************************************
	* ~HUD_Panel():			destructor 
	*
	* Ins:					None
	*      		      
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	~HUD_Panel();

	/*****************************************************************
	* Init():				Initializes the panel by setting properties
	*
	* Ins:					None
	*      		      
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	void Init( CTexture* = NULL );

	/*****************************************************************
	* Update():				Will Update itself and any children it contains 
	*
	* Ins:					fTime
	*      		      
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	virtual void Update(float fTime);

	/*****************************************************************
	* Render():				Will Render the panel and any children it contains 
	*
	* Ins:					None
	*      		      
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	virtual void Render();

	/*****************************************************************
	 * Accessors
	 *****************************************************************/
	CTexture* ImageID() { return m_pImage; }
	CRect* DrawRect() { return m_pTexRect; }

	/*****************************************************************
	 * Mutators
	 *****************************************************************/
	void ImageID ( CTexture* nImage ) { m_pImage = nImage; }
	void DrawRect( CRect* pTexRect) { if (m_pTexRect) delete m_pTexRect; m_pTexRect = pTexRect; }

	__declspec(property(get= ImageID, put= ImageID)) CTexture* pBackgroundImage;
	__declspec(property(get= DrawRect, put= DrawRect)) CRect* pTextureRect;
};

#endif