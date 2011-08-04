#include "HUD_Scene.h"
#include "HUD_Object.h"

HUD_Scene::HUD_Scene()
{
	
}

HUD_Scene::~HUD_Scene()
{
	
}

void HUD_Scene::AddObject(HUD_Object* pObject)
{
	m_vObjects.push_back(pObject);
}

void HUD_Scene::RemoveAll()
{
	vector<HUD_Object*>::iterator iter = m_vObjects.begin();

	for ( ; iter != m_vObjects.end(); iter++)
		delete (*iter);

	m_vObjects.clear();
}

void HUD_Scene::Update( float fTime )
{
	vector<HUD_Object*>::iterator iter = m_vObjects.begin();

	for ( ; iter != m_vObjects.end(); iter++)
	{
		if ( (*iter)->Enabled() )
			(*iter)->Update(fTime);
	}
}

void HUD_Scene::Render()
{
	vector<HUD_Object*>::iterator iter = m_vObjects.begin();

	for ( ; iter != m_vObjects.end(); iter++)
	{
		if ( (*iter)->Display() )
			(*iter)->Render();
	}
}
