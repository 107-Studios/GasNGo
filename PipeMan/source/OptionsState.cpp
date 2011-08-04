////////////////////////////////////////////////////////
//	File			:	"COptionsState.cpp"
//	Author			:	Leo Cho (LC)
//	Purpose			:	To control the option menu
////////////////////////////////////////////////////////
#include "OptionsState.h"

#include "StateMachine.h"
#include "MainMenuState.h"
#include "RenderManager.h"

COptionsState* COptionsState::GetInstance()
{
	static COptionsState instance( "resources/States/Options.msf" );
	return &instance;
}

COptionsState::COptionsState( char* szMSFName ) : IGameState( szMSFName )
{
}

COptionsState::~COptionsState()
{
}

void COptionsState::Enter()
{
	IGameState::Enter();
	ppTriggers[0] = &Trigger_Options_Exit;
	ppTriggers[1] = &Trigger_Options_SavenExit;
}

void COptionsState::Exit()
{
	IGameState::Exit();
}

void COptionsState::Input()
{
	IGameState::Input();
}

bool COptionsState::Update(float fElapsedTime)
{
	if ( !IGameState::Update(fElapsedTime) )
	{
		return false;
	}
	return true;
}

void COptionsState::Render()
{
	CRenderManager::GetInstance()->SpriteBegin();

	IGameState::Render();

	CRenderManager::GetInstance()->SpriteEnd();
}
bool Trigger_Options_Exit( IGameState* pThisState )
{
	CStateMachine::GetInstance()->ChangeState( CMainMenuState::GetInstance() );
	return true;
}
bool Trigger_Options_SavenExit( IGameState* pThisState )
{
	CStateMachine::GetInstance()->ChangeState( CMainMenuState::GetInstance() );
	return true;
}