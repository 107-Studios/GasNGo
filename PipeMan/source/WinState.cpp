////////////////////////////////////////////////////////
//	File			:	"CWinState.cpp"
//	Author			:	Leo Cho (LC)
//	Purpose			:	To control the win state
////////////////////////////////////////////////////////

#include "WinState.h"

#include "StateMachine.h"
#include "MainMenuState.h"

CWinState* CWinState::GetInstance()
{
	static CWinState instance(NULL);//("WinState.msf");
	return &instance;
}

CWinState::CWinState( char* szMSFName ) : IGameState( szMSFName )
{
}

CWinState::~CWinState()
{
}

void CWinState::Enter()
{
	IGameState::Enter();
}

void CWinState::Exit()
{
	IGameState::Exit();
}

void CWinState::Input()
{
}

bool CWinState::Update(float fElapsedTime)
{
	return true;
}

void CWinState::Render()
{
}