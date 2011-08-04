////////////////////////////////////////////////////////
//	File			:	"CLoseState.cpp"
//	Author			:	Leo Cho (LC)
//	Purpose			:	To control the lose state
////////////////////////////////////////////////////////

#include "LoseState.h"

#include "StateMachine.h"
#include "MainMenuState.h"
#include "LoadState.h"
#include "GameplayState.h"

CLoseState* CLoseState::GetInstance()
{
	static CLoseState instance(NULL);//("LoseState.msf");
	return &instance;
}

CLoseState::CLoseState( char* szMSFName ) : IGameState( szMSFName )
{
}

CLoseState::~CLoseState()
{
}

void CLoseState::Enter()
{
	IGameState::Enter();
}

void CLoseState::Exit()
{
	IGameState::Exit();
}

void CLoseState::Input()
{
}

bool CLoseState::Update(float fElapsedTime)
{
	return true;
}
void CLoseState::Render()
{
}