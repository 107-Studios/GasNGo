#include "MENU_StateButton.h"

#include "StateMachine.h"
#include "IGameState.h"


MENU_StateButton::MENU_StateButton()
{
	m_pState= NULL;
}

MENU_StateButton::~MENU_StateButton()
{

}

void MENU_StateButton::Init( void )
{
	MENU_Button::Init();
}

void MENU_StateButton::Update( float fTime )
{
	MENU_Button::Update(fTime);

	if (m_pState && m_eButton == RELEASED)
		CStateMachine::GetInstance()->ChangeState(m_pState);
}

void MENU_StateButton::Render( void )
{
	MENU_Button::Render();
}
