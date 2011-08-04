#include "MENU_DialogBox.h"

#include "RenderManager.h"

MENU_DialogBox::MENU_DialogBox()
{
	m_pOk= NULL;
	m_pCancel= NULL;
	m_d3dBodyColor= D3DCOLOR_ARGB(255, 3, 188, 177);
	m_eDialogType= DT_DECISION;
	m_eDialogStatus= DS_CLOSED;
	m_eDialogResponse= DR_NULL;
	m_bUpdate= false;
	m_bRender= false;
}

MENU_DialogBox::~MENU_DialogBox()
{
	if (m_pCancel)
		delete m_pCancel;

	if (m_pOk)
		delete m_pOk;

	m_pOk= NULL;
	m_pCancel= NULL;
}

void MENU_DialogBox::Init( void )
{
	MENU_BaseObject::Init();

	m_pOk= new MENU_Button();
	m_pCancel= new MENU_Button();

	// ok button settings
	m_pOk->Init();
	m_pOk->Parent(this);
	m_pOk->Text("OK");
	m_pOk->Enabled(false);
	m_pOk->Update(false);
	m_pOk->Renders(false);
	m_pOk->XPosition(long(BAR_OFFSET));
	m_pOk->YPosition(m_pOk->Texture()->GetHeight()*0.84f);
	//////////////////////////////////////////////////////////////////////////

	// cancel button settings
	m_pCancel->Init();
	m_pCancel->Parent(this);
	m_pCancel->Text("Cancel");
	m_pCancel->Enabled(false);
	m_pCancel->Update(false);
	m_pCancel->Renders(false);
	m_pCancel->XPosition(m_pOk->XPosition() + m_pOk->Width() + BAR_OFFSET);
	m_pCancel->YPosition(m_pOk->YPosition());
	//////////////////////////////////////////////////////////////////////////

	this->Texture(CRenderManager::GetInstance()->LoadTexture("resources/MainMenu/dialogbox.png"));
	this->DrawRect(new CRectangleF(0.0f, 0.0f, float(this->Texture()->GetWidth()), BAR_OFFSET));
}

void MENU_DialogBox::Update( float fTime )
{
	MENU_BaseObject::Update(fTime);
	m_pOk->Update(fTime);
	m_pCancel->Update(fTime);

#pragma region is the dialog out and about?
	if (m_eDialogStatus == DS_MOVING && m_vMovementPoints->size() == 0 /*&& m_rBoundingBox > 0*/)
		m_eDialogStatus = DS_OPENING;
#pragma endregion

#pragma region was button pressed on the dialog box?
	if (m_pOk->ButtonStatus() == RELEASED)
	{
		m_eDialogResponse= DR_OK;
		m_eDialogStatus= DS_CLOSING;
		m_pOk->Enabled(false);
		m_pCancel->Enabled(false);
	}
	else if (m_pCancel->ButtonStatus() == RELEASED)
	{
		m_eDialogResponse= DR_CANCEL;
		m_eDialogStatus= DS_CLOSING;
		m_pOk->Enabled(false);
		m_pCancel->Enabled(false);
	}
#pragma endregion

#pragma region update opening/closing animation 
	switch (m_eDialogStatus)
	{
	case DS_OPENING:
		{
			if ( MENU_BaseObject::HeadToward(m_rBodyDrawRect.m_fHeight, float(this->Texture()->GetHeight()), fTime, MENU_MOVEMENT_SPEED) )
			{
				m_eDialogStatus= DS_OPENED;
				m_pOk->Enabled(true);
				m_pCancel->Enabled(true);
			}
		}
		break;

	case DS_CLOSING:
		{
			if ( MENU_BaseObject::HeadToward(m_rBodyDrawRect.m_fHeight, m_rBodyDrawRect.m_fY, fTime, MENU_MOVEMENT_SPEED) )
				m_eDialogStatus= DS_CLOSED;
		}
		break;
	}
#pragma endregion

}

void MENU_DialogBox::Render( void )
{
	MENU_BaseObject::Render();
	m_pOk->Render();
	m_pCancel->Render();
}

void MENU_DialogBox::Display( LPSTR szText, DialogType eDialogType/*= DR_DECISION*/, bool bAutoScaling/*= true*/, void (*pFunc)(void)/*= NULL*/ )
{
	Scaling(bAutoScaling);
	Text(szText);
	ModeSwitch(eDialogType);
	OK_ClickAction(pFunc);
	AddMovementPoint(new D3DXVECTOR2(256.0f, 256.0f));
	m_bUpdate= true;
	m_bRender= true;
	m_eDialogStatus= DS_MOVING;

}

void MENU_DialogBox::Resize( void )
{
	float fTotalWidth= 0.0f,
		  fTotalHeight= 0.0f;

	RECT rTempRect= CFontManager::GetInstance()->CalculateRect( m_pOk->Font(), m_szDialogText );

	fTotalHeight+= rTempRect.bottom;
	fTotalWidth+= rTempRect.right;

	if ( m_pCancel->Enabled() )
	{
		fTotalWidth+= m_pCancel->Width();
		fTotalHeight+= m_pCancel->Height();
	}

	if ( m_pOk->Enabled() )
	{
		fTotalWidth+= m_pOk->Width();
		fTotalHeight+= m_pOk->Height();
	}

	Width(fTotalWidth);
	Height(fTotalHeight);

}

void MENU_DialogBox::ModeSwitch( DialogType eNewType)
{
	if (m_eDialogType == eNewType)
		return;

	m_eDialogType= eNewType;

	switch (m_eDialogType)
	{
	case DT_DECISION:
		{
			m_pOk->Enabled(true);
			m_pCancel->Enabled(true);
		}
		break;

	case DT_NOTIFICATION:
		{
			m_pOk->Enabled(true);
			m_pCancel->Enabled(false);
		}
		break;
	}

	if (Scaling())
		Resize();
}