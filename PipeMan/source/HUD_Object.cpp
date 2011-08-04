#include "HUD_Object.h"
#include "RenderManager.h"
#include "SaveInfo.h"
#include <process.h>

#define GROW_LIMIT 1.5f

HUD_Object::HUD_Object()
{
	m_rObjectBox.m_fX= 0.0f;
	m_rObjectBox.m_fWidth= 128.0f;
	m_rObjectBox.m_fY= 0.0f;
	m_rObjectBox.m_fHeight= 128.0f;
	m_rDisplayBox = m_rObjectBox;

	m_pParent= NULL;
	m_bEnabled= false;
	m_bDisplay= false;
	m_bMouseCollide= false;
	m_bAnimating= false;
	m_eDock= DOCK_NONE;
}

HUD_Object::~HUD_Object()
{
	
}

void HUD_Object::Init()
{
	
}

void HUD_Object::Update( float fTime )
{
	m_bMouseCollide= false;

	if ( m_bEnabled == false )
		return;

	m_bMouseCollide= MouseCollide();

}

void HUD_Object::Render()
{

}

bool HUD_Object::MouseCollide()
{
	POINT ptMousePos = MousePosition();

	if (ptMousePos.x < m_rObjectBox.m_fX )
		return false;

	if (ptMousePos.y < m_rObjectBox.m_fY)
		return false;

	if (ptMousePos.x > m_rObjectBox.m_fWidth + m_rObjectBox.m_fX)
		return false;

	if (ptMousePos.y > m_rObjectBox.m_fHeight + m_rObjectBox.m_fY)
		return false;

	return true;
}

void HUD_Object::Dock( DOCK_SETTING eDock )
{
	m_eDock = eDock;
	float fNewXPosition = m_rObjectBox.m_fX;
	float fNewYPosition = m_rObjectBox.m_fY;
	int nScreenWidth = CSaveInfo::GetInstance()->GetScreenWidth();
	int nScreenHeight = CSaveInfo::GetInstance()->GetScreenHeight();

	if ( m_eDock & DOCK_LEFT)
	{
		if( m_pParent )
			fNewXPosition = m_pParent->m_rObjectBox.m_fX;
		else
			fNewXPosition = nScreenWidth * 0.025f;		
	}

	if ( m_eDock & DOCK_RIGHT )
	{
		if ( m_pParent )
			fNewXPosition = (m_pParent->m_rObjectBox.m_fX + m_pParent->m_rObjectBox.m_fWidth) - m_pParent->m_rObjectBox.m_fWidth;
		else
			fNewXPosition = nScreenWidth - m_pParent->m_rObjectBox.m_fWidth;
	}

	if ( m_eDock & DOCK_TOP )
	{
		if ( m_pParent )
			fNewYPosition = m_pParent->fY;
		else
			fNewYPosition = nScreenHeight * 0.025f;
	}

	if ( m_eDock & DOCK_BOTTOM )
	{
		if ( m_pParent )
			fNewYPosition = (m_pParent->fY + m_pParent->fHeight) - m_rObjectBox.m_fHeight;
		else
			fNewYPosition = nScreenWidth - m_rObjectBox.m_fHeight;
	}

	if ( m_eDock & DOCK_CENTER )
	{
		fNewXPosition = (nScreenWidth/2) - (m_pParent->m_rObjectBox.m_fWidth/2);
		fNewYPosition = (nScreenHeight/2) - (m_pParent->m_rObjectBox.m_fHeight/2);
	}

	m_rObjectBox.m_fX= fNewXPosition;
	m_rObjectBox.m_fY= fNewYPosition;
	m_rDisplayBox= m_rObjectBox;
}

POINT HUD_Object::MousePosition()
{
	POINT ptMousePos;
	GetCursorPos(&ptMousePos);
	ScreenToClient(CRenderManager::GetInstance()->WindowHandle(), &ptMousePos);
	return ptMousePos;
}

void HUD_Object::Grow()
{
	m_bAnimating= true;
	while ( m_rDisplayBox.m_fWidth < m_rObjectBox.m_fWidth * GROW_LIMIT )
	{
		m_rDisplayBox.m_fX+= -0.5f;
		m_rDisplayBox.m_fWidth+= 0.5f;
		m_rDisplayBox.m_fY+= -0.5f;
		m_rDisplayBox.m_fHeight+= 0.5f;
	}
	m_bAnimating= false;
}
