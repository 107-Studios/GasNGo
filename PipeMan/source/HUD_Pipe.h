/***********************************************
 * Filename:  		HUD_Pipe.h
 * Date:      		5/31/2011
 * Mod. Date: 		5/31/2011
 * Mod. Initials:	AD
 * Author:    		Anthony De La Rosa
 ************************************************/
#ifndef _HUD_PIPE_H
#define _HUD_PIPE_H

#include "HUD_Panel.h"
#include <vector>
#include <list>

class HUD_Pipe : public HUD_Panel
{
protected:

public:

	HUD_Pipe();
	~HUD_Pipe();

	virtual void Init(void);
	virtual void Update(float fTime);
	virtual void Render(void);
};

#endif