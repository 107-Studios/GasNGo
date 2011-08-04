#include "Game.h"
#include <time.h>

//----Additional Headers-----//
#include "StateMachine.h"
#include "RenderManager.h"
#include "AnimationManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "FontManager.h"
#include "SplashScreenState.h"
#include "SaveInfo.h"
#include "LevelManager.h"
#include "MENU_DialogBox.h"

#include <iostream>
#include <conio.h>

#include "MainMenuState.h"

//Global Variables
extern HWND wnd;

CGame* CGame::m_pInstance = NULL;

CGame::CGame()
{
	m_fAge = 0.0f;
	m_fElapsedTime = 0.0f;
	m_fFPSTimer = 0.0f;
	m_fFPS = 0.0f;
	m_fFrameCount = 0.0f;

	m_pStateMachine = NULL;
	m_pInput = NULL;
	m_pRenderManager = NULL;
	m_pFont = NULL;
	m_pAnimationManager = NULL;
	m_pDialogBox= NULL;
}

CGame::~CGame()
{

}

void CGame::Initialize(HWND wnd)
{
	//Init Time Variables
	m_fAge = 0.0f;
	m_fElapsedTime = 0.0f;
	m_fFPS = 0.0f;
	m_fFPSTimer = 0.0f;
	m_fFrameCount = 0.0f;

	// #TODO:
	m_pSaveInfo = CSaveInfo::GetInstance();

	// Initialize Rendering information
	m_pRenderManager = CRenderManager::GetInstance();
	m_pRenderManager->Initialize(wnd, m_pSaveInfo->GetScreenWidth(), m_pSaveInfo->GetScreenHeight(), m_pSaveInfo->GetIsWindowed(), m_pSaveInfo->GetVSync());

	// Initialize Animations
	m_pAnimationManager = CAnimationManager::GetInstance();
	m_pAnimationManager->Initialize(m_pRenderManager);

	// Initialize font stuff
	FontAttributes pAttr = FontAttributes();
	pAttr.m_nFontSize= 64;
	m_pFont = CFontManager::GetInstance();
	m_pFont->Initialize(m_pRenderManager->GetDevice(), m_pRenderManager->GetSprite());

	m_pFont->LoadFont("resources/Fonts/Bellerose.ttf", "Bellerose", pAttr);

	// Initialize Input
	m_pInput = CInputManager::CreateInstance(wnd);

	// Initialize Sound
	m_pStateMachine = CStateMachine::Initialize();
	m_pStateMachine->Enter( CMainMenuState::GetInstance() );

	// Initialize the LevelManager
	m_pLevelManager = CLevelManager::Initialize();

	// TODO: TEST DIALOG BOX EXTENSIVELY
	// initialize dialog box
	m_pDialogBox= MENU_DialogBox::GetInstance();
	m_pDialogBox->Init();
}


void CGame::Shutdown()
{
	m_pStateMachine->ChangeState(NULL);
	m_pStateMachine->DeleteInstance();

	m_pInput->Shutdown();

	m_pFont->Shutdown();

	m_pRenderManager->Shutdown();
	m_pLevelManager->Shutdown();
	CSaveInfo::GetInstance()->DeleteInstance();
	// #TODO:
	// Shutdown Sound
}

CGame* CGame::GetInstance()
{
	static CGame theGame;
	return &theGame;
}

bool CGame::Run()
{
	// #TODO:
	// Use this to check when the user alt tabs out
//  	if (m_pRenderManager->GetDevice()->TestCooperativeLevel() != D3D_OK)
//  	{
//  		if (m_pRenderManager->GetDevice()->TestCooperativeLevel() == D3DERR_DEVICELOST)
//  		{
//  			return true;
//  		}
//  
//  		if (m_pRenderManager->GetDevice()->TestCooperativeLevel() == D3DERR_DEVICENOTRESET )
//  		{
//  			m_pInput->RegainControl();
//  			m_pRenderManager->Reset(false);
//  			m_pInput->RegainControl();
//  			return true;
//  		}
//  	}
 
	if (m_pInput->KeyPressedBuffered(DIK_RETURN) && (m_pInput->KeyPressed(DIK_LMENU) || m_pInput->KeyPressed(DIK_RMENU)))
	{
		m_pSaveInfo->ChangeWindowed();
		Reset(true);

		return true;
	}

	CalculateTime();

	// #TODO:
	// Update the input if needed
	m_pInput->Update();

	if (m_pInput->KeyPressedBuffered(DIK_S))
	{
		m_pSaveInfo->SetScreenDimensions(800, 600);
		Reset(true);
	}
	else if (m_pInput->KeyPressedBuffered(DIK_D))
	{
		m_pSaveInfo->SetScreenDimensions(1024, 768);
		Reset(true);
	}

	// #TODO:
	// Stop mouse from going outside the window
// 	if(m_fMouseX >= SCREEN_WIDTH)
// 		m_fMouseX = SCREEN_WIDTH;
// 	if(m_fMouseX <= 0)
// 		m_fMouseX = 0;
// 
// 	if(m_fMouseY >= SCREEN_HEIGHT)
// 		m_fMouseY = SCREEN_HEIGHT;
// 	if(m_fMouseY <= 0)
// 		m_fMouseY = 0;

	return m_pStateMachine->Run(m_fElapsedTime);
}

void CGame::Reset(bool bResize)
{
	if (m_pInput)
		m_pInput->RegainControl();
	if (m_pRenderManager)
		m_pRenderManager->Reset(bResize);
}

//Helpers
void CGame::CalculateTime()
{	
	clock_t CurrTime = clock();
	static clock_t PrevTime = CurrTime;

	m_fElapsedTime = (float)(CurrTime - PrevTime) / (float)CLOCKS_PER_SEC;
	m_fAge += m_fElapsedTime;

	//CALCULATE FPS;
	 m_fFrameCount += 1.0f;
	 m_fFPSTimer += m_fElapsedTime;

	if( m_fFPSTimer >= 1.0f)
	{
		m_fFPS = m_fFrameCount / m_fFPSTimer;

		m_fFPSTimer -= 1.0f;
		m_fFrameCount = 0.0f;
		char szWindowText[128];
		sprintf_s(szWindowText,128, "PipeMan - FPS: %.2f" , m_fFPS);
		SetWindowText(wnd,szWindowText);
	}
	
	PrevTime = CurrTime;
}