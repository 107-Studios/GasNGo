/***********************************************
 * Filename:  		HUD_Object.h
 * Date:      		1/20/2011
 * Mod. Date: 		1/20/2011
 * Mod. Initials:	AD
 * Author:    		Anthony De La Rosa
 * Purpose:   		Base class from which all HUD 
 *					objects will inherit
 ************************************************/
#ifndef _HUD_OBJECT_H
#define _HUD_OBJECT_H

#include <list>
#include <wtypes.h>
#include <d3d9types.h>
#include "RectangleF.h"
using std::list;

#define MAX_THREADS 2
#define SPACING 5.0f

#include <vector>
#include <d3dx9math.h>
using std::vector;

enum { DOCK_NONE = 0, DOCK_LEFT = 1, DOCK_RIGHT = 2, DOCK_TOP = 4, DOCK_BOTTOM = 8, DOCK_CENTER = 16};
typedef char DOCK_SETTING;

class HUD_Object
{
protected:
	CRectangleF m_rObjectBox,
				m_rDisplayBox;

	vector<HANDLE> m_vThreads;

	D3DCOLOR m_d3dColor;

	HUD_Object* m_pParent;

	bool m_bEnabled,
		m_bDisplay,
		m_bMouseCollide,
		m_bAnimating;

	DOCK_SETTING m_eDock;

	D3DXVECTOR2 m_vScale;
	bool m_bAutoScale;

public:

	HUD_Object();
	virtual ~HUD_Object();

	virtual void Init();
	virtual void Update(float fTime);
	virtual void Render();

	/*****************************************************************
	* MouseCollide():		Mouse has collided with the object
	*
	* Ins:					void
	*      		      
	* Outs:					None
	*
	* Returns:				bool - whether or not the mouse is colliding
	*						with object
	*****************************************************************/
	bool MouseCollide();

	/*****************************************************************
	* MousePosition():		returns mouse position in relation to 
	*						Game screen space.
	*
	* Ins:					void
	*      		      
	* Outs:					None
	*
	* Returns:				POINT
	*****************************************************************/
	POINT MousePosition();

	/*****************************************************************
	 *  Accessors
	 *****************************************************************/
	HUD_Object* Parent() { return m_pParent; }
	bool Enabled() { return m_bEnabled; }
	bool Display() { return m_bDisplay; }
	DOCK_SETTING Dock() { return m_eDock; }
	float XPosition() { return m_rObjectBox.m_fX; }
	float YPosition() { return m_rObjectBox.m_fY; }
	float Width()	 { return m_rObjectBox.m_fWidth; }
	float Height()	{ return m_rObjectBox.m_fHeight; }
	CRectangleF* GetRect()	{ return &m_rObjectBox; }
	D3DCOLOR Color() { return m_d3dColor; }
	bool AutoScale() { return m_bAutoScale; }
	D3DXVECTOR2 Scale() { return m_vScale; }

	/*****************************************************************
	 *  Mutators
	 *****************************************************************/
	void Parent(HUD_Object* pParent)	{ m_pParent = pParent; }
	void Enabled( bool bEnabled )	{ m_bEnabled = bEnabled; }
	void Display( bool bDisplay )	{ m_bDisplay = bDisplay; }
	void Dock( DOCK_SETTING eDock );
	void Color(D3DCOLOR d3dColor)  { m_d3dColor = d3dColor; }
	void XPosition(float fXpos) { m_rObjectBox.m_fX = fXpos; m_rDisplayBox.m_fX = fXpos;}
	void YPosition(float fYpos) { m_rObjectBox.m_fY = fYpos; m_rDisplayBox.m_fY = fYpos;}
	void Width(float fWidth) { m_rObjectBox.m_fWidth = fWidth; m_rDisplayBox.m_fWidth = fWidth;}
	void Height(float fHeight) { m_rObjectBox.m_fHeight = fHeight; m_rDisplayBox.m_fHeight = fHeight;}
	void AutoScale( bool bAutoScale ) { m_bAutoScale = bAutoScale; }
	void Scale( D3DXVECTOR2 vScale) { m_vScale = vScale; }

	// TODO:
	__declspec(property(get= Color, put= Color)) D3DCOLOR color;
	__declspec(property(get= XPosition, put= XPosition)) float fX;
	__declspec(property(get= YPosition, put= YPosition)) float fY;
	__declspec(property(get= Width, put= Width)) float fWidth;
	__declspec(property(get= Height, put= Height)) float fHeight;
	__declspec(property(get= Dock, put=Dock)) DOCK_SETTING eDock;
	__declspec(property(get= Display, put= Display)) bool bDisplay;
	__declspec(property(get= Enabled, put= Enabled)) bool bEnabled;
	__declspec(property(get= Parent, put= Parent)) HUD_Object* pParent;
	__declspec(property(get= AutoScale, put= AutoScale)) bool autoscale;
	__declspec(property(get= Scale, put= Scale)) D3DXVECTOR2 scale;

	// Animation threads (ALPHA)
	static UINT _stdcall ThreadProc( void* param );
	void Grow();
	DWORD WINAPI Shrink();

};

#endif