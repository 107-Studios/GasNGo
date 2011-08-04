#ifndef _HUD_INFOAREA_H
#define _HUD_INFOAREA_H

#include "HUD_Panel.h"
#include "HUD_Text.h"

class HUD_InfoArea: public HUD_Panel
{
protected:
	HUD_Text m_szMoney;

	CTexture* m_pCashSign;
	D3DXVECTOR2 vCashSignPos;

public:

	HUD_InfoArea();
	~HUD_InfoArea();

	void Init();
	void Update(float fTime);
	void Render();

	// Money text mutators
	void MoneyAmount( int nNewAmount ) { sprintf_s( const_cast<char*>(m_szMoney.szText), 20, ": %d", nNewAmount); }
	void MoneyColor( D3DCOLOR d3dColor ) { m_szMoney.color = d3dColor; }
};

#endif