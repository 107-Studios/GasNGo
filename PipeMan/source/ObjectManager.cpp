//////////////////////////////////////////////////////////////////////////
// Filename:  			ObjectManager.h
// Date:      			03/15/2010
// Mod. Date: 			06/22/2010
// Mod. Initials:		BK
// Author:    			Brian Kelsey
// Purpose:   			Handles updates for all objects
//////////////////////////////////////////////////////////////////////////
#include "ObjectManager.h"

CObjectManager* CObjectManager::m_pInstance = NULL;

CObjectManager::CObjectManager(void)
{
	m_vObjectList.clear();
	m_vRenderList.clear();
}


CObjectManager* CObjectManager::Initialize()
{
	if (!m_pInstance)
	{
		m_pInstance = new CObjectManager();
	}

	m_pInstance->InitInstance();

	return m_pInstance;
}

void CObjectManager::InitInstance()
{
	m_vObjectList.clear();
	m_vRenderList.clear();
}

void CObjectManager::Shutdown()
{
	m_vObjectList.clear();
	m_vRenderList.clear();

	DeleteInstance();
}


CObjectManager* CObjectManager::GetInstance()
{
	return m_pInstance;
}

void CObjectManager::DeleteInstance()
{
	delete m_pInstance;
	m_pInstance = NULL;
}

void CObjectManager::Update(float fElapsedTime)
{
	m_vRenderList.clear();

	vector<CBaseObject*>::iterator iter = m_vObjectList.begin();

	while(iter != m_vObjectList.end())
	{
		// TODO: Change this to work faster
// 		if( false == (*iter)->GetIsActive() )
// 		{
// 			//this guy is dead return him to factory.
// 			iter = RemoveObject(iter);
// 		}
// 		else
// 		{
// 			m_vRenderList.push_back((*iter));
// 			iter++;
// 		}

		// TODO: Check to see if the object needs to be drawn
		// if so add the object to the render list

	}

	// Update the AI Objects
}

void CObjectManager::Render()
{
	
}

void CObjectManager::AddObject(CBaseObject* pObject)
{
	//	Check for valid object pointer
	if (pObject == NULL)
	{
		return;
	}

	//	Add object to object list
	m_vObjectList.push_back(pObject);

	// Add object to collision list
	

	// If the object is an enemy send to AI list
}

void CObjectManager::RemoveObject(CBaseObject* pObject)
{
	//	Check for valid object pointer
	if (pObject == NULL)
		return;

	vector<CBaseObject*>::iterator iter = m_vObjectList.begin();

	for (;iter != m_vObjectList.end(); iter++)
	{
		// if this is the object we are looking for.
		if ((*iter) == pObject)
		{
			// Remove the object from the list
			RemoveObject(iter);
			break;
		}
	}
}

vector<CBaseObject*>::iterator CObjectManager::RemoveObject(vector<CBaseObject*>::iterator iter)
{
	return m_vObjectList.erase(iter);
}