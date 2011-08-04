#ifndef MENUOBJECTS_H_
#define MENUOBJECTS_H_

////////////////////////////////////////
// File: MenuObjects
// Purpose: Define the multiple structures used with the menu system
// Author: Eric Tjader
////////////////////////////////////////

#include "Rect.h"
#include <D3dx9math.h>
class CTexture;

class IGameState;

enum eObjectType { TYPE_IMAGE = 0, TYPE_BUTTON, TYPE_ANIM, NUM_TYPES };

struct tMenuBaseObject
{
	CTexture* pTexture;
	unsigned eType;

	tMenuBaseObject() : pTexture( NULL ) , eType( TYPE_IMAGE ) {}
};

struct tMenuBaseObjPosition
{
	D3DXVECTOR2 vPosition;
	D3DXVECTOR2 vScale;

	tMenuBaseObject* pObject;

	virtual void Render( IGameState * pState ) = 0;

	tMenuBaseObjPosition() : pObject( NULL ) {}
};



struct tMenuObjImage : public tMenuBaseObject
{
	CRect rDrawRect;
};

struct tMenuObjImagePosition : public tMenuBaseObjPosition
{
	void Render( IGameState * pState );
};



enum eButtonState { STATE_UP, STATE_HOVER, STATE_DOWN, NUM_STATES };

struct tMenuObjButton : public tMenuBaseObject
{
	CRect aDrawRects[3];

	tMenuObjButton() : tMenuBaseObject() {}
};

struct tMenuObjButtonPosition : public tMenuBaseObjPosition
{
	unsigned eState;

	void Render( IGameState * pState );

	tMenuObjButtonPosition() : tMenuBaseObjPosition(), eState( STATE_UP ) {}
};
#endif