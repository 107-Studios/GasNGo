////////////////////////////////////////////////////////
//	File			:	"CCreditsState.cpp"
//	Author			:	Leo Cho (LC)
//	Purpose			:	To control the credit menu
////////////////////////////////////////////////////////
#include "CreditsState.h"

#include "StateMachine.h"
#include "MainMenuState.h"
#include "RenderManager.h"

CCreditsState* CCreditsState::GetInstance()
{
	static CCreditsState instance( "resources/States/Credits.msf" );
	return &instance;
}

CCreditsState::CCreditsState( char* szMSFName ) : IGameState( szMSFName )
{
}

CCreditsState::~CCreditsState()
{
}

void CCreditsState::Enter()
{
	IGameState::Enter();
	ppTriggers[0] = &Trigger_Credits_Exit;
}

void CCreditsState::Exit()
{
	IGameState::Exit();
}

void CCreditsState::Input()
{
	IGameState::Input();
}

bool CCreditsState::Update(float fElapsedTime)
{
	if ( !IGameState::Update(fElapsedTime) )
	{
		return false;
	}
	return true;
}

void CCreditsState::Render()
{
	CRenderManager::GetInstance()->SpriteBegin();

	IGameState::Render();

	CRenderManager::GetInstance()->SpriteEnd();
}
bool Trigger_Credits_Exit( IGameState* pThisState )
{
	CStateMachine::GetInstance()->ChangeState( CMainMenuState::GetInstance() );
	return true;
}