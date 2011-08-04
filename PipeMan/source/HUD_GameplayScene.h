/***********************************************
 * Filename:  		HUD_GameplayScene.h
 * Date:      		2/18/2011
 * Mod. Date: 		2/18/2011
 * Mod. Initials:	AD
 * Author:    		Anthony De La Rosa
 ************************************************/
#ifndef _HUD_GAMEPLAYSCENE_H
#define _HUD_GAMEPLAYSCENE_H

#include "HUD_Scene.h"

class HUD_GameplayScene : public HUD_Scene
{
protected:
	
public:

	HUD_GameplayScene();
	~HUD_GameplayScene();

	void Init();
	void Shutdown();

	void Update(float fTime);
	void Render();

};
#endif