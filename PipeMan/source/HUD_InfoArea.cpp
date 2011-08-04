#include "HUD_InfoArea.h"
#include "RenderManager.h"
#include "Rect.h"

HUD_InfoArea::HUD_InfoArea() : HUD_Panel()
{
	m_pCashSign= NULL;
	vCashSignPos = D3DXVECTOR2(0.0f, 0.0f);
}

HUD_InfoArea::~HUD_InfoArea()
{

}

void HUD_InfoArea::Init()
{
	m_pCashSign= CRenderManager::GetInstance()->LoadTexture("resources/cash_sign.png");
	vCashSignPos.x= 5.0f;
	vCashSignPos.y= 5.0f;

	m_szMoney.Init("Bellerose");
	m_szMoney.pParent= this;
	m_szMoney.fX= vCashSignPos.x  + (m_pCashSign->GetWidth() * 0.25f);
	m_szMoney.fY= -10.0f;
	m_szMoney.szText= ": 117"; // TODO: have set amount?
	m_szMoney.nFont= CFontManager::GetInstance()->FontExists("Bellerose");
	m_szMoney.color= D3DCOLOR_ARGB(255, 255, 255, 255);

}

void HUD_InfoArea::Update( float fTime )
{
	HUD_Panel::Update(fTime);
}

void HUD_InfoArea::Render()
{
	HUD_Panel::Render();
	m_szMoney.Render();

	CRenderManager::GetInstance()->Render(m_pCashSign,
											new CRect(0, 0, 128, 216),
											vCashSignPos + D3DXVECTOR2(this->fX, this->fY),
											D3DXVECTOR2(0.25f, 0.25f));
}
