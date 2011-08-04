#include "HUD_GameplayScene.h"
#include "HUD_Panel.h"
#include "SaveInfo.h"
#include "RenderManager.h"
#include "Color.h"
#include "HUD_InfoArea.h"
#include "HUD_UpcomingPipes.h"
#include "LevelManager.h"
#include "HUD_MoraleBar.h"

#define PANEL_SPACING 10.0f
#define PANEL_WIDTH 0.15f
#define PANEL_HEIGHT 0.30f
#define GRID_PIXEL_WIDTH 768.0f
#define GRID_PIXEL_HEIGHT 640.0f

HUD_GameplayScene::HUD_GameplayScene()
{
}

HUD_GameplayScene::~HUD_GameplayScene()
{
}

void HUD_GameplayScene::Init()
{
	// Screen width/height
	int nScreenWidth = CSaveInfo::GetInstance()->GetScreenWidth();
	int nScreenHeight = CSaveInfo::GetInstance()->GetScreenHeight();

	// upcoming pipes panel (pipe area)
	HUD_UpcomingPipes* pUpcomingPipes = new HUD_UpcomingPipes();
	pUpcomingPipes->fWidth = PANEL_WIDTH * nScreenWidth;
	pUpcomingPipes->fHeight= 0.625f * nScreenHeight;
	pUpcomingPipes->Dock( DOCK_LEFT | DOCK_TOP );
	pUpcomingPipes->Init( CLevelManager::GetInstance()->GetUpcomingPipes(), CRenderManager::GetInstance()->LoadTexture("resources/hudPanel.png"));
	pUpcomingPipes->bEnabled = true;
	pUpcomingPipes->bDisplay = true;
	pUpcomingPipes->autoscale= true;
	pUpcomingPipes->color = COLOR_WHITE;
	AddObject(pUpcomingPipes);

	// TODO: MORALE BAR!!!
	HUD_MoraleBar* pMoraleBar= new HUD_MoraleBar();
	pMoraleBar->Init();
	pMoraleBar->bEnabled= true;
	pMoraleBar->bDisplay= true;
	pMoraleBar->Dock( DOCK_TOP );
	pMoraleBar->fX= (pUpcomingPipes->fX + pUpcomingPipes->fWidth) + PANEL_SPACING;
	pMoraleBar->fWidth= GRID_PIXEL_WIDTH;
	pMoraleBar->fHeight= pUpcomingPipes->fHeight * 0.15f;
	pMoraleBar->pBackgroundImage= pUpcomingPipes->pBackgroundImage;
	pMoraleBar->autoscale= true;
	pMoraleBar->color= COLOR_WHITE;
	pMoraleBar->Indicator(CRenderManager::GetInstance()->LoadTexture( "resources/107_indicator.png" ));
	pMoraleBar->GoodBar(CRenderManager::GetInstance()->LoadTexture( "resources/Morale/goodSide.png"));
	pMoraleBar->EvilBar(CRenderManager::GetInstance()->LoadTexture( "resources/Morale/badSide.png"));
	AddObject(pMoraleBar);

	// Grid ?TODO?
	HUD_Panel* pGrid = new HUD_Panel();
	pGrid->bEnabled= true;
	pGrid->bDisplay= true;
	pGrid->fX= (pUpcomingPipes->fX + pUpcomingPipes->fWidth) + PANEL_SPACING;
	pGrid->fY= (pMoraleBar->fY + pMoraleBar->fHeight) + PANEL_SPACING;
	pGrid->fHeight= GRID_PIXEL_HEIGHT;
	pGrid->fWidth= GRID_PIXEL_WIDTH;
	pGrid->pTextureRect= new CRect(0, 0, 769, 641);
	pGrid->pBackgroundImage= CRenderManager::GetInstance()->LoadTexture( "resources/grid.png" );
	pGrid->color= COLOR_WHITE;
	AddObject(pGrid);

}

void HUD_GameplayScene::Update( float fTime )
{
	HUD_Scene::Update(fTime);
}

void HUD_GameplayScene::Render()
{
	HUD_Scene::Render();
}

void HUD_GameplayScene::Shutdown()
{

}
