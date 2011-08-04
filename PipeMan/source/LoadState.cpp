////////////////////////////////////////////////////////
//	File			:	"LoadState.cpp"
//	Author			:	Leo Cho (LC)
//	Purpose			:	To control the splash screen state
////////////////////////////////////////////////////////
#include "LoadState.h"
#include "StateMachine.h"
#include "GameplayState.h"

CLoadState* CLoadState::GetInstance()
{
	static CLoadState instance(NULL);//("LoadState.msf");
	return &instance;
}

CLoadState::CLoadState( char* szMSFName ) : IGameState( szMSFName )
{
}

CLoadState::~CLoadState()
{
}

void CLoadState::Enter()
{
	IGameState::Enter();
}

void CLoadState::Exit()
{
	IGameState::Exit();
}

void CLoadState::Input()
{
}

bool CLoadState::Update(float fElapsedTime)
{
	return true;
}

void CLoadState::Render()
{
}