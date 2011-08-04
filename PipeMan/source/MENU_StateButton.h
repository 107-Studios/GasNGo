#ifndef _MENU_STATEBUTTON_H_
#define _MENU_STATEBUTTON_H_

#include "MENU_Button.h"

class IGameState;

class MENU_StateButton : public MENU_Button
{
protected:
	IGameState* m_pState; // state the button will go to

public:

	// constructors
	MENU_StateButton();
	~MENU_StateButton();

	// methods
	virtual void Init(void);
	virtual void Update(float fTime);
	virtual void Render(void);

	//accessors
	IGameState* StateDestination(void) { return m_pState; }

	//mutators
	void StateDestination(IGameState* pState) { m_pState= pState; }
};

#endif