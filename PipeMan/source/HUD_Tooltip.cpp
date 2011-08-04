#include "HUD_Tooltip.h"
#include "RenderManager.h"
#include "TextureManager.h"

HUD_Tooltip::HUD_Tooltip()
{
	m_bEnabled= false;
	m_bDisplay= false;
	m_bAutoResize= false;

	m_rBorder.m_fX= 0.0f;
	m_rBorder.m_fY= 0.0f;
	m_rBorder.m_fWidth= 128.0f;
	m_rBorder.m_fHeight= 128.0f;
}

HUD_Tooltip::~HUD_Tooltip()
{
	
}

void HUD_Tooltip::Init()
{
	m_txtHeader.Init("Bellerose", D3DCOLOR_ARGB(255, 255, 0, 0));
	m_txtHeader.Text("< Header >");
	m_txtHeader.XPosition( m_rBorder.m_fX );
	m_txtHeader.YPosition( m_rBorder.m_fY );
	m_txtHeader.Width( m_rBorder.m_fWidth );
	m_txtHeader.CalculateRect();

	m_txtBody.Init("Bellerose", D3DCOLOR_ARGB(255, 0, 0, 255));
	m_txtBody.Text("< Body >");
	m_txtBody.XPosition( m_txtHeader.XPosition() );
	m_txtBody.YPosition( m_txtHeader.Height() + m_txtHeader.YPosition() );
	m_txtBody.Width( m_rBorder.m_fWidth );
	m_txtBody.CalculateRect();

	m_Panel.Init( CRenderManager::GetInstance()->LoadTexture("resources/hudPanel.png"));
	m_Panel.Enabled(true);
	m_Panel.Width( m_rBorder.m_fWidth );
	m_Panel.Height( m_rBorder.m_fHeight );
	m_Panel.Color(D3DCOLOR_RGBA(255, 255, 255, 255));
}

void HUD_Tooltip::Update( float fTime )
{
	if ( m_bEnabled == false)
		return;

	m_Panel.Update(fTime);
	
	// TODO: call HUD_Object static function MOUSE COLLIDE
	POINT pMousePos;
	GetCursorPos(&pMousePos);
	ScreenToClient(CRenderManager::GetInstance()->WindowHandle(), &pMousePos);
	//////////////////////////////////////////////////////////////////////////

	xPosition( float(pMousePos.x) );
	yPosition(pMousePos.y - m_rBorder.m_fHeight);
	m_txtHeader.XPosition( m_rBorder.m_fX );
	m_txtHeader.YPosition( m_rBorder.m_fY );
	m_txtBody.XPosition(m_txtHeader.XPosition());
	m_txtBody.YPosition(m_txtHeader.Height() + m_txtHeader.YPosition());
	m_Panel.XPosition(m_rBorder.m_fX);
	m_Panel.YPosition(m_rBorder.m_fY);
}

void HUD_Tooltip::Render()
{
	if ( Display() == false )
		return;

	m_Panel.Render();
	m_txtHeader.Render();
	m_txtBody.Render();
}

void HUD_Tooltip::Resize()
{
	float fWidth = m_txtHeader.GetRect()->m_fWidth;

	if ( m_txtBody.GetRect()->m_fWidth > fWidth )
		fWidth = m_txtBody.GetRect()->m_fWidth;

	m_rBorder.m_fWidth= fWidth;
	m_rBorder.m_fHeight= m_txtHeader.Height() + m_txtBody.Height() ;
	m_Panel.Width( m_rBorder.m_fWidth );
	m_Panel.Height( m_rBorder.m_fHeight );
}
