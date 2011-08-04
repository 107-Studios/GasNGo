#include "HUD_UpcomingPipes.h"
#include "Rect.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "LevelManager.h"

#define HUD_PIPE_SIZE 64.0f

HUD_UpcomingPipes::HUD_UpcomingPipes(): HUD_Panel()
{
	m_pPipeObjects= NULL;
}

HUD_UpcomingPipes::~HUD_UpcomingPipes()
{

}

void HUD_UpcomingPipes::Init( vector<CPipeObject*>* pUpcomingPipes/*= NULL */, CTexture* pBackgroundImage/*= NULL */ )
{
	HUD_Panel::Init(pBackgroundImage);
	m_pPipeObjects= pUpcomingPipes;

	if ( m_pPipeObjects == NULL ) return;

	AddPipes();
}

void HUD_UpcomingPipes::Update( float fTime )
{
	HUD_Panel::Update(fTime);

	// TODO: REMOVE THE FOLLOWING FOR FINAL BUILD
	if (CInputManager::GetInstance()->KeyPressedBuffered(DIK_RETURN))
	{
		if (m_vUpcomingPipes.size())
			SlideOut();
	}
	//////////////////////////////////////////////////////////////////////////

}

void HUD_UpcomingPipes::Render()
{
	HUD_Panel::Render();
	RenderPipes();
}

void HUD_UpcomingPipes::SlideOut()
{
	m_vUpcomingPipes.erase(m_vUpcomingPipes.begin());
	CLevelManager::GetInstance()->RemovePipe();
	AddPipes();
}

void HUD_UpcomingPipes::RenderPipes( void )
{
	int nStartingPosition = int((this->fY + this->fHeight) - (HUD_PIPE_SIZE+16.0f));

	for (unsigned int unCurrent= 0; unCurrent < m_vUpcomingPipes.size()-1; ++unCurrent)
	{
		m_vUpcomingPipes[unCurrent]->fX= this->fX+(this->fWidth/2.0f) - 32.0f;
		m_vUpcomingPipes[unCurrent]->fY= float(nStartingPosition);
		nStartingPosition -= int(m_vUpcomingPipes[unCurrent]->fHeight);

		CRenderManager::GetInstance()->Render(m_vUpcomingPipes[unCurrent]->ImageID(),
												m_vUpcomingPipes[unCurrent]->DrawRect(),
												D3DXVECTOR2(m_vUpcomingPipes[unCurrent]->XPosition(), m_vUpcomingPipes[unCurrent]->YPosition()));
	}
}

void HUD_UpcomingPipes::AddPipes()
{
	for (unsigned int unCurrent= m_vUpcomingPipes.size(); unCurrent < m_pPipeObjects->size(); unCurrent++)
	{
		HUD_Panel* pNewPipe = new HUD_Panel();
		pNewPipe->Init( const_cast<CTexture*>((*m_pPipeObjects)[unCurrent]->GetImageID()) );
		pNewPipe->fWidth= HUD_PIPE_SIZE;
		pNewPipe->fHeight= HUD_PIPE_SIZE;
		long lTexX= 0+( 64*(*m_pPipeObjects)[unCurrent]->GetPipeType());
		pNewPipe->DrawRect(new CRect( lTexX,
			0,
			63,
			63));
		pNewPipe->pParent= this;
		pNewPipe->Parent(this);
		m_vUpcomingPipes.push_back(pNewPipe);
	}
}
