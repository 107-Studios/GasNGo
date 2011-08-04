#ifndef _HUD_MORALEBAR_H_
#define _HUD_MORALEBAR_H_

#include "HUD_Panel.h"
#include "HUD_RadialMeter.h"

class HUD_MoraleBar : public HUD_Panel
{
protected:
	CTexture*	m_pIndicator;
	CTexture*	m_pEvilBar;
	CTexture*	m_pGoodBar;
	HUD_RadialMeter m_TimeRemaining;

public:

	HUD_MoraleBar();
	~HUD_MoraleBar();

	/*****************************************************************
	* Init():				setups the moralebar component
	*
	* Ins:					None
	*      		      
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	virtual void Init();

	/*****************************************************************
	* Update():				Will Update itself and any children it contains 
	*
	* Ins:					fTime
	*      		      
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	virtual void Update(float fTime);

	/*****************************************************************
	* Render():				Will Render the panel and any children it contains 
	*
	* Ins:					None
	*      		      
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	virtual void Render();

	/*****************************************************************
	* RenderBars():			Will Render the enemy's and player's morale bar side by side 
	*
	* Ins:					None
	*      		      
	* Outs:					None
	*
	* Returns:				Void
	*****************************************************************/
	virtual void RenderBars();

	// accessors
	CTexture* Indicator() { return m_pIndicator; }
	CTexture* GoodBar() { return m_pGoodBar; }
	CTexture* EvilBar() { return m_pEvilBar; }

	// Mutators 
	void Indicator(CTexture* pTexture) { m_pIndicator= pTexture; }
	void GoodBar(CTexture* pGoodbar) { m_pGoodBar= pGoodbar; }
	void EvilBar(CTexture* pEvilbar) { m_pEvilBar= pEvilbar; }
};

#endif