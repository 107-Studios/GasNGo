#include "LevelState.h"
#include "SaveInfo.h"
#include "Color.h"
#include "InputManager.h"
#include "StateMachine.h"
#include "GameplayState.h"
#include "LevelManager.h"

CLevelState::CLevelState( char* szMSFName ) : IGameState(szMSFName)
{
	m_pPointList= NULL;
	m_fTileScale= 0.77f;
}

CLevelState::~CLevelState()
{

}

CLevelState* CLevelState::GetInstance()
{
	static CLevelState instance("resources/States/levelstate.msf");//("GameplayState.msf");
	return &instance;
}

void CLevelState::Enter()
{
	m_pLeveltileOutline= CRenderManager::GetInstance()->LoadTexture("resources/States/107_maptileline.png");

	// TODO: adding levels to state
	{
		LevelTile* pTemp= NULL;
		int unNumLevels = 40;

		for (int unCurrent= -1; unCurrent < CSaveInfo::GetInstance()->GetNextLevel() - 1; ++unCurrent)
		{
			pTemp = new LevelTile(LevelTile::FINISHED);
			m_vLevels.push_back(pTemp);
			--unNumLevels;
		}

		pTemp = new LevelTile(LevelTile::NEXT);
		m_vLevels.push_back(pTemp);
		--unNumLevels;

		for (int unCurrent= 0; unCurrent < unNumLevels; ++unCurrent)
		{
			pTemp = new LevelTile(LevelTile::IDLE);
			m_vLevels.push_back(pTemp);
		}
	}

	BuildTileLayout();
	BuildPointList();
}

void CLevelState::Exit()
{
	for (unsigned int unCurrent= 0; unCurrent < m_vLevels.size(); ++unCurrent)
	{
		CRenderManager::GetInstance()->UnloadTexture(m_vLevels[unCurrent]->m_pTexture);
	}
	m_vLevels.clear();
}

void CLevelState::Input()
{
	if (CInputManager::GetInstance()->KeyPressed(DIK_RETURN))
	{
		CLevelManager::GetInstance()->LoadLevel("Level.bin");
		CStateMachine::GetInstance()->ChangeState( CGameplayState::GetInstance() );
	}
}

bool CLevelState::Update( float fElapsedTime )
{
	return true;
}

void CLevelState::Render()
{
	//draw line between tiles
	CRenderManager::GetInstance()->LineBegin();

	CRenderManager::GetInstance()->LineRender(&m_pPointList->front(), CSaveInfo::GetInstance()->GetNextLevel()+1, COLOR_GREEN);
	CRenderManager::GetInstance()->LineRender(&(*m_pPointList)[CSaveInfo::GetInstance()->GetNextLevel()], m_vLevels.size() - (CSaveInfo::GetInstance()->GetNextLevel()), COLOR_RED);

	CRenderManager::GetInstance()->LineEnd();

	CRenderManager::GetInstance()->SpriteBegin();
	for (unsigned int unCurrent= 0; unCurrent < m_vLevels.size(); ++unCurrent)
	{
		//draw tiles
		CRenderManager::GetInstance()->Render(m_vLevels[unCurrent]->m_pTexture,
												NULL,
												m_vLevels[unCurrent]->m_vPosition,
												D3DXVECTOR2(m_fTileScale, m_fTileScale));

		CRenderManager::GetInstance()->Render(m_pLeveltileOutline,
												NULL,
												m_vLevels[unCurrent]->m_vPosition,
												D3DXVECTOR2(m_fTileScale, m_fTileScale));
	}
	CRenderManager::GetInstance()->SpriteEnd();
}

void CLevelState::BuildTileLayout()
{
	bool bDrawL2R = true;
	int nCounter= 0;
	float fSpacing = 160.0f * m_fTileScale;
	float fStartPointA = 40.0f;
	float fStartPointB = 870.0f;
	D3DXVECTOR2 vStartPoint = D3DXVECTOR2(fStartPointA, CSaveInfo::GetInstance()->GetScreenHeight() * 0.10f);

	if (m_vLevels.size())
		m_vLevels[0]->m_vPosition= vStartPoint;

	for (unsigned int unCurrent= 1; unCurrent < m_vLevels.size(); ++unCurrent)
	{
		nCounter++;
		if (nCounter == 8)
		{
			int nA= int(fStartPointA);
			int nB= int(fStartPointB);

			nA ^= nB;
			nB ^= nA;
			nA ^= nB;

			vStartPoint.x= float(nA);
			vStartPoint.y+= fSpacing;

			fStartPointA= float(nA);
			fStartPointB= float(nB);

			bDrawL2R= !bDrawL2R;
			nCounter= 0;
		}
		else
		{
			if (bDrawL2R)
				vStartPoint.x+= fSpacing;
			else
				vStartPoint.x-= fSpacing;

		}
		m_vLevels[unCurrent]->m_vPosition= vStartPoint;
	}
}

void CLevelState::BuildPointList()
{
	// take care of garbage
	if (!m_pPointList)
	{
		//TODO
	}

	m_pPointList= new vector<D3DXVECTOR2>();

	for (unsigned int unCurrent= 0; unCurrent < m_vLevels.size(); ++unCurrent)
	{
		m_pPointList->push_back(D3DXVECTOR2( m_vLevels[unCurrent]->m_vPosition.x + (m_vLevels[unCurrent]->m_pTexture->GetCenter().x * m_fTileScale),
											 m_vLevels[unCurrent]->m_vPosition.y + (m_vLevels[unCurrent]->m_pTexture->GetCenter().y * m_fTileScale)));
	}
}

void LevelTile::ChangeStatus( int nStatus )
{
	if(nStatus > NEXT) throw;

	m_nStatus= nStatus;
	
	switch (nStatus)
	{
	case IDLE:
		m_pTexture= CRenderManager::GetInstance()->LoadTexture("resources/States/107_maptileidle.png");
		break;

	case FINISHED:
		m_pTexture= CRenderManager::GetInstance()->LoadTexture("resources/States/107_maptiledone.png");
		break;

	case NEXT:
		m_pTexture= CRenderManager::GetInstance()->LoadTexture("resources/States/107_maptilenext.png");
		break;
	}
}
