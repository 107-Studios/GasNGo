#ifndef _GAMEPLAYSTATE_H_
#define  _GAMEPLAYSTATE_H_

#include "IGameState.h"
#include "HUD_GameplayScene.h"

class CLevelManager;
class CCollisionManager;

class CGameplayState : public IGameState
{
	CTexture*			m_pPipeSheet;
	CLevelManager*		m_pTestLevel;
	CCollisionManager*	m_pCollision;
	HUD_GameplayScene	m_cGameplayHUD;

	// Make a true singleton
	CGameplayState( char* szMSFName );
	CGameplayState(const CGameplayState& pState);
	CGameplayState& operator=(const CGameplayState& pState);
	~CGameplayState();

public:
	//////////////////////////////////////////////////////////////////////////
	// GetInstance():		Gets the static instance of the state
	//						returning a pointer to the instance
	//
	// Return:				CGameplayState*
	//////////////////////////////////////////////////////////////////////////
	static CGameplayState* GetInstance();

	//////////////////////////////////////////////////////////////////////////
	// Enter():				Enters the game state setting up all needed
	//						information based on state
	//
	// Return:				void
	//////////////////////////////////////////////////////////////////////////
	void Enter();

	//////////////////////////////////////////////////////////////////////////
	// Exit():				Exits the game state shutting down all
	//						initialized objects and resets all data
	//
	// Return:				void
	//////////////////////////////////////////////////////////////////////////
	void Exit();

	//////////////////////////////////////////////////////////////////////////
	// Input():				Receives input from the user.
	//
	// Return:				void
	//////////////////////////////////////////////////////////////////////////
	void Input();

	//////////////////////////////////////////////////////////////////////////
	// Update():			Updates the state based on the time passed in
	//						Updates all stored objects based on this time
	//
	// In:					fElapsedTime
	//
	// Return:				bool
	//////////////////////////////////////////////////////////////////////////
	bool Update(float fElapsedTime);

	//////////////////////////////////////////////////////////////////////////
	// Render()				Renders information to the screen using
	//						the rendering engine.
	//
	// Return:				void
	//////////////////////////////////////////////////////////////////////////
	void Render();

	// Accessors
	CTexture* PipeSheet(void) { return m_pPipeSheet; }

	// Mutators
	void PipeSheet(CTexture* pPipeSheet) { m_pPipeSheet= pPipeSheet; }
};

#endif