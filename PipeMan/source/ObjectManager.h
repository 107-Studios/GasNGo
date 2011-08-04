//////////////////////////////////////////////////////////////////////////
// Filename:  			ObjectManager.h
// Date:      			03/15/2010
// Mod. Date: 			06/22/2010
// Mod. Initials:		BK
// Author:    			Brian Kelsey
// Purpose:   			Handles updates for all objects
//////////////////////////////////////////////////////////////////////////
#ifndef _OBJECTMANAGER_H
#define _OBJECTMANAGER_H
#include "BaseObject.h"

#include <vector>
using std::vector;

class CObjectManager
{
private:
	vector<CBaseObject*> m_vObjectList;
	vector<CBaseObject*> m_vRenderList;
	
	static CObjectManager* m_pInstance;

	//////////////////////////////////////////////////////////////////////////
	// Private constructor, copy constructors and destructor
	// to make this a true singleton class
	//////////////////////////////////////////////////////////////////////////
	CObjectManager(void);
	CObjectManager(const CObjectManager&){}
	CObjectManager& operator=(const CObjectManager&){ return *this; }
	~CObjectManager(void){}

public:
	//////////////////////////////////////////////////////////////////////////
	// Initialize():		Initializes a static instance of the
	//						object manager and returns it
	//
	// Return:				CObjectManager*
	//////////////////////////////////////////////////////////////////////////
	static CObjectManager* Initialize();

	//////////////////////////////////////////////////////////////////////////
	// InitInstance():		Initializes the objects of the static instance
	//						of the object manager
	//
	// Return:				void
	//////////////////////////////////////////////////////////////////////////
	void InitInstance();

	//////////////////////////////////////////////////////////////////////////
	// Shutdown():			Shuts down the object manager.
	//						Clears the list of objects
	//						and cleaning up itself
	//
	// Return:				void
	//////////////////////////////////////////////////////////////////////////
	 void Shutdown();

	//////////////////////////////////////////////////////////////////////////
	// GetInstance():		Returns the static instance of
	//						the object manager
	//
	// Return:				CObjectManager*
	//////////////////////////////////////////////////////////////////////////
	static CObjectManager* GetInstance();

	//////////////////////////////////////////////////////////////////////////
	// DeleteInstance():	Deletes the static instance of
	//						the object manager
	//
	// Return:				None
	//////////////////////////////////////////////////////////////////////////
	static void DeleteInstance();

	//////////////////////////////////////////////////////////////////////////
	// Update():			Responsible for updating every
	//						object in the object list based on time.
	//						Makes calls to AI functions and collision
	//						Also sorts a list of objects to
	//						be sent to the renderer
	//
	// Ins:					fElapsedTime
	//
	// Return:				void
	//////////////////////////////////////////////////////////////////////////
	void Update(float fElapsedTime);

	//////////////////////////////////////////////////////////////////////////
	// Render():			Passes the list of objects to be rendered
	//						to the rendering engine
	//
	// Return:				void
	//////////////////////////////////////////////////////////////////////////
	void Render();

	//////////////////////////////////////////////////////////////////////////
	// AddObject():			Adds the object to the object list
	//
	// Ins:					pObject*
	//
	// Return:				void
	//////////////////////////////////////////////////////////////////////////
	void AddObject(CBaseObject* pObject);

	//////////////////////////////////////////////////////////////////////////
	// RemoveObject():		Removes the object from the object list
	//
	// Ins:					pObject*
	//
	// Return:				void
	//////////////////////////////////////////////////////////////////////////
	void RemoveObject(CBaseObject* pObject);

	//////////////////////////////////////////////////////////////////////////
	// RemoveObject():		Removes the object from the object list
	//
	// Ins:					iter
	//
	// Return:				vector<CBaseObject*>::iterator
	//////////////////////////////////////////////////////////////////////////
	vector<CBaseObject*>::iterator RemoveObject(vector<CBaseObject*>::iterator iter);
};
#endif