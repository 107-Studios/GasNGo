#ifndef _MENU_MAINMENUBUTTON_H_
#define _MENU_MAINMENUBUTTON_H_

#include "MENU_StateButton.h"

class MENU_MainMenuButton : public MENU_StateButton
{
protected:
	MENU_BaseObject* m_pRod;

public:
	
	// constructors
	MENU_MainMenuButton();
	~MENU_MainMenuButton();

	// methods
	virtual void Init(void);
	virtual void Update(float fTime);
	virtual void Render(void);

	// accessors
	float Rod_Width(void) { return m_pRod->Width(); }
	float Rod_Xposition(void) { return m_pRod->XPosition(); }
	float Rod_Yposition(void)  { return m_pRod->YPosition(); }

	// mutators
	void Rod_Animate(bool bAnimate) { m_pRod->Animate(bAnimate); }
	void Rod_Scaling(bool bScaling) { m_pRod->Scaling(bScaling); }
	void Rod_Color(D3DCOLOR dColor) { m_pRod->Color(dColor); }
	void Rod_AddMovementPoint(D3DXVECTOR2* pPoint) { m_pRod->AddMovementPoint(pPoint); }
	void Rod_Texture(CTexture* pTex) { m_pRod->Texture(pTex); }
	void Rod_Xposition(float lX) { m_pRod->XPosition(lX); }
	void Rod_Yposition(float lY) { m_pRod->YPosition(lY); }
	void Rod_MovementSpeed(float fSpeed) { m_pRod->MovementSpeed(fSpeed); }
	void Rod_Scale(D3DXVECTOR2* pScale) { m_pRod->Scale(pScale); }
	void Rod_Center(D3DXVECTOR2* pCenter) { m_pRod->Center(pCenter); }
};

#endif