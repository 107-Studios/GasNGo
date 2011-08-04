#include "MENU_MainMenuButton.h"
#include "RenderManager.h"


MENU_MainMenuButton::MENU_MainMenuButton()
{
	m_pRod= NULL;
}

MENU_MainMenuButton::~MENU_MainMenuButton()
{
	if (m_pRod)
		delete m_pRod;

	m_pRod= NULL;
}

void MENU_MainMenuButton::Init( void )
{
	MENU_StateButton::Init();
	m_pRod= new MENU_BaseObject();
	m_pRod->Init();
	m_pRod->Color(D3DCOLOR_ARGB(255, 100, 100, 100));
	m_pRod->Texture(CRenderManager::GetInstance()->LoadTexture("resources/MainMenu/bar.png"));

}

void MENU_MainMenuButton::Update( float fTime )
{
	MENU_StateButton::Update(fTime);
	m_pRod->Update(fTime);

	if ( m_pRod->AnimationCompleted() )
		this->Animate(true);
}

void MENU_MainMenuButton::Render( void )
{
	MENU_StateButton::Render();
	m_pRod->Render();
}
