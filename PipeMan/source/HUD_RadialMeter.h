#ifndef _HUD_RADIALMETER_H_
#define _HUD_RADIALMETER_H_

#include "HUD_Object.h"
#include "Texture.h"
#include "Rect.h"

class HUD_RadialMeter : public HUD_Object
{
protected:
	float m_fSpeed, // speed in which the meter decreases to 0
			m_fStartValue,
			m_fCurrentValue;

	CTexture* m_pRadialTexSheet;

	CRect* m_rRadialBGFull,
			*m_rTimeLeft,
			*m_rRadialBGRight,
			*m_rTimeRight;

	D3DXVECTOR2 m_vRadialBGFullCenter,
				m_vTimeLeftCenter,
				m_vRadialBGRightCenter,
				m_vTimeRightCenter;

public:

	HUD_RadialMeter();
	~HUD_RadialMeter();

	void Init(void);
	virtual void Update(float fTime);
	virtual void Render();

};

#endif