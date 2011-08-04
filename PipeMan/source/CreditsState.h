////////////////////////////////////////////////////////
//	File			:	"CCreditsState.h"
//	Author			:	Leo Cho (LC)
//	Purpose			:	To control the credit menu
////////////////////////////////////////////////////////
#ifndef	_CREDITSSTATE_H_
#define _CREDITSSTATE_H_

#include "IGameState.h"

class CCreditsState : public IGameState
{
	CCreditsState( char* szMSFName );
	CCreditsState(const CCreditsState& pState);
	CCreditsState& operator=(const CCreditsState& pState);
	~CCreditsState();

public:

	//////////////////////////////////////////////////////////////////////////
	// GetInstance():		Gets the static instance of the state
	//						returning a pointer to the instance
	//
	// Return:				CCreditsState*
	//////////////////////////////////////////////////////////////////////////
	static CCreditsState* GetInstance();

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
};

//////////////////////////////////////////////////////////////////////////
// Trigger Functions
//			Methods called when the buttons from the IGameState are pressed
//
//
// Return:				bool - Exits the state from IGameState
//////////////////////////////////////////////////////////////////////////
bool Trigger_Credits_Exit( IGameState* pThisState );

#endif