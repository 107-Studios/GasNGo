#include "MENU_Button.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "StateMachine.h"
#include "MainMenuState.h"

#include "Game.h"
#include "MENU_DialogBox.h"

MENU_Button::MENU_Button()
{
	m_eButton= IDLE;
	m_nText= -1;
	m_szDisplayText= NULL;
	m_d3dColor= D3DCOLOR_ARGB(255, 0, 0, 175);
	m_d3dHoverColor= D3DCOLOR_ARGB(255, 255, 127, 80);
	m_d3dClickColor= D3DCOLOR_ARGB(255, 128, 0, 0);
	m_cFontAttributes= FontAttributes();
	m_fpClickAction= NULL;
}

MENU_Button::~MENU_Button()
{
	if (m_szDisplayText)
		delete [] m_szDisplayText;

	m_szDisplayText= NULL;
}

void MENU_Button::Init( void )
{
	MENU_BaseObject::Init();
	Texture(CRenderManager::GetInstance()->LoadTexture("resources/MainMenu/button.png"));
	Font(CFontManager::GetInstance()->LoadFont("resources/Fonts/Bellerose.ttf", "Bellerose", FontAttribute()));

}

void MENU_Button::Update( float fTime )
{
	MENU_BaseObject::Update(fTime);
	
	if (ButtonStatus() == RELEASED)
	{
		if (m_fpClickAction)
			m_fpClickAction();
	}

}

void MENU_Button::Render( void )
{
	if (!m_bRender)
		return;

	if ( m_pImage )
	{
		switch (m_eButton)
		{
		case IDLE:
			{
				CRenderManager::GetInstance()->Render(m_pImage, 
					new CRect(long(m_rImageDrawRect->m_fX), long(m_rImageDrawRect->m_fY), long(m_rImageDrawRect->m_fWidth), long(m_rImageDrawRect->m_fHeight)), 
					m_pParent ? D3DXVECTOR2(this->m_rBoundingBox->m_fX + m_pParent->XPosition(), this->m_rBoundingBox->m_fY + m_pParent->YPosition()) : D3DXVECTOR2(this->m_rBoundingBox->m_fX, this->m_rBoundingBox->m_fY),
					m_bScaling ? D3DXVECTOR2(m_pImage->GetWidth()/m_rBoundingBox->m_fWidth, m_pImage->GetHeight()/m_rBoundingBox->m_fHeight) : D3DXVECTOR2(1.0f, 1.0f),
					m_d3dColor);
			}
		break;

		case HOVER:
			{
				CRenderManager::GetInstance()->Render(m_pImage, 
					new CRect(long(m_rImageDrawRect->m_fX), long(m_rImageDrawRect->m_fY), long(m_rImageDrawRect->m_fWidth), long(m_rImageDrawRect->m_fHeight)), 
					m_pParent ? D3DXVECTOR2(this->m_rBoundingBox->m_fX + m_pParent->XPosition(), this->m_rBoundingBox->m_fY + m_pParent->YPosition()) : D3DXVECTOR2(this->m_rBoundingBox->m_fX, this->m_rBoundingBox->m_fY),
					m_bScaling ? D3DXVECTOR2(m_pImage->GetWidth()/m_rBoundingBox->m_fWidth, m_pImage->GetHeight()/m_rBoundingBox->m_fHeight) : D3DXVECTOR2(1.0f, 1.0f),
					m_d3dHoverColor);
			}
			break;

		case CLICKED:
			{
				CRenderManager::GetInstance()->Render(m_pImage, 
					new CRect(long(m_rImageDrawRect->m_fX), long(m_rImageDrawRect->m_fY), long(m_rImageDrawRect->m_fWidth), long(m_rImageDrawRect->m_fHeight)), 
					m_pParent ? D3DXVECTOR2(this->m_rBoundingBox->m_fX + m_pParent->XPosition(), this->m_rBoundingBox->m_fY + m_pParent->YPosition()) : D3DXVECTOR2(this->m_rBoundingBox->m_fX, this->m_rBoundingBox->m_fY),
					m_bScaling ? D3DXVECTOR2(m_pImage->GetWidth()/m_rBoundingBox->m_fWidth, m_pImage->GetHeight()/m_rBoundingBox->m_fHeight) : D3DXVECTOR2(1.0f, 1.0f),
					m_d3dClickColor);
			}
			break;
		}
	}

	// render the text over button
	if (m_nText >= 0)
	{
		RECT m_rRect;

		if (Parent())
		{
			m_rRect.left= long(m_rBoundingBox->m_fX + m_pParent->XPosition());
			m_rRect.top= long(m_rBoundingBox->m_fY + m_pParent->YPosition());
			m_rRect.bottom= long(m_rBoundingBox->m_fHeight + m_rBoundingBox->m_fY + m_pParent->Height());
			m_rRect.right= long(m_rBoundingBox->m_fWidth + m_rBoundingBox->m_fX + m_pParent->Width());
		}
		else
		{
			m_rRect.left= long(m_rBoundingBox->m_fX);
			m_rRect.top= long(m_rBoundingBox->m_fY);
			m_rRect.bottom= long(m_rBoundingBox->m_fHeight + m_rBoundingBox->m_fY);
			m_rRect.right= long(m_rBoundingBox->m_fWidth + m_rBoundingBox->m_fX);
		}

		CFontManager::GetInstance()->DrawText(m_nText, m_szDisplayText, &m_rRect, D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER);
	}
}

MOUSE_STATUS MENU_Button::ButtonStatus( void )
{
	if (CInputManager::GetInstance()->MouseReleasedBuffered(0/*TODO: this param needs to be an ENUM*/) && Hovering() == HOVER)
		m_eButton= RELEASED;
	else if (CInputManager::GetInstance()->MouseClicked(0/*TODO: this param needs to be an ENUM*/) && Hovering() == HOVER)
		m_eButton= CLICKED;
	else if (Hovering() == HOVER)
		m_eButton= HOVER;
	else
		m_eButton= IDLE;

	return m_eButton;
}

MOUSE_STATUS MENU_Button::Hovering( void )
{
	if (CInputManager::GetInstance()->GetCursorPosition().x < m_rBoundingBox->m_fX)
	{
		m_eButton= IDLE;
		return m_eButton;
	}

	if (CInputManager::GetInstance()->GetCursorPosition().x > m_rBoundingBox->m_fX + m_rBoundingBox->m_fWidth)
	{
		m_eButton= IDLE;
		return m_eButton;
	}

	if (CInputManager::GetInstance()->GetCursorPosition().y < m_rBoundingBox->m_fY)
	{
		m_eButton= IDLE;
		return m_eButton;
	}

	if (CInputManager::GetInstance()->GetCursorPosition().y > m_rBoundingBox->m_fY + m_rBoundingBox->m_fHeight)
	{
		m_eButton= IDLE;
		return m_eButton;
	}

	m_eButton= HOVER;
	return m_eButton;
}

void MENU_Button::Text( char* pText )
{
	if (m_szDisplayText)
		delete [] m_szDisplayText;

	size_t tSize = strlen(pText)+1;
	m_szDisplayText= new char[tSize];
	
	strcpy_s(m_szDisplayText, tSize, pText);
}

void ExitGame()
{
	CMainMenuState::GetInstance()->Running(false);
}

void BringUpDialog()
{
	//CGame::GetInstance()->m_pDialogBox->Display("Are You Sure?", DT_DECISION, true, ExitGame);
}