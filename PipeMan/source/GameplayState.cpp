#include "GameplayState.h"
#include "StateMachine.h"
#include "RenderManager.h"
#include "LevelManager.h"
#include "CollisionManager.h"

CGameplayState* CGameplayState::GetInstance()
{
	static CGameplayState instance("resources/States/Gameplay.msf");//("GameplayState.msf");
	return &instance;
}

CGameplayState::CGameplayState( char* szMSFName ) : IGameState( szMSFName )
{

}

CGameplayState::~CGameplayState()
{

}

void CGameplayState::Enter()
{
	IGameState::Enter();
	m_cGameplayHUD.Init();
	m_pTestLevel = CLevelManager::GetInstance();

	m_pPipeSheet= CRenderManager::GetInstance()->LoadTexture("resources/Pipes/pipeSheet.png");

	m_pCollision = CCollisionManager::Initialize();
}

void CGameplayState::Exit()
{
	m_pCollision->Shutdown();
	m_pTestLevel->UnloadLevel();
	CRenderManager::GetInstance()->UnloadTexture(m_pPipeSheet);
	m_pPipeSheet = NULL;

	IGameState::Exit();
}

void CGameplayState::Input()
{
	IGameState::Input();
	m_pCollision->Input();
}

bool CGameplayState::Update(float fElapsedTime)
{
	if ( !IGameState::Update(fElapsedTime) )
		return false;

	m_cGameplayHUD.Update(fElapsedTime);
	m_pCollision->Update(fElapsedTime);
	return true;
}

void CGameplayState::Render()
{
	CRenderManager::GetInstance()->SpriteBegin();

	IGameState::Render();
	m_cGameplayHUD.Render();

	CRenderManager::GetInstance()->SpriteEnd();
}