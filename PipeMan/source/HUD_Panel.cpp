#include "HUD_Panel.h"
#include "TextureManager.h"
#include "RenderManager.h"

HUD_Panel::HUD_Panel() : HUD_Object()
{
	m_pTexRect= NULL;
	m_bAutoScale= false;
	m_vScale= D3DXVECTOR2(1.0f, 1.0f);
}

HUD_Panel::~HUD_Panel()
{
	CRenderManager::GetInstance()->UnloadTexture( m_pImage );
}

void HUD_Panel::Init( CTexture* pImage/*= NULL */ )
{
	HUD_Object::Init();

	m_pImage= pImage;
}

void HUD_Panel::Update(float fTime)
{
	if ( m_bEnabled == false )
		return;

	HUD_Object::Update(fTime);
}

void HUD_Panel::Render()
{
	HUD_Object::Render();

	if ( m_bDisplay == false )
		return;

	if ( m_pImage )
	{
		CRenderManager::GetInstance()->Render(	m_pImage,
												m_pTexRect,
												D3DXVECTOR2( m_rDisplayBox.m_fX, m_rDisplayBox.m_fY),
												m_bAutoScale ? D3DXVECTOR2(float(m_rDisplayBox.m_fWidth/m_pImage->GetWidth()), float( m_rDisplayBox.m_fHeight/m_pImage->GetHeight() )) : m_vScale,
												m_d3dColor);
	}
}
