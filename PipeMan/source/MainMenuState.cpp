////////////////////////////////////////////////////////
//	File			:	"MainMenuState.cpp"
//	Author			:	Leo Cho (LC)
//	Purpose			:	To control the main menu
////////////////////////////////////////////////////////

#include "MainMenuState.h"

#include "StateMachine.h"
#include "GameplayState.h"
#include "LoadState.h"
#include "SplashScreenState.h"
#include "OptionsState.h"
#include "CreditsState.h"
#include "PauseState.h"
#include "RenderManager.h"

#include "HUD_Text.h"
#include "MENU_Base.h"
#include "LevelState.h"
#include "MENU_MainMenuButton.h"
#include "SaveInfo.h"
#include "MENU_DialogBox.h"

CMainMenuState* CMainMenuState::GetInstance()
{
	static CMainMenuState instance( "resources/States/MainMenu.msf" );
	return &instance;
}

CMainMenuState::CMainMenuState( char* szMSFName ) : IGameState( szMSFName )
{
	
}

CMainMenuState::~CMainMenuState()
{
}

void CMainMenuState::Enter()
{
	IGameState::Enter();

	// initialize the menu for this state
	m_cMenu= new MENU_Base();
	m_cMenu->Init();
	//////////////////////////////////////////////////////////////////////////

	// crafting buttons for this state
	MENU_MainMenuButton* pNewGameObject= new MENU_MainMenuButton();
	pNewGameObject->Init();
	pNewGameObject->StateDestination(CLevelState::GetInstance());
	pNewGameObject->XPosition(0-pNewGameObject->Width());
	pNewGameObject->YPosition(float(CSaveInfo::GetInstance()->GetScreenHeight())*0.70f);
	pNewGameObject->Text("New Game");
	pNewGameObject->AddMovementPoint(new D3DXVECTOR2(float(CSaveInfo::GetInstance()->GetScreenWidth()*0.07f), pNewGameObject->YPosition()));
	pNewGameObject->MovementSpeed(MENU_MOVEMENT_SPEED);
	pNewGameObject->Rod_Xposition(0.0f-pNewGameObject->Rod_Width());
	pNewGameObject->Rod_Yposition(pNewGameObject->YPosition()-16.0f);
	pNewGameObject->Rod_AddMovementPoint(new D3DXVECTOR2(-800.0f, float(pNewGameObject->Rod_Yposition())));
	pNewGameObject->Rod_MovementSpeed(pNewGameObject->MovementSpeed());
	pNewGameObject->Rod_Animate(true);
	m_cMenu->AddObject(pNewGameObject);
	
	MENU_MainMenuButton* pOptionsObject= new MENU_MainMenuButton();
	pOptionsObject->Init();
	pOptionsObject->StateDestination(COptionsState::GetInstance());
	pOptionsObject->XPosition(float(CSaveInfo::GetInstance()->GetScreenWidth()));
	pOptionsObject->YPosition(pNewGameObject->YPosition());
	pOptionsObject->Text("Options");
	pOptionsObject->AddMovementPoint(new D3DXVECTOR2(float(CSaveInfo::GetInstance()->GetScreenWidth()*0.80f), pOptionsObject->YPosition()));
	pOptionsObject->MovementSpeed(MENU_MOVEMENT_SPEED);
	pOptionsObject->Rod_Xposition(pOptionsObject->XPosition()*2.0f); // TODO: figure out weird transforms
	pOptionsObject->Rod_Yposition(pOptionsObject->YPosition()-16.0f);
	pOptionsObject->Rod_AddMovementPoint(new D3DXVECTOR2(float(CSaveInfo::GetInstance()->GetScreenWidth())+(800.0f), pOptionsObject->Rod_Yposition()));
	pOptionsObject->Rod_MovementSpeed(pOptionsObject->MovementSpeed());
	pOptionsObject->Rod_Animate(true);
	pOptionsObject->Rod_Scaling(false);
	pOptionsObject->Rod_Scale(new D3DXVECTOR2(-1.0f, 1.0f));
	pOptionsObject->Rod_Center(new D3DXVECTOR2(512.0f, 16.0f));
	m_cMenu->AddObject(pOptionsObject);

	MENU_MainMenuButton* pContinueObject= new MENU_MainMenuButton();
	pContinueObject->Init();
	pContinueObject->StateDestination(NULL);
	pContinueObject->XPosition(0.0f-pContinueObject->Width());
	pContinueObject->YPosition(pNewGameObject->YPosition()+pNewGameObject->Height()+32.0f);
	pContinueObject->Text("Continue");
	pContinueObject->AddMovementPoint(new D3DXVECTOR2(float(CSaveInfo::GetInstance()->GetScreenWidth()*0.17f), pContinueObject->YPosition()));
	pContinueObject->MovementSpeed(MENU_MOVEMENT_SPEED);
	pContinueObject->Rod_Xposition(0-pContinueObject->Rod_Width());
	pContinueObject->Rod_Yposition(pContinueObject->YPosition()-16.0f);
	pContinueObject->Rod_AddMovementPoint(new D3DXVECTOR2(-700.0f, float(pContinueObject->Rod_Yposition())));
	pContinueObject->Rod_MovementSpeed(pContinueObject->MovementSpeed());
	pContinueObject->Rod_Animate(true);
	m_cMenu->AddObject(pContinueObject);

	MENU_MainMenuButton* pExitObject= new MENU_MainMenuButton();
	pExitObject->Init();
	pExitObject->ClickAction(ExitGame);
	pExitObject->XPosition(float(CSaveInfo::GetInstance()->GetScreenWidth()));
	pExitObject->YPosition(pOptionsObject->YPosition()+pOptionsObject->Height()+32.0f);
	pExitObject->Text("Exit");
	pExitObject->AddMovementPoint(new D3DXVECTOR2(float(CSaveInfo::GetInstance()->GetScreenWidth()*0.70f), pExitObject->YPosition()));
	pExitObject->MovementSpeed(MENU_MOVEMENT_SPEED);
	pExitObject->Rod_Xposition(pExitObject->XPosition()*2.0f); // TODO: figure out weird transforms
	pExitObject->Rod_Yposition(pExitObject->YPosition()-16.0f);
	pExitObject->Rod_AddMovementPoint(new D3DXVECTOR2(float(CSaveInfo::GetInstance()->GetScreenWidth()+700.0f), float(pExitObject->Rod_Yposition())));
	pExitObject->Rod_MovementSpeed(pExitObject->MovementSpeed());
	pExitObject->Rod_Animate(true);
	pExitObject->Rod_Scaling(false);
	pExitObject->Rod_Scale(new D3DXVECTOR2(-1.0f, 1.0f));
	pExitObject->Rod_Center(new D3DXVECTOR2(512.0f, 16.0f));
	m_cMenu->AddObject(pExitObject);
	//////////////////////////////////////////////////////////////////////////

	ppTriggers[0] = &Trigger_MainMenu_Play;
	ppTriggers[1] = &Trigger_MainMenu_Exit;
	ppTriggers[2] = &Trigger_MainMenu_Credits;
	ppTriggers[3] = &Trigger_MainMenu_Options;
}

void CMainMenuState::Exit()
{
	IGameState::Exit();
}

void CMainMenuState::Input()
{
	IGameState::Input();
}

bool CMainMenuState::Update(float fElapsedTime)
{
	if ( !IGameState::Update(fElapsedTime) )
	{
		return false;
	}
	m_cMenu->Update(fElapsedTime);
	return true;
}
void CMainMenuState::Render()
{
	CRenderManager::GetInstance()->SpriteBegin();

	//IGameState::Render();
	m_cMenu->Render();
	CRenderManager::GetInstance()->SpriteEnd();
}
bool Trigger_MainMenu_Play( IGameState* pThisState )
{
	//TODO::Gameplay state
	//CStateMachine::GetInstance()->ChangeState( CGameplayState::GetInstance() );
	CStateMachine::GetInstance()->ChangeState( CLevelState::GetInstance() );
	return true;
}
bool Trigger_MainMenu_Credits( IGameState* pThisState )
{
	CStateMachine::GetInstance()->ChangeState( CCreditsState::GetInstance() );
	return true;
}
bool Trigger_MainMenu_Options( IGameState* pThisState )
{
	CStateMachine::GetInstance()->ChangeState( COptionsState::GetInstance() );
	return true;
}
bool Trigger_MainMenu_Exit( IGameState* pThisState )
{
	CStateMachine::GetInstance()->Exit();
	return true;
}