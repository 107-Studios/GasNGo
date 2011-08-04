#ifndef _LEVELMANAGER_H_
#define _LEVELMANAGER_H_

#include <list>
#include <vector>

using std::list;
using std::vector;

#include "PipeObject.h"

#define GRID_WIDTH  12
#define GRID_HEIGHT 10

class CBaseObject;
class CTexture;
class CRenderManager;
class CSpaceStation;

class CLevelManager
{
private:	// Private structure
	struct tLevel
	{
		char *		m_szLevelName;
		float		m_fGoalMorale;
		float		m_fCurrentMorale;
		int			m_nTimeLimit;
		int			m_nPosX;
		int			m_nPosY;
		int			m_nAsteroidLevel;
		int			m_nPirateLevel;
		int			m_nBlackHoleLevel;
		bool		m_bPipes[4];
	};

private:	// Private data
	tLevel					m_Level;
 	static CLevelManager *	m_pInstance;
	CRenderManager *		m_pRenderManager;
	CBaseObject	*			m_pGrid[GRID_WIDTH][GRID_HEIGHT];	// Constant size
	CSpaceStation *			m_pStation;
	CPipeObject*			m_pCurrentPipe;
	list<CBaseObject*>		m_pObjectList;
	vector<CPipeObject*>	m_vUpcomingPipeList;
	vector<PipeID>			m_vAvailablePipes;
	vector<vector<CBaseObject*>>	m_vFuelList;
	float					m_fTimeRemaining;

public:		// Accessors
	inline static CLevelManager * GetInstance(void) { return m_pInstance; }
	inline tLevel * GetLevelInfo(void) { return &m_Level; }
	inline vector<CPipeObject*>* GetUpcomingPipes(void) { return &m_vUpcomingPipeList; }
	inline void RemovePipe() { m_vUpcomingPipeList.erase(m_vUpcomingPipeList.begin()); RandomPipe(); }

public:		// Functions
	static CLevelManager* Initialize();
	void Shutdown(void);
	void LoadLevel(char const * _szFileName, int const _nLevelToLoad = 0);
	void UnloadLevel(void);
	void Update(float const _fTime);
	void Render(void) const;
	void CalculatePath(void);
	list<CBaseObject*>::iterator RemoveObject(list<CBaseObject*>::iterator pObjectToRemove);
	void RemoveObject(CBaseObject*);
	void RandomPipe(void);
	void RandomActOfViolence();

private: // Helper functions
	CBaseObject* GetNextPipe(int pipePoint, const CBaseObject* pPipe);
	void Setup();

private:	// Dummy Functions
	CLevelManager(void);
	~CLevelManager(void);
	CLevelManager(const CLevelManager& lm);
	CLevelManager& operator=(const CLevelManager& lm) { return *this; }
};

#endif