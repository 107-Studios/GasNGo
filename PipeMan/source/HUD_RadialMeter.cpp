#include "HUD_RadialMeter.h"
#include "RenderManager.h"

HUD_RadialMeter::HUD_RadialMeter()
{
	HUD_Object::HUD_Object();
	m_fStartValue= 60.0f;
	m_fCurrentValue= m_fStartValue;
	m_fSpeed= 1.0f;
	m_rRadialBGFull= NULL;
	m_rTimeLeft= NULL;
	m_rRadialBGRight= NULL;
	m_rTimeRight= NULL;
}

HUD_RadialMeter::~HUD_RadialMeter()
{
	if (m_rRadialBGFull)
		delete m_rRadialBGFull;
	
	if (m_rTimeLeft)
		delete m_rTimeLeft;
	
	if (m_rRadialBGRight)
		delete m_rRadialBGRight;
	
	if (m_rTimeRight)
		delete m_rTimeRight;

	m_rRadialBGFull= NULL;
	m_rTimeLeft= NULL;
	m_rRadialBGRight= NULL;
	m_rTimeRight= NULL;
}

void HUD_RadialMeter::Init( void )
{

	m_pRadialTexSheet= CRenderManager::GetInstance()->LoadTexture("resources/Morale/RadialMeter.png");

	m_rRadialBGFull= new CRect(0, 0, 128, 128);
	m_rTimeLeft= new CRect(128, 0, 128, 128);
	m_rRadialBGRight= new CRect(256, 0, 128, 128);
	m_rTimeRight= new CRect(384, 0, 128, 128);
}

void HUD_RadialMeter::Update( float fTime )
{
	HUD_Object::Update(fTime);

	m_fCurrentValue-= fTime * (m_fSpeed);

	if (m_fCurrentValue < 0.0f)
		m_fCurrentValue= 0.0f;
}

void HUD_RadialMeter::Render()
{
	HUD_Object::Render();

	float fInterpolatedAngle= 6.28f - ( m_fCurrentValue * 6.28f / 100.0f );

	// Draw radial meter background
	CRenderManager::GetInstance()->Render(m_pRadialTexSheet, m_rRadialBGFull, D3DXVECTOR2(XPosition(), YPosition()), D3DXVECTOR2( float(m_rDisplayBox.m_fWidth/128.0f), float( m_rDisplayBox.m_fHeight/128.0f)));

	if (fInterpolatedAngle < D3DX_PI)
	{
		// draw left HP
		CRenderManager::GetInstance()->Render( m_pRadialTexSheet, m_rTimeLeft, D3DXVECTOR2(XPosition(), YPosition()), D3DXVECTOR2( float(m_rDisplayBox.m_fWidth/128.0f), float( m_rDisplayBox.m_fHeight/128.0f)));
		// draw right black
		CRenderManager::GetInstance()->Render( m_pRadialTexSheet, m_rRadialBGRight, D3DXVECTOR2(XPosition(), YPosition()), D3DXVECTOR2( float(m_rDisplayBox.m_fWidth/128.0f), float( m_rDisplayBox.m_fHeight/128.0f)));
		// draw right HP
		CRenderManager::GetInstance()->Render( m_pRadialTexSheet, m_rTimeRight, D3DXVECTOR2(XPosition(), YPosition()), D3DXVECTOR2( float(m_rDisplayBox.m_fWidth/128.0f), float( m_rDisplayBox.m_fHeight/128.0f)), 0xFFFFFFFF, D3DXVECTOR2(/*m_rTimeRight->m_nX+*/0.0f, 0.0f), fInterpolatedAngle);
	}
	else
	{
		// draw left HP
		CRenderManager::GetInstance()->Render( m_pRadialTexSheet, m_rTimeLeft, D3DXVECTOR2(XPosition(), YPosition()), D3DXVECTOR2( float(m_rDisplayBox.m_fWidth/128.0f), float( m_rDisplayBox.m_fHeight/128.0f)), 0xFFFFFFFF, D3DXVECTOR2(float(m_rTimeLeft->m_nX+(m_rTimeLeft->m_nWidth/2.0f)), float(m_rTimeLeft->m_nY+(m_rTimeLeft->m_nHeight/2.0f))), fInterpolatedAngle);
		// draw right black
		CRenderManager::GetInstance()->Render( m_pRadialTexSheet, m_rRadialBGRight, D3DXVECTOR2(XPosition(), YPosition()), D3DXVECTOR2( float(m_rDisplayBox.m_fWidth/128.0f), float( m_rDisplayBox.m_fHeight/128.0f)));
	}
}
