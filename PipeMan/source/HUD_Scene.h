/***********************************************
 * Filename:  		HUD_Scene.h
 * Date:      		2/18/2011
 * Mod. Date: 		2/18/2011
 * Mod. Initials:	AD
 * Author:    		Anthony De La Rosa
 * Purpose:   		in charge of multiple HUD Objects
 ************************************************/
#ifndef _HUD_SCENE_H
#define _HUD_SCENE_H

#include <vector>
using std::vector;

class HUD_Object;

class HUD_Scene
{
protected:
	vector<HUD_Object*> m_vObjects;

public:

	HUD_Scene();
	~HUD_Scene();

	virtual void Init() = 0;
	virtual void Shutdown() = 0;

	void AddObject(HUD_Object*);
	void RemoveAll();
	void Update(float fTime);
	void Render();
};
#endif