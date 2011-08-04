#include "LevelManager.h"
#include "PipeObject.h"
#include "RenderManager.h"
#include "SpaceStationObject.h"

#include <fstream>
#include <iostream>
#include <time.h>
using std::fstream;

CLevelManager* CLevelManager::m_pInstance = NULL;

CLevelManager::CLevelManager(void)
{
	m_pRenderManager	= NULL;
	memset(&m_pGrid, NULL, sizeof(m_pGrid));
	memset(&m_Level, NULL, sizeof(tLevel));
	m_pStation = NULL;
	m_fTimeRemaining = 0.0f;
	m_pCurrentPipe = NULL;
	m_Level.m_fGoalMorale= 1.0f;
	m_Level.m_fCurrentMorale= 0.75f;
}

CLevelManager::~CLevelManager(void)
{

}

CLevelManager* CLevelManager::Initialize()
{
	if(NULL == m_pInstance)
	{
		m_pInstance = new CLevelManager();
		m_pInstance->Setup();
	}

	return m_pInstance;
}

void CLevelManager::Setup()
{
	m_pRenderManager = CRenderManager::GetInstance();
}

void CLevelManager::Shutdown(void)
{
	UnloadLevel();
	if(m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

void CLevelManager::LoadLevel(char const * _szFileName, int const _nLevelToLoad)
{
	// TODO: Look over the format on the server
	//////////////////////////////////////////////////////////////////////////
	//	LOADING FORMAT
	//------------------------------------------------------------------------
	// - String length
	// - Level name (string)
	// - Required number of pipes (int)
	// - Timer (float)
	// - Blockset(int)
	// - Grid(for each block)
	//		- position(in the grid)(2 double)
	//		- model id (int)
	//		- string location (string)
	//		- replaceable(on the grid)(bool)
	//		- direction(int)
	//////////////////////////////////////////////////////////////////////////
	fstream iRead(_szFileName, std::ios_base::in | std::ios_base::binary);

	if (iRead.is_open())
	{
		if(NULL == m_pGrid)
		{
			for (int width = 0; width < GRID_WIDTH; width++)
				for (int height = 0; height < GRID_HEIGHT; height++)
					m_pGrid[width][height] = new CBaseObject();
		}

		// TODO: Seek to the current level
		int numLevels;
		iRead.read((char*)&numLevels, sizeof(int));

		for (int curLevel = 0; curLevel < _nLevelToLoad; ++curLevel)
		{
			int numChars;
			iRead.read((char*)&numChars, sizeof(int));

			iRead.seekg(sizeof(tLevel) - 4 + numChars);
		}

		int numChars = 0;
		iRead.read((char*)&numChars, sizeof(int));

		int goalMorale = 0;
		m_Level.m_szLevelName = new char[numChars + 1]();
		iRead.read(m_Level.m_szLevelName, numChars);
		iRead.read((char*)&goalMorale, sizeof(int));
		iRead.read((char*)&m_Level.m_nTimeLimit, sizeof(int));
		iRead.read((char*)&m_Level.m_nPosX, sizeof(int));
		iRead.read((char*)&m_Level.m_nPosY, sizeof(int));
		iRead.read((char*)&m_Level.m_nAsteroidLevel, sizeof(int));
		iRead.read((char*)&m_Level.m_nPirateLevel, sizeof(int));
		iRead.read((char*)&m_Level.m_nBlackHoleLevel, sizeof(int));
		iRead.read((char*)&m_Level.m_bPipes, sizeof(int));

		m_Level.m_fGoalMorale = (float)goalMorale;
	}
	iRead.clear();
	iRead.close();

	m_fTimeRemaining = float(m_Level.m_nTimeLimit);

	for (int i = 0; i < 4; ++i)
	{
		if (m_Level.m_bPipes[i])
			m_vAvailablePipes.push_back((PipeID)i);
	}

	// Add some random pipes to the list
	for (int i = 0; i < 8; ++i)
		RandomPipe();
}

void CLevelManager::Update(float const _fTime)
{
	m_fTimeRemaining -= _fTime;

	// TODO: Add in random bad things

	// TODO: Fill all necessary pipes.
	// For each list of pipes call the fill method
	// Store the return value of the fill method
	// When the fill returns true remove the pipe from the list
	// This will need to be altered to fit with the T pipes
}

void CLevelManager::CalculatePath(void)
{
	for (int col = 0; col < m_pStation->GetHeight(); ++col)
	{
		for (int row = 0; row < m_pStation->GetWidth(); ++row)
		{
			int curPipePoint = (col == 0) ? 2 : 0;// = m_Level.m_pStart->GetDirection();
			CPipeObject* curPipe = m_pStation->GetPort(row, col);// = m_Level.m_pStart;
		
			if (curPipe == NULL)
				continue;

			curPipe = (CPipeObject*)GetNextPipe(curPipePoint, curPipe);

			vector<CBaseObject*> vFillList;

			while (curPipe->GetObjectID() == CBaseObject::PIPE);
			{
				vFillList.push_back(curPipe);

				curPipePoint = curPipe->GetConnector(curPipePoint);

				curPipe = (CPipeObject*)GetNextPipe(curPipePoint, curPipe);

				if (curPipe->GetConnector(curPipePoint) == -1)
					break;

				// x % 4 == x & 3
				curPipePoint = (curPipePoint + 2) & 3;
			}

			if (curPipe->GetPipeType() == END_PIPE)
			{
				m_vFuelList.push_back(vFillList);
			}
		}
	}
}

CBaseObject* CLevelManager::GetNextPipe(int pipePoint, const CBaseObject* pPipe)
{
	int x = (int)pPipe->GetPosX();
	int y = (int)pPipe->GetPosY();

	if (pipePoint == 0)
		return m_pGrid[x][y - 1];
	else if (pipePoint == 1)
		return m_pGrid[x - 1][y];
	else if (pipePoint == 2)
		return m_pGrid[x][y + 1];
	else
		return m_pGrid[x + 1][y];
}

void CLevelManager::UnloadLevel(void)
{
	// Delete the name
	if(m_Level.m_szLevelName)
	{
		delete[] m_Level.m_szLevelName;
		m_Level.m_szLevelName = NULL;
	}

	// Delete the grid
	for (int height = 0; height < GRID_HEIGHT; height++)
	{
		for (int width = 0; width < GRID_WIDTH; width++)
		{
			RemoveObject(m_pGrid[height][width]);
			delete m_pGrid[height][width];
			m_pGrid[height][width] = NULL;
		}
	}

	// Delete all the objects on the level
	list<CBaseObject*>::iterator objIter = m_pObjectList.begin();
	for( ; objIter != m_pObjectList.end(); ++objIter)
	{
		if((*objIter))
		{
			delete (*objIter);
			(*objIter) = NULL;
		}
	}
	m_pObjectList.clear();

	vector<CPipeObject*>::iterator iter = m_vUpcomingPipeList.begin();
	for (; iter != m_vUpcomingPipeList.end(); ++iter)
	{
		if ((*iter))
		{
			delete (*iter);
			(*iter) = NULL;
		}
	}

	m_vUpcomingPipeList.clear();
	m_pCurrentPipe = NULL;

}

void CLevelManager::RandomPipe( void )
{
	CPipeObject* newPipe = new CPipeObject(m_vAvailablePipes[rand() % m_vAvailablePipes.size()],
		CRenderManager::GetInstance()->LoadTexture("resources/Pipes/pipeSheet.png"));
	m_vUpcomingPipeList.push_back(newPipe);
}

list<CBaseObject*>::iterator CLevelManager::RemoveObject( list<CBaseObject*>::iterator pObjectToRemove )
{
	return m_pObjectList.erase(pObjectToRemove);
}

void CLevelManager::RemoveObject( CBaseObject* pObject)
{
	//	Check for valid object pointer
	if (pObject == NULL)
		return;

	list<CBaseObject*>::iterator iter = m_pObjectList.begin();

	for ( ;iter != m_pObjectList.end(); iter++)
	{
		// if this is the object we are looking for.
		if (&(*iter) == &pObject)
		{
			// Remove the object from the list
			RemoveObject(iter);
			break;
		}
	}
}

void CLevelManager::RandomActOfViolence()
{
	// Punch Sam in the face.
}