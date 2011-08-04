#ifndef _LEVELSTATE_H_
#define _LEVELSTATE_H_

#include "IGameState.h"
#include "HUD_Scene.h"
#include "RenderManager.h"
#include "Texture.h"
#include "Line.h"

struct LevelTile
{
	enum tileStatus{IDLE, FINISHED, NEXT};

	int m_nStatus;
	CTexture* m_pTexture;
	D3DXVECTOR2 m_vPosition;

	LevelTile() { m_nStatus= IDLE; m_pTexture= CRenderManager::GetInstance()->LoadTexture("resources/States/107_maptileidle.png"); m_vPosition= m_pTexture->GetCenter(); }
	LevelTile(int nStatus) { ChangeStatus(nStatus); }

	void ChangeStatus(int nStatus);
};

class CLevelState : public IGameState
{
private:
	// Make a true singleton
	CLevelState( char* szMSFName );
	CLevelState(const CLevelState& pState);
	CLevelState& operator=(const CLevelState& pState);
	~CLevelState();
	float m_fTileScale;

protected:
	vector<LevelTile*> m_vLevels;
	vector<D3DXVECTOR2>* m_pPointList;

	CTexture* m_pLeveltileOutline;

public:
	//////////////////////////////////////////////////////////////////////////
	// GetInstance():		Gets the static instance of the state
	//						returning a pointer to the instance
	//
	// Return:				CGameplayState*
	//////////////////////////////////////////////////////////////////////////
	static CLevelState* GetInstance();

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

	//////////////////////////////////////////////////////////////////////////
	// BuildTileLayout()				Renders information to the screen using
	//						the rendering engine.
	//
	// Return:				void
	//////////////////////////////////////////////////////////////////////////
	void BuildTileLayout();

	//////////////////////////////////////////////////////////////////////////
	// BuildPointList()				Renders information to the screen using
	//						the rendering engine.
	//	
	// Return:				void
	//////////////////////////////////////////////////////////////////////////
	void BuildPointList();

	// accessors
	inline vector<D3DXVECTOR2>* PointList() { return m_pPointList; }
};

#endif