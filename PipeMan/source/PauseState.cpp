////////////////////////////////////////////////////////
//	File			:	"CPauseState.cpp"
//	Author			:	Leo Cho (LC)
//	Purpose			:	To control the pause menu
////////////////////////////////////////////////////////
#include "PauseState.h"
#include "MainMenuState.h"
#include "StateMachine.h"
#include "OptionsState.h"

CPauseState* CPauseState::GetInstance()
{
	static CPauseState instance(NULL);//("PauseState.msf");
	return &instance;
}

CPauseState::CPauseState( char* szMSFName ) : IGameState( szMSFName )
{
}

CPauseState::~CPauseState()
{
}

void CPauseState::Enter()
{
	IGameState::Enter();
}

void CPauseState::Exit()
{
	IGameState::Exit();
}

void CPauseState::Input()
{
}

bool CPauseState::Update(float fElapsedTime)
{
	return true;
}

void CPauseState::Render()
{
}