#ifndef _MENU_BASEOBJECT_H_
#define _MENU_BASEOBJECT_H_

#include "LevelManager.h"
#include "RectangleF.h"
#include "Texture.h"

#define MENU_MOVEMENT_SPEED 800.0f

class MENU_BaseObject
{
protected:
	bool m_bUpdate,
		 m_bRender,
		 m_bAnimate,
		 m_bAnimationComplete,
		 m_bScaling,
		 m_bEnabled;
	
	float m_fMovementSpeed;

	MENU_BaseObject *m_pParent;

	vector<D3DXVECTOR2*>* m_vMovementPoints;
	D3DXVECTOR2 *m_pCurrentMovementPoint,
				 *m_pScale,
				 *m_pCenter;

	CTexture* m_pImage;
	CRectangleF *m_rBoundingBox,
				*m_rImageDrawRect;

	D3DCOLOR m_d3dColor;

public:

	// constructors/destructor
	MENU_BaseObject(void);
	~MENU_BaseObject(void);

	//static methods
	static bool HeadToward(float &pObjectToMove, float pDestination, float fTime, float fSpeed= 100.0f);
	static bool HeadTowardVector(D3DXVECTOR2* pObjectToMove, D3DXVECTOR2* pDestination, float fTime, float fSpeed= 100.0f);

	// methods
	virtual void Init(void);
	virtual void Update(float fTime);
	virtual void Render(void);
	void AddMovementPoint( D3DXVECTOR2* );
	void HeadTowards(D3DXVECTOR2*, float fTime);
	void NextPoint(void);

	// accessors
	bool Updates(void) { return m_bUpdate; }
	bool Renders(void) { return m_bRender; }
	bool Animate(void) { return m_bAnimate; }
	bool AnimationCompleted(void) { return m_bAnimationComplete; }
	bool Scaling(void)	{ return m_bScaling; }
	bool Enabled(void) { return m_bEnabled;}
	float XPosition(void) { return m_rBoundingBox->m_fX; }
	float YPosition(void) { return m_rBoundingBox->m_fY; }
	float Width(void) { return m_rBoundingBox->m_fWidth; }
	float Height(void) { return m_rBoundingBox->m_fHeight; }
	CRectangleF* DrawRect(void) { return m_rImageDrawRect; }
	CTexture* Texture(void) { return m_pImage; }
	float MovementSpeed(void) { return m_fMovementSpeed; }
	D3DCOLOR Color(void) { return m_d3dColor; }
	MENU_BaseObject* Parent(void) { return m_pParent; }
	
	// mutators
	void Update(bool bUpdate) { m_bUpdate= bUpdate; }
	void Renders(bool bRender) { m_bRender= bRender; }
	void Animate(bool bAnimate) { m_bAnimate= bAnimate; m_bAnimate ? m_bAnimationComplete= false : m_bAnimationComplete;}
	void Scaling(bool bScaling) { m_bScaling= bScaling; }
	void Enabled(bool bEnabled) { m_bEnabled= bEnabled; }
	void DrawRect(CRectangleF* pRect) { if (m_rImageDrawRect) delete m_rImageDrawRect; m_rImageDrawRect= pRect; }
	void BoundingRect(CRectangleF* pRect) { if (m_rBoundingBox) delete m_rBoundingBox; m_rBoundingBox= pRect; }
	void XPosition(float lXposition) { m_rBoundingBox ? m_rBoundingBox->m_fX= float(lXposition) : BoundingRect(new CRectangleF(float(lXposition), 0, 128, 128)); }
	void YPosition(float lYposition) { m_rBoundingBox ? m_rBoundingBox->m_fY= float(lYposition) : BoundingRect(new CRectangleF(0, float(lYposition), 128, 128)); }
	void Width(float lWidth) { m_rBoundingBox ? m_rBoundingBox->m_fWidth= float(lWidth) : BoundingRect(new CRectangleF(0, 0, float(lWidth), 128)); }
	void Height(float lHeight) { m_rBoundingBox ? m_rBoundingBox->m_fHeight= float(lHeight) : BoundingRect(new CRectangleF(0, 0, 128, float(lHeight))); }
	void Texture(CTexture* pImage) { m_pImage= pImage; Resize(); }
	void MovementSpeed(float fSpeed) { m_fMovementSpeed= fSpeed; }
	void Color(D3DCOLOR dColor) { m_d3dColor= dColor; }
	void Scale(D3DXVECTOR2* pScale) { if (m_pScale) delete m_pScale; m_pScale= pScale; }
	void Center(D3DXVECTOR2* pCenter) { if (m_pCenter) delete m_pCenter; m_pCenter= pCenter; }
	void Parent(MENU_BaseObject* pParent) { m_pParent= pParent; }

private:
	virtual void Resize(void);
};
#endif