#include "HUD_Button.h"
#include "RenderManager.h"

HUD_Button::HUD_Button() : HUD_Panel()
{
	
}

HUD_Button::~HUD_Button()
{
	
}

void HUD_Button::Init()
{
	m_ToolTip.Init();
	m_ToolTip.Enabled(true);
	m_ToolTip.AutoResize(true);
	m_d3dColor= D3DCOLOR_RGBA(255, 255, 255, 255);
	m_ButtonText.Init("Bellerose", D3DCOLOR_ARGB(255, 255, 255, 0), DT_CENTER | DT_VCENTER);
	m_ButtonText.Parent(this);
	m_pImage= CRenderManager::GetInstance()->LoadTexture("resources/hudPanel.png");
}

void HUD_Button::Update( float fTime )
{
	if ( m_bEnabled == false )
		return;

	HUD_Panel::Update(fTime);
	m_ButtonText.Update(fTime);

	//TODO: mouse over object?	
	if ( m_bMouseCollide )
	{
		m_ToolTip.Display(true);
		m_ButtonText.color= D3DCOLOR_ARGB(255, 255, 0, 255);
	}
	else
	{
		m_ToolTip.Display(false);
		m_ButtonText.color= D3DCOLOR_ARGB(255, 255, 255, 0);
	}

	m_ToolTip.Update(fTime);
}

void HUD_Button::Render()
{
	if ( m_bDisplay == false )
		return;

	HUD_Panel::Render();
	m_ButtonText.Render();
	m_ToolTip.Render();
}
