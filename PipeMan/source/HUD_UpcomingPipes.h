/***********************************************
 * Filename:  		HUD_UpcomingPipes.h
 * Date:      		3/21/2011
 * Mod. Date: 		3/21/2011
 * Mod. Initials:	AD
 * Author:    		Anthony De La Rosa
 ************************************************/
#ifndef _HUD_UPCOMINGPIPES_H
#define _HUD_UPCOMINGPIPES_H

#include "HUD_Panel.h"
#include "PipeObject.h"
#include <vector>
#include <list>

class HUD_UpcomingPipes : public HUD_Panel
{
protected:
	vector<HUD_Panel*> m_vUpcomingPipes;
	vector<CPipeObject*>* m_pPipeObjects;

public:

	HUD_UpcomingPipes();
	~HUD_UpcomingPipes();

	void Init( vector<CPipeObject*>* = NULL, CTexture* = NULL );
	void Update(float fTime);
	void Render();
	void RenderPipes(void);
	void SlideOut();
	void AddPipes();

};

#endif