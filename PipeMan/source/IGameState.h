#ifndef _IGAMESTATE_H_
#define _IGAMESTATE_H_

#include <vector>
#include "MenuObjects.h"

class CRenderManager;
class CSaveInfo;

class IGameState
{
	char* m_szMSFName;

protected:

	unsigned m_uiImageCount;
	CTexture** ppTextures;
	std::vector< tMenuBaseObject* > m_lObjects;
	std::vector< tMenuBaseObjPosition* > m_lPositions;

	//The amount of button positions
	unsigned m_uiTriggerCount;

	bool m_bRunning;

	//Dynamic array of function pointers
	bool (**ppTriggers)( IGameState* pThisState );

	
	CRenderManager* pRenderMan;
	CSaveInfo* pSaveInfo;

public:
	IGameState( char* szMSFName );
	~IGameState();

	//////////////////////////////////////////////////////////////////////////
	// Enter():			Enters the game state setting up all needed
	//					information based on state
	//
	// Return:			void
	//////////////////////////////////////////////////////////////////////////
	virtual void Enter();

	//////////////////////////////////////////////////////////////////////////
	// Exit():			Exits the game state shutting down all
	//					initialized objects and resets all data
	//
	// Return:			void
	//////////////////////////////////////////////////////////////////////////
	virtual void Exit();

	//////////////////////////////////////////////////////////////////////////
	// Input():			Receives input from the user.
	//
	// Return:			void
	//////////////////////////////////////////////////////////////////////////
	virtual void Input();

	//////////////////////////////////////////////////////////////////////////
	// Update():		Updates the state based on the time passed in
	//					Updates all stored objects based on this time
	//
	// In:				fElapsedTime
	//
	// Return:			bool
	//////////////////////////////////////////////////////////////////////////
	virtual bool Update(float fElapsedTime);

	//////////////////////////////////////////////////////////////////////////
	// Render()			Renders information to the screen using
	//					the rendering engine.
	//
	// Return:			void
	//////////////////////////////////////////////////////////////////////////
	virtual void Render();

	//////////////////////////////////////////////////////////////////////////
	// These render functions allow the the structures to use polymorhism
	//		instead of ifs in the render function to determine how to render
	//
	//////////////////////////////////////////////////////////////////////////
	virtual void RenderImage( tMenuObjImagePosition * pPosition );
	virtual void RenderButton( tMenuObjButtonPosition * pPosition );

	// mutators
	void Running(bool bRunning) {m_bRunning= bRunning;}
};

#endif