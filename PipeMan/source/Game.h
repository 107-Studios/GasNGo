#ifndef	_GAME_H_
#define _GAME_H_

#include <windows.h>

class CStateMachine;
class CRenderManager;
class CAnimationManager;
class CInputManager;
class CAudioManger;
class CSaveInfo;
class CFontManager;
class CLevelManager;
class MENU_DialogBox;

class CGame
{
//Class Data
public:
	float	m_fAge;
	float	m_fElapsedTime;
	float   m_fFPSTimer;
	float   m_fFrameCount;
	float   m_fFPS;
	MENU_DialogBox*			m_pDialogBox;

private:
	static CGame*			m_pInstance;
	CStateMachine*			m_pStateMachine;
	CRenderManager*			m_pRenderManager;
	CAnimationManager*		m_pAnimationManager;
	CInputManager*			m_pInput;
	CFontManager*			m_pFont;
	CSaveInfo*				m_pSaveInfo;
	CLevelManager*			m_pLevelManager;

	//Disable Instancing
	CGame();
	~CGame();
	CGame(const CGame&);
	CGame& operator=(const CGame& cg);

	// Helper Functions
	void CalculateTime();	

public: //Interface
	static CGame* GetInstance();

	void Initialize(HWND);
	bool Run();
	void Shutdown();
	void Reset(bool bResize);
};

#endif