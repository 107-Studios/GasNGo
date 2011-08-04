////////////////////////////////////////////////////////
//	File			:	"StateMachine.cpp"
//
//	Author			:	Leo Cho (LC)
//
//	Purpose			:	To control the states
////////////////////////////////////////////////////////

#include "StateMachine.h"
#include "RenderManager.h"

CStateMachine* CStateMachine::m_pInstance = NULL;

CStateMachine::CStateMachine() : m_pRenderManager(CRenderManager::GetInstance())
{
}

CStateMachine::~CStateMachine()
{
	m_vCurrentState.clear();
}

CStateMachine* CStateMachine::GetInstance()
{
	return m_pInstance;
}

CStateMachine* CStateMachine::Initialize()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new CStateMachine();
	}

	return m_pInstance;
}

void CStateMachine::DeleteInstance()
{
	delete m_pInstance;
	m_pInstance = NULL;
}

void CStateMachine::Enter(IGameState* pNewState)
{
	if(!pNewState)
		return;

	m_vCurrentState.push_back(pNewState);

	m_vCurrentState[m_vCurrentState.size() - 1]->Enter();
}

bool CStateMachine::Run(float fElapsedTime)
{
	if(m_vCurrentState.empty())
		return false;

	bool bRunning = true;

	IGameState* prevState = m_vCurrentState[m_vCurrentState.size() - 1];

				((IGameState*)m_vCurrentState[m_vCurrentState.size() - 1])->Input();
	bRunning =	((IGameState*)m_vCurrentState[m_vCurrentState.size() - 1])->Update(fElapsedTime);

	if( prevState != m_vCurrentState[m_vCurrentState.size() - 1] )
	{
		return bRunning;
	}

	//	clear the back buffer
	m_pRenderManager->Clear();
	//	begin the scene for drawing
	m_pRenderManager->BeginScene();

	if( m_vCurrentState.size() > 0 )
	{
		for(unsigned int i = 0; i < m_vCurrentState.size(); i++)
		{
			((IGameState*)m_vCurrentState[i])->Render();
		}
	}

	//	end the scene for drawing
	m_pRenderManager->EndScene();
	//	present the scene to the screen
	m_pRenderManager->PresentScene();

	//if a state returns false then its telling the game to close,
	//the state machine will give this bool back to cgame through this return value
	return bRunning;
}

void CStateMachine::ChangeState(IGameState* pNewState)
{
	int numStates = m_vCurrentState.size();

	for( int nState = 0;  nState < numStates; nState++)
	{
		((IGameState*)m_vCurrentState[nState])->Exit();
	}
	m_vCurrentState.clear();

	AddState(pNewState);
}

void CStateMachine::AddState(IGameState* pNewState)
{
	if(!pNewState)
	{
		return;
	}

	m_vCurrentState.push_back(pNewState);

	((IGameState*)m_vCurrentState[m_vCurrentState.size() - 1])->Enter();
}

void CStateMachine::Exit()
{
	if(m_vCurrentState.size() <= 1)
	{
		return;
	}

	if(m_vCurrentState.size() > 0)
	{
		((IGameState*)m_vCurrentState[m_vCurrentState.size() - 1])->Exit();
	}

	m_vCurrentState.pop_back();
}