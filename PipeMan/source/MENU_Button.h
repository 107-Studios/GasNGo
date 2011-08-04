#ifndef _MENU_BUTTON_H_
#define _MENU_BUTTON_H_

#include "MENU_BaseObject.h"
#include "FontManager.h"

enum MOUSE_STATUS {IDLE, HOVER, CLICKED, RELEASED};

class MENU_Button : public MENU_BaseObject
{
protected:
	//data members
	MOUSE_STATUS m_eButton;
	FONTID m_nText;
	char *m_szDisplayText;
	//MENU_DialogBox *m_pDialog;
	FontAttributes m_cFontAttributes;

	D3DCOLOR	m_d3dHoverColor,
				m_d3dClickColor;

	// methods
	MOUSE_STATUS Hovering(void);

private:
	void (*m_fpClickAction) (void); // member function pointer

public:

	// constructors
	MENU_Button();
	~MENU_Button();

	// methods
	virtual void Init(void);
	virtual void Update(float fTime);
	virtual void Render(void);
	MOUSE_STATUS ButtonStatus(void);

	// accessors
	FONTID Font(void) { return m_nText; }
	FontAttributes FontAttribute(void) { return m_cFontAttributes; }
	char* Text(void) { return m_szDisplayText; }

	// mutators
	void Font(FONTID nID) { m_nText= nID; }
	void Text(char* pText);
	void ClickAction( void (*pFunc)(void)  ) { m_fpClickAction= pFunc;}
};

void ExitGame(void);
void BringUpDialog(void);

#endif