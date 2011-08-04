////////////////////////////////////////////////////////
//	File			:	"SplashScreenState.cpp"
//	Author			:	Leo Cho (LC)
//	Purpose			:	To control the splash screen state
////////////////////////////////////////////////////////
#include "SplashScreenState.h"
#include "StateMachine.h"
#include "MainMenuState.h"

CSplashScreenState* CSplashScreenState::GetInstance()
{
	static CSplashScreenState instance(NULL);//(SplashScreenState.msf");
	return &instance;
}

CSplashScreenState::CSplashScreenState( char* szMSFName ) : IGameState( szMSFName )
{
}

CSplashScreenState::~CSplashScreenState()
{
}

void CSplashScreenState::Enter()
{
	IGameState::Enter();
}

void CSplashScreenState::Exit()
{
	IGameState::Exit();
}

void CSplashScreenState::Input()
{
	// #TODO:
	// Enable this later for users and debugging
	// to skip the splash screen state - click to skip
// #ifdef _DEBUG
// 	if(CInputManager::GetInstance()->MouseClickBuffered(0))
// 	{
// 		CStateMachine::GetInstance()->ChangeState( CMainMenuState::GetInstance() );
// 		return;
// 	}
// #endif
}

bool CSplashScreenState::Update(float fElapsedTime)
{
	return true;
}

void CSplashScreenState::Render()
{
}