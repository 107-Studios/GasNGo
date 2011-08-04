#include "HUD_MoraleBar.h"
#include "RenderManager.h"
#include "LevelManager.h"
#include "InputManager.h"

HUD_MoraleBar::HUD_MoraleBar()
{

}

HUD_MoraleBar::~HUD_MoraleBar()
{

}

void HUD_MoraleBar::Init()
{
	m_TimeRemaining.Init();
}

void HUD_MoraleBar::Update( float fTime )
{
	HUD_Panel::Update(fTime);

	// TODO: REMOVE THE FOLLOWING FOR FINAL BUILD
	if (CInputManager::GetInstance()->KeyPressed(DIK_RIGHT))
	{
		CLevelManager::GetInstance()->GetLevelInfo()->m_fCurrentMorale+= fTime;
		if (CLevelManager::GetInstance()->GetLevelInfo()->m_fCurrentMorale >= 1.0f)
			CLevelManager::GetInstance()->GetLevelInfo()->m_fCurrentMorale= 1.0f;
	}

	if (CInputManager::GetInstance()->KeyPressed(DIK_LEFT))
	{
		CLevelManager::GetInstance()->GetLevelInfo()->m_fCurrentMorale-= fTime;
		if (CLevelManager::GetInstance()->GetLevelInfo()->m_fCurrentMorale <= 0.0f)
			CLevelManager::GetInstance()->GetLevelInfo()->m_fCurrentMorale= 0.0f;
	}
	//////////////////////////////////////////////////////////////////////////

	//m_TimeRemaining.Update(fTime);
}

void HUD_MoraleBar::Render()
{
	HUD_Panel::Render();
	RenderBars();
}

void HUD_MoraleBar::RenderBars()
{
	CRenderManager::GetInstance()->Render(m_pEvilBar, 
											new CRect(0, 0, long(this->Width()), long(this->Height())),
											D3DXVECTOR2(this->XPosition(), this->YPosition()));

	CRenderManager::GetInstance()->Render(m_pGoodBar, 
											new CRect(0, 0, long(this->Width() * CLevelManager::GetInstance()->GetLevelInfo()->m_fCurrentMorale), long(this->Height())),
											D3DXVECTOR2(this->XPosition(), this->YPosition()));
	//m_TimeRemaining.Render();
}
